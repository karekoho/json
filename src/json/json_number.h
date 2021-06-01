#ifndef NUMBER_H
#define NUMBER_H

#include "json_leaf.h"
#include "json_json.h"

#include <cmath>

namespace format
{
  namespace json
  {
    #ifdef UNIT_TEST
      class json_number_test;
    #endif

    #define DOUBLE 0
    #define EXP 1

    #define START 0
    #define END 1

    /**
     * @brief The number class
     */
    class number : public leaf
    {
      friend number * __call_number (json *parent);

    #ifdef UNIT_TEST
      friend class json_number_test;
    #endif

    public:
      /**
       * @brief Number
       */
      number ();

      /**
       * @brief number
       * @param i
       */
      number (int i);

      /**
       * @brief number
       * @param l
       */
      number (long long ll);

      /**
       * @brief number
       * @param f
       */
      number (float f);

      /**
       * @brief number
       * @param d
       */
      number (long double ld);

      /**
       * @brief Number
       * @param other
       */
      number (const number &other);

      /**
       * @brief ~number
       * @return
       */
      virtual ~number () override = default;

      /**
       * @brief clone
       * @param other
       * @return
       */
      virtual inline value *
      clone () const override
      { return new number (*this); }

      /**
       * @brief type
       * @return
       */
      virtual inline value_t
      type () const noexcept override
      { return value::value_t::number_t; }

      /**
       * @note Removed
       * @brief operator =
       * @param n
       * @return
       *
      inline value &
      operator =(const number & n)
      { return _assign (n);  } */

      /**
       * @note Removed
       * @brief operator =
       * @param d
       * @return
       *
      virtual inline value &
      operator =(long double d) noexcept override
      {
        _double_value = d;
        _is_floating_point = true;
        __to_string ();
        return __clear_strp ();
      }*/

      /**
       * @note Removed
       * @brief operator =
       * @param l
       * @return
       *
      virtual inline value &
      operator =(long long l) noexcept override
      {
        _double_value = l;
        _is_floating_point = false;
        __to_string ();
        return __clear_strp ();
      }*/

      /**
       * @brief value
       * @return
       */
      inline long double
      get () const
      { return _double_value; }

    protected:
      /**
       * @brief _value
       */
      long double _double_value;

      /**
       * @brief _digitp
       */
      const wchar_t *_digitp[2][2];

      /**
       * @brief _is_double
       */
      bool _is_floating_point;

      /**
       * @brief _double_str
       */
      std::wstring _double_str;

      /**
       * @brief number
       * @param json
       */
      number (const wchar_t * const json);

      /**
       * @brief number
       * @param parent
       */
      number (json *parent);

      /**
       * @brief parse
       * @param json
       * @return
       */
      virtual const wchar_t *
      _parse (const wchar_t * const json) override;

      /**
       * @brief _digits If >= 1 digits found, return first non-digit character.
       * Else return -1.
       * @return
       */
      int
      _digits () noexcept;

      /**
       * @brief _frag
       * @return
       */
      const wchar_t *
      _frag ();

      /**
       * @brief _exp_
       * @return
       */
      const wchar_t *
      _exp ();

      /**
       * @brief _calculate
       * @param digitp
       * @return
       */
      long double _calculate (const wchar_t * const digitp[2][2]);

      /**
       * @brief _atof
       * @param digitp
       * @return
       */
      inline static long double
      _atof (const wchar_t * const digitp[2])
      { return std::strtold (std::string (digitp[0], digitp[1]).c_str (), nullptr); }

      /**
       * @brief _atoll
       * @param digitp
       * @return
       */
      inline static long long
      _atoll (const wchar_t * const digitp[2])
      { return std::atoll (std::string (digitp[0], digitp[1]).c_str ()); }

      /**
       * @note Removed
       * @brief _assign
       * @param nv
       * @return
       *
      value &
      _assign (const number & nv)
      { return _parent  ? __call__assign (_parent, this, new number (nv)) : *(_clone (nv)); } */

      /**
       * @brief _clear
       */
      virtual void
      _clear () override
      { /* nop */ }

      /**
       * @brief _to_string
       * @return
       */
      virtual inline const wchar_t *
      _to_string (wchar_t * = nullptr) const noexcept override
      { return _double_str.c_str (); }

      /**
       * @brief _clone
       * @return
       */
      virtual value *
      _clone (const value &) override
      { /* nop */ }

      /**
       * @brief str_length
       * @return
       */
      virtual inline size_t
      _str_length () const noexcept override
      { return _double_str.length (); }

      /**
       * @todo To be removed
       * @brief _get
       */
      virtual inline void
      _get () const noexcept override
      { _primitive.double_value = get (); }

    private:
      /**
       * @brief __to_string
       */
      inline void
      __to_string () noexcept
      {
        _double_str = _is_floating_point
          ? std::to_wstring (_double_value)
          : std::to_wstring (static_cast<long long> (_double_value));
      }
    }; // Class number

    inline number *
    __call_number (json *parent)
    { return new number (parent); }
  } // Namespace json
} // Namespace format
#endif // NUMBER_H
