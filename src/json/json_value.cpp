#include "json_value.h"
#include <stdlib.h>

const struct Value::literal_value Value::__ltr_value[3] = {
  { "true", 4, Value::_literal::true_value },
  { "false", 5, Value::_literal::false_value },
  { "null", 4, Value::_literal::null_value }
};

Value::Value (const char *json)
    : _startp (json),
      _readp (json),
      //_endp (0),
      _parent (0),
      _charc (json == 0 ? 0 : strlen (json))
{
}

Value::Value (Value *parent, size_t index)
    : _startp (0),
      _readp (0),
      // _endp (0),
      _parent (parent),
      _charc (index)
{
}

long int
Value::_string (char & endc) const
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
Value::_is_literal (const int _try) const
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
