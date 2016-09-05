#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <ctype.h>
#include <cstring>
#include <string>

#ifdef UNIT_TEST
class json_value_test;
class json_object_test;
#endif
/**
 * @brief The json_value class
 */
class JSON;
class Value
{
#ifdef UNIT_TEST
friend class json_test;
friend class json_value_test;
friend class json_object_test;
#endif

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
  Value (Value *parent);

  virtual ~Value ()
  {
    delete _key;
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
  virtual const Value & at (const char *key) const = 0;

  /**
   * @brief operator []
   * @param key
   * @return
   */
  inline const Value & operator[] (const char *key) const { return _at (key); }

  /**
   * @brief operator =
   * @param v
   */
  inline void operator =(const Value & v) { _assign (v);  }

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


  inline const char *key () const { return _key; }

  inline size_t index () const { return _index; }

  inline void
  setKey (const char *key, size_t charc)
  {
    _key = strndup (key, charc);
  }

  inline void setIndex (const size_t & index) { _index = index;}

protected:

  // TODO: inline void setKey (const char *key) { _key = key; }
  // TODO: inline void setIndex (const size_t & index) { _index = index;}

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
    tab   = 9,    /// \t Horizontal tab
    lf    = 10,   /// \n Line feed or New line
    cr    = 13,   /// \r Carriage return
    space = 32    /// Space
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

  /** TODO: move to json
   * @brief _readp
   */
  const char *_readp;

  /**
   * @brief _parent
   */
  Value *_parent;

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
  virtual const Value & _at (const char *key) const = 0;

  /**
   * @brief _assign Assing value. Delete existing key.
   * @param v
   */
  /** virtual */ void _assign (const Value & v); /** = 0 */

   static const struct literal_value {
     const char * const str_value;
     const size_t len;
     const Value::_literal ltr_value;
   } __ltr_value[3];
};

#endif // JSON_VALUE_H
