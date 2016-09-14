#ifndef STRING
#define STRING

#include "json_value.h"

#ifdef UNIT_TEST
class json_string_test;
#endif

/**
 * @brief The string class
 */
class String : public Value
{
#ifdef UNIT_TEST
friend class json_string_test;
#endif

  public:

  /**
   * @brief String
   */
  String () : Value (), _charc (0) {}

  /**
   * @brief String
   * @param json
   */
  String (const char *json)
    : Value::Value (json),
      _charc (0)
  {
    if (_length == 0)
      throw "null string";

    (void) parse (json);
  }

  /**
   * @brief String
   * @param parent
   * @param charc
   */
  String (JSON *parent, size_t charc)
    : Value::Value (parent),
      _charc (charc)
  {
  }

  /**
   * @brief parse
   * @param json
   * @return
   */
  virtual const char * parse (const char *json);

  /**
   * @brief at
   * @return
   */
  virtual inline Value & at (const char *) { return *this; }

  virtual inline object_type type () const { return Value::object_type::string; }

  virtual inline size_t size () const { return _string_value.length (); }

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
  Value & assign (String & nv);

  /**
   * @brief value
   * @return
   */
  const char * value () const;

protected:

  /**
   * @brief _at
   * @return
   */
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

