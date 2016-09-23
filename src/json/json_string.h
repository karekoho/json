#ifndef STRING
#define STRING

#include "json_value.h"
#include "json_undefined.h"

#ifdef UNIT_TEST
class json_string_test;
#endif

/**
 * @brief The string class
 */
//class Undefined;
class String : public Value
{
#ifdef UNIT_TEST
friend class json_string_test;
#endif

  public:

  /**
   * @brief String
   */
  String ();

  /**
   * @brief String
   * @param json
   */
  String (const char *json);

  /**
   * @brief String
   * @param parent
   * @param charc
   */
  String (JSON *parent, size_t charc);

  /**
   * @brief String
   * @param other
   */
  String (const String & other);

  /**
   * @brief clone
   * @param other
   * @return
   */
  virtual Value * _clone () { return new String (*this); }

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
  virtual inline Value & at (const char *) const { return *(new Undefined); }

  virtual Value & at (size_t) const { return *(new Undefined); }

  virtual inline object_type type () const { return Value::object_type::string; }

  virtual inline size_t size () const { return _string_value.length (); }

  /**
   * @brief operator =
   * @param s
   * @return
   */
  inline Value & operator =(String & s) { return _assign (s); }

  /**
   * @brief operator =
   * @param v
   * @return
   */
  inline Value & operator =(Value & v) { return _assign (v); }

  /**
   * @brief assign
   * @param nv
   * @return
   */
  Value & _assign (String & nv);

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

  /**
   * @brief assign
   * @param nv
   * @return
   */
  virtual Value & _assign (Value & nv) { return Value::_assign (nv); }

  /**
   * @brief _copy
   * @param nv
   */
  void _copy (const String &nv);

  /**
   * @brief _clear
   */
  virtual void _clear () {}

  virtual Value *_clone (const Value &) override { return this; }
};

#endif // STRING

