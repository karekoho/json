#include "basic_json.h"

json::array::array (const char *json)
  : value (json)
{
}


json::array::array (const char *endp, value *parent, size_t charc)
  : value (endp, parent, charc)
{
}

#ifdef UNIT_TEST
const char *
json::array::parse (const char *json) { return json + _charc; }
#else
const char *
json::array::parse (const char *json)
{
    return json + _charc;   /// skips over end_array ]
}
#endif

const value &
json::array::at (const char *key) const
{
}


