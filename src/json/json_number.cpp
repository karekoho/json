#include "json_number.h"
#include <math.h>

const char *
Number::parse (const char *json)
{
  char peek = 0;
  if (json == 0)
    // throw json::error ("error: null string given");
    throw _readp;

  if (_parent == 0)
    {
      _readp = json;

      if (_charc == 0)  /// 1. constructor called with null or zero length string
        _endp = _readp + strlen (json);

      _look_ahead ();
    }
  else
     _readp = json;

  if (_readp == _endp)
    throw _readp;

  _digitp[0][0] = _readp;

  if (*_readp == '-')
    _readp++;

  if (*_readp == 48)    /// Expect 0\0 | 0.digits
    {
      if (*(_readp + 1) == 0)
          return _readp + 1;

      if (*(_readp + 1) == '.')
        {
          _readp++;
          return _frag ();
        }

      throw _readp;
    }

  peek = _digits ();

  if (peek == '.')
    return _frag ();

  if (peek == 'e' || peek == 'E')
    return _exp ();

  if (peek < 0)
    throw _readp;

  _digitp[0][1] = _readp;

  return _readp;
}

int
Number::_digits ()
{
  const char * const startp = _readp;

  while (_readp < _endp && isdigit (*_readp))
    _readp++;

  return _readp > startp ? *_readp : -1;
}

const char *
Number::_frag ()
{
  _readp++; /// Skip '.'

  int peek = _digits ();

  if (peek < 0) /// No digits found
    throw _readp;

  _digitp[0][1] = _readp;

  return peek == 'e' || peek == 'E' ? _exp () : _readp;
}

const char *
Number::_exp ()
{
  _readp++; /// Skip 'e|E'

  _digitp[1][0] =_readp;

  if (*(_readp) == '+' || *(_readp) == '-') _readp++;

  if (_digits () < 0) /// No digits found
    throw _readp;

  _digitp[1][1] = _readp;

  return _readp;
}

double
Number::_calculate (const char * const digitp[2][2]) const
{
  if (digitp[0][0] == 0 || digitp[0][1] == 0)
    return 0;

  _double_valuep = & _double_value;

  _double_value = _atof (digitp[0]);

  if (digitp[1][0] == 0 || digitp[1][1] == 0)
    return _double_value;

  long long exp = _atoll (digitp[1]);

  if (exp == 0)
    return _double_value;

  return _double_value = (exp < 0)
        ? _double_value / pow (10, -1 * exp)
        : _double_value * pow (10, exp);
}

double
Number::_atof (const char * const digitp[2]) const
{
  std::string s (digitp[0], digitp[1]);
  return atof (s.c_str ());
}

long long
Number::_atoll (const char * const digitp[2]) const
{
  std::string s (digitp[0], digitp[1]);
  return atoll (s.c_str ());
}
