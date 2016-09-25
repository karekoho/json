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
  virtual Value & next () = 0;

  /**
   * @brief hasNext
   * @return
   */
  virtual bool hasNext () = 0;
};

#endif // ITERATOR

