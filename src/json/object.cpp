#include "basic_json.h"

json::object::object (const char *json)
  : value (json),
    _pairc (0)
{
}

json::object::object (const char *endp, value *parent, size_t charc)
  : value (endp , parent, charc),
    _pairc (0)
{
}

const char *
json::object::parse (const char *json)
{
  // return json + _charc;
  _readp = json;


  /* do {
      (void) _look_ahead ();

      if (*_readp == sc_::begin_object) {             // '{'
          _readp++;
          _pair ();

        } else if (*_readp == sc_::value_separator) {   // ','
          // if _pairc == 0: error
          _readp++;
          _pair ();

        } else if (*_readp == sc_::end_object) {        // '}'
          return _readp + 1;

          // }  else if (*_readp == '"') { _readp++;

        } else if (_readp == _endp){
          return _readp;

        } else {
          throw "syntax error: unexpected character";
        }
    } while (_readp < _endp); */


  if (_parent == 0 && *(_look_ahead ()) != sc_::begin_object) {
      throw "syntax error: expecting '{'";
    }

  while (_readp < _endp) {
      (void) _look_ahead ();

      if (*_readp == sc_::value_separator) {   // ','
          _readp++;

          if (! _pair ())
            throw "syntax error: unexpected ','";
        }
      else if (*_readp == sc_::end_object)         // '}'
        return _readp + 1;

      else
        _pair ();
    }

  return _readp;
}

bool
json::object::_pair ()
{
  char endc = 0;
  // wchar_t endc;

  long int charc = 0;

  (void) _look_ahead ();

  /// Expect "key"
  if ((charc = _string (endc)) == 0) {  /// No quote opening "
      if (*_readp == 0)
        throw json::syntax_error ("syntax error: expecting closing '}'");

      if (*_readp == sc_::end_object || *(_look_ahead ()) ==  sc_::end_object)  /// Empty object
        return false;
    }

  if (charc < 0)   /// No closing "
    throw json::syntax_error ("syntax error: expecting closing '\"'");

  const char *keyp = _readp + 1;
  _readp += charc;


  if (*(_look_ahead ()) != sc_::name_separator)   /// Expect ':'
    throw json::syntax_error ("syntax error: expecting ':'");   /// TODO: throw syntax error: unexpected character '%c'

  _readp++;

  _member_list.emplace (std::string (keyp, charc - 2), _value ());

  return true;
}

value *
json::object::_value ()
{
  value *value_  = 0;

  long int charc = 0;

  char endc = 0;
  char readc = *(_look_ahead ());

  if (readc == sc_::double_quote) {
      if ((charc = _string (endc)) < 0)
        throw json::syntax_error ("syntax error: expecting closing '\"'");

      value_ = new json::string (_endp, this, charc);
      _readp = value_->parse (_readp);

    } else if (readc == sc_::begin_object) {
      value_ = new json::undefined;
      _readp = value_->parse (_readp);

    } else if (readc == sc_::begin_array) {
      value_ = new json::undefined;
      _readp = value_->parse (_readp);

    } else if (isdigit (readc) || readc == '-') {
      ;

    } else if (true) {  // Literal
      ;

    } else {
      throw json::syntax_error ("syntax error: expecting value after ':'");
    }

  return value_;
}

const value &
json::object::at (const char *key) const
{
  return *this;
}

// value::otype json::object::type () const { }
// size_t json::object::size () const { }
