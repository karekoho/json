#include "json_value.h"
#include "json_json.h"
#include "json_string.h"
#include "json_number.h"
#include "json_boolean.h"
#include "json_null.h"

#include <stdlib.h>

const struct format::json::value::literal_value format::json::value::__ltr_value[3] = {
  { L"true", 4, format::json::value::_literal::true_value },
  { L"false", 5, format::json::value::_literal::false_value },
  { L"null", 4, format::json::value::_literal::null_value }
};

format::json::value::value ()
    : _readp (nullptr),
      _parent (nullptr),
      _key (nullptr),
      _index (0),
      _value ()
{ }

format::json::value::value (const wchar_t * const)
    : _readp (nullptr),
      _parent (nullptr),
      _key (nullptr),
      _index (0),
      _value (nullptr)
{ }

format::json::value::value (long double ld)
  : _readp (nullptr),
    _parent (nullptr),
    _key (nullptr),
    _index (0),
    _value (ld)
{ }

format::json::value::value (bool boolean)
  : _readp (nullptr),
    _parent (nullptr),
    _key (nullptr),
    _index (0),
    _value (boolean)
{ }

format::json::value::value (json *parent)
    : _readp (nullptr),
      _parent (parent),
      _key (nullptr),
      _index (0),
      _value ()
{ }

format::json::value::value(format::json::json *parent, size_t)
  : _readp (nullptr),
    _parent (parent),
    _key (nullptr),
    _index (0),
    _value (nullptr)
{ }

format::json::value::value(format::json::json *parent, long double ld)
  : _readp (nullptr),
    _parent (parent),
    _key (nullptr),
    _index (0),
    _value (ld)
{ }

format::json::value::value(format::json::json *parent, bool boolean)
  : _readp (nullptr),
    _parent (parent),
    _key (nullptr),
    _index (0),
    _value (boolean)
{ }

format::json::value::value (const value &other)
  : _readp (other._readp),
    _parent (nullptr),
    _key (other._key ? new wchar_t [wcslen (other._key) + 1] () : nullptr),
    _index (other._index),
    _value (other._value)
{ }

format::json::value::
~value ()
{
  delete[] _key;
}

long long int
format::json::value::_string (wchar_t &endc) const noexcept
{
  const wchar_t * const startp = _readp;

  if (*startp != _sc::double_quote)
    {
      endc = *startp;
      return 0;
    }

  const wchar_t * readp = _readp + 1;

  while (*readp > 31 && *readp != _sc::double_quote)
    readp++;

  endc = *readp;

  return *readp == _sc::double_quote
    ? (readp - startp) + 1
    : -1 * (readp - startp);
}

format::json::value::_literal
format::json::value::_is_literal (const int _try) const noexcept
{
  const wchar_t *readp = _readp;

  size_t idx = 0;

  while (*(readp + idx) != 0
         && idx < __ltr_value[_try].len
         && *(readp + idx) == *(__ltr_value[_try].str_value + idx))
    idx++;

  if (idx == __ltr_value[_try].len)
    return __ltr_value[_try].ltr_value;

  return _try < 2 ? _is_literal (_try + 1) :  value::_literal::no_literal;
}

format::json::value &
format::json::value::_assign (const undefined &) noexcept
{  
  return _parent ? __call__erase (_parent, *this) : *this;
}

format::json::value &
format::json::value::_assign (const value &nv)
{
  if (_parent == nullptr)
    throw json_error (BAD_ASSIGNMENT);

  return __call__assign (_parent, this, nv.clone ());
}

format::json::value &
format::json::value::_assign (value *nv)
{
  if (_parent == nullptr)
    throw json_error (BAD_ASSIGNMENT);

  return __call__assign (_parent, this, nv);
}

format::json::value &
format::json::value::operator =(bool b)
{
  return _assign (new boolean (b));
}

format::json::value &
format::json::value::operator =(int i)
{
  return _assign (new number (i));
}

format::json::value &
format::json::value::operator =(long long l)
{
  return _assign (new number (static_cast<long long>(l)));
}

format::json::value &format::json::value::operator =(float f)
{
  return _assign (new number (static_cast<float>(f)));
}

format::json::value &
format::json::value::operator =(long double d)
{
  return _assign (new number (d));
}

format::json::value &
format::json::value::operator =(std::nullptr_t)
{
  return _assign (new null ());
}
