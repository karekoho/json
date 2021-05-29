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
  _clone (other);
}

format::json::value &
format::json::string::operator =(const wchar_t * const s)
{
  json *p = _parent;
  _parent = nullptr;

  _clear ();

  (void) _parse (s);

  _parent = p;

  return *this;
}

const wchar_t *
format::json::string::_parse (const wchar_t * const json)
{
  wchar_t endc  = 0;
  long charc    = 0;

  _startp =_readp = json;

  if (_parent == nullptr)   // 2. ctor
    {
      if ((charc = __string (endc)) < 0 )
        throw json_syntax_error (UNEXPECTED_TOKEN, _readp, 1);

      _charc = static_cast<size_t> (charc);
    }

  _readp += _charc;

  // Make unquoted string
  __assign_unquoted_string ();

  // Make quoted string
  __assign_quoted_string ();

  return _readp;
}

void
format::json::string::_clear ()
{
  _string_value[0].clear ();
  _string_value[1].clear ();
}

format::json::value &
format::json::string::_assign (const string &nv)
{
  return _parent ? __call__assign (_parent, this, new string (nv)) : *(_clone (nv));
}

const wchar_t *
format::json::string::_to_string (wchar_t *) const
{
  return (_startp == nullptr || _charc == 0)
      ? L"\"\""
      : _string_value[1].c_str ();
}

size_t
format::json::string::_str_length () const noexcept
{
  if (_startp == nullptr || _charc == 0)
    return 2;

  return *_startp == _sc::double_quote
            ? _charc
            : _charc + 2;
}

format::json::value *
format::json::string::_clone (const value &nv)
{
  const string & other = dynamic_cast<const string &> (nv);

  if (other._startp && other._charc > 0)
    *other._startp == _sc::double_quote
          ? _string_value[0].assign (other._startp + 1, other._charc - 2)
          : _string_value[0].assign (other._startp, other._charc);

  _string_value[1] = other._string_value[1]; // Always at least ""
  _startp = _string_value[0].c_str (); // if other is null or "", _startp points to itself

  return this;
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

void
format::json::string::__assign_unquoted_string ()
{
  *_startp == _sc::double_quote
    ? _string_value[0].assign (_startp + 1, _charc - 2)
    : _string_value[0].assign (_startp, _charc);
}

void
format::json::string::__assign_quoted_string ()
{
  if (*_startp == _sc::double_quote)
    _string_value[1].assign (_startp, _charc);
  else
    {
      try
        {
          size_t charc = _charc + 2;
          wchar_t *s = new wchar_t[charc] ();

          *s = L'"';
          *(wcsncpy (s + 1, _startp, _charc) +_charc) = L'"';
          _string_value[1].assign (s, _charc + 2);

          delete[] s;
        }
      catch (std::bad_alloc & ba)
        {
          throw json_error (ba.what ());
        }
    }
}
