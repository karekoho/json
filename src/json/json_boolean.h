#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "json_leaf.h"
#include "json_json.h"

namespace format
{
  namespace json
  {
      #ifdef UNIT_TEST
        namespace test
        {
          class boolean_test_ctor_dtor_Test;
          class boolean_test_assign_all_values_Test;
          class boolean_test__parse_Test;
          class boolean_test_str_length_Test;
          class boolean_test__to_string_Test;
        }
      #endif
     /**
      * @brief The boolean class
      */
      class boolean : public leaf
      {
        friend boolean * __call_boolean (json *parent, bool b);

      #ifdef UNIT_TEST
//        friend class test::boolean_test_ctor_dtor_Test;
//        friend class test::boolean_test_assign_all_values_Test;
//        friend class test::boolean_test__parse_Test;
//        friend class test::boolean_test_str_length_Test;
//        friend class test::boolean_test__to_string_Test;
      #endif

      public:
       /**
        * @brief Boolean
        */
        boolean ()
          : leaf (false)
        { }

       /**
        * @brief Boolean
        * @param value
        */
        boolean (const bool value)
          : leaf (value)
        { }

       /**
        * @brief Boolean
        * @param other
        */
        boolean (const boolean & other)
          : leaf (other)
        { }

       /**
        * @brief ~Boolean
        */
        virtual ~boolean () override = default;

       /**
        * @brief clone
        * @param other
        * @return
        */
        virtual inline value *
        clone () const override
        { return new boolean (*this); }

       /**
        * @brief type
        * @return
        */
        virtual inline value_t
        type () const noexcept override
        { return value::value_t::boolean_t; }

        /**
         * @brief value
         * @return
         */
        inline bool
        value () const noexcept
        { return _value.boolean; }

        /**
         * @deprecated Use value instead
         * @brief value
         * @return
         */
         inline bool
         get () const noexcept
         { return value (); }

       /**
        * @note Removed
        * @brief operator =
        * @param b
        * @return
        *
        inline value &
        operator =(boolean & b)
        { return _assign (b); } */

        /**
         * @note Removed
         * @brief operator =
         * @param b
         * @return
         *
        virtual inline value &
        operator =(bool b) override
        {
          _primitive.boolean_value = b;
          return *this;
        }*/

       /**
        * @note Removed
        * @brief assign
        * @param nv
        * @return
        *
        value &
        _assign (const boolean & nv)
        { return _parent ? __call__assign (_parent, this, new boolean (nv)) : *(_clone (nv)); } */

      protected:
        /**
         * @brief boolean
         * @param parent
         * @param value
         */
        boolean (json *parent, const bool value)
          : leaf (parent, value)
        {  }

        /**
         * @brief parse
         * @param json
         * @return
         */
        virtual inline const wchar_t *
        _parse (const wchar_t * const json) noexcept override
        { return json + (_value.boolean == true ? 4 : 5); }

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
         _to_string (wchar_t * = nullptr) const noexcept override
         { return _value.boolean == true ? L"true" : L"false"; }

        /**
         * @brief str_length
         * @return
         */
         virtual inline size_t
         _str_length () const noexcept override
         { return _value.boolean == true ? 4 : 5; }
      }; // Class boolean

      inline
      boolean * __call_boolean (json *parent, bool b)
      { return new boolean (parent, b); }
  } // Namespace json
} // Namespace format

#endif // BOOLEAN_H
