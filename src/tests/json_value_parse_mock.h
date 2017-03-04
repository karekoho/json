#ifndef JSON_VALUE_PARSE_MOCK_H
#define JSON_VALUE_PARSE_MOCK_H

#include "unit_test.h"
//using namespace Format;
namespace format  {
class json_value_mock : public value
{
public:

    json_value_mock (json *parent = 0) : value (parent)
    {}

    virtual ~json_value_mock () {}

    virtual const wchar_t *
    _parse (const wchar_t *readp)
    { return readp; }

    virtual value &
    at (const wchar_t *) const
    { return *(new format::undefined); }

    virtual value &
    at (size_t) const
    { return *(new format::undefined); }

    virtual value::value_t
    type () const noexcept
    { return value::value_t::undefined_t; }

    virtual size_t
    count () const noexcept
    { return 0; }

    virtual value *
    clone () const override
    { return 0; }

    virtual value &
    _assign (value *, value *) override
    { return *this; }

    virtual json_iterator *
    iterator () const override
    { return new leaf_iterator (this); }

    //virtual const wchar_t *stringify () noexcept override
    //{ return L""; }

    virtual size_t str_length () const noexcept override
    { return 0; }

    virtual const wchar_t * str_value (wchar_t *) const
    { return L""; }

    virtual value & erase (const value &) noexcept override
    { return *this; }

    virtual value *
    clone (const value *) const override
    { return new json_value_mock (*this); }

protected:

    virtual  value &
    _at (const wchar_t *)
    { return *this; }

    virtual  value &
    _at (size_t)
    { return *this; }


    virtual void _clear () override
    {}

    virtual value *
    clone (const value &) override
    { return this; }
};
}

#endif // JSON_VALUE_PARSE_MOCK_H
