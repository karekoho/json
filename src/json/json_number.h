#ifndef NUMBER_H
#define NUMBER_H

#include "json_value.h"

#define FLOAT 0
#define EXP 1

#define START 0
#define END 1

#ifdef UNIT_TEST
class json_number_test;
#endif

/**
 * @brief The number class
 */
class Number : public Value
{
#ifdef UNIT_TEST
friend class json_number_test;
#endif

public:

  Number ()
  : Value::Value (),
    _double_value (0),
    _double_valuep (&_double_value),
    _digitp {{ 0, 0 },{ 0, 0 }}
  {
  }

  explicit Number (const double value)
    : Value::Value (),
      _double_value (value),
      _double_valuep (&_double_value),
      _digitp {{ 0, 0 },{ 0, 0 }}
  {
  }

  Number (const char *json)
    : Value::Value (json),
      _double_value (0),
      _double_valuep (0),
      _digitp {{ 0, 0 },{ 0, 0 }}
  {
  }

  Number (Value *parent)
    : Value::Value (parent),
      _double_value (0),
      _double_valuep (0),
      _digitp {{ 0, 0 },{ 0, 0 }}
  {
  }

  virtual ~Number () {}

  /**
   * @brief parse
   * @param json
   * @return
   */
  virtual const char *parse (const char *json);

  /**
   * @brief at
   * @param key
   * @return
   */
  virtual inline const Value & at (const char *) const { return *this; }

  /**
   * @brief type
   * @return
   */
  virtual inline object_type type () const { return Value::object_type::number; }

  /**
   * @brief size
   * @return
   */
  virtual inline size_t size () const { return _double_valuep == 0 ? 0 : 1; }

  /**
   * @brief value
   * @return
   */
  inline double value () const { return _double_valuep == 0 ?  _calculate (_digitp) : _double_value; }

protected:

  virtual inline  const Value &_at (const char *) const { return *this; }

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
  mutable const char *_digitp[2][2];

  /**
   * @brief _digits If >= 1 digits found, return last character. Else return -1.
   * @return
   */
  int _digits ();

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
  double _calculate (const char * const digitp[2][2]) const;

  /**
   * @brief _atof
   * @param digitp
   * @return
   */
  double _atof (const char * const digitp[2]) const;

  /**
   * @brief _atoll
   * @param digitp
   * @return
   */
  long long _atoll (const char * const digitp[2]) const;


};

#endif // NUMBER_H
