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
    virtual Value *clone () override { return 0; }
    virtual Value &assign (Value *, Value *) override { return *this; }

protected:

    virtual  Value &_at (const char *) { return *this; }
    virtual void _clear() override {}
    virtual Value *clone(const Value &) override { return this; }

    // Value interface
public:
    virtual Iterator *iterator() const override
    {
      return new Leaf_Iterator (this);
    }

    // Value interface
public:
    virtual const char *stringify () noexcept override { return ""; }
    virtual size_t strLength () const noexcept override { return 0; }
    virtual const char * strValue () const { return ""; }

    // Value interface
public:
    virtual Value & erase (const Value &) noexcept override
    {
      return *this;
    }

    // Value interface
public:
    virtual Value *clone (Value *old) override
    {
      return old;
    }
};


#endif // JSON_VALUE_PARSE_MOCK_H
