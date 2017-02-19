#include "json_array_iterator.h"
using namespace format;

array_iterator::array_iterator (const array::element_list &list)
  : _begin (list.begin ()),
    _end (list.end ())
{
}

value &
array_iterator::next ()
{
  return *(*_begin++);
}

bool
array_iterator::hasNext () const noexcept
{
  return _begin != _end;
}
