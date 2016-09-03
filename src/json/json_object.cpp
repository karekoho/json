#include "json_object.h"
#include "json_string.h"
#include "json_undefined.h"
#include "json_null.h"
#include "json_number.h"
#include "json_boolean.h"

Object::Object (const char *json)
  : JSON::JSON (json)
{
}

Object::Object (const char *endp, Value *parent, size_t charc)
  : JSON::JSON (endp , parent, charc)
{
}

const char *
Object::parse (const char *json)
{
  if (json == 0)
    throw JSON::error ("error: null string given");

  if (_parent == 0)
    {
      _readp = json;

      if (_charc == 0)  /// 1. constructor called with null or zero length string
        _endp = _readp + strlen (json);

      if (*(_look_ahead ()) != _sc::begin_object)
        throw "syntax error: expecting '{'";

      _readp++;
    }
  else
     _readp = json + 1;

  if (*_readp == 0)
    throw _readp;

  while (_readp < _endp)
    {
      (void) _look_ahead ();

      if (*_readp == _sc::value_separator)   // ','
        {
          _readp++;

          if (! _pair ())
            throw "syntax error: unexpected ','";
        }
      else if (*_readp == _sc::end_object)         // '}'
        return _readp + 1;

      else
        _pair ();
    }

  return _readp;
}

bool
Object::_pair ()
{
  char endc = 0;
  // wchar_t endc;

  long int charc = 0;

  (void) _look_ahead ();

  /// Expect "key"
  if ((charc = _string (endc)) == 0)  /// No opening \"
    {
      if (*_readp == 0)
        throw JSON::syntax_error ("syntax error: expecting closing '}'");

      if (*_readp == _sc::end_object || *(_look_ahead ()) ==  _sc::end_object)  /// Empty object
        return false;
    }

  if (charc < 0)   /// No closing "
    throw JSON::syntax_error ("syntax error: expecting closing '\"'");

  const char *keyp = _readp + 1;
  _readp += charc;

  if (*(_look_ahead ()) != _sc::name_separator)   /// Expect ':'
    throw JSON::syntax_error ("pair: syntax error: expecting ':'");   /// TODO: throw syntax error: unexpected character '%c'

  _readp++;

  Value * v = _make_value ();

  if (v->type () == Value::undefined)
    throw "syntax error: expecting value after ':'";

  _member_list.emplace (std::string (keyp, charc - 2), v);

  return true;
}

const Value &
Object::at (const char *key) const
{
  try
    {
      return *(_member_list.at (key));
    }
  catch (std::out_of_range &e)
    {
      throw JSON::out_of_range (e.what ());
    }
}
