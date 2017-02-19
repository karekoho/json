#ifndef NULL_H
#define NULL_H

#include "json_leaf.h"
#include "json_json.h"

#ifdef UNIT_TEST
 class json_null_test;
#endif
namespace Format {
/**
 * @brief The Null class
 */
class null : public leaf
{
#ifdef UNIT_TEST
 friend class json_null_test;
#endif

  public:

  /**
   * @brief Null
   */
  null ()
    : leaf ()
  {}

  /**
   * @brief Null
   * @param endp
   * @param parent
   * @param charc
   */
  null (json *parent)
    : leaf (parent)
  {}

  /**
   * @brief Null
   * @param other
   */
  null (const null &other) = default;

  /**
   * @brief Null
   * @param ov
   * @param nv
   */
  null (const Value *ov, const null &nv)
    : leaf (ov, nv)
  {}

  /**
   * @brief clone
   * @param other
   * @return
   */
  virtual Value *
  clone () const
  { return new null (*this); }

  /**
   * @brief clone
   * @param ov
   * @return
   */
  virtual Value *
  clone (const Value *ov) const override
  { return new null (ov, *this); }

  /**
   * @brief parse
   * @param json
   * @return
   */
  virtual inline const wchar_t *
  parse (const wchar_t *json)
  { return json + 4; }

  /**
   * @brief type
   * @return
   */
  virtual inline Value::object_type
  type () const
  { return Value::object_type::null_t; }

  /**
   * TODO: return nullptr
   * @brief Value
   * @return
   */
  inline std::nullptr_t
  value () const
  { return nullptr; }

  /**
   * @brief operator =
   * @param n
   * @return
   */
  inline Value &
  operator =(const null & n)
  { return _assign (n); }

  /**
   * @brief operator =
   * @param v
   * @return
   */
  inline Value &
  operator =(const Value & v)
  { return Value::_assign (v); }

  /**
   * @brief strValue
   * @return
   */
  virtual const wchar_t *
  strValue (wchar_t *) const noexcept override
  { return L"null"; }

  /**
   * @brief strLength
   * @return
   */
  virtual size_t
  strLength () const noexcept override
  { return 4; }

protected:

  /**
   * @brief _assign
   * @param nv
   * @return
   */
//  virtual Value &
//  _assign (const Value & nv)
//  { return Value::_assign (nv); }

  /**
   * @brief assign
   * @param nv
   * @return
   */
  Value &
  _assign (const null &)
  { return _parent ? _parent->_assign (this, new null (this, *this)) : *this; }

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
  { return this; }

};
}
#endif // NULL_H
