#ifndef NULL_H
#define NULL_H

#include "json_leaf.h"
#include "json_json.h"

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
  Null ()
    : Leaf ()
  {}

  /**
   * @brief Null
   * @param endp
   * @param parent
   * @param charc
   */
  Null (JSON *parent)
    : Leaf (parent)
  {}

  /**
   * @brief Null
   * @param other
   */
  Null (const Null &other) = default;

  /**
   * @brief Null
   * @param ov
   * @param nv
   */
  Null (const Value *ov, const Null &nv)
    : Leaf (ov, nv)
  {}

  /**
   * @brief clone
   * @param other
   * @return
   */
  virtual Value *
  clone () const
  { return new Null (*this); }

  /**
   * @brief clone
   * @param ov
   * @return
   */
  virtual Value *
  clone (const Value *ov) const override
  { return new Null (ov, *this); }

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
  { return Value::object_type::null; }

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
  operator =(const Null & n)
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
  _assign (const Null &)
  { return _parent ? _parent->_assign (this, new Null (this, *this)) : *this; }

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
#endif // NULL_H
