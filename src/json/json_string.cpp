#include "json_string.h"
#include "json_json.h"

Value &
String::assign (String &nv)
{
  if (_parent)
    {
      _parent->_assign (this, &nv);
      return *_parent;
    }

  _charc = nv._charc;

  if (nv._readp && _charc > 0)
    _string_value.assign (nv._readp + 1, _charc - 2);

  _startp = _string_value.c_str ();

  return *this;
}

const char *
String::value () const
{
  if (_string_value.empty () && _readp && _charc > 0)
    _string_value.assign (_readp + 1, _charc - 2);

  return _string_value.c_str ();
}
