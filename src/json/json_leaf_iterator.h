#ifndef LEAF_ITERATOR_H
#define LEAF_ITERATOR_H

#include "json_iterator.h"

/**
 * @brief The Leaf_Iterator class
 */
class Leaf_Iterator : public Iterator
{
public:

  /**
   * @brief Leaf_Iterator
   * @param v
   */
  Leaf_Iterator (Value &v);

  /**
   * @brief next
   * @return
   */
  virtual Value & next () final override;

  /**
   * @brief hasNext
   * @return
   */
  virtual bool hasNext () final override;

protected:

  /**
   * @brief _value
   */
  Value * _value;

  /**
   * @brief _hasNext
   */
  bool _hasNext;
};

#endif // LEAF_ITERATOR_H
