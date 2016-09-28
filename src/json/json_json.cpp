#include "json_json.h"
#include "json_object.h"
#include "json_array.h"
#include "json_string.h"
#include "json_number.h"
#include "json_null.h"
#include "json_undefined.h"
#include "json_boolean.h"
#include "json_leaf_iterator.h"

JSON::JSON () : Value (), __root (0) {}

JSON::JSON (const char *json, const bool _parse)
  : Value (json),
    _str_value { 0, 0 },
    __root (0)

{
  if (_length == 0)
    throw JSON::error ("null string");

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
   __root (other.__root ? other.__root->_clone () : 0)
{
}

JSON::~JSON ()
{
  delete __root;
}

const char *
JSON::JSON::parse (const char *readp)
{
  if (readp == 0)
    throw readp;

  _readp = _startp = readp;

  if (*_readp == 0)
    throw _readp;

  Value * prev_value_ = __root;

  __root = _make_value ();

  delete prev_value_;

  if (*(_look_ahead ()) != 0)
    throw _readp;

  return _readp;
}

Value &
JSON::_assign (JSON &j)
{
  delete __root;

  __root = j._clone ();

  return *this;
}

Value &
JSON::_assign (Value &v)
{
  delete __root;

  __root = v._clone ();

  return *this;
}

Value &
JSON::_at (const char *key)
{
  try
    {
      return type () == Value::undefined ? *(new Undefined) : __root->at (key);
    }
  catch (JSON::out_of_range &)
    {
      return *(new Undefined);
    }
}

Value *
JSON::_make_value ()
{
  Value *value_  = 0;
  long int charc = 0;

  char endc = 0;
  char readc = *(_look_ahead ());

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

Iterator *
JSON::iterator () const
{
  return __root ? __root->iterator () : 0; // TODO: new Leaf_Iterator (new Undefined);  // FIXME: leak
}

const char *
JSON::stringify ()  noexcept
{
  return "";
}

size_t
JSON::strLength () const  noexcept
{
  return 0;
}
