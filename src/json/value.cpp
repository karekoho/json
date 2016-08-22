#include "value.h"

//using namespace json;

value::value (const char *json)
    : _startp (json),
      _readp (json),
      _endp (json == 0 ? 0 : json + strlen (json)),
      _parent (0),
      _charc (0)
{
}

value::value (const char *startp, const char *endp, value *parent, size_t lexlen)
    : _startp (startp),
      _readp (startp),
      _endp (endp),
      _parent (parent),
      _charc (lexlen)
{
}

