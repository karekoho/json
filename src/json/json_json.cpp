#include "json_json.h"
#include "json_object.h"
#include "json_array.h"
#include "json_undefined.h"

// json::undefined __default;

json::json (const char *json)
  : value (json),
  __value (0)
{

}

json::json (const char *endp, value *parent, size_t charc)
  : value (endp, parent, charc),
  __value (0)
{

}

json::~json()
{

}

const char *
json::json::parse (const char *readp)
{
  value *value_ = 0;

  _startp = readp;
  _readp  = readp;

  if (_endp == 0) {     // 1. ctor
      _endp = readp + strlen (readp);
  }

  _look_ahead ();

  if (*_readp == sc_::begin_object) {
      //_readp++;
      value_ = new Object (_endp, this, _charc);
    }
  else if (*_readp == sc_::begin_array) {
      //_readp++;
     value_ = new  Array (_endp, this, _charc);
    }

  /**
    JSON:parse accepts:
    JSON.parse('{}');              // {}
    JSON.parse('[]');              // []
    JSON.parse('true');            // true
    JSON.parse('"foo"');           // "foo"
    JSON.parse('null');            // null
    */

  else {
      throw "syntax error near x";
    }

  _readp = value_->parse (_readp + 1);

  delete __value;

  __value = value_;

  return _readp;
}

const value &
json::at (const char *key) const
{
  return type () == value::undefined
      ? *(new Undefined) // FIXME: leak
      : __value->at (key);
}

/* value *
json::__make_value (const char **readp, const char *endp)
{
  value *value_  = 0;
  const char *readp_ = *readp;

  value::_literal ltr = value::_literal::no_value;

  long int charc = 0;

  char endc = 0;
  char readc = *(_look_ahead ());

  if (readc == sc_::double_quote) {
    if ((charc = _string (endc)) < 0)
        throw json::syntax_error ("syntax error: expecting closing '\"'");

      value_ = new json::string (endp, this, charc);
      readp_ = value_->parse (readp_);

    } else if (readc == sc_::begin_object) {

      value_ = new json::object (endp, this, 0);
      readp_ = value_->parse (readp_);


    } else if (readc == sc_::begin_array) {
      value_ = new json::undefined;
      readp_ = value_->parse (readp_);

    } else if (isdigit (readc) || readc == '-') { // Number
      ;

    } else if ((ltr = _is_literal ()) != value::_literal::no_value) {  // Literal

      if (ltr = value::_literal::null_value)
        value_ = new json::null (endp, this);

      readp_ = value_->parse (readp_);

    } else {
      throw json::syntax_error ("syntax error: expecting value after ':'");
    }

  readp = & readp_;

  return value_;
} */





