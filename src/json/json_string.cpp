#include "json_string.h"
#include "json_json.h"

format::json::string::string ()
  : leaf (),
    _startp (nullptr),
    _charc (0)
{}

format::json::string::string (const wchar_t *const json)
  : leaf (json),
    _startp (nullptr),
    _charc (0)
{
  if (json == nullptr)
    throw json_syntax_error (UNEXPECTED_END_OF_INPUT);

  (void) _parse (json);
}

format::json::string::string (json *parent, size_t charc)
  : leaf (parent),
    _startp (nullptr),
    _charc (charc)
{}

format::json::string::string (const string &other)
  : leaf (other),
    _startp (nullptr),
    _charc (other._charc)
{
  _string_value.assign (other._string_value.c_str (), other.length ()); // Always at least ""
}

const wchar_t *
format::json::string::_parse (const wchar_t * const json)
{
  wchar_t endc  = 0;
  long charc    = 0;

  _startp =_readp = json;

  if (_parent == nullptr) // 2. constructor
    {
      if ((charc = __string (endc)) < 0 )
        throw json_syntax_error (UNEXPECTED_TOKEN, _readp, 1);

      _charc = static_cast<size_t> (charc);
      _string_value.assign (_startp, _charc);
    }
  else if (_charc > 1)  // 3. constructor
    {
      // value::_make_value shuold always call string () with charc >= 2, e.g. L"\"x\"" == 3
      _string_value.assign (_startp + 1, _charc - 2); // Strip quotes
    }

  return (_readp += _charc);
}

size_t
format::json::string::_str_length () const noexcept
{
  if ((_parent == nullptr && _startp == nullptr ) || _charc == 0) // 1. default constructor, or 3.
    return 2; // 0 + 2

  return _parent  // 2. or 3.
      ? _charc    // value::_make_value shuold always call string () with charc >= 2, e.g. L"\"x\"" == 3
      : _charc + 2;
}

long
format::json::string::__string (wchar_t & endc) const noexcept
{
  const wchar_t * readp = _readp;

  if ((*readp > 0 && *readp < 32) || *readp == _sc::double_quote)
    return -1;

  while (*readp > 31 && *readp != _sc::double_quote)
    readp++;

  endc = *readp;
  long charc = readp - _readp;

  return *readp == 0
      ? charc
      : (*readp > 31 && *readp != _sc::double_quote
         ? charc
         : -1 * charc);
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
