#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <ctype.h>
#include <cstring>

/**
 * @brief The json_value class
 */
class json_value
{
public:

  /**
   * @brief The type enum
   */
  enum type {
    object,
    array,
    string,
    number,
    boolean,
    null
  };

  /** TODO: move to json
   * @brief json_value
   * @param json
   *
  json_value (const char *json = 0); */

  /** TODO: move to json
   * @brief json_value
   * @param readp
   * @param endp
   * @param parent
   *
  json_value (const char *readp, const char *endp, json_value *parent = 0); */

  /**
   * @brief parse
   * @param readp
   * @return
   */
  virtual const char *parse (const char *readp) = 0;

  /**
   * @brief get
   * @param key
   * @return
   */
  virtual json_value & get (const char *key) const = 0;

  /**
   * @brief operator []
   * @param key
   * @return
   */
  inline json_value & operator[] (const char *key) const { return get (key); }

  /**
   * @brief type
   * @return
   */
  virtual json_value::type type () const = 0;

  /**
   * @brief size
   * @return
   */
  virtual size_t size () const = 0;

protected:

  /**
   *
   */
  enum {
    begin_object    = '{',
    end_object      = '}',
    begin_array     = '[',
    end_array       = ']',
    name_separator  = ':',
    value_separator = ','
  };

  /**
   * @brief The literal enum
   */
  enum literal {
    NONE  = 0,
    TRUE  = 1,
    FALSE = 2,
    LNULL = 3
  };

  /** TODO: move to json
   * @brief _startp
   */
  const char *_startp;

  /** TODO: move to json
   * @brief _readp
   */
  const char *_readp;

  /** TODO: move to json
   * @brief _endp
   */
  const char *_endp;

  /** TODO: move to json
   * @brief _parent
   */
  json_value *_parent;

  /** TODO: move to json
   * @brief _next_lexeme
   *
  inline void
  _look_ahead ()
  {
    while (_readp < _endp && isspace (*_readp))
      _readp++;
  } */

  /** TODO: move to json
   * @brief _is_literal
   * @return
   *
  json_value::literal _is_literal (); */

  /** TODO: move to json
   * @brief _lexeme
   * @return
   *
  size_t _lexeme (); */
};

#endif // JSON_VALUE_H
