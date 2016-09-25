#ifndef OBJECT_H
#define OBJECT_H

#include "json_json.h"
#include "json_undefined.h"
//class Object;
// #include "json_array.h"
class Array;
class String;
class Number;
class Boolean;
class Null;
class Undefined;
//class json_undefined_test;
/**
 * @brief The object class
 */
class Object : public JSON
{
// TODO: friend void Value::setKey (const char *key);
// TODO: friend void Value::setIndex (const size_t &index);
// friend Value & Object::_assign (Value *ov, Value *nv);

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

  // friend void JSON::_assign (Value *p, Value *ov, const Value *nv);
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
   * @brief clone
   * @param other
   * @return
   */
  virtual Value * _clone () { return new Object (*this); }

  /**
   * @brief ~Object
   */
  virtual ~Object ();

  /**
   * @brief parse
   * @param JSON
   * @return
   */
  virtual const char *parse (const char *json);

  /**
   * @brief at
   * @param key
   * @return
   */
  virtual Value & at (const char *key) const;

  /**
   * @brief at
   * @return
   */
  virtual Value & at (size_t)  { return *this; }

  /**
   * @brief type
   * @return
   */
  virtual inline object_type type () const { return Value::object_type::object; }

  /**
   * @brief size
   * @return
   */
  virtual inline size_t count () const { return _member_list.size (); }

  /**
   * @brief operator =
   * @param o
   * @return
   */
  inline Value & operator =(Object & o) { return _assign (o);  }

  /**
   * @brief operator =
   * @param v
   * @return
   */
  inline Value & operator =(Value & v) { return _assign (v); }

protected:

  /**
   * @brief _member_list
   */
  mutable member_list _member_list;

  /**
   * @brief _pair
   * @return
   */
  bool _pair ();

  /**
   * @brief _assign
   * @param nv
   * @return
   */
  Value & _assign (Object & nv);

  /**
   * @brief _at
   * @param key
   * @return
   */
  virtual Value & _at (const char *key);

  /**
   * @brief _assign
   * @param nv
   * @return
   */
  virtual Value & _assign (Value & nv) { return Value::_assign (nv); }

  /**
   * @brief assign
   * @param ov
   * @param nv
   */
  virtual Value & assign (Value *ov, Value *nv);

  /**
   * @brief _clear
   */
  virtual void _clear ();

  /**
   * @brief _clone
   * @return
   */
  virtual Value *_clone (const Value &other); // override { return this; }
};

#endif // OBJECT_H

