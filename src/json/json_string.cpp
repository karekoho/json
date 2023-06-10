#include "json_string.h"
#include "json_json.h"

format::json::string::string ()
  : leaf (),
    _startp (nullptr),
    _string_value (nullptr),
    _charc (0)
{
  (void) __assign (L"", 0);
}

format::json::string::string (const wchar_t *const string_text)
  : leaf (string_text),
    _startp (nullptr),
    _string_value (nullptr),
    _charc (0)
{
  if (string_text == nullptr)
    throw json_syntax_error (UNEXPECTED_END_OF_INPUT);

  (void) _parse (string_text);
}

format::json::string::string (json *parent, size_t charc)
  : leaf (parent, charc),
    _startp (nullptr),
    _string_value (nullptr),
    _charc (charc)
{ }

format::json::string::string (const string &other)
  : leaf (other),
    _startp (nullptr),
    _string_value (nullptr),
    _charc (other._charc)
{
  (void) __assign (other._to_string (), other.length ());
}

format::json::string::string (string &&other)
  : leaf (other),
    _startp (nullptr),
    _string_value (other._string_value),
    _charc (other._charc)
{
  other._charc = 0;
  other._string_value = nullptr;
}

format::json::string::~string ()
{
  delete [] _string_value;
  _string_value = nullptr;
}

const wchar_t *
format::json::string::_parse (const wchar_t * const json_text)
{
  wchar_t endc  = 0;
  size_t charc  = _charc;
  _startp =_readp = json_text;

  if (_parent == nullptr) // 2. constructor
    {
      long long valid_charc = _unquoted_string (_startp, _readp, endc); // validate

      if (endc > 0 && endc < _ws::space)
        throw json_syntax_error (UNEXPECTED_TOKEN, _readp + valid_charc, 1);

      (void) __assign (_startp, static_cast<size_t> (valid_charc));
    }
  else if (charc > 1)  // 3. constructor
    // value::_make_value shuold always call string () with charc >= 2, e.g. L"\"x\"" == 3
    (void) __assign (_startp + 1, charc - 2); // Strip quotes

  return (_readp += charc);
}

const wchar_t *
format::json::string::__assign (const wchar_t * const offset, size_t charc)
{
  try
    {
      wchar_t *new_string = new wchar_t[charc + 1] ();

      _string_value = new_string;
      _value.string = new_string;
      _charc = charc;

      return wcsncpy (new_string, offset, charc);
    }
  catch (const std::bad_alloc &e)
    {
      throw json_error(e.what ());
    }
}

/** format::json::value &
format::json::string::operator =(const wchar_t * const s)
{
  json *p = _parent;
  _parent = nullptr;
  _clear ();
  (void) _parse (s);
  _parent = p;
  return *this;
}

format::json::value &
format::json::string::_assign (const string &nv)
{
  return _parent ? __call__assign (_parent, this, new string (nv)) : *(_clone (nv));
} */
