#include "basic_json.h"

// json::undefined __default;

 json::json (const char *json)
  : value (json),
  __value (0)
{

}

json::json (const char *endp, value *parent, size_t charc)
  : value (endp, parent, charc),
  __value (0)
{

}

json::~json()
{

}

const char *
json::json::parse (const char *readp)
{
  value *value_ = 0;

  _startp = readp;
  _readp  = readp;

  if (_endp == 0) {     // 1. ctor
      _endp = readp + strlen (readp);
  }

  _look_ahead ();

  if (*_readp == sc_::begin_object) {
      //_readp++;
      value_ = new json::object (_endp, this, _charc);
    }
  else if (*_readp == sc_::begin_array) {
      //_readp++;
     value_ = new json::array (_endp, this, _charc);
    }

  /**
    JSON:parse accepts:
    JSON.parse('{}');              // {}
    JSON.parse('[]');              // []
    JSON.parse('true');            // true
    JSON.parse('"foo"');           // "foo"
    JSON.parse('null');            // null
    */

  else {
      throw "syntax error near x";
    }

  _readp = value_->parse (_readp + 1);

  delete __value;

  __value = value_;

  return _readp;
}

const value &
json::at (const char *key) const
{
  return type () == value::undefined
      ? *(new json::undefined) // FIXME: leak
      : __value->at (key);
}





