#include "json_value.h"
#include <stdlib.h>

const struct value::literal_value value::__ltr_value[3] = {
  { "true", 4, value::_literal::true_value },
  { "false", 5, value::_literal::false_value },
  { "null", 4, value::_literal::null_value }
};

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
