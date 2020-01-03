#include "json_number.h"
#include "json_json.h"
#include <iostream>

format::number::number ()
  : leaf (),
    _double_value (0),
    _double_valuep (& _double_value),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _is_double (false)
{}

format::number::number (long l)
  : leaf (),
    _double_value (l),
    _double_valuep (& _double_value),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _is_double (false)
{}

format::number::number (double d)
  : leaf (),
    _double_value (d),
    _double_valuep (& _double_value),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _is_double (true)
{}

format::number::number (const wchar_t *json)
  : leaf (json),
    _double_value (0),
    _double_valuep (nullptr),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _is_double (false)
{
  if (json == nullptr)
    throw json_error (UNEX_END);

  (void) _parse (json);
}

format::number::number (json *parent)
  : leaf (parent),
    _double_value (0),
    _double_valuep (nullptr),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
   _is_double (false)
{}

format::number::number (const number &other)
 : leaf (other),
   _double_value (0),
   _double_valuep (nullptr),
   _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
   _is_double (false)
{
  (void) _clone (other);
}

const wchar_t *
format::number::_parse (const wchar_t *json)
{
  wchar_t peek = 0;

  if (json == nullptr)
    throw json_error (UNEX_END);

  _readp = json;

  if (_parent == nullptr)
    _look_ahead ();

  if (*_readp == 0)
    throw json_syntax_error (UNEX_TOKEN, _readp, 1);

  if (_double_valuep)
    _clear ();

  _digitp[DOUBLE][START] = _readp;

  if (*_readp == '-')
    _readp++;

  if (*_readp == 48)    // Expect 0\0 | 0.digits
    {
      if (*(_readp + 1) == '.') // Possible float value
        {
          _readp++;
          return _frag ();
        }

      return (_digitp[DOUBLE][END] = ++_readp);  // Found single zero: 0[\0NaN]
    }

  if ((peek = _digits ()) == '.')
    return _frag ();

  if (peek == 'e' || peek == 'E')
    {
      _digitp[DOUBLE][END] = _readp;
      return _exp ();
    }

  if (peek < 0)
    throw json_syntax_error (UNEX_TOKEN, _readp, 1);

  _digitp[DOUBLE][END] = _readp;

  return _readp;
}

int
format::number::_digits () noexcept
{
  const wchar_t * const startp = _readp;

  while (*_readp != 0 && isdigit (*_readp))
    _readp++;

  return _readp > startp ? *_readp : -1;
}

const wchar_t *
format::number::_frag ()
{
  _readp++; // Skip '.'

  int peek = _digits ();

  if (peek < 0) // No digits found
    throw json_syntax_error (UNEX_TOKEN, _readp, 1);

  _digitp[DOUBLE][END] = _readp;

  _is_double = true;

  return peek == 'e' || peek == 'E' ? _exp () : _readp;
}

const wchar_t *
format::number::_exp ()
{
  _digitp[EXP][START] = ++_readp; // Skip 'e|E'

  if (*(_readp) == '+' || *(_readp) == '-')
    _readp++;

  if (_digits () < 0) // No digits found
    throw json_syntax_error (UNEX_TOKEN, _readp, 1);

  _digitp[EXP][END] = _readp;

  return _readp;
}

double
format::number::_calculate (const wchar_t * const digitp[2][2]) const
{
  _double_valuep = & _double_value;

  if (digitp[DOUBLE][START] == nullptr || digitp[DOUBLE][END] == nullptr)
    return (_double_value = 0);

  _double_value = _atof (digitp[DOUBLE]);

  if (digitp[EXP][START] == nullptr || digitp[EXP][END] == nullptr)
    return _double_value;

  long long exp = _atoll (digitp[EXP]);

  if (exp == 0)
    return _double_value;

  return _double_value = (exp < 0)
        ? _double_value / pow (10, -1 * exp)
        : _double_value * pow (10, exp);
}

void
format::number::_clear ()
{
  _double_value   = 0;
  _double_valuep  = nullptr;
  (void) __clear_strp ();
}

format::value *
format::number::_clone (const value &other)
{
  const number & nv = dynamic_cast<const number &> (other);

  _is_double = nv._is_double;

  if (nv._double_valuep)  // nv._calculate () is called or number is assigned with long|double
    {
      _double_value = nv._double_value;
      _double_valuep = &_double_value;
    }
  else  // nv._calculate () not yet called
    {
      _digitp[DOUBLE][START]  = nv._digitp[DOUBLE][START];
      _digitp[DOUBLE][END]    = nv._digitp[DOUBLE][END];
      _digitp[EXP][START]     = nv._digitp[EXP][START];
      _digitp[EXP][END]       = nv._digitp[EXP][END];
    }

  return this;
}

size_t
format::number::_str_length () const noexcept
{
 (void) get ();
 __to_string ();

  return _double_str.length ();
}

const wchar_t *
format::number::_to_string (wchar_t *) const
{
  (void) get ();
  __to_string ();

  return _double_str.c_str ();
}
