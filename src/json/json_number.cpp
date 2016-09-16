#include "json_number.h"
#include "json_json.h"

#include <math.h>

/* Number::Number (const double value)
  : value::value (0),
    _double_value (value),
    _double_valuep (&_double_value),
    _digitp {{ 0, 0 },{ 0, 0 }}
{
}

Number::Number (const char *json)
  : value::value (json),
    _double_value (0),
    _double_valuep (0),
    _digitp {{ 0, 0 },{ 0, 0 }}
{
}

Number::Number (const char *endp, value *parent, size_t charc)
  : value::value (endp, parent, charc),
    _double_value (0),
    _double_valuep (0),
    _digitp {{ 0, 0 },{ 0, 0 }}
{
} */

const char *
Number::parse (const char *json)
{
  char peek = 0;

  if (json == 0)
    throw _readp;

  if (_parent == 0)
    {
      _readp = json;

      // if (_charc == 0)  /// 1. constructor called with null or zero length string
      //  _endp = _readp + strlen (json);

      _look_ahead ();
    }
  else
     _readp = json;

  if (*_readp == 0)
    throw _readp;

  _digitp[DOUBLE][START] = _readp;

  if (*_readp == '-')
    _readp++;

  if (*_readp == 48)    /// Expect 0\0 | 0.digits
    {
      if (*(_readp + 1) == 0) /// Null terminator, found single zero
          return _readp + 1;

      if (*(_readp + 1) == '.') /// Possible float value
        {
          _readp++;
          return _frag ();
        }

      throw _readp; /// Anything else is no good
    }

  if ((peek = _digits ()) == '.')
    return _frag ();

  if (peek == 'e' || peek == 'E')
    {
      _digitp[DOUBLE][END] = _readp;
      return _exp ();
    }

  if (peek < 0)
    throw _readp;

  _digitp[DOUBLE][END] = _readp;

  return _readp;
}

int
Number::_digits ()
{
  const char * const startp = _readp;

  while (*_readp != 0 && isdigit (*_readp))
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

  _digitp[DOUBLE][END] = _readp;

  return peek == 'e' || peek == 'E' ? _exp () : _readp;
}

const char *
Number::_exp ()
{
  _digitp[EXP][START] = ++_readp; /// Skip 'e|E'

  if (*(_readp) == '+' || *(_readp) == '-')
    _readp++;

  if (_digits () < 0) /// No digits found
    throw _readp;

  _digitp[EXP][END] = _readp;

  return _readp;
}

double
Number::_calculate (const char * const digitp[2][2])
{
  if (digitp[DOUBLE][START] == 0 || digitp[DOUBLE][END] == 0)
    return 0;

  _double_valuep = & _double_value;

  _double_value = _atof (digitp[DOUBLE]);

  if (digitp[EXP][START] == 0 || digitp[EXP][END] == 0)
    return _double_value;

  long long exp = _atoll (digitp[EXP]);

  if (exp == 0)
    return _double_value;

  return _double_value = (exp < 0)
        ? _double_value / pow (10, -1 * exp)
        : _double_value * pow (10, exp);
}

double
Number::_atof (const char * const digitp[2]) const
{
  return atof (std::string (digitp[0], digitp[1]).c_str ());
}

long long
Number::_atoll (const char * const digitp[2]) const
{
  return atoll (std::string (digitp[0], digitp[1]).c_str ());
}

Value &
Number::_assign (Number &nv)
{
  if (_parent)
    {
      _parent->assign (this, &nv);
      return *_parent;
    }

  _digitp[DOUBLE][START]  = nv._digitp[DOUBLE][START];
  _digitp[DOUBLE][END]    = nv._digitp[DOUBLE][END];
  _digitp[EXP][START]     = nv._digitp[EXP][START];
  _digitp[EXP][END]       = nv._digitp[EXP][END];

  if (nv._double_valuep)
    {
      _double_value = nv._double_value;
      _double_valuep = &_double_value;
    }
  else
    _double_value = _calculate (_digitp);

  return *this;
}
