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

/* const char *
Boolean::stringify () const noexcept
{
  char *s = 0;

  if (_parent && (s = (char *)_parent->_str_value[0]) != 0)
    {
      // return Value::_str_append (s, strValue (), strLength ());
      s= Value::_str_append (s, strValue(), strLength ());

      return s;
    }

  return strValue ();
} */

//size_t
//Boolean::strLength () const noexcept
//{
//  return _boolean_value == true ? 4 : 5;
//}

//const char *
//Boolean::strValue () const
//{
//  return _boolean_value == true ? "true" : "false";
//}
