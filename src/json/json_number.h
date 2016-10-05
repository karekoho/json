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
  Number (const char *json);

  /**
   * @brief Number
   * @param parent
   */
  Number (JSON *parent);

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
  Number (Value *ov, const Number &nv);

  /**
   * @brief clone
   * @param other
   * @return
   */
  virtual Value *
  clone ()
  { return new Number (*this); }

  /**
   * @brief clone
   * @param ov
   * @return
   */
  virtual Value *
  clone (Value *ov) override
  { return new Number (ov, *this); }

  /**
   * @brief parse
   * @param json
   * @return
   */
  virtual const char *parse (const char *json);

  /**
   * @brief type
   * @return
   */
  virtual object_type
  type () const
  { return Value::object_type::number; }

  /**
   * @brief _assign
   * @param nv
   * @return
   */
  virtual Value &
  _assign (Value & nv)
  { return Value::_assign (nv); }

  /**
   * @brief operator =
   * @param n
   * @return
   */
  inline Value &
  operator =(Number & n)
  { return _assign (n);  }

  /**
   * @brief operator =
   * @param v
   * @return
   */
  inline Value &
  operator =(Value & v)
  { return _assign (v);  }

  /**
   * @brief value
   * @return
   */
  inline double
  value ()
  { return _double_valuep == 0 ?  _calculate (_digitp) : _double_value; }

  /**
   * @brief strLength
   * @return
   */
  virtual size_t strLength () const noexcept override;

  /**
   * @brief strValue
   * @return
   */
  virtual const char *strValue () const;

protected:

  /**
   * @brief _value
   */
  double _double_value;

  /**
   * @brief _double_valuep
   */
  double *_double_valuep;

  /**
   * @brief _digitp
   */
  const char *_digitp[2][2];

  /**
   * @brief _double_str
   */
  mutable std::string _double_str;

  /**
   * @brief _digits If >= 1 digits found, return last character. Else return -1.
   * @return
   */
  int _digits () noexcept;

  /**
   * @brief _frag
   * @return
   */
  const char * _frag ();

  /**
   * @brief _exp_
   * @return
   */
  const char * _exp ();

  /**
   * @brief _calculate
   * @param digitp
   * @return
   */
  double _calculate (const char * const digitp[2][2]);

  /**
   * @brief _atof
   * @param digitp
   * @return
   */
  inline double
  _atof (const char * const digitp[2]) const
  { return std::atof (std::string (digitp[0], digitp[1]).c_str ()); }

  /**
   * @brief _atoll
   * @param digitp
   * @return
   */
  inline long long
  _atoll (const char * const digitp[2]) const
  { return std::atoll (std::string (digitp[0], digitp[1]).c_str ()); }

  /**
   * @brief _assign
   * @param nv
   * @return
   */
  Value &
  _assign (Number & nv)
  { return _parent  ? _parent->assign (this, new Number (nv)) : *(clone (nv)); }

  /**
   * @brief _clear
   */
  virtual void _clear ();

  /**
   * @brief _clone
   * @return
   */
  virtual Value *clone (const Value &other);
};

#endif // NUMBER_H
