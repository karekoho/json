#ifndef ARRAY_ITERATOR_H
#define ARRAY_ITERATOR_H

#include "json_iterator.h"
#include "json_array.h"

#include <vector>

namespace Format
{
  /**
   * @brief The Array_Iterator class
   */
  class array_iterator : public json_iterator
  {
  public:

    /**
     * @brief Array_Iterator
     * @param vec
     */
    array_iterator (const array::element_list & list);

    /**
     * @brief next
     * @return
     */
    virtual Value & next () override;

    /**
     * @brief hasNext
     * @return
     */
    virtual bool hasNext () const noexcept override;

  protected:

    /**
     * @brief _begin
     */
    std::vector<Value *>::const_iterator _begin;

    /**
     * @brief _end
     */
    std::vector<Value *>::const_iterator _end;
  };
}
#endif // ARRAY_ITERATOR_H
