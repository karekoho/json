#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <ctype.h>
#include <cstring>
#include <string>

#define UNEX_END    "Unexpected end of JSON input"
#define UNEX_TOKEN  "Unexpected token "
#define BAD_ASSIGN  "Bad assignment"

#ifdef UNIT_TEST
  class json_value_test;
  class json_leaf_test;
#endif
namespace Format {
/**
 * @brief The json_value class
 */
class json;
class json_iterator;
class undefined;
class Value
{
#ifdef UNIT_TEST
  friend class json_value_test;
  friend class json_leaf_test;
#endif

  public:

  /**
   * @brief The otype enum
   */
  enum object_type
  {
    no_value_t,
    undefined_t,
    object_t,
    array_t,
    string_t,
    number_t,
    boolean_t,
    null_t
  };

  /**
   * @brief Value
   */
  Value ();

  /**
   * @brief json_value
   * @param json
   */
  Value (const wchar_t *);

  /**
   * @brief json_value
   * @param endp
   * @param parent
   * @paran charc
   */
  Value (json *parent);

  /**
   * @brief Value
   * @param other
   */
  Value (const Value &other);

  /**
   * @brief Value
   * @param ov
   * @param nv
   */
  Value (const Value *ov, const Value &nv);

  /**
   * @brief clone Call object copy constructor from Value interface: Value *v->clone ()
   * @param other
   * @return
   */
  virtual Value *
  clone () const = 0;

  /**
   * @brief clone Call object copy constructor from Value interface: Value *v->clone ().
   * Store previous key|index=>value for deletion.
   * @param ov  previous key|index=>value
   * @return
   */
  virtual Value *
  clone (const Value *ov) const = 0;

  /**
   * @brief ~Value
   */
  virtual
  ~Value ();

  /**
   * @brief parse
   * @param json
   * @return
   * @see https://tools.ietf.org/html/rfc7159
   * @see https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/JSON/parse
   * @see http://www.ecma-international.org/ecma-262/5.1/#sec-15.12.2
   * @see https://en.wikipedia.org/wiki/List_of_Unicode_characters
   * @see http://en.cppreference.com/w/cpp/language/types
   */
  virtual const wchar_t *
  parse (const wchar_t *json) = 0;

  /**
   * @brief operator []
   * @param key
   * @return
   */
  inline Value &
  operator [](const wchar_t *key)
  { return _at (key); }

  /**
   * @brief operator []
   * @param index
   * @return
   */
  inline Value &
  operator [](size_t index)
  { return _at (index); }

  /**
   * @brief operator =
   * @param v
   */
  inline Value &
  operator =(const Value & v)
  { return _assign (v);  }

  /**
   * TODO
   *
   * @brief operator =
   * @param v
   * @return
   *
    Value &
    operator =(const Value *v);
   */

  /**
   * @brief operator =
   * @param s
   * @return
   */
  Value &
  operator =(const wchar_t *s);

  /**
   * @brief operator =
   * @param d
   * @return
   */
  Value &
  operator =(double d);

  /**
   * @brief operator =
   * @param b
   * @return
   */
  Value &
  operator =(bool b);

  /**
   * @brief type
   * @return
   */
  virtual object_type
  type () const /* TODO: noexcept */ = 0;

  /**
   * @brief size
   * @return
   */
  virtual size_t
  count () const = 0;

  /**
   * @brief setParent
   * @param parent
   */
  inline void
  setParent (json *parent)
  { _parent = parent; }

  /**
   * @brief key
   * @return
   */
  inline const wchar_t *
  key () const noexcept
  { return _key; }

  /**
   * TODO: protected
   *
   * @brief setKey
   * @param key
   * @param charc
   */
  inline void
  setKey (const wchar_t *key, size_t charc) noexcept
  {
     delete[] _key;
     wchar_t *dest_ = new wchar_t[charc + 1] ();
     _key = wcsncpy (dest_, key, charc);
  }

  /**
   * @brief index
   * @return
   */
  inline size_t
  index () const noexcept
  { return _index; }

  /**
   * TODO: protected
   *
   * @brief setIndex
   * @param index
   */
  inline void
  setIndex (const size_t &index) noexcept
  { _index = index; }

  /**
   * @brief iterator
   * @return
   */
  virtual json_iterator *
  iterator () const = 0;

  /**
   * @brief isLeaf
   * @return
   */
  virtual bool
  isLeaf () const noexcept
  { return false; }

  /**
   * @brief isNode
   * @return
   */
  inline bool
  isNode () const noexcept
  { return ! isLeaf (); }

  /**
   * @brief stringify
   * @return
   */
  virtual const wchar_t *
  stringify () /* TODO: noexcept */ noexcept = 0;

