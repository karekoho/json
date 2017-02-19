#ifndef JSON_VALUE_PARSE_MOCK_H
#define JSON_VALUE_PARSE_MOCK_H

#include "unit_test.h"
//using namespace Format;
namespace Format  {
class json_value_mock : public Value
{
public:

    json_value_mock (json *parent = 0) : Value (parent)
    {}

    virtual ~json_value_mock () {}

    virtual const wchar_t *
    parse (const wchar_t *readp)
    { return readp; }

    virtual Value &
    at (const wchar_t *) const
    { return *(new Format::undefined); }

    virtual Value &
    at (size_t) const
    { return *(new Format::undefined); }

    virtual Value::object_type
    type () const
    { return Value::object_type::undefined_t; }

    virtual size_t
    count () const
    { return 0; }

    virtual Value *
    clone () const override
    { return 0; }

    virtual Value &
    _assign (Value *, Value *) override
    { return *this; }

    virtual json_iterator *
    iterator () const override
    { return new leaf_iterator (this); }

    virtual const wchar_t *stringify () noexcept override
    { return L""; }

    virtual size_t strLength () const noexcept override
    { return 0; }

    virtual const wchar_t * strValue (wchar_t *) const
    { return L""; }

    virtual Value & erase (const Value &) noexcept override
    { return *this; }

    virtual Value *
    clone (const Value *) const override
    { return new json_value_mock (*this); }

protected:

    virtual  Value &
    _at (const wchar_t *)
    { return *this; }

    virtual  Value &
    _at (size_t)
    { return *this; }


    virtual void _clear () override
    {}

    virtual Value *
    clone (const Value &) override
    { return this; }
};
}

#endif // JSON_VALUE_PARSE_MOCK_H
