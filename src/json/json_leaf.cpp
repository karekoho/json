#include "json_leaf.h"
#include "json_json.h"
#include "json_leaf_iterator.h"
#include "json_shared_undefined.h"

using namespace Format;

Value &
leaf::_at (const wchar_t *)
{
  return Shared_Undefined::instance ();
}

Value &
leaf::_at (size_t)
{
  return Shared_Undefined::instance ();
}

json_iterator *
leaf::iterator () const
{
  return new leaf_iterator (this);
}
