#ifndef UNDEFINED_H
#define UNDEFINED_H

#include "json_value.h"

/**
 * @brief The undefined class
 */
class Undefined : public Value {
  public:

  Undefined () : Value::Value (0, 0) {}
  Undefined (const char *json) : Value::Value (json) {}
  Undefined (Value *parent, size_t charc = 0) : Value::Value (parent,charc) {}

  inline const char * value () const { return "undefined"; }

  /// value interface
  virtual const char *parse (const char *json) { return json + _charc; }
  virtual inline const Value & at (const char *) const { return *this; }
  virtual inline object_type type () const { return Value::object_type::undefined; }
  virtual inline size_t size () const { return 0; }

protected:
  virtual const Value &_at(const char *) const { return *this; }
public:



  // Value interface

};

#endif // UNDEFINED_H
