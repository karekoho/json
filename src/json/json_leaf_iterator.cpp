#include "json_leaf_iterator.h"

using namespace Format;

leaf_iterator::leaf_iterator (const Value *v)
  : _value (v),
    _hasNext (true)
{
}

const Value &
leaf_iterator::next ()
{
  _hasNext = false;
  return *_value;
}

bool
leaf_iterator::hasNext () const noexcept
{
  return _hasNext;
}
