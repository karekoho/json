#include "json_leaf.h"
#include "json_json.h"
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

JSON_Iterator *
Leaf::iterator () const
{
  return new Leaf_Iterator (this);
}

//const char *
//Leaf::stringify () noexcept
//{
//  char *dstp = 0;
//  return (_parent && (dstp = (char *)_parent->_str_value[0]) != 0)
//      ? Value::_str_append (dstp, strValue (), strLength ())
//      : strValue ();
//}
