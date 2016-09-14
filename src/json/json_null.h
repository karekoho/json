#ifndef NULL_H
#define NULL_H

#include "json_value.h"

/**
 * @brief The Null class
 */
class Null : public Value
{
  public:

  /**
   * @brief Null
   */
  Null () : Value::Value () {}

  /**
   * @brief Null
   * @param json
   */
  Null (const char *json) : Value::Value (json) {}

  /**
   * @brief Null
   * @param endp
   * @param parent
   * @param charc
   */
  Null (JSON *parent) : Value::Value (parent) {}

protected:

  virtual Value &_at (const char *) { return *this; }

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
  virtual inline Value & at (const char *) { return *this; }

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
  inline const char * value () const { return ""; }

  /**
   * @brief assign
   * @param nv
   * @return
   */
  virtual Value & assign (Value & nv) { return Value::assign (nv); }

  /**
   * @brief assign
   * @param nv
   * @return
   */
  Value & assign (Null & nv);
};
#endif // NULL_H
