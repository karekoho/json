#ifndef STRING
#define STRING

#include "json_value.h"

/**
 * @brief The string class
 */
class String : public Value
{
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

  virtual Value & assign (Value & nv) { return Value::assign (nv); }

  Value & assign (String & nv);

  const char * value () const;

protected:

  virtual Value &_at (const char *) { return *this; }

  /**
   * @brief _charc
   */
  size_t _charc;

  /**
   * @brief _value
   */
  mutable std::string _string_value;
};

#endif // STRING

