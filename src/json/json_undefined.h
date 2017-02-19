#ifndef UNDEFINED_H
#define UNDEFINED_H

#include "json_leaf.h"

#ifdef UNIT_TEST
  class json_undefined_test;
#endif

namespace Format {
/**
 * @brief The undefined class
 */
class undefined : public Leaf
{
#ifdef UNIT_TEST
  friend class json_undefined_test;
#endif

  public:

  undefined ()
    : Leaf ()
  {}

  /**
   * @brief Undefined
   * @param parent
   */
  undefined (json *parent)
    : Leaf (parent)
  {}

  /**
   * @brief Undefined
   * @param other
   */
  undefined (const undefined &other) = default;

  /**
   * @brief Undefined
   * @param ov
   * @param nv
   */
  undefined (const Value *ov, const undefined &nv)
    : Leaf (ov, nv)
  {}

  /**
   * @brief clone
   * @param other
   * @return
   */
  virtual Value *
  clone () const
  { return new undefined (*this); }

  /**
   * @brief clone
   * @param ov
   * @return
   */
  virtual Value *
  clone (const Value *ov) const override
  { return new undefined (ov, *this); }

  /**
   * TODO: return nullptr
   * @brief value
   * @return
   */
  inline std::nullptr_t
  value () const
  { return nullptr; }

  /**
   * @brief parse
   * @param json
   * @return
   */
  virtual const wchar_t *
  parse (const wchar_t *json)
  { return json; }

  /**
   * @brief type
   * @return
   */
  virtual inline object_type
  type () const
  { return Value::object_type::undefined_t; }

  /**
   * @brief operator =
   * @param v
   * @return
   */
  inline Value &
  operator =(const Value & v)
  { return Value::_assign (v);  }

  /**
   * @brief strLength
   * @return
   */
  virtual size_t
  strLength () const noexcept override
  { return 0; }

  /**
   * @brief strValue
   * @return
   */
  virtual const wchar_t *
  strValue (wchar_t * = 0) const
  { return L""; }

protected:

  /**
   * @brief assign
   * @param nv
   * @return
   */
//  virtual Value &
//  _assign (const Value & nv)
//  { return Value::_assign (nv); }

  /**
   * @brief _clear
   */
  virtual void
  _clear ()
  {}

  /**
   * @brief _clone
   * @return
   */
  virtual Value *
  clone (const Value &) override
  { return new undefined (*this); }
};
}
#endif // UNDEFINED_H
