#include "json_array_iterator.h"

Array_Iterator::Array_Iterator (const Array::element_list &list)
  : _begin (list.begin ()),
    _end (list.end ())
{
}

Value &
Array_Iterator::next ()
{
  return *(*_begin++);
}

bool
Array_Iterator::hasNext ()
{
  return _begin != _end;
}
