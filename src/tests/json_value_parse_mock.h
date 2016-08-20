#ifndef JSON_VALUE_PARSE_MOCK_H
#define JSON_VALUE_PARSE_MOCK_H

#include "unit_test.h"

// using namespace json;

class json_value_parse_mock : public json::value
{
public:
    json_value_parse_mock (const char *readp, const char *endp, value *parent = 0);

    virtual const char *parse (const char *readp);
    virtual const json::value & at (const char *key) const;
    virtual json::value::type type () const;
    virtual size_t size () const;
};

#endif // JSON_VALUE_PARSE_MOCK_H
