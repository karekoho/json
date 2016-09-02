#ifndef NULL_H
#define NULL_H

#include "json_value.h"

/**
 * @brief The Null class
 */
class Null : public Value {
  public:

  /**
   * @brief Null
   */
  Null () : Value::Value (0, 0, 0) {}

  /**
   * @brief Null
   * @param json
   */
  Null (const char *json = 0) : Value::Value (json) {}

  /**
   * @brief Null
   * @param endp
   * @param parent
   * @param charc
   */
  Null (const char *endp, Value *parent, size_t charc = 0) : Value::Value (endp, parent, charc) {}

protected:

  virtual const Value &_at (const char *) const { return *this; }

public:
  /**
   * @brief parse
   * @param json
   * @return
   */
  virtual inline const char *parse (const char *json) { return json + 4; }

  /**
   * @brief at
   * @param key
   * @return
   */
  virtual inline const Value & at (const char *key) const { return *this; }

  /**
   * @brief type
   * @return
   */
  virtual inline Value::object_type type () const { return Value::object_type::null; }

  /**
   * @brief size
   * @return
   */
  virtual inline size_t size () const { return 1; }

  /**
   * @brief Value
   * @return
   */
  inline const char * Value () const { return ""; }

  // Value interface

};
#endif // NULL_H
