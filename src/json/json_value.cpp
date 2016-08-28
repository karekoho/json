#include "json_value.h"

const struct value::literal_value value::__ltr_value[3] = {
  { "true", 4, value::_literal::true_value },
  { "false", 5, value::_literal::false_value },
  { "null", 4, value::_literal::null_value }
};

#include <stdlib.h>

value::value (const char *json)
    : _startp (json),
      _readp (json),
      _endp (json == 0 ? 0 : json + strlen (json)),
      _parent (0),
      _charc (0)
{
}

value::value (const char *endp, value *parent, size_t charc)
    : _startp (0),
      _readp (0),
      _endp (endp),
      _parent (parent),
      _charc (charc)
{
}

// value *value::_make_value() {}

long int
value::_string (char & endc) const
{
    const char * const starp = _readp;

    if (*starp != sc_::double_quote) {
        endc = *starp;
        return 0;
    }

    const char * readp = _readp + 1;

    while (readp < _endp && *readp != sc_::double_quote) {
        readp++;
    }

    endc = *readp;

    return readp < _endp ? (readp - starp) + 1 : -1 * (readp - starp);
}

value::_literal
value::_is_literal (const int _try) const
{
  const char *readp = _readp;

  size_t idx = 0;

  while (readp + idx < _endp
         && idx < __ltr_value[_try].len
         && *(readp + idx) == *(__ltr_value[_try].str_value + idx)) {
      idx++;
    }

  if (idx == __ltr_value[_try].len)
    return __ltr_value[_try].ltr_value;

  return _try < 2 ? _is_literal (_try + 1) :  value::_literal::no_value;
}
