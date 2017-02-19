#ifndef NUMBER_H
#define NUMBER_H

#include "json_leaf.h"
#include "json_json.h"

#include <cmath>

#define DOUBLE 0
#define EXP 1

#define START 0
#define END 1

#ifdef UNIT_TEST
  class json_number_test;
#endif
namespace Format {
/**
 * @brief The number class
 */
class Number : public Leaf
{
#ifdef UNIT_TEST
  friend class json_number_test;
#endif

public:

  /**
   * @brief Number
   */
  Number ();

  /**
   * @brief Number
   * @param value
   */
  explicit Number (const double value);

  /**
   * @brief Number
   * @param json
   */
  Number (const wchar_t *json);

  /**
   * @brief Number
   * @param parent
   */
  Number (json *parent);

  /**
   * @brief Number
   * @param other
   */
  Number (const Number &other);

  /**
   * @brief Number
   * @param ov
   * @param nv
   */
  Number (const Value *ov, const Number &nv);

  /**
   * @brief clone
   * @param other
   * @return
   */
  virtual Value *
  clone () const
  { return new Number (*this); }

  /**
   * @brief clone
   * @param ov
   * @return
   */
  virtual Value *
  clone (const Value *ov) const override
  { return new Number (ov, *this); }

  /**
   * @brief parse
   * @param json
   * @return
   */
  virtual const wchar_t *
  parse (const wchar_t *json);

  /**
   * @brief type
   * @return
   */
  virtual object_type
  type () const
  { return Value::object_type::number_t; }

  /**
   * @brief operator =
   * @param n
   * @return
   */
  inline Value &
  operator =(const Number & n)
  { return _assign (n);  }

  /**
   * @brief operator =
   * @param v
   * @return
   */
  inline Value &
  operator =(const Value & v)
  { return Value::_assign (v);  }

  /**
   * @brief value
   * @return
   */
  inline double
  value () const
  {
    return _double_valuep == 0 ?  _calculate (_digitp) : _double_value; }

  /**
   * @brief strLength
   * @return
   */
  virtual size_t
  strLength () const noexcept override;

  /**
   * @brief strValue
   * @return
   */
  virtual const wchar_t *
  strValue (wchar_t * = 0) const;

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
   * @brief _double_str
   */
  mutable std::wstring _double_str;

  /**
   * @brief _digits If >= 1 digits found, return last character. Else return -1.
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
  Value &
  _assign (const Number & nv)
  { return _parent  ? _parent->_assign (this, new Number (this, nv)) : *(clone (nv)); }

  /**
   * @brief _clear
   */
  virtual void
  _clear ();

  /**
   * @brief _clone
   * @return
   */
  virtual Value *
  clone (const Value &other);
};
}
#endif // NUMBER_H
