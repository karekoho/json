#ifndef UNDEFINED_H
#define UNDEFINED_H

#include "json_value.h"

#ifdef UNIT_TEST
  class json_undefined_test;
#endif

/**
 * @brief The undefined class
 */
class Undefined : public Value
{
#ifdef UNIT_TEST
  friend class json_undefined_test;
#endif

  public:

  Undefined () : Value::Value () {}

  /**
   * @brief Undefined
   * @param parent
   */
  Undefined (JSON *parent) : Value::Value (parent) {}

  /**
   * @brief Undefined
   * @param other
   */
  Undefined (const Undefined &other) = default;

  /**
   * @brief clone
   * @param other
   * @return
   */
  virtual Value * _clone () { return new Undefined (*this); }

  inline const char * value () const { return "undefined"; }

  virtual const char *parse (const char *json) { return json; }

  virtual Value & at (const char *)  { return *this; }

  virtual Value & at (size_t) { return *this; }

  virtual inline object_type type () const { return Value::object_type::undefined; }

  virtual inline size_t size () const { return 0; }

  inline Value & operator =(Value & v) { return _assign (v);  }

protected:

  /**
   * @brief _at
   * @return
   */
  virtual Value &_at (const char *) { return *this; }

  /**
   * @brief assign
   * @param nv
   * @return
   */
  virtual Value & _assign (Value & nv) { return Value::_assign (nv); }

  /**
   * @brief _clear
   */
  virtual void _clear () {}

  virtual Value *_clone(const Value &other) override
  {
    return this;
  }
};

#endif // UNDEFINED_H
