#include "json_boolean.h"
#include "json_json.h"

Value &
Boolean::assign (Boolean &nv)
{
  if (_parent)
    {
      _parent->_assign (this, &nv);
      return *_parent;
    }

  _boolean_value = nv._boolean_value;

  return *this;
}
