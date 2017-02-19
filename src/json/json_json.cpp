#include "json_json.h"
#include "json_object.h"
#include "json_array.h"
#include "json_string.h"
#include "json_number.h"
#include "json_null.h"
#include "json_undefined.h"
#include "json_boolean.h"
#include "json_leaf_iterator.h"
using namespace Format;

json::json ()
  : Value (),
    _str_value { 0, 0 },
    __root (0),
    __reviver (0)
{
}

json::json (const wchar_t *json, const bool _parse)
  : Value (json),
    _str_value { 0, 0 },
    __root (0),
    __reviver (0)
{
  if (json == 0)
    throw JSON_Syntax_Error (UNEX_END);

  _startp = json;

  if (_parse)
    (void) parse (json);
}

json::json (const wchar_t *json, Reviver r)
  : Value (json),
    _str_value { 0, 0 },
    __root (0),
    __reviver (r)
{
  if (json == 0)
    throw JSON_Syntax_Error (UNEX_END);

  _startp = json;

  (void) parse (json);

  __reviver = 0;
}


json::json (json *parent)
  : Value (parent),
    _str_value { 0, 0 },
    __root (0),
    __reviver (parent ? parent->__reviver : 0)
{
}

json::json (const json &other)
  : Value (other),
    _str_value { 0, 0 },
    __root (other.__root ? other.__root->clone () : 0),
    __reviver (0)
{
}

json::json (const Value *ov, const json &nv)
  : Value (ov, nv),
    _str_value { 0, 0 },
    __root (nv.__hasRoot () ? nv.__root->clone () : 0),
    __reviver (0)
{
}

json::~json ()
{
  if (_parent == 0 && _str_value[BEGIN])
    {
      delete[] _str_value[BEGIN];

      _str_value[BEGIN] = 0;
    }

  delete __root;
}

const wchar_t *
json::json::parse (const wchar_t *readp)
{
  if (readp == 0 || *readp == 0)
    throw JSON_Syntax_Error (UNEX_END);

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
json::_assign (const json &j)
{
  if (j.__hasRoot ())
    {
      delete __root;

      __root = j.__root->clone ();
    }

  return *this;
}

Value &
json::_assign (const Value &v)
{
  delete __root;

  __root = v.clone ();

  return *this;
}

Value *
json::_make_value ()
{
  Value *value_  = 0;
  long int charc = 0;

  wchar_t endc = 0;
  wchar_t readc = *(_look_ahead ());

  if (readc == _sc::double_quote)           // String
    {
      if ((charc = _string (endc)) < 0)
        throw JSON_Syntax_Error (UNEX_TOKEN, *_readp);

      value_ = new string (this, charc);
    }
  else if (readc == _sc::begin_object)      // Object
    value_ = new Object (this);

  else if (readc == _sc::begin_array)       // Array
    value_ = new Array (this);

  else if (isdigit (readc) || readc == '-') // Number
    value_ = new number (this);

  else                                      // Literal or Undefined
    switch (_is_literal ())
      {
      case Value::_literal::null_value:
        value_ = new null (this);
        break;
      case Value::_literal::true_value :
        value_ = new Boolean (this, true);
        break;
      case Value::_literal::false_value:
        value_ = new Boolean (this, false);
        break;
      default:
        value_ = No_Value::instance (this);
        break;
      }

  _readp = value_->parse (_readp);

  return value_;
}

Value *
json::_call_reviver (Value *v, const wchar_t *key, size_t index) const
{
  if (__reviver == 0)
    return v;

  Value *r = (__reviver) (key == 0 ? std::to_wstring (index).c_str () : key, v);

  if (r != v)
    delete v;

  return r;
}


