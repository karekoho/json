#include "json_leaf.h"
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
