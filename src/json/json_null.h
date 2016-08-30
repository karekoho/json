#ifndef NULL_H
#define NULL_H

#include "json_json.h"

/**
 * @brief The null class
 */
class Null : public json {
  public:

  Null () : json::json (0, 0, 4) {}
  Null (const char *json) : json::json (0) {}
  Null (const char *endp, value *parent = 0, size_t charc = 0) : json::json (endp, parent, 4) {}

  /// value interface
  virtual inline const char *parse (const char *json) { return json + 4; }
  virtual inline const value & at (const char *key) const { return *this; }
  virtual inline value::otype type() const { return value::otype::null; }
  virtual inline size_t size() const { return 0; }

  inline const char * value () const { return ""; }
};
#endif // NULL_H
