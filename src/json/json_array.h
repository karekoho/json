#ifndef ARRAY
#define ARRAY

#include "json_json.h"

/**
 * @brief The array class
 */
class Array : public json {
#ifdef UNIT_TEST
//  friend class json_array_test;
// friend value * __make_value (value *member);
#endif
  public:

  Array (const char *json);
  Array (const char *endp, value *parent = 0, size_t charc = 0);

  virtual ~Array () {}

  virtual const char *parse ( const char *json);
  virtual const value & at (const char *key) const;
  virtual inline otype type () const { return value::otype::array; }
  virtual inline size_t size () const { return 0; }

protected:
  /**
   * @brief _element_list
   */
  std::vector<Array *> _element_list;
  /**
   * @brief _debug_value
   */
  std::string _debug_value;
}; /// class array

#endif // ARRAY

