#ifndef JSON_VALUE_PARSE_MOCK_H
#define JSON_VALUE_PARSE_MOCK_H

#include "unit_test.h"

// using namespace json;

class json_value_parse_mock : public value
{
public:

    /* json_value_parse_mock (const char *endp, value *parent = 0, size_t charc = 0, value::otype type = otype::null);
    virtual ~json_value_parse_mock () {}

    virtual const char *parse (const char *readp) { return readp; }
    const char *parse (const char *readp, size_t charc) { return readp + charc; }
    virtual const value & at (const char *key) const;
    virtual value::otype type () const;
    virtual size_t size () const; */

    value::otype _type;

    json_value_parse_mock (const char *endp, value *parent, size_t charc, value::otype type = otype::null)
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
