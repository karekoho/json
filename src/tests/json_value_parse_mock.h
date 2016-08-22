#ifndef JSON_VALUE_PARSE_MOCK_H
#define JSON_VALUE_PARSE_MOCK_H

#include "unit_test.h"

// using namespace json;

class json_value_parse_mock : public value
{
public:
    json_value_parse_mock (const char *readp, const char *endp, value *parent = 0, size_t lexlen = 0);
    virtual ~json_value_parse_mock () {}

    virtual const char *parse (const char *readp);
    virtual const value & at (const char *key) const;
    virtual value::otype type () const;
    virtual size_t size () const;
};

#endif // JSON_VALUE_PARSE_MOCK_H
