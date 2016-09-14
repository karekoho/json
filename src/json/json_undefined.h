#ifndef UNDEFINED_H
#define UNDEFINED_H

#include "json_value.h"

/**
 * @brief The undefined class
 */
class Undefined : public Value
{
  public:

  Undefined () : Value::Value () {}

  // Undefined (const char *json) : Value::Value (json) {}  // Not needed

  Undefined (JSON *parent) : Value::Value (parent) {}

  inline const char * value () const { return "undefined"; }

  virtual const char *parse (const char *json) { return json; }

  virtual inline Value & at (const char *)  { return *this; }

  virtual inline object_type type () const { return Value::object_type::undefined; }

  virtual inline size_t size () const { return 0; }

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
  Value & assign (Undefined & nv);

protected:

  virtual Value &_at (const char *) { return *this; }

};

#endif // UNDEFINED_H
