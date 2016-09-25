#ifndef OBJECT_ITERATOR_H
#define OBJECT_ITERATOR_H

#include "json_iterator.h"
#include "json_object.h"

#include <unordered_map>

/**
 * @brief The Object_Iterator class
 */
class Object_Iterator : public Iterator
{
public:

  /**
   * @brief Object_Iterator
   * @param umap
   */
  Object_Iterator (const Object::member_list & list);

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
  std::unordered_map<std::string, Value *>::const_iterator _begin;

  /**
   * @brief _begin
   */
  std::unordered_map<std::string, Value *>::const_iterator _end;
};

#endif // OBJECT_ITERATOR_H
