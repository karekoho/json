#include "json_value.h"
#include "json_json.h"
#include "json_string.h"
#include "json_number.h"
#include "json_boolean.h"
#include "json_null.h"

#include <stdlib.h>

const struct format::value::literal_value format::value::__ltr_value[3] = {
  { L"true", 4, format::value::_literal::true_value },
  { L"false", 5, format::value::_literal::false_value },
  { L"null", 4, format::value::_literal::null_value }
};

format::value::value ()
    : _readp (0),
      _parent (0),
      _key (0),
      _index (0)
{}

format::value::value (const wchar_t *)
    : _readp (0),
      _parent (0),
      _key (0),
      _index (0)
{}

format::value::value (json *parent)
    : _readp (0),
      _parent (parent),
      _key (0),
      _index (0)
{}

format::value::value (const value &other)
  : _readp (other._readp),
    _parent (0),
    _key (other._key ? new wchar_t [wcslen (other._key) + 1] () : 0),
    _index (other._index)    
{}

format::value::
~value ()
{
  delete[] _key;
}

long int
format::value::_string (wchar_t &endc) const noexcept
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

format::value::_literal
format::value::_is_literal (const int _try) const noexcept
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

format::value &
format::value::_assign (const undefined &) noexcept
{  
  return _parent ? __call__erase (_parent, *this) : *this;
}

format::value &
format::value::_assign (const value &nv)
{
  if (_parent == 0)
    throw json_error (BAD_ASSIGN);

  return __call__assign (_parent, this, nv.clone ());
}

format::value &
format::value::_assign (value *nv)
{
  if (_parent == 0)
    throw json_error (BAD_ASSIGN);

  return __call__assign (_parent, this, nv);
}

format::value &
format::value::operator =(bool b)
{
  return _assign (new boolean (b));
}

format::value &
format::value::operator =(const wchar_t *json_text)
{
  return _assign (new json (json_text));
}

format::value &
format::value::operator =(long l)
{
  return _assign (new number ((long) l));
}

format::value &
format::value::operator =(double d)
{
  return _assign (new number (d));
}

format::value &
format::value::operator =(std::nullptr_t)
{
  return _assign (new null ());
}

format::value &
format::value::_point (format::value::reference_token *rt, value & v)
{
  if (v.type () == value::value_t::undefined_t)
    return v;

  const wchar_t * const key = rt->path_next ();

  if (*key == 0)
    {
      delete rt;
      return v;
    }

  if (*key == _sc::path_separator)
    {
      delete rt;
      return v._at (L"");
    }

  return _point (rt, v._at (key));
}
