#ifndef NULL_H
#define NULL_H

#include "json_leaf.h"

#ifdef UNIT_TEST
 class json_null_test;
#endif

/**
 * @brief The Null class
 */
class Null : public Leaf
{
#ifdef UNIT_TEST
 friend class json_null_test;
#endif

  public:

  /**
   * @brief Null
   */
  Null () : Leaf () {}

  /**
   * @brief Null
   * @param endp
   * @param parent
   * @param charc
   */
  Null (JSON *parent) : Leaf (parent) {}

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
   * @brief type
   * @return
   */
  virtual inline Value::object_type type () const { return Value::object_type::null; }

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

  /**
   * @brief _clone
   * @return
   */
  virtual Value *_clone (const Value &) override { return this; }
};
#endif // NULL_H
