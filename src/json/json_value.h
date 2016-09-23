#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <ctype.h>
#include <cstring>
#include <string>

#ifdef UNIT_TEST
  class json_value_test;
  // class json_object_test;
  // class json_null_test;
  // class json_undefined_test;
#endif
/**
 * @brief The json_value class
 */

class JSON;
//class Undefined;
// class Object;
class Value
{
#ifdef UNIT_TEST
  // friend class json_test;
  friend class json_value_test;
  // friend class json_object_test;
  //friend class json_null_test;  // WTF ???
  //friend class json_undefined_test; // WTF ???
#endif

  //friend void Undefined::_assign (Value *, Value *);
  public:

  /**
   * @brief The otype enum
   */
  enum object_type {
    undefined,
    object,
    array,
    string,
    number,
    boolean,
    null
  };

  /**
   * @brief Value
   */
  Value ();

  /**
   * @brief json_value
   * @param json
   */
  Value (const char *json);

  /**
   * @brief json_value
   * @param endp
   * @param parent
   * @paran charc
   */
  Value (JSON *parent);

  /**
   * @brief Value
   * @param other
   */
  Value (const Value &other) = default;

  /**
   * @brief clone
   * @param other
   * @return
   */
  virtual Value * _clone () = 0;

  /**
   * @brief ~Value
   */
  virtual ~Value ()
  {
    free ((char *)_key);
  }

  /**
   * @brief parse
   * @param json
   * @return
   * @see https://tools.ietf.org/html/rfc7159
   * @see https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/JSON/parse
   * @see http://www.ecma-international.org/ecma-262/5.1/#sec-15.12.2
   * @see https://en.wikipedia.org/wiki/List_of_Unicode_characters
   */
  virtual const char *parse (const char *json) = 0;

  /**
   * @brief at If key does not exist, throws json::out_of_range exception
   * @param key
   * @return
   */
  virtual Value & at (const char *key) const  = 0;

  /**
   * @brief at
   * @param index
   * @return
   */
  virtual Value & at (size_t index) const = 0;

  /**
   * @brief operator []
   * @param key
   * @return
   */
  inline Value & operator[] (const char *key) { return _at (key); }

  /**
   * @brief operator =
   * @param v
   */
  inline Value & operator =(Value & v) { return _assign (v);  }

  /**
   * @brief type
   * @return
   */
 virtual object_type type () const = 0;

  /**
   * @brief size
   * @return
   */
  virtual size_t size () const = 0;

  /**
   * @brief key
   * @return
   */
  inline const char *key () const { return _key; }

  /**
    TODO: protected
   * @brief setKey
   * @param key
   * @param charc
   */
  inline void setKey (const char *key, size_t charc)
  {
    free ((char *)_key);
    _key = strndup (key, charc);
  }

  /**
   * @brief index
   * @return
   */
  inline size_t index () const { return _index; }

  /**
    TODO: protected
   * @brief setIndex
   * @param index
   */
  inline void setIndex (const size_t &index) { _index = index;}

  /**
   * TODO: pure virtual, return Value &
   *
   * @brief _assign
   */

  virtual Value & assign (Value *, Value *) = 0;

protected:

  /**
   * @brief assign
   * @param nv
   * @return
   */
  virtual Value & _assign (Value & nv);

  /**
   * @brief The _sc enum Structural characters.
   */
  enum _sc {
    begin_object    = '{',
    end_object      = '}',
    begin_array     = '[',
    end_array       = ']',
    name_separator  = ':',
    value_separator = ',',
    double_quote    = 34
  };

  /**
   * @brief The _ws enum White space characters.
   */
  enum _ws {
    tab   = 9,    // \t Horizontal tab
    lf    = 10,   // \n Line feed or New line
    cr    = 13,   // \r Carriage return
    space = 32    // Space
  };

  /**
   * @brief The literal enum
   */
  enum _literal {
    no_value    = 0,
    true_value  = 1,
    false_value = 2,
    null_value  = 3
  };

  /**
   * @brief _startp
   */
  const char *_startp;

  /**
   * @brief _readp
   */
  const char *_readp;

  /**
   * @brief _parent
   */
  JSON *_parent;

  /**
   * @brief charc
   */
  size_t _length;

  /**
   * @brief _key
   */
  const char * _key;

  /**
   * @brief _index
   */
  size_t _index;

  /**
   * @brief _look_ahead Move read pointer to next non-white space character
   */
  inline const char *
  _look_ahead ()
  {
    while (*_readp != 0 && ( *_readp == _ws::tab
            || *_readp == _ws::lf
            || *_readp == _ws::cr
            || *_readp == _ws::space))
      _readp++;

    return _readp;
  }

  /**
   * @brief _string Read in string.
   * If no opening quote, return 0.
   * If no closing quote, unicode control charater, return characters read * -1.
   * Else return number of characters read + 2 (quotes).
   * @param endc Last character read
   * @return Number of characters read
   */
  long int _string (char &endc) const;

  /**
   * @brief _is_literal
   * @param try_
   * @return
   */
  Value::_literal _is_literal (const int _try = 0) const;

  /**
   * @brief _at json::object behavior: if key does not exist, assign key with value of type undefined.
   * @param key
   * @return
   */
  virtual Value & _at (const char *key)  = 0;

  /**
   * @brief _clear
   */
  virtual void _clear () = 0;

  /**
   * @brief _clone
   * @param other
   * @return
   */
  virtual Value * _clone (const Value &other) = 0;

  /**
   * @brief _clone
   * @param v
   * @return
   */
  static inline Value * _clone_cb (Value *v) { return v->_clone (); }

  /**
   * @brief _assign Assing value. Delete existing key.
   * @param v
   */

   static const struct literal_value
   {
     const char * const str_value;
     const size_t len;
     const Value::_literal ltr_value;
   } __ltr_value[3];
};

#endif // JSON_VALUE_H
