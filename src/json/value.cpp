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

value::value (const char *endp, value *parent, size_t charc)
    : _startp (0),
      _readp (0),
      _endp (endp),
      _parent (parent),
      _charc (charc)
{
}

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

