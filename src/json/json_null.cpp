#include "json_null.h"
#include "json_json.h"

Value &
Null::_assign (Null &nv)
{
  return _parent ? _parent->assign (this, &nv) : *this;
}
