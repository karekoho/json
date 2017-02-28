#include "json_object.h"
#include "json_array.h"
#include "json_string.h"
#include "json_undefined.h"
#include "json_null.h"
#include "json_number.h"
#include "json_boolean.h"
#include "json_object_iterator.h"
using namespace format;

object::object () : json () {}

object::object (const wchar_t *text)
  : json (text, false)
{
  (void) _parse (text);
}

object::object(std::initializer_list<std::pair<std::__cxx11::wstring, value *> > il)
  : json(), _member_list (il.begin (), il.end ())
{
}

object::object (json *parent)
  : json::json (parent)
{
}

object::object (const object &other)
  : json(other)
{
  (void) clone (other);
}

object::object (const value *ov, const object &nv)
  : json (ov, nv)
{
  (void) clone (nv);
}

object::~object ()
{
 _clear ();
}

const wchar_t *
object::_parse (const wchar_t *json)
{
  if (json == 0)
    throw json_syntax_error (UNEX_END);

  if (_parent == 0)   // 1. Object (), 2. Object (const char *json)
    {
      _readp = json;

      if (*(_look_ahead ()) != _sc::begin_object)
        throw json_syntax_error (UNEX_END);

      _readp++;
    }
  else
    {
      _startp = json;
      _readp = json + 1;
    }

  if (*_readp == 0)
    throw json_syntax_error (UNEX_END);

  if (! _member_list.empty ())
    _clear ();

  while (*_readp != 0)
    {
      (void) _look_ahead ();

      if (*_readp == _sc::value_separator)   // ','
        {
          _readp++;

          if (! _pair ())
            throw json_syntax_error (UNEX_END);
        }
      else if (*_readp == _sc::end_object)         // '}'
        return _readp + 1;

      else
        _pair ();
    }

  return _readp;
}

bool
object::_pair ()
{
  wchar_t endc = 0;

  long int charc = 0;

  (void) _look_ahead ();

  // Expect "key"
  if ((charc = _string (endc)) == 0)  // No opening \"
    {
      if (*_readp == 0)
        throw json_syntax_error (UNEX_END);

      if (*_readp == _sc::end_object || *(_look_ahead ()) ==  _sc::end_object)  // Empty object
        return false;
    }

  if (charc < 0)   // No closing "
    throw json_syntax_error ("Unexpected token ", *_readp);

  const wchar_t *keyp = _readp + 1;
  _readp += charc;

  if (*(_look_ahead ()) != _sc::name_separator)   // Expect ':'
    throw json_syntax_error ("Unexpected token ", *_readp);   // TODO: throw syntax error: unexpected character '%c'

  _readp++;

  value * v = _make_value ();

  if (v->type () == value::no_value_t)
    throw json_syntax_error ("Unexpected token ", *_readp);

  std::wstring key (keyp, charc - 2);

  if ((v = _call_reviver (v, key.c_str ()))->type () == value::undefined_t)   // Reviver returned undefined, value is not added
    return true;

  (void) _member_list.emplace (key, v);

  v->set_key (keyp, charc - 2);

  return true;
}

//Value &
//Object::at (const wchar_t *key) const
//{
//  try
//    {
//      return *(_member_list.at (key));
//    }
//  catch (std::out_of_range & e)
//    {
//      throw JSON_Out_Of_Range (e.what ());
//  }
//}

json_iterator *
object::iterator () const
{
  return new object_iterator (_member_list);
}

value &
object::_assign (const object &nv)
{
  return _parent ? _parent->_assign (this, new object (this, nv)) : *(clone (nv));
}

value &
object::_at (const wchar_t *key)
{
  try
    {
      return *(_member_list.at (key));
    }
  catch (std::out_of_range &)
    {
      value *v = new undefined (this);

      v->set_key (key, wcslen (key));
      _member_list.emplace (key, v);

      return *v;
  }
}

value &
object::_assign (value *ov, value *nv)
{
  const wchar_t *key = ov->key ();

  _member_list[key] = nv;

  nv->set_key (key, wcslen (key));
  nv->set_parent (this);

  return *this;
}

void
object::_clear ()
{
  for (auto it = _member_list.begin (); it != _member_list.end (); it = _member_list.erase (it))
    {
      delete static_cast <std::pair<std::wstring, value *>>(*it).second;
    }
}

value *
object::clone (const value &other)
{
  const object & nv = static_cast<const object &>(other);

  _clear ();

  if (nv._member_list.empty ())
    return this;

  _member_list.reserve (nv._member_list.size ());

  auto end = nv._member_list.cend ();
  auto cur = nv._member_list.cbegin ();

  while (cur != end)
    {
      std::pair<std::wstring, value *> p = *cur++;
      _member_list.emplace (p.first, p.second->clone ());
    }

  return this;
}

size_t
object::str_length () const noexcept
{
  if (_member_list.empty ())
    return 2;

  size_t len = 1;   // {

  auto end = _member_list.cend ();
  auto cur = _member_list.cbegin ();

  while (cur != end)
    {
      std::pair<std::wstring, value *> p = *cur++;
      len += p.first.size () + dynamic_cast<value *>(p.second)->str_length () + 4;   // " + key + " + : +  value + , or }
    }

  return len;
}

const wchar_t *
object::str_value (wchar_t *offset) const
{
  wchar_t *str_value[2] = { 0, 0 };

  if (offset)
    str_value[OFFSET] = offset;

  else if (_str_value[BEGIN])
    return _str_value[BEGIN];

  else
    str_value[OFFSET] = new wchar_t[str_length () + 1] ();

  str_value[BEGIN] = str_value[OFFSET];

  *(str_value[OFFSET]++) = _sc::begin_object;

  auto end = _member_list.cend ();
  auto cur = _member_list.cbegin ();

  while (cur != end)
    {
      std::pair<std::wstring, value *> p = *cur;

      str_value[OFFSET] = _str_append (_str_append (str_value[OFFSET], L"\"", 1), p.first.c_str (), p.first.size ());   // Key
      str_value[OFFSET] = _str_append (str_value[OFFSET], L"\":", 2);
      str_value[OFFSET] = _str_append (str_value[OFFSET], p.second->str_value (str_value[OFFSET]), p.second->str_length ()); // Value

      if (++cur != end)
        *(str_value[OFFSET]++) = _sc::value_separator;
    }

  *(str_value[OFFSET]++) = _sc::end_object;

  if (offset == 0)
    _str_value[BEGIN] = str_value[BEGIN];

  return str_value[BEGIN];
}

value &
object::erase (const value & v) noexcept
{
  auto it = _member_list.find (v.key ());

  if (it == _member_list.end ())
    return *this;

  (void) _member_list.erase (it);

  return *this;
}
