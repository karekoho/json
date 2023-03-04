#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <ctype.h>
#include <cstring>
#include <string>

#include "json_exception.h"

namespace format
{
  namespace json
  {
    #define UNEXPECTED_END_OF_INPUT         "Unexpected end of JSON input"
    #define UNEXPECTED_START_OF_INPUT       "Unexpected start of JSON input"
    #define UNEXPECTED_TOKEN                "Unexpected token "
    #define BAD_ASSIGNMENT                  "Bad assignment"
    #define BAD_CAST_NULL_TO_NUMERIC        "Cannot cast null to boolean or numeric type"
    #define BAD_CAST_OBJECT_TO_NUMERIC      "Cannot cast object to boolean or numeric type"
    #define BAD_CAST_NUMERIC_TO_STRING      "Cannot cast boolean or numeric type to string"
    #define BAD_CAST_OBJECT_TO_STRING       "Cannot cast object to string"
    #define BAD_CAST_UNDEFINED_TO_NUMERIC   "Cannot cast undefined to numeric or boolean"
    #define BAD_CAST_UNDEFINED_TO_STRING    "Cannot cast undefined to string"

    /**
     * @brief The interface for all values that a JSON object can hold
     */
    class json;
    class json_iterator;
    class undefined;
    class value
    {
      public:
      /**
       * @brief JSON types and internal types
       */
      enum value_t
      {
        no_value_t,
        undefined_t,
        object_t,
        array_t,
        string_t,
        number_t,
        boolean_t,
        null_t
      };

      /**
       * @brief Default constructor
       */
      value ();

      /**
       * @brief Parseable constructor
       * @param JSON text
       */
      value (const wchar_t * const);

      /**
       * @brief Activating constructor for union primitive_value { long double }
       * @param Union member
       */
      value (long double);

      /**
       * @brief Activating constructor for union primitive_value { bool }
       * @param Union member
       */
      value (bool);

      /**
       * @brief Called by json::_make_value before value::_parse (json_text)
       * @param The parent object where the parsed object will be assigned
       */
      value (json *parent);

      /**
       * @brief Called by json::_make_value before value::_parse (json_text)
       * @param The parent object where the parsed object will be assigned
       * @param union member to activate, actives string with nullptr
       */
      value (json *parent, size_t);

      /**
       * @brief Called by json::_make_value before value::_parse (json_text)
       * @param The parent object where the parsed object will be assigned
      * @param union member to activate
       */
      value (json *parent, long double);

      /**
       * @brief Called by json::_make_value before value::_parse (json_text)
       * @param The parent object where the parsed object will be assigned
       * @param union member to activate
       */
      value (json *parent, bool);

      /**
       * @brief Copy constructor
       * @param The object to copy
       */
      value (const value &other);

      /**
       * @brief Destructor
       */
      virtual ~value ();

      /**
       * @brief Call object copy constructor when derived type in not known
       * @see format::json::value * format::json::array::_clone (const value &other)
       * @return
       */
      virtual value *
      clone () const = 0;

      /**
       * @brief Return the JSON type of the object
       * @return
       */
      virtual value_t
      type () const noexcept = 0;

      /**
       * @brief Return the count of members of the JSON object
       * @return Count of object keys or array elements
       */
      virtual size_t
      size () const noexcept = 0;

      /**
       * @deprecated Will be removed, use stringify instead
       * @brief See stringify
       * @return
       */
      inline const wchar_t *
      get () const
      { return _to_string (); }

      /**
       * @brief Generate parseable text representation from the JSON object
       * @return Pointer to the allocated memory
       */
      virtual inline const wchar_t *
      stringify () const
      { return _to_string (); }

      /**
       * @brief Get element at key
       * @param key
       * @return JSON value
       */
      inline value &
      operator [](const wchar_t *const key)
      { return _at (key); }

      /**
       * @brief Get element at key
       * @param key
       * @return JSON value
       */
      inline const value &
      operator [](const wchar_t *const key) const
      { return _at (key); }

      /**
       * @brief Get element at index
       * @param index
       * @return JSON value
       */
      inline value &
      operator [](size_t index)
      { return _at (index); }

      /**
       * @brief Get element at index
       * @param index
       * @return JSON value
       */
      inline const value &
      operator [](size_t index) const
      { return _at (index); }

      /**
       * @brief Assing new value to the object v, e.g. json j[L"foo"] = L"bar"
       * @param The value to assign
       * @return The object where new value was assigned to
       */
      inline value &
      operator =(value *v)
      { return _assign (v); }

