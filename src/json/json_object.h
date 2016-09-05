#ifndef OBJECT_H
#define OBJECT_H

#include "json_json.h"
#include "json_undefined.h"

/**
 * @brief The object class
 */
class Object : public JSON
{
  // TODO: friend void Value::setKey (const char *key);
  // TODO: friend void Value::setIndex (const size_t &index);

#ifdef UNIT_TEST
  friend class json_test;
  friend class json_object_test;
#endif

public:

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
  Object (Value *parent);

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
  virtual const Value & at (const char *key) const;

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

  protected:

  /**
   * @brief _member_list
   */
  mutable std::unordered_map<std::string, Value *> _member_list;

  bool _pair ();

  Value *_value ();

  // Value interface
protected:

  virtual Value &_at (const char *key)
  {
    try
      {
        return *(_member_list.at (key));
      }
    catch (std::out_of_range &e)
      {
        Value *v = new Undefined (this);
        _member_list.emplace (key, v);
        return *v;
      }
  }

  inline virtual void
  _assign (Value *ov, const Value *nv)
  {
  }
};

#endif // OBJECT_H

