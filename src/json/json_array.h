#ifndef ARRAY
#define ARRAY

#include "json_json.h"

#ifdef UNIT_TEST
class json_test;
class json_array_test;
class json_object_test;
class json_string_test;
class json_number_test;
class json_boolean_test;
class json_null_test;
class json_undefined_test;
#endif

/**
 * @brief The array class
 */
class Array : public JSON
{
#ifdef UNIT_TEST
  friend class json_test;
  friend class json_array_test;
  friend class json_object_test;
  friend class json_string_test;
  friend class json_number_test;
  friend class json_boolean_test;
  friend class json_null_test;
  friend class json_undefined_test;
#endif
  // TODO: friend void Value::setKey (const char *key);
  // TODO: friend void Value::setIndex (const size_t &index);

  public:

  Array ();

  /**
   * @brief Array
   * @param json
   */
  Array (const char *json);

  /**
   * @brief Array
   * @param endp
   * @param parent
   * @param charc
   */
  Array (JSON *parent);

  /**
   * @brief Array
   * @param other
   */
  Array (const Array &other) = default;

  /**
   * @brief ~Array
   */
  virtual ~Array (); // { std::vector<Value *>().swap (_element_list); }

  /**
   * @brief parse
   * @param json
   * @return
   */
  virtual const char *parse ( const char *json);

  /**
   * @brief at
   * @param key
   * @return
   */
  virtual inline Value & at (const char *key)  { return at (atoll (key)); }

  /**
   * @brief at
   * @param index
   * @return
   */
  inline Value & at (size_t index) const;

  /**
   * @brief assign
   * @param ov
   * @param nv
   */
  virtual void assign (Value *ov, Value *nv);

  /**
   * @brief type
   * @return
   */
  virtual inline object_type type () const { return Value::object_type::array; }

  /**
   * @brief size
   * @return
   */
  virtual inline size_t size () const { return _element_list.size (); }

  /**
   * @brief operator =
   * @param a
   * @return
   */
  inline Value & operator =(Array & a) { return _assign (a); }

  /**
   * @brief operator =
   * @param v
   * @return
   */
  inline Value & operator =(Value & v) { return _assign (v); }

protected:

  /**
   * @brief _element_list
   */
  std::vector<Value *> _element_list;

  /**
   * @brief _at
   * @return
   */
  virtual Value &_at (const char *)  { return *this; }

  /**
   * @brief _assign
   * @param nv
   * @return
   */
  Value & _assign (Array & nv);

  /**
   * @brief _assign
   * @param nv
   * @return
   */
  virtual Value & _assign (Value & nv) { return Value::_assign (nv); }

  /**
   * @brief _at
   * @param index
   * @return
   */
  Value &_at (size_t index);
};

#endif // ARRAY

