#ifndef JSON_VALUE_PARSE_MOCK_H
#define JSON_VALUE_PARSE_MOCK_H

#include "unit_test.h"

class json_value_parse_mock : public Value
{
public:

    Value::object_type _type;

    json_value_parse_mock (Value *parent, size_t charc, Value::object_type type = object_type::null)
      // : json (endp, parent, charc),
      : Value (parent, charc),
        _type (type)
    {
    }

    virtual ~json_value_parse_mock () {}

    virtual const char *parse (const char *readp) { return readp; }
    virtual const Value & at (const char *) const { return *this; }
    virtual Value::object_type type () const { return _type;}
    virtual size_t size () const { return 0;}

    // Value interface
protected:
    virtual const Value &_at(const char *) const { return *this; }
};

#endif // JSON_VALUE_PARSE_MOCK_H
