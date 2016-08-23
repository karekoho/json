#include "basic_json.h"

 json::json(const char *json)
  : value (json),
  __value (0)
{

}

json::json (const char *endp, value *parent, size_t charc)
  : value (endp, parent, charc),
  __value (0)
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
     value_ = new json::object (_endp, this, _charc);
    }
  else if (*_readp == sc_::begin_array) {
     value_ = new json::array (_endp, this, _charc);
    }
  else {
      throw "syntax error near x";
    }

  _readp = value_->parse (_readp);

  delete __value;

  __value = value_;

  return _readp;
}

const value &
json::json::at (const char *key) const
{
}

value::otype
json::type () const
{
    // return value::otype::empty;
    return __value == 0 ? value::otype::undefined : __value->type ();
}

size_t
json::size () const
{
}





