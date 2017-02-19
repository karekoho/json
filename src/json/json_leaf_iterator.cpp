#include "json_leaf_iterator.h"

using namespace format;

leaf_iterator::leaf_iterator (const value *v)
  : _value (v),
    _hasNext (true)
{
}

const value &
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
