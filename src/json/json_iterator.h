#ifndef ITERATOR
#define ITERATOR

#include "json_value.h"

namespace Format
{
  /**
   * @brief The Iterator class
   */
  class json_iterator
  {
  public:

    /**
     * @brief ~Iterator
     */
    virtual ~json_iterator () = default;

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
} // Namespace format

#endif // ITERATOR

