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
   * @brief ~Array
   */
  virtual ~Array () { std::vector<Value *>().swap (_element_list); }

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


  inline Value & at (size_t index) const;

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

  Value & assign (Array & nv);

  virtual Value & assign (Value & nv) { return Value::assign (nv); }

protected:

  /**
   * @brief _element_list
   */
  std::vector<Value *> _element_list;

  /**
   * @brief _debug_value
   */
  //std::string _debug_value;

protected:


  /**
   * @brief _at
   * @return
   */
  virtual inline Value &_at (const char *)  { return *this; }

  Value &_at (size_t index)
  {
    try
      {
        return *_element_list.at (index);
      }
    catch (std::out_of_range &)
      {
        Value *v = new Undefined (this);

        _element_list.push_back (v);
        v->setIndex (_element_list.size () - 1);

        return *v;
      }
   }

  virtual inline void
  _assign (Value *ov, Value *nv)
  {
    _element_list.at (ov->index ()) = nv;
  }
};

#endif // ARRAY

