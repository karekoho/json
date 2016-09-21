#ifndef NUMBER_H
#define NUMBER_H

#include "json_value.h"
#include "json_json.h"

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
class Number : public Value
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
   * @brief ~Number
   */
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
  virtual Value & at (const char *) { return *this; }

  /**
   * @brief at
   * @return
   */
  virtual Value & at (size_t) { return *this; }

  /**
   * @brief type
   * @return
   */
  virtual object_type type () const { return Value::object_type::number; }

  /**
   * @brief size
   * @return
   */
  virtual size_t size () const { return _double_valuep == 0 ? 0 : 1; }

  /**
   * @brief _assign
   * @param nv
   * @return
   */
  virtual Value & _assign (Value & nv) { return Value::_assign (nv); }

  /**
   * @brief operator =
   * @param n
   * @return
   */
  inline Value & operator =(Number & n) { return _assign (n);  }

  /**
   * @brief operator =
   * @param v
   * @return
   */
  inline Value & operator =(Value & v) { return _assign (v);  }

  /**
   * @brief value
   * @return
   */
  inline double value () { return _double_valuep == 0 ?  _calculate (_digitp) : _double_value; }

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
  double _calculate (const char * const digitp[2][2]);

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

  /**
   * @brief _at
   * @return
   */
  virtual inline Value &_at (const char *) { return *this; }

  /**
   * @brief _assign
   * @param nv
   * @return
   */
  Value & _assign (Number & nv);

  /**
   * @brief _copy
   * @param nv
   */
  void _copy (const Number &nv);

protected:
  virtual void _clear() override
  {
  }
};

#endif // NUMBER_H
