#ifndef OBJECT_ITERATOR_H
#define OBJECT_ITERATOR_H

#include "json_iterator.h"
#include "json_object.h"

#include <unordered_map>

namespace Format
{
  /**
   * @brief The Object_Iterator class
   */
  class object_iterator : public json_iterator
  {
  public:

    /**
     * @brief Object_Iterator
     * @param umap
     */
    object_iterator (const Object::member_list & list);

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
    std::unordered_map<std::wstring, Value *>::const_iterator _begin;

    /**
     * @brief _begin
     */
    std::unordered_map<std::wstring, Value *>::const_iterator _end;
  };
} // Namespace format

#endif // OBJECT_ITERATOR_H
