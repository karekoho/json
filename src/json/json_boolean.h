#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "json_value.h"

#ifdef UNIT_TEST
  class json_boolean_test;
#endif
/**
 * @brief The boolean class
 */
class Boolean : public Value
{
#ifdef UNIT_TEST
  friend class json_boolean_test;
#endif
  public:

  Boolean () : Value::Value (), _boolean_value (false) {}

  /**
   * @brief Boolean
   * @param value
   */
  Boolean (const bool value) : Value::Value (), _boolean_value (value) {}

  /**
   * @brief Boolean
   * @param json
   */
  // Boolean (const char *json) : Value::Value (json), _boolean_value (false) {}

  /**
   * @brief Boolean
   * @param parent
   * @param value
   */
  Boolean (JSON *parent, const bool value) : Value::Value (parent), _boolean_value (value) {}

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
  Value & assign (Boolean & nv);

  /**
   * @brief value
   * @return
   */
  inline bool value () const { return _boolean_value; }

  /**
   * @brief setValue
   * @param value
   */
  void setValue (bool value) { _boolean_value = value; }

protected:

  /**
   * @brief _boolean_value
   */
  bool _boolean_value;

  /**
   * @brief _at
   * @param key
   * @return
   */
  virtual inline Value &_at (const char *)  { return *this; }
};

#endif // BOOLEAN_H
