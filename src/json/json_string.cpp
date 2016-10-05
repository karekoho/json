#include "json_string.h"
#include "json_json.h"

String::String() : Leaf (), _charc (0) {}

String::String (const char *json)
  : Leaf (json),
    _charc (0)
{
  if (json == 0)
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
  _clone (other);
}

const char *
String::parse (const char *json)
{
  char endc   = 0;
  long charc  = 0;

  _startp =_readp = json;

  _string_value[0].clear ();

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
  return _parent ? _parent->assign (this, new String (nv)) : *(_clone (nv));
}

const char *
String::value () const
{
  if (_string_value[0].empty () && _startp && _charc > 0)
    _string_value[0].assign (_startp + 1, _charc - 2);

  return _string_value[0].c_str ();
}

const char *
String::strValue () const
{
  if (_startp == 0 || _charc == 0)
    return "";

  if (_string_value[1].empty ())
    _string_value[1].assign (_startp, _charc);

  return _string_value[1].c_str ();
}

Value *
String::_clone (const Value &nv)
{
  const String & s = dynamic_cast<const String &>(nv);

  if (s._startp && s._charc > 0)
    _string_value[0].assign (s._startp + 1, s._charc - 2);

  _startp = _string_value[0].c_str ();

  return this;
}

//void
//String::_copy (const String &nv)
//{
//  if (nv._startp && _charc > 0)
//    _string_value[0].assign (nv._startp + 1, _charc - 2);

//  _startp = _string_value[0].c_str ();
//}

