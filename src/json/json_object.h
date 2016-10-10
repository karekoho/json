#ifndef OBJECT_H
#define OBJECT_H

#include "json_json.h"
#include "json_undefined.h"

/**
 * @brief The object class
 */
class Object : public JSON
{
#ifdef UNIT_TEST
  friend class json_test;
  friend class json_object_test;
  friend class json_array_test;
  friend class json_string_test;
  friend class json_number_test;
  friend class json_boolean_test;
  friend class json_null_test;
  friend class json_undefined_test;
#endif

public:

  typedef std::unordered_map<std::string, Value *> member_list;

  /**
   * @brief Object
   */
  Object ();

  /**
   * @brief Object
   * @param JSON
   */
  Object (const char *json);

/**
   * @brief Object
   * @param endp
   * @param parent
   * @param charc
   */
  Object (JSON *parent);

  /**
   * @brief Object
   * @param other
   */
  Object (const Object &other);

  /**
   * @brief Object
   * @param ov
   * @param nv
   */
  Object (const Value *ov, const Object &nv);

  /**
   * @brief clone
   * @param other
   * @return
   */
  virtual Value *
  clone () const
  { return new Object (*this); }

  /**
   * @brief clone
   * @param ov
   * @return
   */
  virtual Value *
  clone (const Value *ov) const override
  { return new Object (ov, *this); }

  /**
   * @brief ~Object
   */
  virtual ~Object ();

  /**
   * @brief parse
   * @param JSON
   * @return
   */
  virtual const char *
  parse (const char *json);

  /**
   * @brief at
   * @param key
   * @return
   */
  virtual Value &
  at (const char *key) const;

  /**
   * @brief at
   * @return
   */
  virtual Value &
  at (size_t)
  { /* return *this; */ throw JSON::out_of_range (); }

  /**
   * @brief type
   * @return
   */
  virtual inline object_type
  type () const
  { return Value::object_type::object; }

  /**
   * @brief size
   * @return
   */
  virtual inline size_t
  count () const
  { return _member_list.size (); }

  /**
   * @brief operator =
   * @param o
   * @return
   */
  inline Value &
  operator =(const Object & o)
  { return _assign (o);  }

  /**
   * @brief operator =
   * @param v
   * @return
   */
  inline Value &
  operator =(const Value & v)
  { return _assign (v); }

  /**
   * @brief iterator
   * @return
   */
  virtual Iterator *
  iterator () const override;

  /**
   * @brief stringify
   * @return
   */
  virtual const char *
  stringify () noexcept override
  { return strValue (); }

  /**
   * @brief strLength
   * @return
   */
  virtual size_t
  strLength () const noexcept override;

  /**
   * @brief strValue
   * @return
   */
  virtual const char *
  strValue () const;

  /**
   * @brief erase
   * @param v
   * @return
   */
  virtual Value &
  erase (const Value &v) noexcept override;

protected:

  /**
   * @brief _member_list
   */
  mutable member_list _member_list;

  /**
   * @brief _pair
   * @return
   */
  bool
  _pair ();

  /**
   * @brief _assign
   * @param nv
   * @return
   */
  Value &
  _assign (const Object & nv);

  /**
   * @brief _at
   * @param key
   * @return
   */
  virtual Value &
  _at (const char *key);

  /**
   * @brief _assign
   * @param nv
   * @return
   */
  virtual Value &
  _assign (const Value & nv)
  { return Value::_assign (nv); }

  /**
   * @brief assign
   * @param ov
   * @param nv
   */
  virtual Value &
  assign (Value *ov, Value *nv);

  /**
   * @brief _clear
   */
  virtual void
  _clear ();

  /**
   * @brief _clone
   * @return
   */
  virtual Value *
  clone (const Value &other);
};

#endif // OBJECT_H

