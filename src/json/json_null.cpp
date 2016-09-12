#include "json_null.h"
#include "json_json.h"

Value &
Null::assign (Null &nv)
{
  if (_parent)
    {
      _parent->_assign (this, &nv);
      return *_parent;
    }

  return *this;
}
