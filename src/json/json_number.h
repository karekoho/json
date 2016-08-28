#ifndef NUMBER_H
#define NUMBER_H

#include "json_json.h"

/**
 * @brief The number class
 */
class Number : public json {

  explicit Number (const double value = 0)
    : json::json (0),
      _double_value (value),
      _digitp {{0,0,0},{0,0,0}},
      _exp (0)
  {
  }

  Number (const char *json)
    : json::json (json),
      _double_value (0),
      _digitp {{0,0,0},{0,0,0}},
      _exp (0)
  {
  }

  Number (const char *endp, value *parent = 0, size_t charc = 0)
    : json::json (endp, parent, charc),
      _double_value (0),
      _digitp {{0,0,0},{0,0,0}},
      _exp (0)
  {
  }

  /// value interface
  virtual const char *parse (const char *json) { return json; }
  virtual const value & at (const char *key) const { return *this; }
  virtual inline otype type () const { return value::otype::number; }
  virtual size_t size () const { return _double_value == 0 ? 0 : 1; }

  /**
     * @brief value
     * @return
     */
  double value () const { return _double_value; }

protected:
  /**
     * @brief _value
     */
  mutable double _double_value;
  /**
     * @brief _digitp
     */
  mutable const char *_digitp[2][3];

  /**
     * @brief _exp Power of 10
     */
  unsigned long int _exp;
};

#endif // NUMBER_H
