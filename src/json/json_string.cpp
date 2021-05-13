#include "json_string.h"
#include "json_json.h"

format::json::string::string ()
  : leaf (),
    _startp (nullptr),
    _charc (0)
{}

format::json::string::string (const wchar_t *json)
  : leaf (json),
    _startp (nullptr),
    _charc (0)
{
  if (json == nullptr)
    throw json_syntax_error (UNEX_END);

  (void) _parse (json);
}

format::json::string::string (json *parent, size_t charc)
  : leaf (parent),
    _startp (nullptr),
    _charc (charc)
{}

format::json::string::string (const string &other)
  : leaf (other),
    _startp (other._startp),
    _charc (other._charc)
{
  _clone (other);
}

const wchar_t *
format::json::string::_parse (const wchar_t *json)
{
  wchar_t endc  = 0;
  long charc    = 0;

  _startp =_readp = json;

  if (_parent == nullptr)   // 2. ctor
    {
      if ((charc = __string (endc)) < 0 )
        throw json_syntax_error (UNEX_TOKEN, _readp, 1);

      _charc = static_cast<size_t> (charc);
    }

  return _readp += _charc;
}

format::json::value &
format::json::string::_assign (const string &nv)
{
  return _parent ? __call__assign (_parent, this, new string (nv)) : *(_clone (nv));
}

const wchar_t *
format::json::string::get () const
{
  if (_string_value[0].empty () && _startp && _charc > 0)
    *_startp == _sc::double_quote
      ? _string_value[0].assign (_startp + 1, _charc - 2)
      : _string_value[0].assign (_startp, _charc);

  return _string_value[0].c_str ();
}

const wchar_t *
format::json::string::_to_string (wchar_t *) const
{
  if (_startp == nullptr || _charc == 0)
    return L"";

  if (_string_value[1].empty ())
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

  return _string_value[1].c_str ();
}

format::json::value *
format::json::string::_clone (const value &nv)
{
  const string & s = dynamic_cast<const string &> (nv);

  if (s._startp && s._charc > 0)
    *s._startp == _sc::double_quote
        ? _string_value[0].assign (s._startp + 1, s._charc - 2)
        : _string_value[0].assign (s._startp, s._charc);

  _startp = _string_value[0].c_str ();

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
