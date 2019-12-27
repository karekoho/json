#include "json_json.h"
#include "json_object.h"
#include "json_array.h"
#include "json_string.h"
#include "json_number.h"
#include "json_null.h"
#include "json_undefined.h"
#include "json_boolean.h"

format::json::json ()
  : value (),
    _str_value { nullptr, nullptr },
    __root (nullptr),
    __reviver (nullptr)
{}

format::json::json (const wchar_t *json)
  : value (json),
    _str_value { nullptr, nullptr },
    __root (nullptr),
    __reviver (nullptr)
{
  if (json == nullptr)
    throw json_syntax_error (UNEX_END);

  (void) _parse (json);
}

format::json::json (const wchar_t *json, const bool _call_parse)
  : value (json),
    _str_value { nullptr, nullptr },
    __root (nullptr),
    __reviver (nullptr)
{
  if (json == nullptr)
    throw json_syntax_error (UNEX_END);

  if (_call_parse)
    (void) _parse (json);
}

format::json::json (const wchar_t *json, reviver r)
  : value (json),
    _str_value { nullptr, nullptr },
    __root (nullptr),
    __reviver (r)
{
  if (json == nullptr)
    throw json_syntax_error (UNEX_END);

  (void) _parse (json);

  __reviver = nullptr;
}

format::json::json (json *parent)
  : value (parent),
    _str_value { nullptr, nullptr },
    __root (nullptr),
    __reviver (parent ? parent->__reviver : nullptr)
{}

format::json::json (object *o)
  : value (),
  _str_value { nullptr, nullptr },
  __root (o),
  __reviver (nullptr)
{}

format::json::json (array *a)
  : value (),
  _str_value { nullptr, nullptr },
  __root (a),
  __reviver (nullptr)
{}

format::json::json (const json &other)
  : value (other),
    _str_value { nullptr, nullptr },
    __root (other.__root ? other.__root->clone () : nullptr),
    __reviver (nullptr)
{}

format::json::~json ()
{
  delete[] _str_value[BEGIN];
  _str_value[BEGIN] = nullptr;

  delete __root;
}

format::value &
format::json::point (const wchar_t *json_pointer)
{
  if (json_pointer == nullptr)
    throw json_pointer_error ("JSON pointer is null");

  reference_token rt (json_pointer);
  return _point (rt, *this);
}

const wchar_t *
format::json::json::_parse (const wchar_t *readp)
{
  _readp = readp;

  if ((__root = _make_value ())->type () == value::no_value_t)
    __root = nullptr;

  if (*(_look_ahead ()) != 0)
    throw json_syntax_error (UNEX_TOKEN, *_readp);

  return _readp;
}

format::value &
format::json::_at (const wchar_t *key)
{
  if (! __hasRoot ())
    __root = new object ();

  return (*__root)[key];
}

format::value &
format::json::_at (size_t index)
{
  if (! __hasRoot ())
    __root = new array ();

  return (*__root)[index];
}

format::value &
format::json::_assign (const json &j)
{
  if (j.__hasRoot ())
    {
      delete __root;
      __root = j.__root->clone ();
    }
  return *this;
}

format::value &
format::json::operator =(format::array *a)
{
  delete __root;
  __root = a;
  return *this;
}

format::value &
format::json::operator =(format::object *o)
{
  delete __root;
  __root = o;
  return *this;
}

format::value *
format::json::_make_value ()
{
  value *value_  = nullptr;
  long charc = 0;

  wchar_t endc = 0;
  wchar_t readc = *(_look_ahead ());

  if (readc == _sc::double_quote)           // string
    {
      if ((charc = _string (endc)) < 0)
        throw json_syntax_error (UNEX_TOKEN, *_readp);

      value_ = __call_string (this, static_cast<size_t> (charc));
    }
  else if (readc == _sc::begin_object)      // object
    value_ = __call_object (this);

  else if (readc == _sc::begin_array)       // array
    value_ = __call_array (this);

  else if (isdigit (readc) || readc == '-') // number
    value_ = __call_number (this);

  else
     {  // literal or udefined
      switch (_is_literal ())
        {
          case value::_literal::null_value:
            value_ = __call_null (this);
            break;
          case value::_literal::true_value :
            value_ = __call_boolean (this, true);
            break;
          case value::_literal::false_value:
            value_ = __call_boolean (this, false);
            break;
          default:
            value_ = no_value::instance (this);
            break;
        }
    }

  _readp = __call__parse (value_, _readp);

  return value_;
}

format::value *
format::json::_call_reviver (value *v, const wchar_t *key, size_t index) const
{
  if (__reviver == nullptr)
    return v;

  value *r = (__reviver) (key == nullptr ? std::to_wstring (index).c_str () : key, v);

  if (r != v)
    delete v;

  return r;
}
