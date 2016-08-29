#ifndef ARRAY
#define ARRAY

#include "json_json.h"

/**
 * @brief The array class
 */

class Array : public json {
  public:

  Array (const char *json = 0);
  Array (const char *endp, value *parent, size_t charc = 0);

  virtual ~Array () {}

  virtual const char *parse ( const char *json);
  virtual const value & at (const char *key) const;
  virtual inline otype type () const { return value::otype::array; }
  virtual inline size_t size () const { return _element_list.size(); }

protected:
  /**
   * @brief _element_list
   */
  std::vector<value *> _element_list;

  /**
   * @brief _debug_value
   */
  std::string _debug_value;
};

#endif // ARRAY

