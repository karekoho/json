#include "json_null.h"
#include "json_json.h"

Value &
Null::_assign (Null &nv)
{
  return _parent ? _parent->assign (this, &nv) : *this;
}


const char *
Null::stringify () const  noexcept
{
  return "";
}

size_t
Null::strLength () const  noexcept
{
  return 0;
}
