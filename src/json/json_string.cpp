#include "json_string.h"
#include "json_json.h"
using namespace format;

string::string() : leaf (), _charc (0) {}

string::string (const wchar_t *json)
  : leaf (json),
    _charc (0)
{
  if (json == 0)
    throw json_syntax_error ("Unexpected end of JSON input");

  (void) parse (json);
}

string::string (json *parent, size_t charc)
  : leaf (parent),
    _charc (charc)
{
}

string::string (const string &other)
  : leaf (other),
    _charc (other._charc)
{
  clone (other);
}

string::string (const value *ov, const string &nv)
  : leaf (ov, nv),
    _charc (nv._charc)
{
  clone (nv);
}

const wchar_t *
string::parse (const wchar_t *json)
{
  wchar_t endc   = 0;
  long charc  = 0;

  _startp =_readp = json;

  _string_value[0].clear ();

  if (_parent == 0)   // 2. ctor
    {
      if ((charc = _string (endc)) <= 0 )
        throw json_syntax_error ("Unexpected token ", *_readp);

      _charc = (size_t) charc;
    }

  return _readp += _charc;
}

value &
string::_assign (const string &nv)
{
  return _parent ? _parent->_assign (this, new string (this, nv)) : *(clone (nv));
}

const wchar_t *
string::get () const
{
  if (_string_value[0].empty () && _startp && _charc > 0)
    _string_value[0].assign (_startp + 1, _charc - 2);

  return _string_value[0].c_str ();
}

const wchar_t *
string::strValue (wchar_t *) const
{
  if (_startp == 0 || _charc == 0)
    return L"";

  if (_string_value[1].empty ())
    _string_value[1].assign (_startp, _charc);

  return _string_value[1].c_str ();
}

value *
string::clone (const value &nv)
{
  const string & s = dynamic_cast<const string &>(nv);

  if (s._startp && s._charc > 0)
    _string_value[0].assign (s._startp + 1, s._charc - 2);

  _startp = _string_value[0].c_str ();

  return this;
}
