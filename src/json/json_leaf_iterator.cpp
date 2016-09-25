#include "json_leaf_iterator.h"

Leaf_Iterator::Leaf_Iterator (const Value *v)
  : _value (v),
    _hasNext (true)
{
}

const Value &
Leaf_Iterator::next ()
{
  _hasNext = false;
  return *_value;
}

bool
Leaf_Iterator::hasNext () const noexcept
{
  return _hasNext;
}
