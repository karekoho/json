#ifndef ARRAY
#define ARRAY

#include "json_json.h"

/**
 * @brief The array class
 */
class Array : public JSON
{
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
  virtual const Value & at (const char *key) const;

  /**
   * @brief type
   * @return
   */
  virtual inline object_type type () const { return Value::object_type::array; }

  /**
   * @brief size
   * @return
   */
  virtual inline size_t size () const { return _element_list.size(); }

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
  virtual const Value &_at(const char *) const { return *this; }
};

#endif // ARRAY

