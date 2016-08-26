#include "value.h"

//using namespace json;
#include <stdlib.h>

value::value (const char *json)
    : _startp (json),
      _readp (json),
      _endp (json == 0 ? 0 : json + strlen (json)),
      _parent (0),
      _charc (0)
{
}

value::value (const char *endp, value *parent, size_t charc)
    : _startp (0),
      _readp (0),
      _endp (endp),
      _parent (parent),
      _charc (charc)
{
}

long int
value::_string (char & endc) const
{
    const char * const starp = _readp;

    if (*starp != sc_::double_quote) {
        endc = *starp;
        return 0;
    }

    const char * readp = _readp + 1;

    while (readp < _endp && *readp != sc_::double_quote) {
        readp++;
    }

    endc = *readp;

    return readp < _endp ? (readp - starp) + 1 : -1 * (readp - starp);
}

value::_literal
value::_is_literal () const
{
  const char *readp = _readp;
  const char * const startp = readp;

  while (readp < _endp
         && *readp != ws_::tab
         && *readp != ws_::lf
         && *readp != ws_::cr
         && *readp != ws_::space) {
      readp++;
    }

  size_t charc = readp - startp;

  if (charc < 4 || charc > 5) {
      return _literal::no_value;
    }

  value::_literal ltr = _literal::no_value;

  char *test = new char[charc + 1]();

  test = strncpy (test, startp, charc);

  if (strcmp ("true", test) == 0) {
      ltr = _literal::true_value;
    }

  else if (strcmp ("false", test) == 0) {
      ltr =  _literal::false_value;
    }

  else if (strcmp ("null", test) == 0) {
      ltr = _literal::null_value;
    }

  delete[] test;

  return ltr;
}

/* value *
value::_valuex ()
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

      value_ = new json::object (_endp, this, 0);
      _readp = value_->parse (_readp);


    } else if (readc == sc_::begin_array) {
      value_ = new json::undefined;
      _readp = value_->parse (_readp);

    } else if (isdigit (readc) || readc == '-') { // Number
      ;

    } else if (true) {  // Literal
      ;

    } else {
      throw json::syntax_error ("syntax error: expecting value after ':'");
    }

  return value_;
} */


