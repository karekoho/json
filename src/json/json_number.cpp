#include "json_number.h"
#include "json_json.h"

using namespace Format;

number::number ()
  : leaf (),
    _double_value (0),
    _double_valuep (&_double_value),
    _digitp {{ 0, 0 }, { 0, 0 }}
{
}

number::number (const double value)
  : leaf (),
    _double_value (value),
    _double_valuep (&_double_value),
    _digitp {{ 0, 0 }, { 0, 0 }}
{
}

number::number (const wchar_t *json)
  : leaf (json),
    _double_value (0),
    _double_valuep (0),
    _digitp {{ 0, 0 }, { 0, 0 }}
{
  if (json == 0)
    throw json_error (UNEX_END);

  (void) parse (json);
}

number::number (json *parent)
  : leaf (parent),
    _double_value (0),
    _double_valuep (0),
    _digitp {{ 0, 0 }, { 0, 0 }}
{
}

number::number (const number &other)
 : leaf (other),
   _double_value (0),
   _double_valuep (0),
   _digitp {{ 0, 0 }, { 0, 0 }}
{
  (void) clone (other);
}

number::number (const Value *ov, const number &nv)
: leaf (ov, nv),
  _double_value (0),
  _double_valuep (0),
  _digitp {{ 0, 0 }, { 0, 0 }}
{
  (void) clone (nv);
}

const wchar_t *
number::parse (const wchar_t *json)
{
  wchar_t peek = 0;

  if (json == 0)
    throw json_error (UNEX_END);

  _readp = json;

  if (_parent == 0)
    {
      _look_ahead ();
    }
  else
    _startp = json;

  if (*_readp == 0)
    throw _readp;

  if (_double_valuep)
    _clear ();

  _digitp[DOUBLE][START] = _readp;

  if (*_readp == '-')
    _readp++;

  if (*_readp == 48)    // Expect 0\0 | 0.digits
    {
      if (*(_readp + 1) == 0) // Null terminator, found single zero
          return _readp + 1;

      if (*(_readp + 1) == '.') // Possible float value
        {
          _readp++;
          return _frag ();
        }

      // throw _readp; // Anything else is no good
      throw json_syntax_error (UNEX_TOKEN, *_readp); // Anything else is no good
    }

  if ((peek = _digits ()) == '.')
    return _frag ();

  if (peek == 'e' || peek == 'E')
    {
      _digitp[DOUBLE][END] = _readp;
      return _exp ();
    }

  if (peek < 0)
    // throw _readp;
    throw json_syntax_error (UNEX_TOKEN, *_readp);

  _digitp[DOUBLE][END] = _readp;

  return _readp;
}

int
number::_digits () noexcept
{
  const wchar_t * const startp = _readp;

  while (*_readp != 0 && isdigit (*_readp))
    _readp++;

  return _readp > startp ? *_readp : -1;
}

const wchar_t *
number::_frag ()
{
  _readp++; // Skip '.'

  int peek = _digits ();

  if (peek < 0) // No digits found
    throw json_syntax_error (UNEX_TOKEN, *_readp);

  _digitp[DOUBLE][END] = _readp;

  // TODO: assign struct _value.is_double = true
  // TODO: assign struct _value.double_value

  return peek == 'e' || peek == 'E' ? _exp () : _readp;
}

const wchar_t *
number::_exp ()
{
  _digitp[EXP][START] = ++_readp; // Skip 'e|E'

  if (*(_readp) == '+' || *(_readp) == '-')
    _readp++;

  if (_digits () < 0) // No digits found
    throw json_syntax_error (UNEX_TOKEN, *_readp);

  _digitp[EXP][END] = _readp;

  return _readp;
}

double
number::_calculate (const wchar_t * const digitp[2][2]) const
{
  _double_valuep = & _double_value;

  if (digitp[DOUBLE][START] == 0 || digitp[DOUBLE][END] == 0)
    {
      return (_double_value = 0);
    }

  _double_value =  _atof (digitp[DOUBLE]);

  if (digitp[EXP][START] == 0 || digitp[EXP][END] == 0)
    return _double_value;

  long long exp =  _atoll (digitp[EXP]);

  if (exp == 0)
    return _double_value;

  return _double_value = (exp < 0)
        ? _double_value / pow (10, -1 * exp)
        : _double_value * pow (10, exp);
}

void
number::_clear ()
{
  _double_value   = 0;
  _double_valuep  = 0;

  _digitp[DOUBLE][START]  = 0;
  _digitp[DOUBLE][END]    = 0;
  _digitp[EXP][START]     = 0;
  _digitp[EXP][END]       = 0;
}

Value *
number::clone (const Value &other)
{
  const number & nv = dynamic_cast<const number &>(other);

  if (nv._double_valuep)
    {
      _double_value = nv._double_value;
      _double_valuep = &_double_value;
    }
  else
    {
      _digitp[DOUBLE][START]  = nv._digitp[DOUBLE][START];
      _digitp[DOUBLE][END]    = nv._digitp[DOUBLE][END];
      _digitp[EXP][START]     = nv._digitp[EXP][START];
      _digitp[EXP][END]       = nv._digitp[EXP][END];
    }

  return this;
}

size_t
number::strLength () const noexcept
{
 (void) get ();

  if (_double_str.empty ())
    _double_str = std::to_wstring (_double_value);

  return _double_str.length ();
}

const wchar_t *
number::strValue (wchar_t *) const
{
  (void) get ();

  if (_double_str.empty ())
    _double_str = std::to_wstring (_double_value);

  return _double_str.c_str ();
}
