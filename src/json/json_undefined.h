#ifndef UNDEFINED_H
#define UNDEFINED_H

#include "json_value.h"

/**
 * @brief The undefined class
 */
class Undefined : public Value {
  public:

  Undefined () : Value::Value () {}
  Undefined (const char *json) : Value::Value (json) {}
  Undefined (JSON *parent) : Value::Value (parent) {}

  inline const char * value () const { return "undefined"; }

  /// value interface
  virtual const char *parse (const char *json) { return json + _length; }
  virtual inline Value & at (const char *)  { return *this; }
  // virtual inline const Value & at (const char *) const { return *this; }
  virtual inline object_type type () const { return Value::object_type::undefined; }
  virtual inline size_t size () const { return 0; }

protected:
  virtual Value &_at (const char *) { return *this; }
public:



  // Value interface

};

#endif // UNDEFINED_H
