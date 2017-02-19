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
class undefined : public leaf
{
#ifdef UNIT_TEST
  friend class json_undefined_test;
#endif

  public:

  undefined ()
    : leaf ()
  {}

  /**
   * @brief Undefined
   * @param parent
   */
  undefined (json *parent)
    : leaf (parent)
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
  undefined (const value *ov, const undefined &nv)
    : leaf (ov, nv)
  {}

  /**
   * @brief clone
   * @param other
   * @return
   */
  virtual value *
  clone () const
  { return new undefined (*this); }

  /**
   * @brief clone
   * @param ov
   * @return
   */
  virtual value *
  clone (const value *ov) const override
  { return new undefined (ov, *this); }

  /**
   * TODO: return nullptr
   * @brief value
   * @return
   */
  inline std::nullptr_t
  get () const
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
  { return value::object_type::undefined_t; }

  /**
   * @brief operator =
   * @param v
   * @return
   */
  inline value &
  operator =(const value & v)
  { return value::_assign (v);  }

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
  virtual value *
  clone (const value &) override
  { return new undefined (*this); }
};
}
#endif // UNDEFINED_H
