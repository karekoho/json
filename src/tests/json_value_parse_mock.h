#ifndef JSON_VALUE_PARSE_MOCK_H
#define JSON_VALUE_PARSE_MOCK_H

#include "unit_test.h"

class json_value_parse_mock : public value
{
public:

    value::otype _type;

    json_value_parse_mock (const char *endp, value *parent, size_t charc, value::otype type = otype::null)
      // : json (endp, parent, charc),
      : value (endp, parent, charc),
        _type (type)
    {
    }

    virtual ~json_value_parse_mock () {}

    virtual const char *parse (const char *readp) { return readp; }
    virtual const value & at (const char *key) const { return *this; }
    virtual value::otype type () const { return _type;}
    virtual size_t size () const { return 0;}
};

#endif // JSON_VALUE_PARSE_MOCK_H
