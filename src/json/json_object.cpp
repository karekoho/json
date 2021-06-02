#include "json_object.h"

format::json::object::object ()
  : json ()
{}

format::json::object::object (const wchar_t * const json_text)
  : json (json_text, false)
{
  (void) _parse (json_text);
}

format::json::object::object (std::initializer_list<std::pair<std::wstring, value *> > il)
  : json ()
{
  _set_initializer_list (il);
}

format::json::object::object (json *parent)
  : json::json (parent)
{}

format::json::object::object (const object &other)
  : json (other)
{
  (void) _clone (other);
}

format::json::object::~object ()
{
  _clear ();
}

const wchar_t *
format::json::object::_parse (const wchar_t *json_text)
{
  if (_parent == nullptr)   // 1. Object (), 2. Object (const char *json)
    {
      _readp = json_text;

      if (*(_look_ahead ()) != _sc::begin_object)
        throw json_syntax_error (UNEXPECTED_END_OF_INPUT);

      _readp++;
    }
  else
    _readp = json_text + 1;

  if (*_readp == 0)
    throw json_syntax_error (UNEXPECTED_END_OF_INPUT);

  while (*_readp != 0)
    {
      (void) _look_ahead ();

      if (*_readp == _sc::value_separator)   // ','
        {
          _readp++;

          if (! _pair ())
            throw json_syntax_error (UNEXPECTED_END_OF_INPUT);
        }
      else if (*_readp == _sc::end_object)         // '}'
        return _readp + 1;

      else
        _pair ();
    }

  return _readp;
}

bool
format::json::object::_pair ()
{
  wchar_t endc = 0;

  long charc = 0;

  (void) _look_ahead ();

  // Expect "key"
  if ((charc = _string (endc)) == 0)  // No opening \"
    {
      if (*_readp == 0)
        throw json_syntax_error (UNEXPECTED_END_OF_INPUT);

      if (*_readp == _sc::end_object || *(_look_ahead ()) ==  _sc::end_object)  // Empty object
        return false;
    }

  if (charc < 0)   // No closing "
    throw json_syntax_error (UNEXPECTED_TOKEN, _readp, 1);

  const wchar_t *keyp = _readp + 1;
  _readp += charc;

  if (*(_look_ahead ()) != _sc::name_separator)   // Expect ':'
    throw json_syntax_error (UNEXPECTED_TOKEN, _readp, 1);   // TODO: throw syntax error: unexpected character '%c'

  _readp++;

  value * v = _make_value ();

  if (v->type () == value::no_value_t)
    throw json_syntax_error (UNEXPECTED_TOKEN, _readp, 1);

  std::wstring key (keyp, static_cast<size_t> (charc - 2));

  if ((v = _call_reviver (v, key.c_str ()))->type () == value::undefined_t)   // Reviver returned undefined, value is not added
    return true;

  (void) _member_list.emplace (key, v);

  __call__set_key (v, keyp, static_cast<size_t> (charc - 2));

  return true;
}

format::json::value &
format::json::object::_at (const wchar_t * const key)
{
  try
    {
      return *(_member_list.at (key));
    }
  catch (const std::out_of_range &)
    {
      value *v = new unique_undefined (this);

      __call__set_key (v, key, wcslen (key));
      _member_list.emplace (key, v);

      return *v;
  }
}

const format::json::value &
format::json::object::_at (const wchar_t * const key) const
{
  try
    {
      return *(_member_list.at (key));
    }
  catch (const std::out_of_range & e)
    {
      throw json_out_of_range (e.what ());
    }
}

format::json::value &
format::json::object::operator =(const format::json::object &o)
{
  if (_parent)
    return __call__assign (_parent, this, new object (o));

  if (! _member_list.empty ())
    _clear ();

  return *(_clone (o));
}

format::json::value &
format::json::object::_assign (value *ov, value *nv)
{
  const wchar_t *key = ov->key ();

  _member_list[key] = nv;

  __call__set_key (nv, key, wcslen (key));
  __call__set_parent (nv, this);

  delete ov;
  ov = nullptr;

  return *this;
}

void
format::json::object::_clear ()
{
  auto begin = _member_list.begin ();
  auto end = _member_list.end ();

  while (begin != end)
    {
      delete static_cast <std::pair<std::wstring, value *>>(*begin).second;
      begin = _member_list.erase (begin);
    }
}

format::json::value *
format::json::object::_clone (const value &other)
{
  const object & nv = static_cast<const object &>(other);

  if (nv._member_list.empty ())
    return this;

  _member_list.reserve (nv._member_list.size ());

  auto end = nv._member_list.cend ();
  auto cur = nv._member_list.cbegin ();

  while (cur != end)
    {
      std::pair<std::wstring, const value *> p = *cur++;
      value *v = p.second->clone ();
      __call__set_parent (v, this);
      _member_list.emplace (p.first, v);
    }

  return this;
}

size_t
format::json::object::_str_length () const noexcept
{
  if (_member_list.empty ())
    return 2;

  size_t len = 1;   // {

  auto end = _member_list.cend ();
  auto cur = _member_list.cbegin ();

  while (cur != end)
    {
      std::pair<std::wstring, const value *> p = *cur++;
      len += p.first.size () + __call__str_length (static_cast<const value *>(p.second)) + 4;   // " + key + " + : +  value + , or }
    }

  return len;
}

const wchar_t *
format::json::object::_to_string (wchar_t *offset) const
{
  wchar_t *str_value[2] = { nullptr, nullptr };

  if (offset) // Parent calls, memory allocateds
    str_value[OFFSET] = offset;
  else
    str_value[OFFSET] = new wchar_t[_str_length () + 1] ();

  str_value[BEGIN] = str_value[OFFSET];

  *(str_value[OFFSET]++) = _sc::begin_object;

  auto end = _member_list.cend ();
  auto cur = _member_list.cbegin ();

  while (cur != end)
    {
      const std::pair<std::wstring, const value *> p = *cur;

      str_value[OFFSET] = _str_append (str_value[OFFSET], L"\"", 1);  // Double quote
      str_value[OFFSET] = _str_append (str_value[OFFSET], p.first.c_str (), p.first.size ());   // Key
      str_value[OFFSET] = _str_append (str_value[OFFSET], L"\":", 2); // Double quote and name separator
      str_value[OFFSET] = _quote_value (str_value[OFFSET], p.second);

      if (++cur != end)
        *(str_value[OFFSET]++) = _sc::value_separator;
    }

  *(str_value[OFFSET]++) = _sc::end_object;

  return str_value[BEGIN];
}

format::json::value &
format::json::object::_erase (const value & v) noexcept
{
  auto it = _member_list.find (v.key ());

  if (it == _member_list.end ())
    return *this;

  (void) _member_list.erase (it);
  delete & v;

  return *this;
}

void
format::json::object::_set_initializer_list (const std::initializer_list<std::pair<std::wstring, value *> > & il)
{
  if (il.size () == 0)
    return;

  _member_list.reserve (il.size ());

  auto cur = il.begin ();
  auto end = il.end ();

  while (cur != end)
    {
      std::pair<std::wstring, value *> p = *(cur++);
      (void) _member_list.emplace (p);
      __call__set_key (p.second, p.first.c_str (), p.first.length ());
      __call__set_parent (p.second, this);
    }
}
