#include "json_object.h"
#include "json_array.h"
#include "json_string.h"
#include "json_undefined.h"
#include "json_null.h"
#include "json_number.h"
#include "json_boolean.h"
#include "json_object_iterator.h"

Object::Object() : JSON (){}

Object::Object (const char *json)
  : JSON::JSON (json, false)
{
  if (_length == 0)
    throw JSON::error ("null string");

  (void) parse (json);
}

Object::Object (JSON *parent)
  : JSON::JSON (parent)
{
}

Object::Object(const Object &other)
  : JSON(other)
{
  (void) _clone (other);
}

Object::~Object()
{
 _clear ();
}

const char *
Object::parse (const char *json)
{
  if (json == 0)
    throw JSON::error ("error: null string given");

  if (_parent == 0)
    {
      _readp = json;

      if (*(_look_ahead ()) != _sc::begin_object)
        throw "syntax error: expecting '{'";

      _readp++;
    }
  else
     _readp = json + 1;

  if (*_readp == 0)
    throw _readp;

  if (! _member_list.empty ())
    _clear ();

  while (*_readp != 0)
    {
      (void) _look_ahead ();

      if (*_readp == _sc::value_separator)   // ','
        {
          _readp++;

          if (! _pair ())
            throw "syntax error: unexpected ','";
        }
      else if (*_readp == _sc::end_object)         // '}'
        return _readp + 1;

      else
        _pair ();
    }

  return _readp;
}

bool
Object::_pair ()
{
  char endc = 0;
  // wchar_t endc;

  long int charc = 0;

  (void) _look_ahead ();

  // Expect "key"
  if ((charc = _string (endc)) == 0)  // No opening \"
    {
      if (*_readp == 0)
        throw JSON::syntax_error ("syntax error: expecting closing '}'");

      if (*_readp == _sc::end_object || *(_look_ahead ()) ==  _sc::end_object)  // Empty object
        return false;
    }

  if (charc < 0)   // No closing "
    throw JSON::syntax_error ("syntax error: expecting closing '\"'");

  const char *keyp = _readp + 1;
  _readp += charc;

  if (*(_look_ahead ()) != _sc::name_separator)   // Expect ':'
    throw JSON::syntax_error ("pair: syntax error: expecting ':'");   // TODO: throw syntax error: unexpected character '%c'

  _readp++;

  Value * v = _make_value ();

  if (v->type () == Value::undefined)
    throw "syntax error: expecting value after ':'";

  (void) _member_list.emplace (std::string (keyp, charc - 2), v);

  v->setKey (keyp, charc - 2);

  return true;
}

Value &
Object::at (const char *key) const
{
  try
    {
      return *(_member_list.at (key));
    }
  catch (std::out_of_range &e)
    {
      throw JSON::out_of_range (e.what ());
  }
}

Iterator *
Object::iterator () const
{
  return new Object_Iterator (_member_list);
}

Value &
Object::_assign (Object &nv)
{
  return _parent ? _parent->assign (this, &nv) : *(_clone (nv));
}

Value &
Object::_at (const char *key)
{
  try
    {
      return *(_member_list.at (key));
    }
  catch (std::out_of_range &)
    {
      Value *v = new Undefined (this);

      v->setKey (key, strlen (key));
      _member_list.emplace (key, v);

      return *v;
  }
}

Value &
Object::assign (Value *ov, Value *nv)
{
   _member_list[ov->key ()] = nv;

   return *this;
}

void
Object::_clear ()
{
  for (auto it = _member_list.begin (); it != _member_list.end (); it = _member_list.erase (it))
    delete static_cast <std::pair<std::string, Value *>>(*it).second;
}

Value *
Object::_clone (const Value &other)
{
  const Object &nv = static_cast<const Object &>(other);

  _clear ();

  if (nv._member_list.empty ())
    return this;

  _member_list.reserve (nv._member_list.size ());

  auto end = nv._member_list.cend ();
  auto cur = nv._member_list.cbegin ();

  while (cur != end)
    {
      std::pair<std::string, Value *> p = *cur++;
      _member_list.emplace (p.first, p.second->_clone ());
    }

  return this;
}

size_t
Object::strLength () const noexcept
{
  if (_member_list.empty ())
    return 2;

  size_t len = 1;   // {

  auto end = _member_list.cend ();
  auto cur = _member_list.cbegin ();

  while (cur != end)
    {
      std::pair<std::string, Value *> p = *cur++;
      len += p.first.size () + dynamic_cast<Value *>(p.second)->strLength () + 4;   // " + key + " + : +  value + , or }
    }

  return len;
}

const char *
Object::strValue () const
{
  _str_value[CURSOR] = _parent && _parent->_str_value[CURSOR]
      ? _parent->_str_value[CURSOR]
      : new char[strLength () + 1] ();

  _str_value[BEGIN] = _str_value[CURSOR];

  *(_str_value[CURSOR]++) = _sc::begin_object;

  auto end = _member_list.cend ();
  auto cur = _member_list.cbegin ();

  while (cur != end)
    {
      std::pair<std::string, Value *> p = *cur;

      _str_value[CURSOR] = _str_append (_str_append (_str_value[CURSOR], "\"", 1), p.first.c_str (), p.first.size ());
      _str_value[CURSOR] = _str_append (_str_value[CURSOR], "\":", 2);
      _str_value[CURSOR] = _str_append (_str_value[CURSOR] /*_str_append (_str_value[CURSOR], "\":", 2)*/, p.second->strValue (), p.second->strLength ());

      if (++cur != end)
        *(_str_value[CURSOR]++) = _sc::value_separator;
    }

  *(_str_value[CURSOR]++) = _sc::end_object;

  return _str_value[BEGIN];
}

Value &
Object::erase (const Value &v) noexcept
{
  auto it = _member_list.find (v.key ());

  if (it == _member_list.end ())
    return *this;

  (void) _member_list.erase (it);

  return *this;
}
