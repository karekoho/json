#ifndef NULL_H
#define NULL_H

#include "json_leaf.h"
#include "json_json.h"

namespace format
{
  namespace json
  {
    #ifdef UNIT_TEST
     class json_null_test;
     namespace test {
       class null_test_ctor_dtor_Test;
       class null_test__clone_const_value_ref_Test;
       class null_test__parse_Test;
     }
    #endif

    /**
     * @brief The null class
     */
    class null : public leaf
    {
      friend null * __call_null (json *);

      #ifdef UNIT_TEST
        friend class json_null_test;
        friend class test::null_test_ctor_dtor_Test;
        friend class test::null_test__clone_const_value_ref_Test;
        friend class test::null_test__parse_Test;
      #endif

      public:
      /**
       * @brief null
       */
      null ()
        : leaf ()
      {}

      /**
       * @brief Null
       * @param other
       */
      null (const null &other) = default;

      /**
       * @brief ~null
       */
      virtual ~null () override = default;

      /**
       * @brief clone
       * @param other
       * @return
       */
      virtual inline value *
      clone () const override
      { return new null (*this); }

      /**
       * @brief type
       * @return
       */
      virtual inline value::value_t
      type () const noexcept override
      { return value::value_t::null_t; }

      /**
       * @brief Value
       * @return
       */
      inline std::nullptr_t
      value () const noexcept
      { return nullptr; }

      /**
       * @deprecated Use value instead
       * @return
       */
      inline std::nullptr_t
      get () const noexcept
      { return value (); }

      /**
       * @note Removed
       * @brief operator =
       * @param n
       * @return
       *
      inline value &
      operator =(const null & n)
      { return _assign (n); } */

      /**
       * @note Removed
       * @brief operator =
       * @return
       *
      inline value &
      operator =(std::nullptr_t)
      { return *this; } */

    protected:
      /**
       * @brief null
       * @param parent
       */
      null (json *parent)
        : leaf (parent)
      { }

      /**
       * @brief _parse
       * @param json
       * @return
       */
      virtual inline const wchar_t *
      _parse (const wchar_t * const json) noexcept override
      { return json + 4; }

      /**
       * @brief _clone
       * @return
       */
      virtual inline class value *
      _clone (const class value &) noexcept override
      { return this; }

      /**
       * @brief strValue
       * @return
       */
      virtual inline const wchar_t *
      _to_string (wchar_t *) const noexcept override
      { return L"null"; }

      /**
       * @brief strLength
       * @return
       */
      virtual inline size_t
      _str_length () const noexcept override
      { return 4; }

      /**
       * @note Removed
       * @brief assign
       * @param nv
       * @return
       *
      value &
      _assign (const null &)
      { return _parent ? __call__assign (_parent, this, new null (*this)) : *this; } */
    };  // Class null

    inline
    null * __call_null (json *parent)
    { return new null (parent); }
  } // Namespace json
} // Namespace format

#endif // NULL_H
