#include "json_value.h"
#include "json_json.h"
#include "json_string.h"
#include "json_number.h"
#include "json_boolean.h"

#include <stdlib.h>

const struct Value::literal_value Value::__ltr_value[3] = {
  { L"true", 4, Value::_literal::true_value },
  { L"false", 5, Value::_literal::false_value },
  { L"null", 4, Value::_literal::null_value }
};

Value::Value ()
    : _startp (0),
      _readp (0),
      _parent (0),
      _key (0),
      _index (0),
      _old_value (0)
{
}

Value::Value (const wchar_t *)
    : _startp (0),
      _readp (0),
      _parent (0),
      _key (0),
      _index (0),
      _old_value (0)
{
}

Value::Value (JSON *parent)
    : _startp (0),
      _readp (0),
      _parent (parent),
      _key (0),
      _index (0),
      _old_value (0)
{
}

Value::Value (const Value &other)
  : _startp (other._startp),
    _readp (other._readp),
    _parent (0),
    _key (other._key ? new wchar_t [wcslen (other._key) + 1] () : 0),
    _index (other._index),
    _old_value (0)
{
}

Value::Value (const Value *ov, const Value &nv)
  : _startp (nv._startp),
    _readp (nv._readp),
    _parent (0),
    _key (nv._key ? new wchar_t [wcslen (nv._key) + 1] () : 0),
    _index (nv._index),
    _old_value (0)
{
  delete nv._old_value;
  nv._old_value = ov;
}

Value::~Value ()
{
  delete[] _key;

  delete _old_value;
  _old_value = 0;
}

long int
Value::_string (wchar_t &endc) const noexcept
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

Value::_literal
Value::_is_literal (const int _try) const noexcept
{
  const wchar_t *readp = _readp;

  size_t idx = 0;

  while (*(readp + idx) != 0
         && idx < __ltr_value[_try].len
         && *(readp + idx) == *(__ltr_value[_try].str_value + idx))
    idx++;

  if (idx == __ltr_value[_try].len)
    return __ltr_value[_try].ltr_value;

  return _try < 2 ? _is_literal (_try + 1) :  Value::_literal::no_literal;
}

void
Value::_erase () noexcept
{
  if (_parent)
    (void) _parent->erase (*this);
}

Value &
Value::_assign (const Value &nv)
{
  if (_parent == 0)
    throw JSON_Error (BAD_ASSIGN);

  return _parent->assign (this, nv.clone (this));
}

Value &
Value::operator =(bool b)
{
  return _assign (*(new Boolean (b)));
}

Value &
Value::operator =(const wchar_t *s)
{
  return _assign (*(new String (s)));
}

Value &
Value::operator =(double d)
{
  return _assign (*(new Number (d)));
}

