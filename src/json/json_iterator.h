#ifndef ITERATOR
#define ITERATOR

#include "json_value.h"
namespace Format {
/**
 * @brief The Iterator class
 */
class JSON_Iterator
{
public:

  /**
   * @brief ~Iterator
   */
  virtual ~JSON_Iterator () = default;

  /**
   * @brief next
   * @return
   */
  virtual const Format::Value & next () = 0;

  /**
   * @brief hasNext
   * @return
   */
  virtual bool hasNext () const noexcept = 0;
};
}
#endif // ITERATOR

