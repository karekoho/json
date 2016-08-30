#include "json_array.h"

Array::Array (const char *json)
  : json::json (json)
{
}

Array::Array (const char *endp, value *parent, size_t charc)
  : json::json (endp, parent, charc)
{
}

const char *
Array::parse (const char *json)
{
  if (json == 0)
    throw json::error ("error: null string given");

  if (_parent == 0)
    {
      _readp = json;

      if (_charc == 0) /// 1. constructor called with null or zero length string
        _endp = _readp + strlen (json);

      if (*(_look_ahead ()) != sc_::begin_array)
        throw "syntax error: expecting '['";
    }
  else
    _readp = json + 1;

  value *v = 0;

  while (_readp < _endp)
    {
      (void) _look_ahead ();

      if (*_readp == sc_::value_separator) // ','
        {
          _readp++;

          if ((v = _make_value ())->type () == value::undefined)
            throw "syntax error: unexpected ','";

          _element_list.push_back (v);
        }
      else if (*_readp == sc_::end_array)         // ']'
        return _readp + 1;

      else if (_make_value ()->type () == value::undefined) // No valid value found
        {
          if (*_readp != value::ws_::space /** TODO: check other ws_ characters */)
              throw "array::parse: unexpected character";
          // empty array
        }
      else  // Value found
        _element_list.push_back (_make_value ());
    }

  return _readp;
}

const value &
Array::at (const char *key) const
{
  // size_t index = atoll (key);
  return *(_element_list.at (atoll (key)));
}


