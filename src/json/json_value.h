#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <ctype.h>
#include <cstring>

#ifdef UNIT_TEST
class json_value_test;
class json_object_test;
#endif
/**
 * @brief The json_value class
 */
class value
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
  enum otype {
    undefined,
    object,
    array,
    string,
    number,
    boolean,
    null
  };

  /**
   * @brief json_value
   * @param json
   */
  value (const char *json = 0);

  /**
   * @brief json_value
   * @param endp
   * @param parent
   * @paran charc
   */
  explicit value (const char *endp, value *parent, size_t charc);

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
  virtual const value & at (const char *key) const = 0;

  /**
   * @brief operator []
   * @param key
   * @return
   */
  inline const value & operator[] (const char *key) const { return _at (key); }

  /**
   * @brief type
   * @return
   */
 virtual otype type () const = 0;

  /**
   * @brief size
   * @return
   */
  virtual size_t size () const = 0;

protected:

  /**
   * @brief The sc_ enum Structural characters.
   */
  enum sc_ {
    begin_object    = '{',
    end_object      = '}',
    begin_array     = '[',
    end_array       = ']',
    name_separator  = ':',
    value_separator = ',',
    double_quote    = 34
  };

  /**
   * @brief The ws enum White space characters.
   */
  enum ws_ {
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
   * @brief _endp
   */
  const char *_endp;

  /**
   * @brief _parent
   */
  value *_parent;

  /**
   * @brief charc
   */
  size_t _charc;

  /**
   * @brief _look_ahead Move read pointer to next non-white space character
   *
  inline const char *
  _look_ahead ()
  {
    while (_readp < _endp && ( *_readp == ws_::tab
            || *_readp == ws_::lf
            || *_readp == ws_::cr
            || *_readp == ws_::space))
      _readp++;

    return _readp;
  } */

  /**
   * @brief _string Read in string.
   * If no opening quote, return 0.
   * If no closing quote, unicode control charater, return characters read * -1.
   * Else return number of characters read + 2 (quotes).
   * @param endc Last character read
   * @return Number of characters read
   *
  long int _string (char &endc) const;

  /**
   * @brief _lexeme Read in next non-white space characters.
   * @param endc Last character read
   * @return Count of characters read
   *
  size_t _lexeme ();

  /**
   * @brief _is_literal
   * @param try_
   * @return
   *
  value::_literal _is_literal (const int _try = 0) const; */

  /**
   * @brief _at json::object behavior: if key does not exist, assign key with value of type undefined.
   * @param key
   * @return
   */
  const value & _at (const char *key) const;

  /**
   * @brief _at json::array behavior: if key does not exist behaviour is undefined
   * @param index
   * @return
   */
  const value & _at (size_t *index) const;

  /**
   * @brief _assign Assing value. Delete existing key.
   * @param v
   */
  // virtual void _assign (const value & v); /// TODO = 0

  /**
   * @brief operator =
   * @param v
   */
  inline void operator =(const value & v) { /* _assign (v); */ }

  /**
   * @brief is_quoted
   * @param strlen
   * @return
   */
  // bool _is_quoted (const size_t strlen) const;

  /**
   * @brief is_number
   * @return
   */
  // bool _is_number () const;

   static const struct literal_value {
     const char * const str_value;
     const size_t len;
     const value::_literal ltr_value;
   } __ltr_value[3];
};

#endif // JSON_VALUE_H