      /**
       * @brief Assing new value to the object v, e.g. json j[L"foo"] = L"bar"
       * @param The value to assign
       * @return The object where new value was assigned to
       */
      inline value &
      operator =(const value & v)
      { return _assign (v); }

      /**
       * @brief Remove value from object, e.g. json j[L"foo"] = undefined ()
       * @param Assinged undefined
       * @return The object where the value was removed from
       */
      inline value &
      operator =(const undefined & u)
      { return _assign (u); }

      /**
       * @brief operator =
       * @param l
       * @return The object where new value was assigned to
       */
      virtual value &
      operator =(int i);

      /**
       * @brief operator =
       * @param l
       * @return The object where new value was assigned to
       */
      virtual value &
      operator =(long long l);

      /**
       * @brief operator =
       * @param l
       * @return The object where new value was assigned to
       */
      virtual value &
      operator =(float f);

      /**
       * @brief operator =
       * @param d
       * @return The object where new value was assigned to
       */
      virtual value &
      operator =(long double ld);

      /**
       * @brief operator =
       * @param b
       * @return The object where new value was assigned to
       */
      virtual value &
      operator =(bool b);

      /**
       * @brief Assign JSON null value to the object e.g json j[L"foo"] = nullptr_t
       * @return The object where new value was assigned to
       */
      value &
      operator =(std::nullptr_t);

      /**
       * @brief Check if object of the given JSON type
       * @param The type to check
       * @return True if of same type
       */
      inline bool
      operator ==(value_t t) const noexcept
      { return type () == t; }

      /**
       * @brief Get the key with the element was assigned
       * @return At least empty string if object is assigned to object,
       *  or nullptr_t if object is assigned to array
       */
      inline const wchar_t *
      key () const noexcept
      { return _key; }

      /**
       * @brief Get the index with the element was assigned
       * @return Always at least 0
       */
      inline size_t
      index () const noexcept
      { return _index; }

      /**
       * @brief Get the parent object where object is assigned to
       * @return The parent object or undefined if no parent exists
       */
      inline value *
      parent () const
      { return _parent; }

      /**
       * @brief Get the primitive value the object holds.
       * @return any numeric type or bool
       * @throw Throws json_conversion_error if not possible to cast to primitive type.
       */
      template<typename T>
      auto as () const -> typename std::enable_if<(not std::is_pointer<T>::value && not std::is_reference<T>::value), T>::type
      {
        value_t t = type ();

        if (t == value_t::number_t)
          return _value.long_double;

        if (t == value_t::boolean_t)
          return _value.boolean;

        // String to boolean
        if (t == value_t::string_t)
         return static_cast<bool>(_value.string);

        if (t == value_t::null_t)
          throw json_conversion_error (BAD_CAST_NULL_TO_NUMERIC);

        if (t == value_t::undefined_t)
          throw json_conversion_error (BAD_CAST_UNDEFINED_TO_NUMERIC);

        // Object
        throw json_conversion_error (BAD_CAST_OBJECT_TO_NUMERIC);
      }

      /**
       * @brief Get the primitive value the object holds.
       * @return const wchar_t *
       * @throw Throws json_conversion_error if not possible to cast to primitive type.
       */
      template<typename T>
      auto as () const -> typename std::enable_if<(std::is_same<T, const wchar_t *>::value), T>::type
      {
        value_t t = type ();

        if (t == value_t::string_t)
          return _to_string ();

        // null to string
        if (t == value_t::null_t)
          return L"";

        if (t == value_t::boolean_t || t == value_t::number_t)
          throw json_conversion_error (BAD_CAST_NUMERIC_TO_STRING);

        if (t == value_t::undefined_t)
          throw json_conversion_error (BAD_CAST_UNDEFINED_TO_STRING);

        // Object
        throw json_conversion_error (BAD_CAST_OBJECT_TO_STRING);
      }

      /** @note Removed
      inline bool operator ==(const value & v) const noexcept { return operator ==(v.type ()); } */

      /** @note Removed
      virtual value & operator =(const wchar_t *json_text); */

