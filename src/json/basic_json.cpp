#include "basic_json.h"

json::json(const char *json)
  : value (json),
  __value (0)
{

}

json::json (const char *json, const char *endp, value *parent, size_t lexlen)
  : value (json, endp, parent, lexlen),
  __value (0)
{

}

const char *
json::json::parse (const char *readp)
{
  value *value_ = 0;

  _startp = readp;
  _readp  = readp;

  if (_endp == 0) {
      _endp = readp + strlen (readp);
  }

  // do {
  _look_ahead ();

  if (*readp == sc_::begin_object) {
      // value_ = new json::object ();
    }
  else if (*readp == sc_::begin_array) {
      // value_ = new json::array ();
    }
  else {
      throw "syntax error near x";
    }

  readp = value_->parse (readp);

  delete __value;

  __value = value_;

  //} while (readp < _endp);

  return readp;
}

const value &
json::json::at (const char *key) const
{
}

value::otype
json::type () const
{
}

size_t
json::size () const
{
}
