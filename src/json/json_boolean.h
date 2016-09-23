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
   * @param parent
   * @param value
   */
  Boolean (JSON *parent, const bool value) : Value::Value (parent), _boolean_value (value) {}

  /**
   * @brief Boolean
   * @param other
   */
  Boolean (const Boolean &other) = default;

  /**
   * @brief clone
   * @param other
   * @return
   */
  virtual Value * _clone () { return new Boolean (*this); }

public:

  /**
   * @brief parse
   * @param json
   * @return
   */
  virtual const char *parse (const char *json) { return json + (_boolean_value == true ? 4 : 5); }

  /**
   * @brief at
   * @param key
   * @return
   */
  virtual inline Value & at (const char *)  { return *this; }

  /**
   * @brief at
   * @return
   */
  virtual Value & at (size_t) { return *this; }

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
   * @brief operator =
   * @param b
   * @return
   */
  inline Value & operator =(Boolean & b) { return _assign (b); }

  /**
   * @brief operator =
   * @param v
   * @return
   */
  inline Value & operator =(Value & v) { return _assign (v); }

  /**
   * @brief assign
   * @param nv
   * @return
   */
  Value & _assign (Boolean & nv);

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

  /**
   * @brief _assign
   * @param nv
   * @return
   */
  virtual Value & _assign (Value & nv) { return Value::_assign (nv); }

  /**
   * @brief _clear
   */
  virtual void _clear () {}

  virtual Value *_clone (const Value &other) override
  {
    return this;
  }
};

#endif // BOOLEAN_H