      /**
       * @brief Base class for iterators
       */
      template <class Iterator,
                class Category,
                class T,
                class Distance = std::ptrdiff_t,
                class Pointer = T*,
                class Reference = T& > class iterator
          : public std::iterator<Category, T, Distance, Pointer, Reference>
      {
      public:
        /**
         * @brief Default constructor
         */
        iterator ()
        {}

        /**
        * @brief Point constructor
        * @param Set to iterator to start at the element pointed by parameter it
        */
        iterator (Iterator it)
          : _it (it)
        {}

        /**
         * @brief Copy constructor
         * @param Iterator to copy
         */
        iterator (const iterator & other)
          : _it (other._it)
        {}

        /**
         * @brief Destructor
         */
        virtual ~iterator () = default;

        /**
         * @brief Pre increment
         * @return iterator
         */
        inline const iterator &
        operator ++()
        {
          ++_it;
          return *this;
        }

        /**
         * @brief Post increment
         * @return iterator
         */
        iterator
        operator ++(int)
        {
          iterator it (*this);
          ++(*this);
          return it;
        }

        /**
         * @brief Is equal
         * @param Iterator to compare
         * @return iterator
         */
         inline bool
         operator ==(const iterator &rhs) const noexcept
         { return _it == rhs._it; }

        /**
         * @brief Is not equal
         * @param Iterator to compare
         * @return iterator
         */
         inline bool
         operator !=(const iterator &rhs) const noexcept
         { return ! operator ==(rhs); }

      protected:
         /**
          * @brief Iterator
          */
         Iterator _it;
      };  // Class iterator

    protected:

      /**
       * @brief The _sc enum Structural characters.
       */
      enum _sc
      {
        begin_object    = 123,  // '{'
        end_object      = 125,  // '}'
        begin_array     = 91,   // '[',
        end_array       = 93,   // ']',
        name_separator  = 58,   // ':',
        value_separator = 44,   // ',',
        double_quote    = 34    // "
      };

      /**
       * @brief The _ws enum Control, white space and other characters.
       */
      enum _ws
      {
        tab   = 9,    // \t Horizontal tab
        lf    = 10,   // \n Line feed or New line
        cr    = 13,   // \r Carriage return
        us    = 31,   // Unit separator
        space = 32,   // ' ' Space
        rs    = 92    // \ Reverse solidus
      };

      /**
       * @brief The literal enum
       */
      enum _literal
      {
        no_literal  = 0,
        true_value  = 1,
        false_value = 2,
        null_value  = 3
      };

      /**
       * @brief _literal_value
       */
      static const struct literal_value
      {
        const wchar_t * const str_value;
        const size_t len;
        const value::_literal ltr_value;

      } __ltr_value[];

      /**
       * @brief _readp
       */
      const wchar_t *_readp;

      /**
       * @todo json* --> value*
       * @brief _parent
       */
      value *_parent;

      /**
       * @brief _key
       */
      const wchar_t * _key;

      /**
       * @brief _index
       */
      size_t _index;

      /**
       * @brief Holds the pritive value for JSON object. null is constant.
       */
      mutable
      union primitive_value
      {
        bool          boolean;
        const wchar_t *string;
        long double   long_double;

        primitive_value (bool b) : boolean (b) {}
        primitive_value (long double ld) : long_double (ld) {}
        primitive_value (const wchar_t *s = nullptr) : string (s) {}

      } _value;

      /**
       * @brief _parse
       * @param json
       * @return
       * @see https://tools.ietf.org/html/rfc7159
       * @see https://datatracker.ietf.org/doc/html/rfc8259
       * @see https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/JSON/parse
       * @see http://www.ecma-international.org/ecma-262/5.1/#sec-15.12.2
       * @see https://en.wikipedia.org/wiki/List_of_Unicode_characters
       * @see http://en.cppreference.com/w/cpp/language/types
       */
      virtual const wchar_t *
      _parse (const wchar_t *json_text) = 0;

      /**
       * @brief _assign
       * @param nv
       * @return
       */
      value &
      _assign (value *nv);

      /**
       * If value has parent object, assign to new value to this->_parent->[key],
       * otherwise assign new value to Value object itself.
       *
       * @brief assign
       * @param nv
       * @return
       */
      value &
      _assign (const value & nv);

      /**
       * Assign Value object to member_list or element_list.
       *
       * @brief _assign
       * @param Old value
       * @param New value
       * @return
       */
      virtual value &
      _assign (value *, value *) = 0;

      /**
       * If value has parent object, remove value from it's parent,
       * otherwise do nothing.
       *
       * @brief _assign
       * @param u
       * @return
       */
      value &
      _assign (const undefined &) noexcept;

      /**
       * @brief _set_key
       * @param key
       * @param charc
       **/
      inline void
      _set_key (const wchar_t *const key, size_t charc) noexcept
      {
         delete[] _key;
         _key = wcsncpy (new wchar_t[charc + 1] (), key, charc);
      }

      /**
       * @brief _set_key
       * @param target
       * @param keyp
       * @param charc
       */
      inline static void
      _set_key (value *target, const wchar_t *keyp, size_t charc)
      { target->_set_key (keyp, charc); }

