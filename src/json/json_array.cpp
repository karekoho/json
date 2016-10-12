#include "json_array.h"
#include "json_array_iterator.h"

#include <algorithm>

Array::Array () : JSON () {}

Array::Array (const char *json)
  : JSON (json, false)
{
  (void) parse (json);
}

Array::Array (JSON *parent)
  : JSON (parent)
{
}

Array::Array (const Array &other)
  : JSON (other)
{
  (void) clone (other);
}

Array::Array (const Value *ov, const Array &nv)
  : JSON (ov, nv)
{
  (void) clone (nv);
}

Array::~Array ()
{
  _clear ();
}

const char *
Array::parse (const char *json)
{
  if (json == 0)
    throw JSON::error ("error: null string given");

  if (_parent == 0)   // 1. Array (), 2. Array (const char *json)
    {
      _readp = json;

      if (*(_look_ahead ()) != _sc::begin_array)
        throw "syntax error: expecting '['";

      _readp++;
    }
  else
    {
      _startp = json;
      _readp  = json + 1;
    }

  if (*_readp == 0)
    throw _readp;

  if (! _element_list.empty ())
    _clear ();

  Value *v = 0;

  while (*_readp != 0)
    {
      (void) _look_ahead ();

      if (*_readp == _sc::value_separator) // ','
        {
          _readp++;

          if ((v = _make_value ())->type () == Value::undefined)
            throw "syntax error: unexpected ','";

          _element_list.push_back (v);
          v->setIndex (_element_list.size () - 1);
        }
      else if (*_readp == _sc::end_array)         // ']'
        return _readp + 1;

      else if ((v = _make_value ())->type () == Value::undefined)  // No valid value found
        {
          if (*_readp != Value::_ws::space /* TODO: check other ws_ characters */)
            throw "array::parse: unexpected character";

          // Empty array
        }
      else  // Value found
        {
          _element_list.push_back (v);
          v->setIndex (_element_list.size () - 1);
        }
    }

  return _readp;
}

Value &
Array::at (size_t index) const
{
  try
    {
      return *(_element_list.at (index));
    }
  catch (std::out_of_range &e)
    {
      throw JSON::out_of_range (e.what ());
    }
}

Value &
Array::_assign (const Array &nv)
{
  return _parent ? _parent->assign (this, new Array (this, nv)) : *(clone (nv));
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
      Value *v = new Undefined (this);

      _element_list.push_back (v);
      v->setIndex (_element_list.size () - 1);

      return *v;
  }
}

Value &
Array::assign (Value *ov, Value *nv)
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
  const Array &nv = dynamic_cast<const Array &> (other);

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

const char *
Array::strValue () const
{
  _str_value[CURSOR] = _parent && _parent->_str_value[CURSOR]
      ? _parent->_str_value[CURSOR]
      : new char[strLength () + 1] ();

  _str_value[BEGIN] = _str_value[CURSOR];

  *(_str_value[CURSOR]++) = _sc::begin_array;

  auto end = _element_list.cend ();
  auto cur = _element_list.cbegin ();

  while (cur != end)
    {
      Value *v = *cur;
      _str_value[CURSOR] = _str_append (_str_value[CURSOR], v->strValue (), v->strLength ());

      if (++cur != end)
        *(_str_value[CURSOR]++) = _sc::value_separator;
    }

  *(_str_value[CURSOR]++) = _sc::end_array;

  return _str_value[BEGIN];
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
