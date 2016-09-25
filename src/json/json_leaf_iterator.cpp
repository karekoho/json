#include "json_leaf_iterator.h"

Leaf_Iterator::Leaf_Iterator (Value &v)
  : _value (&v),
    _hasNext (true)
{
}

Value &
Leaf_Iterator::next ()
{
  _hasNext = false;
  return *_value;
}

bool
Leaf_Iterator::hasNext ()
{
  return _hasNext;
}
