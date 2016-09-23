#ifndef NULL_H
#define NULL_H

#include "json_value.h"

#ifdef UNIT_TEST
 class json_null_test;
#endif

/**
 * @brief The Null class
 */
class Null : public Value
{
#ifdef UNIT_TEST
 friend class json_null_test;
#endif

  public:

  /**
   * @brief Null
   */
  Null () : Value::Value () {}

  /**
   * @brief Null
   * @param endp
   * @param parent
   * @param charc
   */
  Null (JSON *parent) : Value::Value (parent) {}

  /**
   * @brief Null
   * @param other
   */
  Null (const Null &other) = default;

  /**
   * @brief clone
   * @param other
   * @return
   */
  virtual Value * _clone () { return new Null (*this); }

  /**
   * @brief parse
   * @param json
   * @return
   */
  virtual inline const char *parse (const char *json) { return json + 4; }

  /**
   * @brief at
   * @param key
   * @return
   */
  virtual inline Value & at (const char *) { return *this; }

  /**
   * @brief at
   * @return
   */
  virtual Value & at (size_t) { return *this; }

  /**
   * @brief type
   * @return
   */
  virtual inline Value::object_type type () const { return Value::object_type::null; }

  /**
   * @brief size
   * @return
   */
  virtual inline size_t size () const { return 1; }

  /**
   * @brief Value
   * @return
   */
  inline const char * value () const { return ""; }

  /**
   * @brief operator =
   * @param n
   * @return
   */
  inline Value & operator =(Null & n) { return _assign (n); }

  /**
   * @brief operator =
   * @param v
   * @return
   */
  inline Value & operator =(Value & v) { return _assign (v); }

  protected:

  /**
   * @brief _at
   * @return
   */
  virtual Value &_at (const char *) { return *this; }

  /**
   * @brief _assign
   * @param nv
   * @return
   */
  virtual Value & _assign (Value & nv) { return Value::_assign (nv); }

  /**
   * @brief assign
   * @param nv
   * @return
   */
  Value & _assign (Null & nv);

  /**
   * @brief _clear
   */
  virtual void _clear () {}

  virtual Value *_clone(const Value &other) override
  {
    return this;
  }
};
#endif // NULL_H
