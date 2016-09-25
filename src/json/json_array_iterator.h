#ifndef ARRAY_ITERATOR_H
#define ARRAY_ITERATOR_H

#include "json_iterator.h"
#include <vector>

/**
 * @brief The Array_Iterator class
 */
class Array_Iterator : public Iterator
{
public:

  /**
   * @brief Array_Iterator
   * @param vec
   */
  Array_Iterator (const std::vector<Value *> & vec);

  /**
   * @brief next
   * @return
   */
  virtual Value & next () override;

  /**
   * @brief hasNext
   * @return
   */
  virtual bool hasNext () override;

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

#endif // ARRAY_ITERATOR_H
