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
    // size_t pairc = 0;

    return json + _charc;

    do {
        _look_ahead ();

        if (*_readp == sc_::begin_object) {             // '{'
            _readp++;
            _pair ();
            continue;

        } else if (*_readp == sc_::value_separator) {   // ','
            // if _pairc == 0: error
            // _readp++;
            // _pair ();
            // continue

        } else if (*_readp == sc_::end_object) {        // '}'
            // return _readp;

        } else {
            throw "syntax error";
        }
    } while (_readp < _endp);

    return _readp;
}

void
json::object::_pair ()
{
    char endc;
    long int charc = 0;

    _look_ahead ();

    // Expect \"key\"
    if ((charc = _string (endc))  == 0) { // No quote \"
        throw json::syntax_error ("syntax error: expecting opening '\"'");
      }
    if (charc < 0) {  // No closing \"
        throw json::syntax_error ("syntax error: expecting closing '\"'");
      }

    std::string key (_readp + 1, charc - 1);

    _readp += charc;

    _look_ahead ();

    // Expect ':'
    if (*_readp != sc_::name_separator) {
        throw json::syntax_error ("syntax error: expecting ','");
      }

    _readp++;

    // expect value
    _look_ahead ();

    // if object | array : _readp = new object | array
    // else if string | number |literal : _readp + charc

    _member_list.emplace (key, this /** TODO: _value () */);

    // _pairc++
}

const value &
json::object::at (const char *key) const
{
  return *this;
}

// value::otype json::object::type () const { }
// size_t json::object::size () const { }
