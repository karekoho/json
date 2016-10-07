#include "json_value.h"
#include "json_json.h"
#include <stdlib.h>

const struct Value::literal_value Value::__ltr_value[3] = {
  { "true", 4, Value::_literal::true_value },
  { "false", 5, Value::_literal::false_value },
  { "null", 4, Value::_literal::null_value }
};

Value::Value ()
    : _startp (0),
      _readp (0),
      _parent (0),
     // _length (0),
      _key (0),
      _index (0),
      _old (0)
{
}

Value::Value (const char *)
    : _startp (0),
      _readp (0),
      _parent (0),
     // _length (1 /* json == 0 ? 0 : strlen (json) */),
      _key (0),
      _index (0),
      _old (0)
{
}

Value::Value (JSON *parent)
    : _startp (0),
      _readp (0),
      _parent (parent),
     // _length (0),
      _key (0),
      _index (0),
      _old (0)
{
}

Value::Value (const Value &other)
  : _startp (other._startp),
    _readp (other._readp),
    _parent (0),
    // _length (other._length),
    _key (other._key ? strdup (other._key) : 0),
    _index (other._index),
    _old (0)
{
}

Value::Value (Value *ov, const Value &nv)
  : _startp (nv._startp),
    _readp (nv._readp),
    _parent (0),
    _key (nv._key ? strdup (nv._key) : 0),
    _index (nv._index),
    _old (0)
{
  nv._old = ov;
}

Value::~Value ()
{
  free ((char *)_key);

  delete _old;
  _old = 0;
}

long int
Value::_string (char & endc) const noexcept
{
  const char * const starp = _readp;

  if (*starp != _sc::double_quote) {
        endc = *starp;
        return 0;
    }

    const char * readp = _readp + 1;

    while (*readp != 0 && *readp != _sc::double_quote) {
        readp++;
    }

    endc = *readp;

    return *readp != 0 ? (readp - starp) + 1 : -1 * (readp - starp);
}

Value::_literal
Value::_is_literal (const int _try) const noexcept
{
  const char *readp = _readp;

  size_t idx = 0;

  while (*(readp + idx) != 0
         && idx < __ltr_value[_try].len
         && *(readp + idx) == *(__ltr_value[_try].str_value + idx)) {
      idx++;
    }

  if (idx == __ltr_value[_try].len)
    return __ltr_value[_try].ltr_value;

  return _try < 2 ? _is_literal (_try + 1) :  Value::_literal::no_value;
}

void
Value::_erase () noexcept
{
  if (_parent)
    (void) _parent->erase (*this);
}

Value &
Value::_assign (Value &nv)
{
  if (_parent == 0)
    throw JSON::error ("bad assignment");

  return _parent->assign (this, nv.clone (this));
}
