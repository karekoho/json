#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "json_value.h"
/**
 * @brief The boolean class
 */
class Boolean : public Value
{
  public:

  /**
   * @brief Boolean
   * @param value
   */
  explicit Boolean (const bool value) : Value::Value (), _boolean_value (value) {}

  /**
   * @brief Boolean
   * @param json
   */
  Boolean (const char *json) : Value::Value (json), _boolean_value (false) {}

  /**
   * @brief Boolean
   * @param parent
   * @param value
   */
  Boolean (JSON *parent, const bool value) : Value::Value (parent), _boolean_value (value) {}

protected:

  /**
   * @brief _at
   * @param key
   * @return
   */
  virtual inline Value &_at (const char *)  { return *this; }

public:

  /**
   * @brief parse
   * @param json
   * @return
   */
  virtual inline const char *parse (const char *json) { return json + (_boolean_value == true ? 4 : 5); }

  /**
   * @brief at
   * @param key
   * @return
   */
  virtual inline Value & at (const char *)  { return *this; }

  /**
   * @brief type
   * @return
   */
  virtual inline object_type type () const { return Value::object_type::boolean; }

  /**
   * @brief size
   * @return
   */
  virtual inline size_t size () const { return 1;}

  /**
   * @brief value
   * @return
   */
  inline bool Value () const { return _boolean_value; }

protected:

  /**
   * @brief _boolean_value
   */
  bool _boolean_value;
};

#endif // BOOLEAN_H
