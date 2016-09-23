#include "json_array.h"
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

  // if (nv._element_list.empty ()) return this;

  // TODO: assure that this._element_list is empty when other._element_list is empty.
  _element_list.reserve (nv._element_list.size ());

  std::transform (nv._element_list.begin (), nv._element_list.end (), std::back_inserter (_element_list), _clone_cb);

  return this;
}
