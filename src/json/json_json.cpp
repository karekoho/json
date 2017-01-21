#include "json_json.h"
#include "json_object.h"
#include "json_array.h"
#include "json_string.h"
#include "json_number.h"
#include "json_null.h"
#include "json_undefined.h"
#include "json_boolean.h"
#include "json_leaf_iterator.h"

JSON::JSON ()
  : Value (),
    _str_value { 0, 0 },
    __root (0)
{
}

JSON::JSON (const wchar_t *json, const bool _parse)
  : Value (json),
    _str_value { 0, 0 },
    __root (0)
{
  if (json == 0)
    throw JSON::error ("null string");

  _startp = json;

  if (_parse)
    (void) parse (json);
}

JSON::JSON (JSON *parent)
  : Value (parent),
    _str_value { 0, 0 },
    __root (0)
{
}

JSON::JSON (const JSON &other)
  : Value (other),
    _str_value { 0, 0 },
   __root (other.__root ? other.__root->clone () : 0)
{
}

JSON::JSON (const Value *ov, const JSON &nv)
  : Value (ov, nv),
    _str_value { 0, 0 },
   __root (nv.__hasRoot () ? nv.__root->clone () : 0)
{
}

JSON::~JSON ()
{
  if (_parent == 0 && _str_value[BEGIN])
    {
      delete[] _str_value[BEGIN];

      _str_value[BEGIN] = 0;
    }

  delete __root;
}

const wchar_t *
JSON::JSON::parse (const wchar_t *readp)
{
  if (readp == 0 || *readp == 0)
    throw readp;

  _readp = readp;

  // if (*_readp == 0) throw _readp;

  Value * old_root = __root;

  __root = _make_value ();

  delete old_root;

  if (*(_look_ahead ()) != 0)
    throw _readp;

  return _readp;
}

Value &
JSON::_assign (const JSON &j)
{
  if (j.__hasRoot ())
    {
      delete __root;

      __root = j.__root->clone ();
    }

  return *this;
}

Value &
JSON::_assign (const Value &v)
{
  delete __root;

  __root = v.clone ();

  return *this;
}

Value *
JSON::_make_value ()
{
  Value *value_  = 0;
  long int charc = 0;

  wchar_t endc = 0;
  wchar_t readc = *(_look_ahead ());

  if (readc == _sc::double_quote)           // String
    {
      if ((charc = _string (endc)) < 0)
        throw JSON::syntax_error ("syntax error: expecting closing '\"'");

      value_ = new String (this, charc);
    }
  else if (readc == _sc::begin_object)      // Object
    value_ = new Object (this);

  else if (readc == _sc::begin_array)       // Array
    value_ = new Array (this);

  else if (isdigit (readc) || readc == '-') // Number
    value_ = new Number (this);

  else                                      // Literal or Undefined
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
