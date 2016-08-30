#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "json_json.h"
/**
 * @brief The boolean class
 */
class Boolean : public json {
  public:

  explicit Boolean (const bool value)
    : json::json (0, 0, value == true ? 4 : 5),
      _boolean_value (value)
  {
  }

  Boolean (const char *json)
    : json::json (json),
      _boolean_value (false)
  {
  }

  Boolean (const char *endp, value *parent = 0, size_t charc = 0)
    : json::json (endp, parent, charc),
      _boolean_value (false)
  {
  }

  /// value interface
  virtual inline const char *parse (const char *json) { return json + _charc;}
  virtual inline const value & at (const char *key) const { return *this; }
  virtual inline otype type () const { return value::otype::boolean; }
  virtual inline size_t size () const { return 0;}

  /**
   * @brief value
   * @return
   */
  inline bool value () const { return _boolean_value; }

protected:

  bool _boolean_value;
};

#endif // BOOLEAN_H
