#ifndef UNDEFINED_H
#define UNDEFINED_H

#include "json_value.h"

/**
 * @brief The undefined class
 */
class Undefined : public value {
  public:

  Undefined () : value::value (0, 0, 0) {}
  Undefined (const char *json) : value::value (json) {}
  Undefined (const char *endp, value *parent = 0, size_t charc = 0) : value::value (endp, parent,charc) {}

  /// value interface
  virtual const char *parse (const char *json) { return json + _charc; }
  virtual inline const value & at (const char *key) const { return *this; }
  virtual inline otype type () const { return value::otype::undefined; }
  virtual inline size_t size () const { return 0; }

  inline const char * value () const { return "undefined"; }
}; /// class undefined


#endif // UNDEFINED_H