      /**
       * @brief _set_index
       * @param v
       * @param index
       */
      inline static void
      _set_index (value *v, const size_t & index)
      { v->_index = index; }

      /**
       * @brief Set the owner object
       * @param The child object
       * @param The parent object
       */
      inline static void
      _set_parent (value *child, value *parent)
      { child->_parent = parent; }

      /**
       * @brief _erase
       * @param parent
       * @param v
       * @return
       */
      inline static value &
      _erase (value *parent,  const value & v)
      { return parent->_erase (v); }

      /**
       * @brief str_length
       * @return
       */
      virtual size_t
      _str_length () const noexcept = 0;

      /**
       * @brief Generate parseable json text
       * @param If present, json text will be written to the memory pointed by offset.
       *  This is when called by parent object.
       * @return Generated text
       */
      virtual const wchar_t *
      _to_string (wchar_t *offset = nullptr) const = 0;

      /**
       * @brief _clone Called by copy constructor
       * @param other
       * @return
       */
      virtual value *
      _clone (const value &other) = 0;

      /**
       * @brief _look_ahead Move read pointer to next non-white space character
       */
      inline const wchar_t *
      _look_ahead () noexcept
      {
        while (*_readp != 0 && _is_whitespace (*_readp))
          _readp++;

        return _readp;
      }

      /**
       * @brief _is_whitespace
       * @param c
       * @return
       */
      static inline bool
      _is_whitespace (int c) noexcept
      {
        return c == _ws::tab
            || c == _ws::lf
            || c == _ws::cr
            || c == _ws::space;
      }

      /**
       * @brief _str_append Copy src to dst.
       * Move dst right after the last copied character.
       * @param dst Destination string
       * @param src Source string
       * @param charc Number of characters to copy
       * @return Pointer to the location where the next write starts
       * @todo Move definition to json_value.cpp
       */
      static wchar_t *
      _str_append (wchar_t *dst, const wchar_t *src, size_t charc) noexcept;

      /**
       * @brief Double quote value type of string_t
       * @param Pointer to the allocated memory where the string is written
       * @param The value to quote
       * @return Pointer to the location where the next write starts
       * @todo Move definition to json_value.cpp
       */
      static wchar_t *
      _quote_value (wchar_t *dst, const value *v) noexcept;

      /**
       * @brief _string Read in string.
       * If no opening quote, return 0.
       * If no closing quote or unescaped unicode control character (0-31) met,
       * return number characters read as a negative value. For example "\"xx\u001F\"" = -3
       * Else return number of characters read + 2 (quotes). For example "\"xxx\"" = 5
       * @param endc Last character read
       * @return Number of characters read, including quotes
       */
      long long _string (wchar_t &endc) const noexcept;

      /**
       * @brief _unquoted_string
       * @param endc
       * @return
       */
      static long long _unquoted_string (const wchar_t * const startp, const wchar_t *readp, wchar_t &endc) noexcept;

      /**
       * @brief _is_literal Detect if _readp points to "true", "false" or "null".
       * @param try_
       * @return
       */
      value::_literal
      _is_literal (const int _try = 0) const noexcept;

      /**
       * @brief _at json::object behavior: if key does not exist, assign key with value of type undefined.
       * @param key
       * @return
       */
      virtual value &
      _at (const wchar_t *const key)  = 0;

      /**
       * @brief _at
       * @param key
       * @return
       */
      const virtual value &
      _at (const wchar_t *const key) const  = 0;

      /**
       * @brief _at
       * @param index
       * @return
       */
      virtual value &
      _at (size_t index) = 0;

      /**
       * @brief _at
       * @param index
       * @return
       */
      virtual const value &
      _at (size_t index) const = 0;

      /**
       * @brief _clear
       */
      virtual void _clear () = 0;

      /**
       * @brief _erase
       * @param v
       * @return
       */
      virtual value &
      _erase (const value &v) noexcept = 0;

      friend const wchar_t * __call__parse (value *, const wchar_t * const);
      friend value & __call__assign (value *, value *, value *);
      friend size_t __call__str_length (const value *);
      friend const wchar_t * __call_str_value (const value *, wchar_t * const);

    };  // Class value

    inline const wchar_t * __call__parse (value *v, const wchar_t *readp) { return v->_parse (readp); }
    inline const wchar_t * __call_str_value (const value *v, wchar_t *offset) { return v->_to_string (offset); }
    inline value & __call__assign (value *parent, value *ov, value*nv) { return parent->_assign (ov, nv); }
    inline size_t __call__str_length (const value *parent) { return parent->_str_length (); }
  } // Namespace json
} // Namespace format
#endif // JSON_VALUE_H
