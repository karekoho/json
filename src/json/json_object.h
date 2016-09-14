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
  friend class json_null_test;
  friend class json_undefined_test;
#endif

public:
  // friend void JSON::_assign (Value *p, Value *ov, const Value *nv);
  /**
   * @brief Object
   */
  Object ();

/**
   * @brief Object
   * @param JSON
   */
  explicit Object (const char *json);

/**
   * @brief Object
   * @param endp
   * @param parent
   * @param charc
   */
  Object (JSON *parent);

  /**
   * @brief ~Object
   */
  virtual ~Object () { std::unordered_map<std::string, Value *>().swap (_member_list); }

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
  virtual Value & at (const char *key);

  /**
   * @brief type
   * @return
   */
  virtual inline object_type type () const { return Value::object_type::object; }

  /**
   * @brief size
   * @return
   */
  virtual inline size_t size () const { return _member_list.size (); }

  Value & assign (Object & nv);

  virtual Value & assign (Value & nv) { return Value::assign (nv); }

//  Value & assign (Array & nv);
//  Value & assign (String & nv);
//  Value & assign (Number & nv);
//  Value & assign (Boolean & nv);
//  Value & assign (Null & nv);

  protected:

  /**
   * @brief _member_list
   */
  mutable std::unordered_map<std::string, Value *> _member_list;

  bool _pair ();

  Value *_value ();

  // Value interface
protected:

  virtual Value &
  _at (const char *key)
  {
    try
      {
        return *(_member_list.at (key));
      }
    catch (std::out_of_range &)
      {
        Value *v = new Undefined (this);

        v->setKey (key, strlen (key));
        _member_list.emplace (key, v);

        return *v;
      }
  }

  inline virtual void
  _assign (Value *ov, Value *nv)
  {
    _member_list[ov->key ()] = nv;
  }
};

#endif // OBJECT_H

