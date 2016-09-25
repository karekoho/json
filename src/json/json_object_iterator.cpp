#include "json_object_iterator.h"

Object_Iterator::Object_Iterator (const Object::member_list &list)
  : _begin (list.begin ()),
    _end (list.end ())
{
}

Value &
Object_Iterator::next ()
{
  return *(*_begin++).second;
}

bool
Object_Iterator::hasNext () const noexcept
{
  return _begin != _end;
}