  /**
   * @brief strLength
   * @return
   */
  virtual size_t
  strLength () const noexcept = 0;

  /**
   * @brief strValue
   * @return
   */
  virtual const wchar_t *
  strValue (wchar_t *offset = 0) /* TODO: noexcept */ const = 0;

  /**
   * TODO: REMOVE
   * @brief erase
   * @param v
   * @return
   */
  virtual Value &
  erase (const Value &v) noexcept = 0;

  /**
   * @brief value
   * @return
   */
  inline const wchar_t *
  value () const
  { return strValue (); }

  /**
   * @brief parent
   * @return
   */
  inline json *
  parent () const
  { return _parent; }

protected:

  /**
   * If value has parent object, assign to new value to this->_parent->[key],
   * otherwise assign new value to Value object itself.
   *
   * @brief assign
   * @param nv
   * @return
   */
  virtual Value &
  _assign (const Value & nv);

  /**
   * Assign Value object to member_list or element_list.
   *
   * @brief _assign
   * @param Old value
   * @param New value
   * @return
   */
  virtual Value &
  _assign (Value *, Value *) = 0;

  /**
   * @brief _assign
   * @param u
   * @return
   */
  Value &
  _assign (const Format::undefined &)
  {
    _erase ();
    return *this;
  }

  /**
   * @brief The _sc enum Structural characters.
   */
  enum _sc
  {
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
  enum _ws
  {
    tab   = 9,    // \t Horizontal tab
    lf    = 10,   // \n Line feed or New line
    cr    = 13,   // \r Carriage return
    space = 32    // Space
  };

  /**
   * @brief The literal enum
   */
  enum _literal
  {
    no_literal    = 0,
    true_value  = 1,
    false_value = 2,
    null_value  = 3
  };

  /**
   * @brief _startp
   */
  const wchar_t *_startp;

  /**
   * @brief _readp
   */
  const wchar_t *_readp;

  /**
   * @brief _parent
   */
  json *_parent;

  /**
   * @brief charc
   * size_t _length;
   */

  /**
   * @brief _key
   */
  const wchar_t * _key;

  /**
   * @brief _index
   */
  size_t _index;

  /**
   * @brief _old
   */
  mutable const Value *_old_value;

  /**
   * @brief _look_ahead Move read pointer to next non-white space character
   */
  inline const wchar_t *
  _look_ahead () noexcept
  {
    while (*_readp != 0 && (*_readp == _ws::tab
            || *_readp == _ws::lf
            || *_readp == _ws::cr
            || *_readp == _ws::space))
      _readp++;

    return _readp;
  }

  /**
   * @brief _str_append Copy src to dst.
   * Move dst right after the last copied character.
   * @param dst Destination string
   * @param src Source string
   * @param charc Number of characters to copy
   * @return
   */
  static inline wchar_t *
  _str_append (wchar_t *dst, const wchar_t *src, size_t charc) noexcept
  {
    const wchar_t * const endp = dst + charc;

    while (dst < endp)
      *(dst++) = *(src++);

    return dst;
  }

  /**
   * @brief _string Read in string.
   * If no opening quote, return 0.
   * If no closing quote or unescaped unicode control character (0-31) met,
   * return number characters read as a negative value. For example "\"xx\u001F\"" = -3
   * Else return number of characters read + 2 (quotes). For example "\"xxx\"" = 5
   * @param endc Last character read
   * @return Number of characters read, including quotes
   */
  long int
  _string (wchar_t &endc) const noexcept;

  /**
   * @brief _is_literal Detect if _readp points to "true", "false" or "null".
   * @param try_
   * @return
   */
  Value::_literal
  _is_literal (const int _try = 0) const noexcept;

  /**
   * @brief _at json::object behavior: if key does not exist, assign key with value of type undefined.
   * @param key
   * @return
   */
  virtual Value &
  _at (const wchar_t *key)  = 0;

  /**
   * @brief _at
   * @param index
   * @return
   */
  virtual Value &
  _at (size_t index) = 0;

  /**
   * @brief _clear
   */
  virtual void
  _clear () = 0;

  /**
   * TODO: rename to *** _clone ***
   * @brief _clone  Called by copy constructor
   * @param other
   * @return
   */
  virtual Value *
  clone (const Value &other) = 0;

  /**
   * @brief _clone
   * @param v
   * @return
   */
  static inline Value *
  _clone_cb (Value *v)
  { return v->clone (); }

  /**
   * @brief _erase
   */
  void
  _erase () noexcept;

  /**
   * @brief _literal_value
   */
  static const struct literal_value
  {
    const wchar_t * const str_value;
    const size_t len;
    const Value::_literal ltr_value;

  } __ltr_value[3];
};
}
#endif // JSON_VALUE_H
