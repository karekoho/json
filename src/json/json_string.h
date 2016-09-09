#ifndef STRING
#define STRING

#include "json_value.h"

/**
 * @brief The string class
 */
class String : public Value {

  public:

  String () : Value (), _charc (0) {}

  String (const char *json) : Value::Value (json), _charc (0) {}

  String (JSON *parent, size_t charc)
    : Value::Value (parent),
      _charc (charc)
  {
  }

  virtual const char *
  parse (const char *json)
  {
    /// TODO: if (_parent == 0) { // validate }
    _readp = json;

    return json + _charc;
  }

  /// value interface
  virtual inline Value & at (const char *) { return *this; }

  virtual inline object_type type () const { return Value::object_type::string; }

  virtual inline size_t size () const { return _string_value.length (); }

protected:

  virtual Value &_at (const char *) { return *this; }

public:

  const char *
  value () const
  {
    if (_string_value.empty () && _readp && _charc > 0)
      _string_value.assign (_readp + 1, _charc - 2);

    return _string_value.c_str ();
  }

protected:

  /**
   * @brief _charc
   */
  size_t _charc;

  /**
   * @brief _value
   */
  mutable std::string _string_value;

  // Value interface

}; /// class string

#endif // STRING

