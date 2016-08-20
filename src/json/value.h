#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <ctype.h>
#include <cstring>

namespace json {


/**
 * @brief The json_value class
 */
class value
{
protected:

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

public:

  /** TODO: move to json
   * @brief json_value
   * @param json
   */
  value (const char *json = 0);

  /** TODO: move to json
   * @brief json_value
   * @param readp
   * @param endp
   * @param parent
   */
  value (const char *readp, const char *endp, value *parent = 0);

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
 virtual type type () const = 0;

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

  /** TODO: move to json
   * @brief _next_lexeme
   */
  inline void
  _look_ahead ()
  {
    while (_readp < _endp && isspace (*_readp))
      _readp++;
  }

  /**
   * @brief _is_literal
   * @return
   */
  value::literal _is_literal () const;

  /**
   * @brief _lexeme
   * @return
   */
  size_t _lexeme (char & endc);

  /**
   * @brief is_quoted
   * @param strlen
   * @return
   */
  bool _is_quoted (const size_t strlen) const;

  /**
   * @brief is_number
   * @return
   */
  bool _is_number () const;

};
}

#endif // JSON_VALUE_H
