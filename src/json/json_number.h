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
       * @param l
       */
      number (long long l);

      /**
       * @brief number
       * @param d
       */
      number (double d);

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
      virtual value *
      clone () const override
      { return new number (*this); }

      /**
       * @brief type
       * @return
       */
      virtual value_t
      type () const noexcept override
      { return value::value_t::number_t; }

      /**
       * @brief operator =
       * @param n
       * @return
       */
      inline value &
      operator =(const number & n)
      { return _assign (n);  }

      /**
       * @brief operator =
       * @param d
       * @return
       */
      virtual inline value &
      operator =(double d) noexcept override
      {
        _double_value   = d;
        _double_valuep  = & _double_value;
        _primitive.double_value = d;
        _is_floating_point = true;
        return __clear_strp ();
      }

      /**
       * @brief operator =
       * @param l
       * @return
       */
      virtual inline value &
      operator =(long long l) noexcept override
      {
        _double_value   = l; // FIXME: store integer type in long long
        _double_valuep  = & _double_value;
        _primitive.double_value = l;
        _is_floating_point = false;
        return __clear_strp ();
      }

      /**
       * @brief value
       * @return
       */
      inline double
      get () const
      { return _double_valuep == nullptr ? (_primitive.double_value = _calculate (_digitp)) : _double_value; }

    protected:
      /**
       * TODO: long double
       * @brief _value
       */
      mutable double _double_value;

      /**
       * TODO: get rid of this --> v2.x
       * @brief _double_valuep
       */
      mutable double *_double_valuep;

      /**
       * @brief _digitp
       */
      const wchar_t *_digitp[2][2];

      /**
       * TODO: _is_float
       * @brief _is_double
       */
      bool _is_floating_point;

      /**
       * TODO: get rid of this --> v2.x
       * @brief _double_str
       */
      mutable std::wstring _double_str;

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
      double _calculate (const wchar_t * const digitp[2][2]) const;

      /**
       * @brief _atof
       * @param digitp
       * @return
       */
      inline double
      _atof (const wchar_t * const digitp[2]) const
      { return std::atof (std::string (digitp[0], digitp[1]).c_str ()); }

      /**
       * @brief _atoll
       * @param digitp
       * @return
       */
      inline long long
      _atoll (const wchar_t * const digitp[2]) const
      { return std::atoll (std::string (digitp[0], digitp[1]).c_str ()); }

      /**
       * @brief _assign
       * @param nv
       * @return
       */
      value &
      _assign (const number & nv)
      { return _parent  ? __call__assign (_parent, this, new number (nv)) : *(_clone (nv)); }

      /**
       * @brief _clear
       */
      virtual void
      _clear () override;

      /**
       * @brief strValue
       * @return
       */
      virtual const wchar_t *
      _to_string (wchar_t * = nullptr) const override;

      /**
       * @brief _clone
       * @return
       */
      virtual value *
      _clone (const value & other) override;

      /**
       * @brief str_length
       * @return
       */
      virtual size_t
      _str_length () const noexcept override;

      virtual void
      _get () const override
      { (void) get (); }

    private:
      /**
       * @brief _to_string
       */
      inline void
      __to_string () const noexcept
      {
        if (_double_str.empty ())
          _double_str = _is_floating_point
              ? std::to_wstring (_double_value)
              : std::to_wstring (static_cast<long long> (_double_value));
      }

      /**
       * @brief __clear__digitp
       */
      inline void
      __clear__digitp () noexcept
      {
        _digitp[DOUBLE][START]  = nullptr;
        _digitp[DOUBLE][END]    = nullptr;
        _digitp[EXP][START]     = nullptr;
        _digitp[EXP][END]       = nullptr;
      }

      /**
       * @brief __clear__strp Clear all string related pointers
       * @return
       */
      inline value &
      __clear_strp () noexcept
      {
        _double_str.clear ();
        __clear__digitp ();
        return *this;
      }
    }; // Class number

    inline number *
    __call_number (json *parent)
    { return new number (parent); }
  } // Namespace json
} // Namespace format
#endif // NUMBER_H
