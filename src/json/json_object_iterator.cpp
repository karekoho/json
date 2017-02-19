#include "json_object_iterator.h"
using namespace Format;

object_iterator::object_iterator (const object::member_list &list)
  : _begin (list.begin ()),
    _end (list.end ())
{
}

Value &
object_iterator::next ()
{
  return *(*_begin++).second;
}

bool
object_iterator::hasNext () const noexcept
{
  return _begin != _end;
}
