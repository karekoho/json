#ifndef NUMBER_H
#define NUMBER_H

#include "json_value.h"
#ifdef UNIT_TEST
class json_number_test;
#endif
/**
 * @brief The number class
 */
class Number : public value
{
#ifdef UNIT_TEST
friend class json_number_test;
#endif
public:
  explicit Number (const double value = 0)
    : value::value (0),
      _double_value (value),
      _double_valuep (&_double_value),
      _digitp {{0,0},{0,0}}
     // _llong_exp (0),
     //_llong_expp (0)
  {
  }

  Number (const char *json)
    : value::value (json),
      _double_value (0),
      _double_valuep (0),
      _digitp {{0,0},{0,0}}
      // _llong_exp (0),
      //_llong_expp (0)
  {
  }

  Number (const char *endp, value *parent = 0, size_t charc = 0)
    : value::value (endp, parent, charc),
      _double_value (0),
      _double_valuep (0),
      _digitp {{0,0},{0,0}}
      // _llong_exp (0),
      //_llong_expp (0)
  {
  }

  /// value interface
  virtual const char *parse (const char *json); // { return json; }
  virtual const value & at (const char *key) const { return *this; }
  virtual inline otype type () const { return value::otype::number; }
  virtual size_t size () const { return _double_value == 0 ? 0 : 1; }

  /**
     * @brief value
     * @return
     */
  double value () const { return _double_valuep == 0 ?  _calculate (_digitp) : _double_value; }

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
   * @brief _digitp [][3] unused
   */
  mutable const char *_digitp[2][2];

  /**
   * @brief _exp Power of 10
   */
  // long long _llong_exp;

  /**
   * @brief _llong_expp
   */
  // const long long *_llong_expp;

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
