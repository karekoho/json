#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <ctype.h>
#include <cstring>

#ifdef UNIT_TEST
class json_value_test;
#endif
/**
 * @brief The json_value class
 */
class value
{
#ifdef UNIT_TEST
friend class json_value_test;
#endif
protected:

  /**
   * @brief The otype enum
   */
  enum otype {
    object,
    array,
    string,
    number,
    boolean,
    null
  };

public:

  /**
   * @brief json_value
   * @param json
   */
  value (const char *json = 0);

  /**
   * @brief json_value
   * @param startp TODO: remove
   * @param endp
   * @param parent
   * @paran charc
   */
  explicit value (const char *startp, const char *endp, value *parent = 0, size_t lexlen = 0);

  /**
   * @brief parse
   * @param json
   * @return
   */
  virtual const char *parse (const char *json) = 0;

  /**
   * @brief get
   * @param key
   * @return
   */
  virtual const value & at (const char *key) const = 0;

  /**
   * @brief operator []
   * @param key
   * @return
   */
  inline const value & operator[] (const char *key) const   { return at (key); }

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
    value_separator = ','
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
  enum literal_ {
    lnone   = 0,
    ltrue   = 1,
    lfalse  = 2,
    lnull   = 3
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
   */
  inline void
  _look_ahead ()
  {
    while (_readp < _endp && ( *_readp == ws_::tab
            || *_readp == ws_::lf
            || *_readp == ws_::cr
            || *_readp == ws_::space))
      _readp++;
  }

  /**
   * @brief _string Read in string. Return number of characters read, including quotation marks.
   * @return
   */
  size_t _string ();

  /**
   * @brief _lexeme Read in next non-white space characters.
   * @param endc Last character read
   * @return Count of characters read
   */
  size_t _lexeme ();

  /**
   * @brief _is_literal
   * @return
   */
  value::literal_ _is_literal () const;

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
  bool _is_number () const;

};

#endif // JSON_VALUE_H
