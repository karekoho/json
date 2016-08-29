// #include "basic_json.h"
#include "json_object.h"
#include "json_string.h"
#include "json_undefined.h"
#include "json_null.h"
#include "json_number.h"
#include "json_boolean.h"

Object::Object (const char *json)
  : json::json (json),
    _pairc (0)
{
}

Object::Object (const char *endp, value *parent, size_t charc)
  : json::json (endp , parent, charc),
    _pairc (0)
{
}

const char *
Object::parse (const char *json)
{
  if (_parent == 0) {
      _readp = json;

      if (*(_look_ahead ()) != sc_::begin_object)
        throw "syntax error: expecting '{'";
    }
  else {
      _readp = json + 1;
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
Object::_pair ()
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

    throw json::syntax_error ("pair: syntax error: expecting ':'");   /// TODO: throw syntax error: unexpected character '%c'

  _readp++;

  _member_list.emplace (std::string (keyp, charc - 2), _make_value ());
  // _member_list.emplace (std::string (keyp, charc - 2), json::__make_value (&_readp, _endp));

  return true;
}

const value &
Object::at (const char *key) const
{
  if (_member_list.empty ()) {
      return *(new Undefined); /// FIXME: leak
    }

  try {
    return *(_member_list.at (key));

  } catch (std::out_of_range &e) {
    return *(new Undefined);  /// FIXME: leak
  }
}

/* value *
Object::_value ()
{
  value *value_  = 0;

  value::_literal ltr = value::_literal::no_value;

  long int charc = 0;

  char endc = 0;
  char readc = *(_look_ahead ());

  if (readc == sc_::double_quote) {
    if ((charc = _string (endc)) < 0)
        throw json::syntax_error ("syntax error: expecting closing '\"'");

      value_ = new String (_endp, this, charc);
      _readp = value_->parse (_readp);

    } else if (readc == sc_::begin_object) {

      value_ = new Object (_endp, this, 0);
      _readp = value_->parse (_readp);


    } else if (readc == sc_::begin_array) {
      value_ = new Undefined;
      _readp = value_->parse (_readp);

    } else if (isdigit (readc) || readc == '-') { // Number
      ;

    } else if ((ltr = _is_literal ()) != value::_literal::no_value) {  // Literal

      if (ltr == value::_literal::null_value)
        value_ = new Null (_endp, this);

      _readp = value_->parse (_readp);

    } else {
      throw json::syntax_error ("syntax error: expecting value after ':'");
    }

  return value_;
} */


// value::otype json::object::type () const { }
// size_t json::object::size () const { }
