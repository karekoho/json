#include "json_number.h"
#include "json_json.h"
#include <iostream>

format::json::number::number ()
  : leaf (static_cast<long double> (0), 0),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _is_floating_point (false)
{
  __to_string ();
}

format::json::number::number (int i)
  : leaf (static_cast<long double> (i), 0), // do leaf ((int) long double) --> value (int) long double) to activate primitive value
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _is_floating_point (false)
{
   __to_string ();
}

format::json::number::number (long long ll)
  : leaf (static_cast<long double> (ll), 0),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _is_floating_point (false)
{
  __to_string ();
}

format::json::number::number (float f)
  : leaf (static_cast<long double> (f), 0),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _is_floating_point (true)
{
  __to_string ();
}

format::json::number::number (long double ld)
  : leaf (ld, 0),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _is_floating_point (true)
{
  __to_string ();
}

format::json::number::number (const wchar_t * const json)
  : leaf (json),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _is_floating_point (false)
{
  if (json == nullptr)
    throw json_error (UNEXPECTED_END_OF_INPUT);

  (void) _parse (json);
}

format::json::number::number (json *parent)
  : leaf (parent, static_cast<long double> (0)),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
   _is_floating_point (false)
{
  __to_string ();
}

format::json::number::number (const number &other)
 : leaf (other),
   _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
   _is_floating_point (other._is_floating_point)
{
  __to_string ();
}

const wchar_t *
format::json::number::_parse (const wchar_t * const json)
{
  wchar_t peek = 0;

  if (json == nullptr)
    throw json_error (UNEXPECTED_END_OF_INPUT);

  _readp = json;

  if (_parent == nullptr)
    _look_ahead ();

  if (*_readp == 0)
    throw json_syntax_error (UNEXPECTED_TOKEN, _readp, 1);

  _digitp[DOUBLE][START] = _readp;

  if (*_readp == '-') // Negative value
    _readp++;

  if (*_readp == 48)    // Expect 0\0 | 0.digits
    {
      if (*(_readp + 1) == '.') // Possible float value
        {
          _readp++;
          return _frag (); // Look for decimals
        }

      return (_digitp[DOUBLE][END] = ++_readp);  // Found single zero: 0[\0NaN]
    }

  if ((peek = _digits ()) == '.')
    return _frag (); // Look for decimals

  if (peek == 'e' || peek == 'E')
    {
      _digitp[DOUBLE][END] = _readp;
      return _exp (); // Look for exponent
    }

  if (peek < 0)
    throw json_syntax_error (UNEXPECTED_TOKEN, _readp, 1);

  _digitp[DOUBLE][END] = _readp;
  _value.long_double = _calculate (_digitp); // Integer value
  __to_string ();

  return _readp;
}

int
format::json::number::_digits () noexcept
{
  const wchar_t * const startp = _readp;

  while (*_readp != 0 && isdigit (*_readp))
    _readp++;

  return _readp > startp ? *_readp : -1;
}

const wchar_t *
format::json::number::_frag ()
{
  _readp++; // Skip '.'

  int peek = _digits ();

  if (peek < 0) // No digits found
    throw json_syntax_error (UNEXPECTED_TOKEN, _readp, 1);

  _digitp[DOUBLE][END] = _readp;

  _is_floating_point = true;

  if (peek == 'e' || peek == 'E')
    return _exp ();

  _value.long_double = _calculate (_digitp);
  __to_string ();

  return _readp;
}

const wchar_t *
format::json::number::_exp ()
{
  _digitp[EXP][START] = ++_readp; // Skip 'e|E'

  if (*(_readp) == '+' || *(_readp) == '-')
    _readp++;

  if (_digits () < 0) // No digits found
    throw json_syntax_error (UNEXPECTED_TOKEN, _readp, 1);

  _digitp[EXP][END] = _readp;

  _value.long_double = _calculate (_digitp);
  __to_string ();

  return _readp;
}

long
double format::json::number::_calculate (const wchar_t * const digitp[2][2])
{
  // Value is zero
  if (digitp[DOUBLE][START] == nullptr || digitp[DOUBLE][END] == nullptr)
    return (_value.long_double = 0);

  _value.long_double = _atof (digitp[DOUBLE]);

  // No exponent
  if (digitp[EXP][START] == nullptr || digitp[EXP][END] == nullptr)
    return _value.long_double;

  long long exp = _atoll (digitp[EXP]);

  // No exponent
  if (exp == 0)
    return _value.long_double;

  return exp < 0
          ? _value.long_double / std::powl (10, -1 * exp)
          : _value.long_double * std::powl (10, exp);
}
