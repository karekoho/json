#ifndef STRING
#define STRING

#include "json_leaf.h"

namespace format
{
  namespace json
  {
    #ifdef UNIT_TEST
      class json_string_test;
    #endif
    /**
     * @brief The string class
     */
    class string : public leaf
    {
      friend string * __call_string (json *parent, size_t charc);

    #ifdef UNIT_TEST
      friend class json_string_test;
    #endif

      public:
      /**
       * @brief String
       */
      string ();

      /**
       * @brief string
       * @param json
       */
      string (const wchar_t * const string_text);

      /**
       * @brief String
       * @param other
       */
      string (const string & other);

      /**
       * @brief ~string
       */
      virtual ~string () override;

      /**
       * @brief clone
       * @param other
       * @return
       */
      virtual inline value *
      clone () const override
      { return new string (*this); }

      /**
       * @brief type
       * @return
       */
      virtual inline value_t
      type () const noexcept override
      { return value::value_t::string_t; }

      /**
       * @brief value
       * @return
       */
      inline const wchar_t *
      value () const noexcept
      { return _to_string (); }

      /**
       * @deprecated Use value instead
       * @return
       */
      inline const wchar_t *
      get () const noexcept
      { return value (); }

      /**
       * @brief length
       * @return
       */
      inline size_t
      length () const noexcept
      { return _charc; }

      /**
       * @note Removed
       * @brief operator =
       * @param s
       * @return
       *
      inline value &
      operator =(const string & s)
      { return _assign (s); } */

      /**
       * @note Removed
       * @brief operator =
       * @param s
       * @return
       *
      virtual value &
      operator =(const wchar_t * const s) override; */

    protected:
      /**
       * @brief Pointer to the beginning of the string in JSON text
       */
      const wchar_t *_startp;

      /**
       * @brief String content
       */
      const wchar_t * _string_value;

      /**
       * @brief Length of the unserialized string, i.e. without quotes
       */
      size_t _charc;

      /**
       * @brief string
       * @param parent
       * @param charc
       */
      string (json *parent, size_t charc);

      /**
       * @brief parse
       * @param json
       * @return
       */
      virtual const wchar_t *
      _parse (const wchar_t * const json_text) override;

      /**
       * @todo To be removed
       * @brief _clear
       */
      virtual void
      _clear () override
      { /* nop */ }

      /**
       * @brief _clone
       * @return
       */
      virtual class value *
      _clone (const class value &) override
      { return this; }

      /**
       * @brief strValue
       * @return
       */
      virtual inline const wchar_t *
      _to_string (wchar_t * = nullptr) const override
      { return _string_value == nullptr ? L"" : _string_value; }

      /**
       * @brief str_length
       * @return
       */
      virtual inline size_t
      _str_length () const noexcept override
      { return _charc + 2; }

      /**
       * @todo To be removed
       * @brief _get
       */
      virtual inline void
      _get () const noexcept override
      { /* nop */ }

      /**
       * @note Removed
       * @brief assign
       * @param nv
       * @return
       *
      value &
      _assign (const string & nv); */

    private:
      /**
       * @brief __string Read characters until character is < 32 or \".
       * If last charater is \0, return string length,
       * otherwise return string as negative value.
       * @return Number of characters read
       */
      long long
      __string (wchar_t & endc) const noexcept;

      /**
       * @brief __assign
       * @param offset
       * @param charc
       * @return
       */
      const wchar_t * __assign (const wchar_t * const offset, size_t charc);

    }; // Class string

    /**
     * @brief call_string
     * @param parent
     * @param charc
     * @return
     */
    inline string *
    __call_string (json *parent, size_t charc)
    { return new string (parent, charc); }
  } // Namespace json
} // Namespace format
#endif // STRING

