#include "json_json.h"
#include "json_object.h"
#include "json_array.h"
#include "json_string.h"
#include "json_number.h"
#include "json_null.h"
#include "json_undefined.h"
#include "json_boolean.h"

JSON::JSON () : Value (), __value (0) {}

JSON::JSON (const char *json)
  : Value (json),
    __value (0)
{
  // if (_readp) (void) parse (json);
  if (_length == 0)
    throw JSON::error ("null string");
    // (void) parse (json);
}

JSON::JSON (Value *parent)
  : Value (parent),
    __value (0)
{
}

JSON::~JSON ()
{
  delete __value;
}

const char *
JSON::JSON::parse (const char *readp)
{
  if (readp == 0)
    throw readp;

  _readp = _startp = readp;

  if (*_readp == 0)
    throw _readp;

  Value * prev_value_ = __value;

  __value = _make_value ();

  delete prev_value_;

  if (*(_look_ahead ()) != 0)
    throw _readp;

  return _readp;
}

const Value &
JSON::at (const char *key) const
{
  return _at (key);
}

Value *
JSON::_make_value ()
{
  Value *value_  = 0;
  long int charc = 0;

  char endc = 0;
  char readc = *(_look_ahead ());

  if (readc == _sc::double_quote)           /// String
    {
      if ((charc = _string (endc)) < 0)
        throw JSON::syntax_error ("syntax error: expecting closing '\"'");

      value_ = new String (this, charc);
    }
  else if (readc == _sc::begin_object)      /// Object
    value_ = new Object (this);

  else if (readc == _sc::begin_array)       /// Array
    value_ = new Array (this);

  else if (isdigit (readc) || readc == '-') /// Number
    value_ = new Number (this);

  else                                      /// Literal or undefined
    switch (_is_literal ())
      {
      case Value::_literal::null_value:
        value_ = new Null (this);
        break;
      case Value::_literal::true_value :
        value_ = new Boolean (this, true);
        break;
      case Value::_literal::false_value:
        value_ = new Boolean (this, false);
        break;
      default:
        value_ = new Undefined (this);
        break;
      }

  _readp = value_->parse (_readp);

  return value_;
}

const Value &
JSON::_at (const char *key) const
{
  return type () == Value::undefined ? _undef_value : __value->at (key);
}
