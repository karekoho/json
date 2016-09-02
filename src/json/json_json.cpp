#include "json_json.h"
#include "json_object.h"
#include "json_array.h"
#include "json_string.h"
#include "json_number.h"
#include "json_null.h"
#include "json_undefined.h"
#include "json_boolean.h"

// const Undefined * const JSON::_undef_value = new Undefined;

JSON::JSON (const char *json)
  : Value (json),
    __value (0)
{
  if (_charc > 0)
    {
      _endp = _startp + _charc;
      (void) parse (json);
    }
}

JSON::JSON (const char *endp, Value *parent, size_t charc)
  : Value (endp, parent, charc),
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

  if (_charc == 0)  /// 1. constructor called with null or zero length string
    _endp = _readp + strlen (readp);

  if (_readp == _endp)
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
  // return type () == Value::undefined
  //? *(new Undefined)  // FIXME: leak
  //    : __value->at (key);

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

      value_ = new String (_endp, this, charc);
    }
  else if (readc == _sc::begin_object)      /// Object
    value_ = new Object (_endp, this, 0);

  else if (readc == _sc::begin_array)       /// Array
    value_ = new Array (_endp, this, 0);

  else if (isdigit (readc) || readc == '-') /// Number
    value_ = new Number (_endp, this, 0);

  else                                      /// Literal or undefined
    switch (_is_literal ())
      {
      case Value::_literal::null_value:
        value_ = new Null (_endp, this);
        break;
      case Value::_literal::true_value :
        value_ = new Boolean (true);
        break;
      case Value::_literal::false_value:
        value_ = new Boolean (false);
        break;
      default:
        value_ = new Undefined;
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
