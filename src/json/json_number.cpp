#include "json_number.h"
#include "json_json.h"
#include <iostream>

format::json::number::number ()
  : leaf (),
    _double_value (0),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _is_floating_point (false)
{
  _primitive.double_value = 0;
}

format::json::number::number (int i)
  : leaf (),
    _double_value (i),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _is_floating_point (false)
{
   _primitive.double_value = i;
}

format::json::number::number (long long ll)
  : leaf (),
    _double_value (ll),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _is_floating_point (false)
{
  _primitive.double_value = ll;
}

format::json::number::number (float f)
  : leaf (),
    _double_value (static_cast<long double> (f)),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _is_floating_point (true)
{
  _primitive.double_value = static_cast<long double> (f);
}

format::json::number::number (long double d)
  : leaf (),
    _double_value (d),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _is_floating_point (true)
{
  _primitive.double_value = d;
}

format::json::number::number (const wchar_t * const json)
  : leaf (json),
    _double_value (0),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _is_floating_point (false)
{
  if (json == nullptr)
    throw json_error (UNEXPECTED_END_OF_INPUT);

  (void) _parse (json);
}

format::json::number::number (json *parent)
  : leaf (parent),
    _double_value (0),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
   _is_floating_point (false)
{
  _primitive.double_value = 0;
}

format::json::number::number (const number &other)
 : leaf (other),
   _double_value (0),
   _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
   _is_floating_point (false)
{
  // set _double_value,
  // set _is_floating_point
  (void) _clone (other);
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

  if (_digitp[DOUBLE][START])
    _clear ();

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
  _double_value = _calculate (_digitp); // Integer value

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

  if (peek == 'e' || peek == 'E') {
      return _exp ();
    }

  _double_value = _calculate (_digitp);
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

  _double_value = _calculate (_digitp);
  return _readp;
}

long
double format::json::number::_calculate (const wchar_t * const digitp[2][2])
{
  // Value is zero
  if (digitp[DOUBLE][START] == nullptr || digitp[DOUBLE][END] == nullptr)
    return (_double_value = 0);

  _double_value = _atof (digitp[DOUBLE]);

  // No exponent
  if (digitp[EXP][START] == nullptr || digitp[EXP][END] == nullptr)
    return _double_value;

  long long exp = _atoll (digitp[EXP]);

  // No exponent
  if (exp == 0)
    return _double_value;

  return exp < 0
          ? _double_value / std::powl (10, -1 * exp)
          : _double_value * std::powl (10, exp);
}

void
format::json::number::_clear ()
{
  _double_value   = 0;
  (void) __clear_strp ();
}

format::json::value *
format::json::number::_clone (const value &other)
{
  const number & nv = static_cast<const number &> (other);

  _is_floating_point = nv._is_floating_point;
  _double_value = nv._double_value;

  return this;
}

size_t
format::json::number::_str_length () const noexcept
{
 (void) get ();
 __to_string ();

  return _double_str.length ();
}

const wchar_t *
format::json::number::_to_string (wchar_t *) const
{
  (void) get ();
  __to_string ();

  return _double_str.c_str ();
}
