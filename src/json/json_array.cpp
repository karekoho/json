#include "json_array.h"

#include <algorithm>

format::json::array::array () : json () {}

format::json::array::array (const wchar_t * const json_text)
  : json (json_text, false)
{
  (void) _parse (json_text);
}

format::json::array::array (std::initializer_list<value *> il)
  : json ()
{
  _set_initializer_list (il);
}

format::json::array::array (json *parent)
  : json (parent)
{}

format::json::array::array (const array &other)
  : json (other)
{
  (void) _clone (other);
}

format::json::array::~array ()
{
  _clear ();
}

const wchar_t *
format::json::array::_parse (const wchar_t *const json_text)
{  
  if (_parent == nullptr)   // 1. Array (), 2. Array (const char *json)
    {
      _readp = json_text;

      if (*(_look_ahead ()) != _sc::begin_array)  // Expecting '['
        throw json_syntax_error (UNEXPECTED_END_OF_INPUT);

      _readp++;
    }
  else
    _readp  = json_text + 1;

  if (*_readp == 0)
    throw json_syntax_error (UNEXPECTED_END_OF_INPUT);

  value *v = nullptr;
  size_t next_idx = 0;

  while (*_readp != 0)
    {
      (void) _look_ahead ();

      if (*_readp == _sc::value_separator) // ','
        {
          _readp++;

          if ((v = _make_value ())->type () == value::no_value_t)
            throw json_syntax_error (UNEXPECTED_TOKEN, _readp, 1);

          next_idx = _element_list.size ();

          if ((v = _call_reviver (v, nullptr, next_idx))->type () != value::undefined_t)
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
            throw json_syntax_error (UNEXPECTED_TOKEN, _readp, 1);
          // Empty array
        }
      else if ((v = _call_reviver (v, nullptr, next_idx))->type () != value::undefined_t)  // Value found
        {
          _element_list.push_back (v);
          __call__set_index (v, next_idx);
        }
    }

  return _readp;
}

format::json::value &
format::json::array::_at (size_t index)
{
  try
    {
      return *_element_list.at (index);
    }
  catch (const std::out_of_range &)
    {
      value *v = new unique_undefined (this);

      _element_list.push_back (v);      
      __call__set_index (v, _element_list.size () - 1);

      return *v;
  }
}

const format::json::value &
format::json::array::_at (size_t index) const
{
  try
    {
      return *_element_list.at (index);
    }
  catch (const std::out_of_range &e)
    {
      throw json_out_of_range (e.what ());
    }
}

format::json::value &
format::json::array::operator =(const format::json::array &a)
{
  if (_parent)
    return __call__assign (_parent, this, new array (a));

  if (! _element_list.empty ())
    _clear ();

  return *(_clone (a));
}

format::json::value &
format::json::array::_assign (value *ov, value *nv)
{
  size_t index = ov->index ();

  _element_list.at (index) = nv;

  __call__set_index (nv, index);
  __call__set_parent (nv, this);

  delete ov;

  return *this;
}

void
format::json::array::_clear ()
{
  for (auto it = _element_list.begin (); it !=_element_list.end (); it = _element_list.erase (it))
    delete *it;
}

format::json::value *
format::json::array::_clone (const value &other)
{
  const array & nv = static_cast<const array &> (other);

  if (nv._element_list.empty ())
    return this;

  _element_list.reserve (nv._element_list.size ());

  std::transform (nv._element_list.begin (),
                  nv._element_list.end (),
                  std::back_inserter (_element_list), [this] (value *v) -> value *
  {
    value *nv = v->clone ();
    __call__set_parent (nv, this);
    return nv;
  });

  return this;
}

size_t
format::json::array::_str_length () const noexcept
{
  if (_element_list.empty ())
    return 2;

  size_t len = 1;   // [

  auto end = _element_list.cend ();
  auto cur = _element_list.cbegin ();

  while (cur != end)    
    len += __call__str_length (*cur++) + 1;   // , or ]

  return len;
}

const wchar_t *
format::json::array::_to_string (wchar_t *offset) const
{
  wchar_t *str_value[2] = { nullptr, nullptr };

  if (offset) // Parent calls, memory allocated
    str_value[OFFSET] = offset;
  else
    str_value[OFFSET] = new wchar_t[_str_length () + 1] ();

  str_value[BEGIN] = str_value[OFFSET];

  *(str_value[OFFSET]++) = _sc::begin_array;

  auto end = _element_list.cend ();
  auto cur = _element_list.cbegin ();

  while (cur != end)
    {
      value *v = *cur;      
      str_value[OFFSET] = _quote_value (str_value[OFFSET], v);

      if (++cur != end)
        *(str_value[OFFSET]++) = _sc::value_separator;
    }

  *(str_value[OFFSET]++) = _sc::end_array;

  return str_value[BEGIN];
}

format::json::value &
format::json::array::_erase (const value & v) noexcept
{
  size_t index = v.index ();

  if (index == _element_list.size ())
    return *this;

  (void) _element_list.erase (_element_list.cbegin () + static_cast<long> (index));
  delete & v;

  return *this;
}

void
format::json::array::_set_initializer_list (const std::initializer_list<value *> & il)
{
  if (il.size () == 0)
    return;

  _element_list.reserve (il.size ());

  auto cur = il.begin ();
  auto end = il.end ();

  size_t next_idx = 0;

  while (cur != end)
    {
      value *v = *(cur++);
      (void) _element_list.push_back (v);
      __call__set_index (v, next_idx++);
      __call__set_parent (v, this);
    }
}
