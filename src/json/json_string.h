#ifndef STRING
#define STRING

#include "json_value.h"

/**
 * @brief The string class
 */
class String : public Value {

  public:

  String (const char *json) : Value::Value (json) {}
  String (const char *endp, Value *parent = 0, size_t charc = 0) : Value::Value (endp, parent, charc) {}

  virtual const char *
  parse (const char *json)
  {
//      if (_parent == 0) { TODO: validate }
    _readp = json;

    return json + _charc;
  }

  /// value interface
  virtual inline const Value & at (const char *key) const { return *this; }

  virtual inline object_type type () const { return Value::object_type::string; }

  virtual inline size_t size () const { return _string_value.length (); }

protected:
  virtual const Value &_at(const char *key) const;
public:

  const char *
  Value () const {

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

  // Value interface

}; /// class string

#endif // STRING

