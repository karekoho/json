#include "json_null.h"
#include "json_json.h"

Value &
Null::_assign (Null &nv)
{
  if (_parent)
    {
      _parent->assign (this, &nv);
      return *_parent;
    }

  return *this;
}
