#include "value.h"

//using namespace json;

value::value (const char *json)
    : _startp (json),
      _readp (json),
      _endp (json == 0 ? 0 : json + strlen (json)),
      _parent (0)
{
}

value::value (const char *readp, const char *endp, value *parent)
    : _startp (readp),
      _readp (0),
      _endp (endp),
      _parent (parent)
{
}

