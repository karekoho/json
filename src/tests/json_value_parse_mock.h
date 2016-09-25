#ifndef JSON_VALUE_PARSE_MOCK_H
#define JSON_VALUE_PARSE_MOCK_H

#include "unit_test.h"

class json_value_parse_mock : public Value
{
public:
    json_value_parse_mock (JSON *parent = 0) : Value (parent){}
    virtual ~json_value_parse_mock () {}

    virtual const char *parse (const char *readp) { return readp; }
    virtual Value & at (const char *) const { return *(new Undefined); }
    virtual Value & at (size_t) const { return *(new Undefined); }
    virtual Value::object_type type () const { return Value::object_type::undefined; }
    virtual size_t count () const { return 0; }
    virtual Value *_clone () override { return 0; }
    virtual Value &assign (Value *, Value *) override { return *this; }

protected:

    virtual  Value &_at (const char *) { return *this; }
    virtual void _clear() override {}
    virtual Value *_clone(const Value &) override { return this; }

    // Value interface
public:
    virtual Iterator *iterator() const override
    {
      return new Leaf_Iterator (this);
    }
};

#endif // JSON_VALUE_PARSE_MOCK_H
