#include "json_leaf.h"
#include "json_leaf_iterator.h"
#include "json_undefined.h"

Value &
Leaf::at (const char *) const
{
  return *(new Undefined);
}

Value &
Leaf::at (size_t) const
{
  return *(new Undefined);
}

Value &
Leaf::_at (const char *)
{
  return *(new Undefined);
}

Iterator *
Leaf::iterator () const
{
  return new Leaf_Iterator (this);
}
