#include "json_string.h"
#include "json_json.h"

String::String() : Leaf (), _charc (0) {}

String::String (const char *json)
  : Leaf (json),
    _charc (0)
{
  if (_length == 0)
    throw "null string";

  (void) parse (json);
}

String::String (JSON *parent, size_t charc)
  : Leaf (parent),
    _charc (charc)
{
}

String::String (const String &other)
  : Leaf (other),
    _charc (other._charc)
{
  _copy (other);
}

const char *
String::parse (const char *json)
{
  char endc   = 0;
  long charc  = 0;

  _startp =_readp = json;

  _string_value.clear ();

  if (_parent == 0)   // 2. ctor
    {
      if ((charc = _string (endc)) <= 0 )
        throw _readp;

      _charc = (size_t) charc;
    }

  return _readp += _charc;
}

Value &
String::_assign (String &nv)
{
  if (_parent)
    {
      _parent->assign (this, &nv);
      return *_parent;
    }

  _charc = nv._charc;
  _copy (nv);

  return *this;
}

const char *
String::value () const
{
  if (_string_value.empty () && _startp && _charc > 0)
    _string_value.assign (_startp + 1, _charc - 2);

  return _string_value.c_str ();
}

void
String::_copy (const String &nv)
{
  if (nv._startp && _charc > 0)
    _string_value.assign (nv._startp + 1, _charc - 2);

  _startp = _string_value.c_str ();
}

const char *
String::stringify () const noexcept
{
  return "";
}

size_t
String::strLength () const noexcept
{
  return 0;
}
