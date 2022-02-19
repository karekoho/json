#include "json_number.h"
#include "json_json.h"
#include <iostream>
#include <cfloat>

format::json::number::number ()
  : leaf (static_cast<long double> (0), 0),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _long_double_str (nullptr),
    _long_double_str_length (1), // _to_string returns "0"
    _is_floating_point (false)
{
//  wchar_t *str = new wchar_t[2] ();
//  *str = L'0';
//  _long_double_str = str;
}

format::json::number::number (int i)
  : leaf (static_cast<long double> (i), 0),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _long_double_str (nullptr),
    _long_double_str_length (__to_string_ld (static_cast<long double> (i))),
    _is_floating_point (false)
{ }

format::json::number::number (long long ll)
  : leaf (static_cast<long double> (ll), 0),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _long_double_str (nullptr),
    _long_double_str_length (__to_string_ld (static_cast<long double> (ll))),
    _is_floating_point (false)
{ }

format::json::number::number (float f)
  : leaf (static_cast<long double> (f), 0),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _long_double_str (nullptr),
    _long_double_str_length (__to_string_ld (static_cast<long double> (f))),
    _is_floating_point (true)
{ }

format::json::number::number (long double ld)
  : leaf (ld, 0),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _long_double_str (nullptr),
    _long_double_str_length (__to_string_ld (static_cast<long double> (ld))),
    _is_floating_point (true)
{ }

format::json::number::number (const wchar_t * const json_text)
  : leaf (json_text),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _long_double_str (nullptr),
    _long_double_str_length (0),
    _is_floating_point (false)
{
  if (json_text == nullptr)
    throw json_error (UNEXPECTED_END_OF_INPUT);

  (void) _parse (json_text);
}

format::json::number::number (json *parent)
  : leaf (parent, static_cast<long double> (0)),
    _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
    _long_double_str (nullptr),
    _long_double_str_length (0),
    _is_floating_point (false)
{ }

format::json::number::number (const number &other)
 : leaf (other),
   _digitp {{ nullptr, nullptr }, { nullptr, nullptr }},
   _long_double_str (other.stringify ()),
   _long_double_str_length (other._str_length ()),
   _is_floating_point (other._is_floating_point)
{ }

format::json::number::~number ()
{
  delete [] _long_double_str;
}

const wchar_t *
format::json::number::_parse (const wchar_t * const json_text)
{
  wchar_t peek = 0;

  if (json_text == nullptr)
    throw json_error (UNEXPECTED_END_OF_INPUT);

  _readp = json_text;

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

      //return (_digitp[DOUBLE][END] = ++_readp);  // Found single zero: 0[\0NaN]

      _digitp[DOUBLE][END] = ++_readp; // Found single zero: 0[\0NaN]

      long long ll = static_cast<long long> (_calculate (_digitp));
      _long_double_str_length = __to_string_ld (ll);
      _value.long_double = ll;

      return _readp;
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
  // _value.long_double = _calculate (_digitp); // Integer value
  //__to_string ();

  long long ll = static_cast<long long> (_calculate (_digitp)); // Integer value
  _long_double_str_length = __to_string_ld (ll);
  _value.long_double = ll;

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

  //_value.long_double = _calculate (_digitp);
  //__to_string ();

  long double ld = _calculate (_digitp);
  _long_double_str_length = __to_string_ld (ld);
  _value.long_double = ld;

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

  //_value.long_double = _calculate (_digitp);
  //__to_string ();

  long double ld = _calculate (_digitp);
  _long_double_str_length = __to_string_ld (ld);
  _value.long_double = ld;

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
          ? _value.long_double / powl (10, -1 * exp) // powl is not std in GNU
          : _value.long_double * powl (10, exp);
}

size_t
format::json::number::__to_string_ll (long long ll)
{
  try
    {
      unsigned long buf_len = __integral_length (ll) + 1;
      long long charc = 0;

      wchar_t *buf = new wchar_t[buf_len] ();
      _long_double_str = buf;

      if ((charc = std::swprintf (buf, static_cast<size_t> (buf_len), L"%lld", ll)) < 0)
        throw json_error (std::strerror (errno));

      return static_cast<size_t> (charc);
    }
  catch (const std::bad_alloc &e)
    {
      throw new json_error (e.what ());
    }
}

size_t
format::json::number::__to_string_ld (long double ld)
{
  try
    {
      const size_t dec_exp_len = LDBL_DIG + LDBL_MAX_EXP + 2;

      unsigned long buf_len = dec_exp_len + 1;
      long long charc = 0;

      wchar_t *buf = new wchar_t[buf_len] ();
      _long_double_str = buf;

      const size_t format_len = 4 + dec_exp_len + 1;
      wchar_t s[format_len];
      wchar_t *format = static_cast<wchar_t *> (memset (s, 0, format_len));

      if ((charc = std::swprintf (format, static_cast<size_t> (format_len), L"%%.%uLg", LDBL_DIG)) < 0
          || (charc = std::swprintf (buf, static_cast<size_t> (buf_len), format, ld)) < 0)
        throw json_error (std::strerror (errno));

      return static_cast<size_t> (charc);
    }
  catch (const std::bad_alloc &e)
    {
      throw new json_error (e.what ());
    }
}

size_t
format::json::number::__integral_length (long double ld)
{
  if (ld < 0)
    return static_cast<size_t> (log10 (ld * -1)) + 2;

  else if (ld > 0)
    return static_cast<size_t> (log10 (ld)) + 1;

  // zero
  return 1;
}
