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
      /**
       * @brief The mock_value class
       */
      class mock_value : public value
      {
        friend class value_test__lookahead_Test;
        friend class value_test__string_Test;
        friend class value_test__is_literal_Test;
        friend class value_test__str_append_Test;
        friend class value_test__quote_value_Test;

        public:

        mock_value (json *parent = nullptr) : value (parent) {}
        virtual ~ mock_value () override {}

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

        static void
        _set_key (value *target, const wchar_t *keyp, size_t charc)
        { return value::_set_key (target, keyp, charc); }

        static size_t
        _str_length (const value *parent)
        { return value::_str_length (parent); }

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
      }; // Class mock_value

      class json_test__parse_Test;
      class json_test__to_string_Test;
      class json_test_make_value_Test;
      /**
       * @brief The mock_json class
       */
      class mock_json : public json
      {
        friend class json_test__parse_Test;
        friend class json_test__to_string_Test;
        friend class json_test_make_value_Test;

        public:

        mock_json () : json () {}
        mock_json (const wchar_t * const json_text) : json (json_text){}
        mock_json (object *o) : json (o) {}
        mock_json (array *a): json (a) {}
        mock_json (const json &other) : json (other) {}
      };// Class mock_json

      class object_test__erase_Test;
      class object_test_ctor_dtor_Test;
      class object_test_assign_all_values_Test;
      class object_test__parse_Test;
      class object_test_key_Test;
      class object_test_operator_at_key_Test;
      class object_test__pair_Test;
      class object_test__clear_Test;
      class object_test__str_length_Test;
      class object_test__to_string_Test;
      class object_test__assign_value_ptr_value_ptr_Test;
      class object_test__clone_const_value_ref_Test;
      /**
       * @brief The mock_object class
       */
      class mock_object : public format::json::object
      {
        friend class object_test__erase_Test;
        friend class object_test_ctor_dtor_Test;
        friend class object_test_assign_all_values_Test;
        friend class object_test__parse_Test;
        friend class object_test_key_Test;
        friend class object_test_operator_at_key_Test;
        friend class object_test__pair_Test;
        friend class object_test__clear_Test;
        friend class object_test__str_length_Test;
        friend class object_test__to_string_Test;
        friend class object_test__assign_value_ptr_value_ptr_Test;
        friend class object_test__clone_const_value_ref_Test;

      public:

        mock_object () : object () {}
        mock_object (const wchar_t *input) : object (input) {}
        mock_object (json *parent) : object (parent) {}
        mock_object (std::initializer_list<std::pair<std::wstring, value *> > il) : object (il) {}
        mock_object (std::initializer_list<std::pair<std::wstring, value &&> > il) : object (il) {}
        /**
         * @brief begin
         * @return
         */
        std::unordered_map<std::wstring, value *>::iterator
        begin ()
        { return _member_list.begin (); }

        /**
         * @brief end
         * @return
         */
        std::unordered_map<std::wstring, value *>::iterator
        end ()
        { return _member_list.end (); }

        /**
         * @brief clear
         */
        void
        clear ()
        { _clear (); }

        /**
         * @brief _clear
         */
        void
        _clear ()
        { _member_list.clear (); }

        /**
         * @brief assign
         * @param ov
         * @param nv
         * @return
         */
        value & assign (value *ov, value *nv)
        { return _assign (ov, nv); }
      };  // Class mock_object

      class array_test_ctor_dtor_Test;
      class array_test__parse_Test;
      class array_test_index_Test;
      class array_test_assign_all_values_Test;
      class array_test__to_string_Test;
      class array_test_operator_at_key_Test;
      class array_test_operator_at_index_Test;
      class array_test__clear_Test;
      class array_test_str_length_Test;
      class array_test__erase_Test;
      class array_test__assign_value_ptr_value_ptr_Test;
      class array_test_operator_assign_wchar_t_ptr_Test;
      /**
       * @brief The mock_array class
       */
      class mock_array : public format::json::array
      {
        friend class test::array_test_ctor_dtor_Test;
        friend class test::array_test__parse_Test;
        friend class test::array_test_index_Test;
        friend class test::array_test_assign_all_values_Test;
        friend class test::array_test__to_string_Test;
        friend class test::array_test_operator_at_key_Test;
        friend class test::array_test_operator_at_index_Test;
        friend class test::array_test__clear_Test;
        friend class test::array_test_str_length_Test;
        friend class test::array_test__erase_Test;
        friend class test::array_test__assign_value_ptr_value_ptr_Test;
        friend class test::array_test_operator_assign_wchar_t_ptr_Test;

        public:

        mock_array () : array () {}
        mock_array (json *parent) : array (parent) {}
        mock_array (const wchar_t *input) : array (input) {}
        mock_array (std::initializer_list<value *> il) : array (il) {}

        /**
         * @brief push
         * @param v
         */
        size_t push (format::json::value *v)
        {
          _element_list.push_back (v);
          return _element_list.size () - 1;
        }

        /**
         * @brief assign
         * @param ov
         * @param nv
         * @return
         */
        value & assign (value *ov, value *nv)
        { return _assign (ov, nv); }

        /**
         * @brief clear
         */
        void
        clear ()
        { _clear (); }

        /**
         * @brief _clear
         */
        void
        _clear ()
        { _element_list.clear (); }

        /**
         * @brief begin
         * @return
         */
        std::vector<value *>::const_iterator
        begin () const
        { return _element_list.begin (); }

        /**
         * @brief end
         * @return
         */
        std::vector<value *>::const_iterator
        end () const
        { return _element_list.end (); }
      };  // Class mock_array

      class string_test;
      class string_test__string_Test;
      class string_test_ctor_dtor_Test;
      class string_test_assign_all_values_Test;
      class string_test__clone_const_value_ref_Test;
      /**
       * @brief The mock_string class
       */
      class mock_string : public format::json::string
      {
        friend class test::string_test;
        friend class test::string_test__string_Test;
        friend class test::string_test_ctor_dtor_Test;
        friend class test::string_test_assign_all_values_Test;
        friend class test::string_test__clone_const_value_ref_Test;

      public:

        mock_string () : string () {}
        mock_string (const wchar_t * const string_text) : string (string_text) {}
        mock_string (const mock_string & other) : string (other) {}
        mock_string (mock_string && other) : string (other) {}
        mock_string (format::json::json *parent, size_t charc) : string (parent,charc) {}
      };

      class number_test_ctor_dtor_Test;
      class number_test__to_string_Test;
      class number_test__parse_Test;
      class number_test__digits_Test;
      class number_test__frag_Test;
      class number_test__exp_Test;
      class number_test__atoll_Test;
      class number_test__atof_Test;
      class number_test__calculate_Test;
      class number_test_assign_all_values_Test;
      class number_test__str_length_Test;
      class number_test__clear_Test;
      class number_test__integral_length_Test;
      class number_test__to_string_ll_Test;
      class number_test__to_string_ld_Test;
      class number_test__clone_const_value_ref_Test;
      /**
       * @brief The mock_number class
       */
      class mock_number : public format::json::number
      {
        friend class number_test_ctor_dtor_Test;
        friend class number_test__to_string_Test;
        friend class number_test__parse_Test;
        friend class number_test__digits_Test;
        friend class number_test__frag_Test;
        friend class number_test__exp_Test;
        friend class number_test__atoll_Test;
        friend class number_test__atof_Test;
        friend class number_test__calculate_Test;
        friend class number_test_assign_all_values_Test;
        friend class number_test__str_length_Test;
        friend class number_test__clear_Test;
        friend class number_test__integral_length_Test;
        friend class number_test__to_string_ll_Test;
        friend class number_test__to_string_ld_Test;
        friend class number_test__clone_const_value_ref_Test;

      public:

        mock_number () : number () {}
        mock_number (int i): number (i) {}
        mock_number (long long ll): number (ll) {}
        mock_number (float f): number (f) {}
        mock_number (long double ld): number (ld) {}
        mock_number (const number &other): number (other) {}
        mock_number (number&& other): number (other) {}
        mock_number (const wchar_t * const json_text) : number (json_text) {}
        mock_number (format::json::json *parent) : number (parent){}
      };

      class null_test_ctor_dtor_Test;
      class null_test__clone_const_value_ref_Test;
      class null_test__parse_Test;
      /**
       * @brief The mock_null class
       */
      class mock_null : public format::json::null
      {
        friend class null_test_ctor_dtor_Test;
        friend class null_test__clone_const_value_ref_Test;
        friend class null_test__parse_Test;

      public:

        mock_null () : null () {}
        mock_null (const mock_null &other) = default;
        mock_null (format::json::json *parent): null (parent){}
      };

      class boolean_test_ctor_dtor_Test;
      class boolean_test_assign_all_values_Test;
      class boolean_test__parse_Test;
      class boolean_test_str_length_Test;
      class boolean_test__to_string_Test;
      /**
       * @brief The mock_boolean class
       */
      class mock_boolean : public format::json::boolean
      {
        friend class boolean_test_ctor_dtor_Test;
        friend class boolean_test_assign_all_values_Test;
        friend class boolean_test__parse_Test;
        friend class boolean_test_str_length_Test;
        friend class boolean_test__to_string_Test;

      public:

        mock_boolean (format::json::json *parent, bool b): boolean (parent, b) {}
        mock_boolean () : boolean (false) { }
        mock_boolean (const bool value) : boolean (value) { }
        mock_boolean (const boolean & other) : boolean (other) { }
      };

      class undefined_test_ctor_dtor_Test;
      class undefined_test_assign_all_values_Test;
      class undefined_test__parse_Test;
      class undefined_test_str_length_Test;
      class undefined_test__to_string_Test;
      /**
       * @brief The mock_undefined class
       */
      class mock_undefined : public format::json::undefined
      {
        friend class undefined_test_str_length_Test;
        friend class undefined_test__to_string_Test;

      public:

        mock_undefined () : undefined () {}
        mock_undefined (json *parent) : undefined (parent) {}
        mock_undefined (const mock_undefined &other) = default;
      };

      class mock_unique_undefined : public mock_undefined
      {
        friend class undefined_test_assign_all_values_Test;

      public:

        mock_unique_undefined () : mock_undefined () {}
        mock_unique_undefined (json *parent) : mock_undefined (parent) {}
      };

    } // Namespace test
  } // Namespace json
} // Namespace format

#endif // MOCK_VALUE_H
