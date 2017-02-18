#include "json_leaf.h"
#include "json_json.h"
#include "json_leaf_iterator.h"
#include "json_shared_undefined.h"

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
