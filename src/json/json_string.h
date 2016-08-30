#ifndef STRING
#define STRING

#include "json_value.h"

/**
 * @brief The string class
 */
class String : public value {

  public:

  String (const char *json) : value::value (json) {}
  String (const char *endp, value *parent = 0, size_t charc = 0) : value::value (endp, parent, charc) {}

  virtual const char *
  parse (const char *json)
  {
//      if (_parent == 0) { TODO: validate }
    _readp = json;

    return json + _charc;
  }

  /// value interface
  virtual inline const value & at (const char *key) const { return *this; }

  virtual inline otype type () const { return value::otype::string; }

  virtual inline size_t size () const { return _string_value.length (); }

  const char *
  value () const {

    if (_string_value.empty () && _readp && _charc > 0) {
        _string_value.assign (_readp + 1, _charc - 2);
      }

    return _string_value.c_str ();
  }

protected:
  /**
   * @brief _value
   */
  mutable std::string _string_value;
}; /// class string

#endif // STRING

