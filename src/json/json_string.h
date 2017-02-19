#ifndef STRING
#define STRING

#include "json_leaf.h"

#ifdef UNIT_TEST
  class json_string_test;
#endif
namespace Format {
/**
 * @brief The string class
 */
class String : public Leaf
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
  String (const wchar_t *json);

  /**
   * @brief String
   * @param parent
   * @param charc
   */
  String (json *parent, size_t charc);

  /**
   * @brief String
   * @param other
   */
  String (const String & other);

  /**
   * @brief String
   * @param ov
   * @param nv
   */
  String (const Value *ov, const String & nv);

  /**
   * @brief clone
   * @param other
   * @return
   */
  virtual Value *
  clone () const
  { return new String (*this); }

  /**
   * @brief clone
   * @param ov
   * @return
   */
  virtual Value *
  clone (const Value *ov) const override
  { return new String (ov, *this);}

  /**
   * @brief parse
   * @param json
   * @return
   */
  virtual const wchar_t *
  parse (const wchar_t *json);

  /**
   * @brief type
   * @return
   */
  virtual inline object_type
  type () const
  { return Value::object_type::string_t; }

  /**
   * @brief operator =
   * @param s
   * @return
   */
  inline Value &
  operator =(const String & s)
  { return _assign (s); }

  /**
   * @brief operator =
   * @param v
   * @return
   */
  inline Value &
  operator =(const Value & v)
  { return Value::_assign (v); }

  /**
   * @brief assign
   * @param nv
   * @return
   */
  Value &
  _assign (const String & nv);

  /**
   * @brief value
   * @return
   */
  const wchar_t *
  value() const;

  /**
   * @brief strLength
   * @return
   */
  virtual size_t
  strLength () const noexcept override
  { return _charc; }

  /**
   * @brief strValue
   * @return
   */
  virtual const wchar_t *
  strValue (wchar_t * = 0) const;

protected:

  /**
   * @brief _charc
   */
  size_t _charc;

  /**
   * @brief _value
   */
  mutable std::wstring _string_value[2];

  /**
   * @brief _copy
   * @param nv
   * void _copy (const String &nv);
   */

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
  clone (const Value &nv) override;
};
}
#endif // STRING

