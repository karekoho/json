#ifndef JSON_VALUE_PARSE_MOCK_H
#define JSON_VALUE_PARSE_MOCK_H

#include "unit_test.h"

namespace format
{
  class json_mock_value : public value
  {
  public:

      json_mock_value (json *parent = nullptr)
        : value (parent)
      {}

      virtual ~
      json_mock_value ()
      {}

      virtual const wchar_t *
      _parse (const wchar_t *readp) override
      { return readp; }

      virtual value &
      at (const wchar_t *) const
      { return *(new format::undefined ()); }

      virtual value &
      at (size_t) const
      { return *(new format::undefined ()); }

      virtual value::value_t
      type () const noexcept override
      { return value::value_t::undefined_t; }

      virtual size_t
      count () const noexcept override
      { return 0; }

      virtual value *
      clone () const override
      { return nullptr; }

      virtual value &
      _assign (value *, value *) override
      { return *this; }

      virtual size_t
      _str_length () const noexcept override
      { return 0; }

      virtual const wchar_t *
      _to_string (wchar_t *) const override
      { return L""; }

      virtual value &
      _erase (const value &) noexcept override
      { return *this; }

//      virtual value *
//      _clone (const value *) const override
//      { return new json_mock_value (*this); }

  protected:

      virtual  value &
      _at (const wchar_t *) override
      { return *(new format::undefined ()); }

      virtual  value &
      _at (size_t) override
      { return *(new format::undefined ()); }

      virtual void _clear () override
      {}

      virtual value *
      _clone (const value &) override
      { return this; }

//      virtual size_t
//      _sizeof () const noexcept
//      { return sizeof (json_mock_value); }

      // value interface
  public:
      virtual value & point (const wchar_t *) override {
        return  *this;
      }
  };
}

#endif // JSON_VALUE_PARSE_MOCK_H
