#ifndef UNDEFINED_H
#define UNDEFINED_H

#include "json_json.h"

/**
 * @brief The undefined class
 */
class Undefined : public json {
  public:

  Undefined () : json::json (0, 0, 0) {}
  Undefined (const char *json) : json::json (0) {}
  Undefined (const char *endp, value *parent = 0, size_t charc = 0) : json::json (endp, parent, 0) {}

  /// value interface
  virtual const char *parse (const char *json) { return json + _charc; }
  virtual inline const value & at (const char *key) const { return *this; }
  virtual inline otype type () const { return value::otype::undefined; }
  virtual inline size_t size () const { return 0; }

  inline const char * value () const { return "undefined"; }
};

#endif // UNDEFINED_H
