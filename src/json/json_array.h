#ifndef ARRAY
#define ARRAY

#include "json_json.h"
#ifdef UNIT_TEST
class json_test;
class json_array_test;
#endif
/**
 * @brief The array class
 */
class Array : public JSON
{
#ifdef UNIT_TEST
  friend class json_test;
friend class json_array_test;
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
  Array (Value *parent);

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
  virtual inline const Value & at (const char *key) const { return at (atoll (key)); }

  inline const Value & at (size_t index) const { return *(_element_list.at (index)); }

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

protected:

  /**
   * @brief _element_list
   */
  std::vector<Value *> _element_list;

  /**
   * @brief _debug_value
   */
  std::string _debug_value;

protected:


  /**
   * @brief _at
   * @return
   */
  virtual inline const Value &_at (const char *) const { return *this; }

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

  virtual inline void _assign (Value *ov, Value *nv) { _element_list[ov->index ()] = nv; }
};

#endif // ARRAY

