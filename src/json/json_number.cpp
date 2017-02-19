#include "json_number.h"
#include "json_json.h"
using namespace Format;

Number::Number ()
  : Leaf (),
    _double_value (0),
    _double_valuep (&_double_value),
    _digitp {{ 0, 0 }, { 0, 0 }}
{
}

Number::Number (const double value)
  : Leaf (),
    _double_value (value),
    _double_valuep (&_double_value),
    _digitp {{ 0, 0 }, { 0, 0 }}
{
}

Number::Number (const wchar_t *json)
  : Leaf (json),
    _double_value (0),
    _double_valuep (0),
    _digitp {{ 0, 0 }, { 0, 0 }}
{
  if (json == 0)
    throw JSON_Error (UNEX_END);

  (void) parse (json);
}

Number::Number (json *parent)
  : Leaf (parent),
    _double_value (0),
    _double_valuep (0),
    _digitp {{ 0, 0 }, { 0, 0 }}
{
}

Number::Number (const Number &other)
 : Leaf (other),
   _double_value (0),
   _double_valuep (0),
   _digitp {{ 0, 0 }, { 0, 0 }}
{
  (void) clone (other);
}

Number::Number (const Value *ov, const Number &nv)
: Leaf (ov, nv),
  _double_value (0),
  _double_valuep (0),
  _digitp {{ 0, 0 }, { 0, 0 }}
{
  (void) clone (nv);
}

const wchar_t *
Number::parse (const wchar_t *json)
{
  wchar_t peek = 0;

  if (json == 0)
    throw JSON_Error (UNEX_END);

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
      throw JSON_Syntax_Error (UNEX_TOKEN, *_readp); // Anything else is no good
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
    throw JSON_Syntax_Error (UNEX_TOKEN, *_readp);

  _digitp[DOUBLE][END] = _readp;

  return _readp;
}

int
Number::_digits () noexcept
{
  const wchar_t * const startp = _readp;

  while (*_readp != 0 && isdigit (*_readp))
    _readp++;

  return _readp > startp ? *_readp : -1;
}

const wchar_t *
Number::_frag ()
{
  _readp++; // Skip '.'

  int peek = _digits ();

  if (peek < 0) // No digits found
    throw JSON_Syntax_Error (UNEX_TOKEN, *_readp);

  _digitp[DOUBLE][END] = _readp;

  // TODO: assign struct _value.is_double = true
  // TODO: assign struct _value.double_value

  return peek == 'e' || peek == 'E' ? _exp () : _readp;
}

const wchar_t *
Number::_exp ()
{
  _digitp[EXP][START] = ++_readp; // Skip 'e|E'

  if (*(_readp) == '+' || *(_readp) == '-')
    _readp++;

  if (_digits () < 0) // No digits found
    throw JSON_Syntax_Error (UNEX_TOKEN, *_readp);

  _digitp[EXP][END] = _readp;

  return _readp;
}

double
Number::_calculate (const wchar_t * const digitp[2][2]) const
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
Number::_clear ()
{
  _double_value   = 0;
  _double_valuep  = 0;

  _digitp[DOUBLE][START]  = 0;
  _digitp[DOUBLE][END]    = 0;
  _digitp[EXP][START]     = 0;
  _digitp[EXP][END]       = 0;
}

Value *
Number::clone (const Value &other)
{
  const Number & nv = dynamic_cast<const Number &>(other);

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
Number::strLength () const noexcept
{
 (void) value ();

  if (_double_str.empty ())
    _double_str = std::to_wstring (_double_value);

  return _double_str.length ();
}

const wchar_t *
Number::strValue (wchar_t *) const
{
  (void) value ();

  if (_double_str.empty ())
    _double_str = std::to_wstring (_double_value);

  return _double_str.c_str ();
}
