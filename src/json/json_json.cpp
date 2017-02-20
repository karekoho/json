#include "json_json.h"
#include "json_object.h"
#include "json_array.h"
#include "json_string.h"
#include "json_number.h"
#include "json_null.h"
#include "json_undefined.h"
#include "json_boolean.h"
#include "json_leaf_iterator.h"
using namespace format;

json::json ()
  : value (),
    _str_value { 0, 0 },
    __root (0),
    __reviver (0)
{
}

json::json (const wchar_t *json, const bool _parse)
  : value (json),
    _str_value { 0, 0 },
    __root (0),
    __reviver (0)
{
  if (json == 0)
    throw json_syntax_error (UNEX_END);

  _startp = json;

  if (_parse)
    (void) parse (json);
}

json::json (const wchar_t *json, reviver r)
  : value (json),
    _str_value { 0, 0 },
    __root (0),
    __reviver (r)
{
  if (json == 0)
    throw json_syntax_error (UNEX_END);

  _startp = json;

  (void) parse (json);

  __reviver = 0;
}


json::json (json *parent)
  : value (parent),
    _str_value { 0, 0 },
    __root (0),
    __reviver (parent ? parent->__reviver : 0)
{
}

json::json (const json &other)
  : value (other),
    _str_value { 0, 0 },
    __root (other.__root ? other.__root->clone () : 0),
    __reviver (0)
{
}

json::json (const value *ov, const json &nv)
  : value (ov, nv),
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
    throw json_syntax_error (UNEX_END);

  _readp = readp;

  // if (*_readp == 0) throw _readp;

  value * old_root = __root;

  __root = _make_value ();

  delete old_root;

  if (*(_look_ahead ()) != 0)
    throw _readp;

  return _readp;
}

value &
json::_assign (const json &j)
{
  if (j.__hasRoot ())
    {
      delete __root;

      __root = j.__root->clone ();
    }

  return *this;
}

value &
json::_assign (const value &v)
{
  delete __root;

  __root = v.clone ();

  return *this;
}

value *
json::_make_value ()
{
  value *value_  = 0;
  long int charc = 0;

  wchar_t endc = 0;
  wchar_t readc = *(_look_ahead ());

  if (readc == _sc::double_quote)           // String
    {
      if ((charc = _string (endc)) < 0)
        throw json_syntax_error (UNEX_TOKEN, *_readp);

      value_ = new string (this, charc);
    }
  else if (readc == _sc::begin_object)      // Object
    value_ = new object (this);

  else if (readc == _sc::begin_array)       // Array
    value_ = new array (this);

  else if (isdigit (readc) || readc == '-') // Number
    value_ = new number (this);

  else                                      // Literal or Undefined
    switch (_is_literal ())
      {
      case value::_literal::null_value:
        value_ = new null (this);
        break;
      case value::_literal::true_value :
        value_ = new boolean (this, true);
        break;
      case value::_literal::false_value:
        value_ = new boolean (this, false);
        break;
      default:
        value_ = no_value::instance (this);
        break;
      }

  _readp = value_->parse (_readp);

  return value_;
}

value *
json::_call_reviver (value *v, const wchar_t *key, size_t index) const
{
  if (__reviver == 0)
    return v;

  value *r = (__reviver) (key == 0 ? std::to_wstring (index).c_str () : key, v);

  if (r != v)
    delete v;

  return r;
}


