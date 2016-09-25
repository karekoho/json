#include "json_array_iterator.h"

Array_Iterator::Array_Iterator(const std::vector<Value *> &vec)
  : _begin (vec.begin ()),
    _end (vec.end ())
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
