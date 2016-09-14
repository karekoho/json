#include "json_undefined.h"
#include "json_json.h"

Value &
Undefined::assign (Undefined &nv)
{
  if (_parent)
    {
      _parent->_assign (this, &nv);
      return *_parent;
    }

  return *this;
}
