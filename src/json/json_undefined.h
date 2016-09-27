#ifndef UNDEFINED_H
#define UNDEFINED_H

#include "json_leaf.h"

#ifdef UNIT_TEST
  class json_undefined_test;
#endif

/**
 * @brief The undefined class
 */
class Undefined : public Leaf
{
#ifdef UNIT_TEST
  friend class json_undefined_test;
#endif

  public:

  Undefined () : Leaf () {}

  /**
   * @brief Undefined
   * @param parent
   */
  Undefined (JSON *parent) : Leaf (parent) {}

  /**
   * @brief Undefined
   * @param other
   */
  Undefined (const Undefined &other) = default;

  /**
   * @brief clone
   * @param other
   * @return
   */
  virtual Value * _clone () { return new Undefined (*this); }

  /**
   * @brief value
   * @return
   */
  inline const char * value () const { return "undefined"; }

  /**
   * @brief parse
   * @param json
   * @return
   */
  virtual const char * parse (const char *json) { return json; }

  /**
   * @brief type
   * @return
   */
  virtual inline object_type type () const { return Value::object_type::undefined; }

  /**
   * @brief operator =
   * @param v
   * @return
   */
  inline Value & operator =(Value & v) { return _assign (v);  }

protected:

  /**
   * @brief assign
   * @param nv
   * @return
   */
  virtual Value & _assign (Value & nv) { return Value::_assign (nv); }

  /**
   * @brief _clear
   */
  virtual void _clear () {}

  /**
   * @brief _clone
   * @return
   */
  virtual Value *_clone (const Value &) override { return this; }

  // Value interface
public:
  virtual const char *stringify() const noexcept override
  {
    return "";
  }
  virtual size_t strLength() const noexcept override
  {
    return 0;
  }
};

#endif // UNDEFINED_H
