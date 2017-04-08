#include "json_array.h"

#include <algorithm>

format::array::array () : json () {}

format::array::array (const wchar_t *text)
  : json (text, false)
{
  (void) _parse (text);
}

format::array::array (std::initializer_list<value *> il)
  : json ()
{
  _element_list.reserve (il.size ());

  auto cur = il.begin ();
  auto end = il.end ();

  while (cur != end)
    {
      (void) _element_list.push_back (*cur);
      __call__set_parent (*(cur++), this);
    }
}

format::array::array (json *parent)
  : json (parent)
{}

format::array::array (const array &other)
  : json (other)
{
  (void) _clone (other);
}

format::array::~array ()
{
  _clear ();
}

const wchar_t *
format::array::_parse (const wchar_t *json)
{  
  if (_parent == 0)   // 1. Array (), 2. Array (const char *json)
    {
      _readp = json;

      if (*(_look_ahead ()) != _sc::begin_array)  // Expecting '['
        throw json_syntax_error (UNEX_END);

      _readp++;
    }
  else
    _readp  = json + 1;

  if (*_readp == 0)
    throw json_syntax_error (UNEX_END);

  if (! _element_list.empty ())
    _clear ();

  value *v = 0;
  size_t next_idx = 0;

  while (*_readp != 0)
    {
      (void) _look_ahead ();

      if (*_readp == _sc::value_separator) // ','
        {
          _readp++;

          if ((v = _make_value ())->type () == value::no_value_t)
            throw json_syntax_error (UNEX_TOKEN, *_readp);

          next_idx = _element_list.size ();

          if ((v = _call_reviver (v, 0, next_idx))->type () != value::undefined_t)
            {
              _element_list.push_back (v);
              __call__set_index (v, next_idx);
            }
        }
      else if (*_readp == _sc::end_array)         // ']'
        return _readp + 1;

      else if ((v = _make_value ())->type () == value::no_value_t)  // No valid value found
        {
          if (*_readp != value::_ws::space
              && *_readp != value::_ws::tab
              && *_readp != value::_ws::lf
              && *_readp != value::_ws::cr)
            throw json_syntax_error (UNEX_TOKEN, *_readp);

          // Empty array
        }
      else if ((v = _call_reviver (v, 0, next_idx))->type () != value::undefined_t)  // Value found
        {
          _element_list.push_back (v);
          __call__set_index (v, next_idx);
        }
    }

  return _readp;
}

format::value &
format::array::_at (size_t index)
{
  try
    {
      return *_element_list.at (index);
    }
  catch (std::out_of_range &)
    {
      value *v = new unique_undefined (this);

      _element_list.push_back (v);      
      __call__set_index (v, _element_list.size () - 1);

      return *v;
  }
}

format::value &
format::array::_assign (value *ov, value *nv)
{
  size_t index = ov->index ();

  _element_list.at (index) = nv;

  __call__set_index (nv, index);
  __call__set_parent(nv, this);

  delete ov;

  return *this;
}

void
format::array::_clear ()
{
  for (auto it = _element_list.begin (); it != _element_list.end (); it = _element_list.erase (it))
    delete *it;
}

format::value *
format::array::_clone (const value &other)
{
  const array & nv = dynamic_cast<const array &> (other);

  _clear ();

  if (nv._element_list.empty ())
    return this;

  _element_list.reserve (nv._element_list.size ());

  std::transform (nv._element_list.begin (),
                  nv._element_list.end (),
                  std::back_inserter (_element_list), [] (value *v) -> value * { return v->clone (); });

  return this;
}

size_t
format::array::str_length () const noexcept
{
  if (_element_list.empty ())
    return 2;

  size_t len = 1;   // [

  auto end = _element_list.cend ();
  auto cur = _element_list.cbegin ();

  while (cur != end)
    len += ((*cur++)->str_length () + 1);   // , or ]

  return len;
}

const wchar_t *
format::array::str_value (wchar_t *offset) const
{
  wchar_t *str_value[2] = { 0, 0 };

  if (offset)
    str_value[OFFSET] = offset;

  else if (_str_value[BEGIN])
    return _str_value[BEGIN];

  else
    str_value[OFFSET] = new wchar_t[str_length () + 1] ();

  str_value[BEGIN] = str_value[OFFSET];

  *(str_value[OFFSET]++) = _sc::begin_array;

  auto end = _element_list.cend ();
  auto cur = _element_list.cbegin ();

  while (cur != end)
    {
      value *v = *cur;
      str_value[OFFSET] = _str_append (str_value[OFFSET], v->str_value (str_value[OFFSET]), v->str_length ());

      if (++cur != end)
        *(str_value[OFFSET]++) = _sc::value_separator;
    }

  *(str_value[OFFSET]++) = _sc::end_array;

  if (offset == 0)
    _str_value[BEGIN] = str_value[BEGIN];

  return str_value[BEGIN];
}

format::value &
format::array::_erase (const value &v) noexcept
{
  size_t index = v.index ();

  if (index == _element_list.size ())
    return *this;

  (void) _element_list.erase (_element_list.cbegin () + index);
  delete & v;

  return *this;
}
