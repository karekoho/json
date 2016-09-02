#ifndef ARRAY
#define ARRAY

#include "json_json.h"

/**
 * @brief The array class
 */
class Array : public JSON {
  public:

  /**
   * @brief Array
   * @param json
   */
  Array (const char *json = 0);

  /**
   * @brief Array
   * @param endp
   * @param parent
   * @param charc
   */
  Array (const char *endp, Value *parent, size_t charc = 0);

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

  // Value interface
protected:
  virtual const Value &_at(const char *key) const;
};

#endif // ARRAY

