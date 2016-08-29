#include "json_array.h"

Array::Array (const char *json)
  : json::json (json)
{
}

Array::Array (const char *endp, value *parent, size_t charc)
  : json::json (endp, parent, charc)
{
}

const char *
Array::parse (const char *json)
{
  return json + _charc;   /// skips over end_array ]
}

const value &
Array::at (const char *key) const
{
  return *this;
}


