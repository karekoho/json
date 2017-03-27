#ifndef NUMBER_H
#define NUMBER_H

#include "json_leaf.h"
#include "json_json.h"

#include <cmath>

namespace format
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
     * @param d
     */
    number (double d);

    /**
     * @brief Number
     * @param json
     */
    number (const wchar_t *json);

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
    clone () const
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
     * @brief value
     * @return
     */
    inline double
    get () const
    { return _double_valuep == 0 ?  _calculate (_digitp) : _double_value; }

    /**
     * @brief strLength
     * @return
     */
    virtual size_t
    str_length () const noexcept override;

    /**
     * @brief strValue
     * @return
     */
    virtual const wchar_t *
    str_value (wchar_t * = 0) const override;

  protected:
    /**
     * @brief _value
     */
    mutable double _double_value;

    /**
     * @brief _double_valuep
     */
    mutable double *_double_valuep;

    /**
     * @brief _digitp
     */
    const wchar_t *_digitp[2][2];

    /**
     * @brief _is_double
     */
    bool _is_double;

    /**
     * @brief _double_str
     */
    mutable std::wstring _double_str;

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
    _parse (const wchar_t *json) override;

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
    double
    _calculate (const wchar_t * const digitp[2][2]) const;

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
    { return _parent  ? _parent->_assign (this, new number (nv)) : *(_clone (nv)); }

    /**
     * @brief _clear
     */
    virtual void
    _clear ();

    /**
     * @brief _to_string
     */
    inline void
    _to_string () const noexcept
    {
      if (_double_str.empty ())
        _double_str = _is_double
            ? std::to_wstring (_double_value)
            : std::to_wstring ((long) _double_value);
    }

    /**
     * @brief _clone
     * @return
     */
    virtual value *
    _clone (const value &other);
  }; // Class boolean

  inline number *
  __call_number (json *parent)
  { return new number (parent); }
} // Namespace Format
#endif // NUMBER_H
