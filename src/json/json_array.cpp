#include "json_array.h"
#include "json_array_iterator.h"

#include <algorithm>
using namespace Format;

Array::Array () : json () {}

Array::Array (const wchar_t *text)
  : json (text, false)
{
  (void) parse (text);
}

Array::Array(std::initializer_list<Value *> il)
  : json (), _element_list (il)
{
}

Array::Array (json *parent)
  : json (parent)
{
}

Array::Array (const Array &other)
  : json (other)
{
  (void) clone (other);
}

Array::Array (const Value *ov, const Array &nv)
  : json (ov, nv)
{
  (void) clone (nv);
}

Array::~Array ()
{
  _clear ();
}

const wchar_t *
Array::parse (const wchar_t *json)
{
  if (json == 0)
    throw JSON_Syntax_Error (UNEX_END);

  if (_parent == 0)   // 1. Array (), 2. Array (const char *json)
    {
      _readp = json;

      if (*(_look_ahead ()) != _sc::begin_array)  // Expecting '['
        throw JSON_Syntax_Error (UNEX_END);

      _readp++;
    }
  else
    {
      _startp = json;
      _readp  = json + 1;
    }

  if (*_readp == 0)
    throw JSON_Syntax_Error (UNEX_END);

  if (! _element_list.empty ())
    _clear ();

  Value *v = 0;
  size_t next_idx = 0;

  while (*_readp != 0)
    {
      (void) _look_ahead ();

      if (*_readp == _sc::value_separator) // ','
        {
          _readp++;

          if ((v = _make_value ())->type () == Value::no_value_t)
            throw JSON_Syntax_Error (UNEX_TOKEN, *_readp);

          next_idx = _element_list.size ();

          if ((v = _call_reviver (v, 0, next_idx))->type () != Value::undefined_t)
            {
              _element_list.push_back (v);
              v->setIndex (next_idx);
            }
        }
      else if (*_readp == _sc::end_array)         // ']'
        return _readp + 1;

      else if ((v = _make_value ())->type () == Value::no_value_t)  // No valid value found
        {
          if (*_readp != Value::_ws::space
              && *_readp != Value::_ws::tab
              && *_readp != Value::_ws::lf
              && *_readp != Value::_ws::cr)
            throw JSON_Syntax_Error (UNEX_TOKEN, *_readp);

          // Empty array
        }
      else if ((v = _call_reviver (v, 0, next_idx))->type () != Value::undefined_t)  // Value found
        {
          _element_list.push_back (v);
          v->setIndex (next_idx);
        }
    }

  return _readp;
}

Value &
Array::_assign (const Array &nv)
{
  return _parent ? _parent->_assign (this, new Array (this, nv)) : *(clone (nv));
}

Value &
Array::_at (size_t index)
{
  try
    {
      return *_element_list.at (index);
    }
  catch (std::out_of_range &)
    {
      Value *v = new undefined (this);

      _element_list.push_back (v);
      v->setIndex (_element_list.size () - 1);

      return *v;
  }
}

Value &
Array::_assign (Value *ov, Value *nv)
{
  size_t index = ov->index ();

  _element_list.at (index) = nv;

  nv->setIndex (index);
  nv->setParent (this);

  return *this;
}

void
Array::_clear ()
{
  for (auto it = _element_list.begin (); it != _element_list.end (); it = _element_list.erase (it))
    delete *it;
}

Value *
Array::clone (const Value &other)
{
  const Array & nv = dynamic_cast<const Array &> (other);

  _clear ();

  if (nv._element_list.empty ())
    return this;

  _element_list.reserve (nv._element_list.size ());

  std::transform (nv._element_list.begin (), nv._element_list.end (), std::back_inserter (_element_list), _clone_cb);

  return this;
}

JSON_Iterator *
Array::iterator () const
{
  return new Array_Iterator (_element_list);
}

size_t
Array::strLength () const noexcept
{
  if (_element_list.empty ())
    return 2;

  size_t len = 1;   // [

  auto end = _element_list.cend ();
  auto cur = _element_list.cbegin ();

  while (cur != end)
    len += ((*cur++)->strLength () + 1);   // , or ]

  return len;
}

const wchar_t *
Array::strValue (wchar_t *offset) const
{
  wchar_t *str_value[2] = { 0, 0 };

  if (offset)
    str_value[OFFSET] = offset;

  else if (_str_value[BEGIN])
    return _str_value[BEGIN];

  else
    str_value[OFFSET] = new wchar_t[strLength () + 1] ();

  str_value[BEGIN] = str_value[OFFSET];

  *(str_value[OFFSET]++) = _sc::begin_array;

  auto end = _element_list.cend ();
  auto cur = _element_list.cbegin ();

  while (cur != end)
    {
      Value *v = *cur;
      str_value[OFFSET] = _str_append (str_value[OFFSET], v->strValue (str_value[OFFSET]), v->strLength ());

      if (++cur != end)
        *(str_value[OFFSET]++) = _sc::value_separator;
    }

  *(str_value[OFFSET]++) = _sc::end_array;

  if (offset == 0)
    _str_value[BEGIN] = str_value[BEGIN];

  return str_value[BEGIN];
}

Value &
Array::erase (const Value &v) noexcept
{
  size_t index = v.index ();

  if (index == _element_list.size ())
    return *this;

  (void) _element_list.erase (_element_list.cbegin () + index);

  return *this;
}
