#ifndef LEAF_ITERATOR_H
#define LEAF_ITERATOR_H

#include "json_iterator.h"

namespace Format
{
  /**
   * @brief The Leaf_Iterator class
   */
  class leaf_iterator : public json_iterator
  {
  public:

    /**
     * @brief Leaf_Iterator
     * @param v
     */
    leaf_iterator (const Value *v);

    /**
     * @brief next
     * @return
     */
    virtual const Value & next () final override;

    /**
     * @brief hasNext
     * @return
     */
    virtual bool hasNext () const noexcept final override;

  protected:

    /**
     * @brief _value
     */
    const Value * _value;

    /**
     * @brief _hasNext
     */
    bool _hasNext;
  };
} // Namespace format

#endif // LEAF_ITERATOR_H
