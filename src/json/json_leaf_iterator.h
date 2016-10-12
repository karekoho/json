#ifndef LEAF_ITERATOR_H
#define LEAF_ITERATOR_H

#include "json_iterator.h"

/**
 * @brief The Leaf_Iterator class
 */
class Leaf_Iterator : public JSON_Iterator
{
public:

  /**
   * @brief Leaf_Iterator
   * @param v
   */
  Leaf_Iterator (const Value *v);

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

#endif // LEAF_ITERATOR_H
