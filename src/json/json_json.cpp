#include "json_json.h"
#include "json_object.h"
#include "json_array.h"
#include "json_string.h"
#include "json_null.h"
#include "json_undefined.h"

json::json (const char *json)
  : value (json),
//    _startp (json),
//    _readp (json),
//    _endp (0),
//    _parent (0),
//    _charc (json == 0 ? 0 : strlen (json)),
    __value (0)
{
  if (_charc > 0)
    {
      _endp = _startp + _charc;
      (void) parse (json);
    }
}

json::json (const char *endp, value *parent, size_t charc)
  : value (endp, parent, charc),
//    _startp (0),
//    _readp (0),
//    _endp (endp),
//    _parent (parent),
//    _charc (charc),
    __value (0)
{
}

json::~json ()
{
}

const char *
json::json::parse (const char *readp)
{
  value *value_ = 0;

  _startp = readp;
  _readp  = readp;

  if (_endp == 0)  // 1. ctor
    _endp = readp + strlen (readp);

  _look_ahead ();

  if (*_readp == sc_::begin_object)
    {
      value_ = new Object (_endp, this, _charc);
    }
  else if (*_readp == sc_::begin_array)
    {
      value_ = new  Array (_endp, this, _charc);
    }
  else
    {
      throw "syntax error near x";
    }

  /**
    JSON:parse accepts:
    JSON.parse('{}');              // {}
    JSON.parse('[]');              // []
    JSON.parse('true');            // true
    JSON.parse('"foo"');           // "foo"
    JSON.parse('null');            // null
    */

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

//long int
//json::_string (char & endc) const
//{
//    const char * const starp = _readp;

//    if (*starp != sc_::double_quote) {
//        endc = *starp;
//        return 0;
//    }

//    const char * readp = _readp + 1;

//    while (readp < _endp && *readp != sc_::double_quote) {
//        readp++;
//    }

//    endc = *readp;

//    return readp < _endp ? (readp - starp) + 1 : -1 * (readp - starp);
//}

//value::_literal
//json::_is_literal (const int _try) const
//{
//  const char *readp = _readp;

//  size_t idx = 0;

//  while (readp + idx < _endp
//         && idx < __ltr_value[_try].len
//         && *(readp + idx) == *(__ltr_value[_try].str_value + idx)) {
//      idx++;
//    }

//  if (idx == __ltr_value[_try].len)
//    return __ltr_value[_try].ltr_value;

//  return _try < 2 ? _is_literal (_try + 1) :  value::_literal::no_value;
//}

value *
json::_make_value ()
{
  value *value_  = 0;

  value::_literal ltr = value::_literal::no_value;

  long int charc = 0;

  char endc = 0;
  char readc = *(_look_ahead ());

  if (readc == sc_::double_quote) // String
    {
      if ((charc = _string (endc)) < 0)
        throw json::syntax_error ("syntax error: expecting closing '\"'");

      value_ = new String (_endp, this, charc);
      _readp = value_->parse (_readp);
    }
  else if (readc == sc_::begin_object)  // Object
    {
      value_ = new Object (_endp, this, 0);
      _readp = value_->parse (_readp);
    }
  else if (readc == sc_::begin_array) // Array
    {
      value_ = new Array (_endp, this, 0);
      _readp = value_->parse (_readp);
    }
  else if (isdigit (readc) || readc == '-') // Number
    {
      ;
    }
  else if ((ltr = _is_literal ()) != value::_literal::no_value) // Literal
    {
      if (ltr == value::_literal::null_value)
        value_ = new Null (_endp, this);

      /// TODO: else if (boolean)
      _readp = value_->parse (_readp);
    }
  else
    {
      value_ = new Undefined;

      // throw json::syntax_error ("syntax error: expecting value after ':'");
    }

  return value_;
}





