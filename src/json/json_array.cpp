#include "json_array.h"

Array::Array() : JSON (){}

Array::Array (const char *json)
  : JSON::JSON (json)
{
}

Array::Array (JSON *parent)
  : JSON::JSON (parent)
{
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

  Value *v = 0;

  while (*_readp != 0)
    {
      (void) _look_ahead ();

      if (*_readp == _sc::value_separator) /// ','
        {
          _readp++;

          if ((v = _make_value ())->type () == Value::undefined)
            throw "syntax error: unexpected ','";

          _element_list.push_back (v);
          v->setIndex (_element_list.size () - 1);
        }
      else if (*_readp == _sc::end_array)         /// ']'
        return _readp + 1;

      else if ((v = _make_value())->type () == Value::undefined)  /// No valid value found
        {
          if (*_readp != Value::_ws::space /** TODO: check other ws_ characters */)
            throw "array::parse: unexpected character";

          /// empty array
        }
      else  /// Value found
        {
          _element_list.push_back (v);
          v->setIndex (_element_list.size () - 1);
        }
    }

  return _readp;
}

/* const Value &
Array::at (size_t index) const
{
  return *(_element_list.at (atoll (index)));
} */
