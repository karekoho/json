#include "json_leaf.h"
#include "json_json.h"
#include "json_leaf_iterator.h"
#include "json_shared_undefined.h"

Value &
Leaf::at (const wchar_t *) const
{
  return Shared_Undefined::instance ();
}

Value &
Leaf::at (size_t) const
{
  return Shared_Undefined::instance ();
}

Value &
Leaf::_at (const wchar_t *)
{
  return Shared_Undefined::instance ();
}

Value &
Leaf::_at (size_t)
{
  return Shared_Undefined::instance ();
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
