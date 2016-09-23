#include "json_boolean.h"
#include "json_json.h"

Value &
Boolean::_assign (Boolean &nv)
{
  return _parent ? _parent->assign (this, &nv) : *(_clone (nv));
}

Value *
Boolean::_clone (const Value &other)
{
  _boolean_value = static_cast<const Boolean &>(other)._boolean_value;
  return this;
}
