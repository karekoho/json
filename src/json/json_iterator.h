#ifndef ITERATOR
#define ITERATOR

#include "json_value.h"

/**
 * @brief The Iterator class
 */
class Iterator
{
public:

  /**
   * @brief ~Iterator
   */
  virtual ~Iterator () = default;

  /**
   * @brief next
   * @return
   */
  virtual const Value & next () = 0;

  /**
   * @brief hasNext
   * @return
   */
  virtual bool hasNext () const noexcept = 0;
};

#endif // ITERATOR

