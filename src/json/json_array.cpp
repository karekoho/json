#include "json_array.h"
#include "json_array_iterator.h"
#include <algorithm>

Array::Array() : JSON (){}

Array::Array (const char *json)
  : JSON::JSON (json, false)
{
  if (_length == 0)
    throw JSON::error ("null string");

  (void) parse (json);
}

Array::Array (JSON *parent)
  : JSON::JSON (parent)
{
}

Array::Array (const Array &other)
  : JSON (other)
{
  (void) _clone (other);
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

  if (_parent == 0)
    {
      _readp = json;

      if (*(_look_ahead ()) != _sc::begin_array)
        throw "syntax error: expecting '['";

      _readp++;
    }
  else
    _readp = json + 1;

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
Array::_assign (Array &nv)
{
  return _parent ? _parent->assign (this, &nv) : *(_clone (nv));
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
  _element_list.at (ov->index ()) = nv;

  return *this;
}

void
Array::_clear ()
{
  for (auto it = _element_list.begin (); it != _element_list.end (); it = _element_list.erase (it))
    delete *it;
}

Value *
Array::_clone (const Value &other)
{
  const Array &nv = static_cast<const Array &> (other);

  _clear ();

  if (nv._element_list.empty ())
    return this;

  _element_list.reserve (nv._element_list.size ());

  std::transform (nv._element_list.begin (), nv._element_list.end (), std::back_inserter (_element_list), _clone_cb);

  return this;
}

Iterator *
Array::iterator () const
{
  return new Array_Iterator (_element_list);
}

const char *
Array::stringify () noexcept
{
  char *dstp = _parent ? _parent->_str_value[CURSOR] : 0;

  return dstp ? Value::_str_append (dstp, strValue (), strLength ())
              : strValue ();
}

size_t
Array::strLength () const noexcept
{
  if (_element_list.empty ())
    return 2;

  size_t len = 1;   // [

  for (auto it = _element_list.cbegin (); it != _element_list.cend (); ++it)
    len += ((*it)->strLength () + 1);   // , or ]

  return len;
}

const char *
Array::strValue () const
{
  if (_parent && _parent->_str_value[CURSOR])
    _str_value[CURSOR] = _parent->_str_value[CURSOR];

  else
    {
      size_t len = strLength ();
      _str_value[CURSOR] = new char[len + 1] ();
    }

  _str_value[BEGIN] = _str_value[CURSOR];

  *(_str_value[CURSOR]++) = _sc::begin_array;

  for (auto it = _element_list.cbegin (); it != _element_list.cend (); ++it)
    {
      _str_value[CURSOR] = (char *) (*it)->stringify ();

      if ((it + 1) != _element_list.cend ())
        *(_str_value[CURSOR]++) = ',';
    }

  *(_str_value[CURSOR]++) = _sc::end_array;

  return _str_value[BEGIN];
}
