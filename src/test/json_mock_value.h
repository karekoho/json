#ifndef MOCK_VALUE_H
#define MOCK_VALUE_H

#include "unit_test.h"

namespace format
{
  namespace json
  {
    namespace test
    {
      class value_test__lookahead_Test;
      class value_test__string_Test;
      class value_test__is_literal_Test;
      class value_test__str_append_Test;
      class value_test__quote_value_Test;

      class mock_value : public value
      {
        friend class value_test__lookahead_Test;
        friend class value_test__string_Test;
        friend class value_test__is_literal_Test;
        friend class value_test__str_append_Test;
        friend class value_test__quote_value_Test;

        public:
        mock_value (json *parent = nullptr) : value (parent)
        {}

        virtual ~
        mock_value () override
        {}

        virtual const wchar_t *
        _parse (const wchar_t *readp) override
        { return readp; }

        virtual value &
        at (const wchar_t *) const
        { return *(new format::json::undefined ()); }

        virtual value &
        at (size_t) const
        { return *(new format::json::undefined ()); }

        virtual value::value_t
        type () const noexcept override
        { return value::value_t::undefined_t; }

        virtual size_t
        size () const noexcept override
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

        protected:
        virtual  value &
        _at (const wchar_t *) override
        { return *(new format::json::undefined ()); }

        virtual  value &
        _at (size_t) override
        { return *(new format::json::undefined ()); }

        virtual  const value &
        _at (const wchar_t *) const override
        { return *(new format::json::undefined ()); }

        virtual  const value &
        _at (size_t) const override
        { return *(new format::json::undefined ()); }

        virtual void _clear () override
        {}

        virtual value *
        _clone (const value &) override
        { return this; }
      };
    }
  }
}

#endif // MOCK_VALUE_H
