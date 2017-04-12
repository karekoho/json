#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <ctype.h>
#include <cstring>
#include <string>

namespace format
{
  #define UNEX_END    "Unexpected end of JSON input"
  #define UNEX_TOKEN  "Unexpected token "
  #define BAD_ASSIGN  "Bad assignment"

  #ifdef UNIT_TEST
    class json_value_test;
  #endif

  /**
   * @brief The json_value class
   */
  class json;
  class json_iterator;
  class undefined;
  class value
  {
    friend const wchar_t * __call__parse (value *, const wchar_t *);
    friend void __call__set_key (value *, const wchar_t *, size_t);
    friend void __call__set_index (value *, const size_t &);
    friend void __call__set_parent (value *, json *);
    friend const wchar_t * __call_str_value (value *, wchar_t *);
    friend value & __call__erase (value *, const value &);

    #ifdef UNIT_TEST
      friend class json_value_test;
    #endif

    public:

    /**
     * @brief The otype enum
     */
    enum value_t
    {
      no_value_t = 0,
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
    value ();

    /**
     * @brief json_value
     * @param json
     */
    value (const wchar_t *);

    /**
     * @brief value
     * @param d
     */
    //TODO: value (double d);

    /**
     * @brief value
     * @param b
     */
    //TODO: value (bool b);

    /**
     * @brief value
     * @param
     */
    //TODO: value (std::nullptr_t);

    /**
     * @brief Value
     * @param other
     */
    value (const value &other);

    /**
     * @brief clone Call object copy constructor when derived type in not known
     * @param other
     * @return
     */
    virtual value *
    clone () const = 0;

    /**
     * @brief ~Value
     */
    virtual
    ~value ();

    /**
     * @brief operator []
     * @param key
     * @return
     */
    inline value &
    operator [](const wchar_t *key)
    { return _at (key); }

    /**
     * @brief operator []
     * @param index
     * @return
     */
    inline value &
    operator [](size_t index)
    { return _at (index); }

    /**
     * @brief operator =
     * @param v
     * @return
     */
    inline value &
    operator =(value *v)
    { return _assign (v); }

    /**
     * @brief operator =
     * @param v
     */
    inline value &
    operator =(const value & v)
    { return _assign (v);  }

    /**
     * @brief operator =
     * @param u
     * @return
     */
    inline value &
    operator =(const undefined & u)
    { return _assign (u);}

    /**
     * @brief operator =
     * @param s
     * @return
     */
    value &
    operator =(const wchar_t *json_text);

    /**
     * @brief operator =
     * @param d
     * @return
     */
    value &
    operator =(double d);

    /**
     * @brief operator =
     * @param b
     * @return
     */
    value &
    operator =(bool b);

    /**
     * @brief operator =
     * @return
     */
    value &
    operator =(std::nullptr_t);

    /**
     * @brief type
     * @return
     */
    virtual value_t
    type () const noexcept = 0;

    /**
     * @brief operator ==
     * @param t
     * @return
     */
    inline bool
    operator ==(value_t t) const noexcept
    { return type () == t; }

    /**
     * @brief operator ==
     * @param v
     * @return
     */
    inline bool
    operator ==(const value & v) const noexcept
    { return operator ==(v.type ()); }

    /**
     * @brief count
     * @return
     */
    virtual size_t
    length () const noexcept = 0;

    /**
     * @brief key
     * @return
     */
    inline const wchar_t *
    key () const noexcept
    { return _key; }

    /**
     * @brief index
     * @return
     */
    inline size_t
    index () const noexcept
    { return _index; }

    /**
     * @brief stringify
     * @return
     */
    const wchar_t *
    stringify () noexcept
    { return _to_string (); }

    /**
     * TODO: protected
     *
     * @brief str_length
     * @return
     */
    virtual size_t
    str_length () const noexcept = 0;

    /**
     * @brief value
     * @return
     */
    inline const wchar_t *
    get () const
    { return _to_string (); }

    /**
     * @brief parent
     * @return
     */
    inline json *
    parent () const
    { return _parent; }

    /**
     * @brief The iterator class
     */
    template <class Iterator,
              class Category,
              class T,
              class Distance = std::ptrdiff_t,
              class Pointer = T*,
              class Reference = T& > class iterator
        : public std::iterator<Category, T, Distance, Pointer, Reference>
    {
    public:
      /**
       * @brief iterator
       */
      iterator ()
      {}

      /**
       * @brief iterator
       */
      iterator (Iterator it)
        : _it (it)
      {}

      /**
       * @brief iterator
       * @param other
       */
      iterator (const iterator & other)
        : _it (other._it)
      {}

      /**
       * @brief ~iterator
       */
      virtual ~iterator () = default;

      /**
       * @brief operator ++
       * @return
       */
      iterator &
      operator ++()
      {
        ++_it;
        return *this;
      }

      /**
       * @brief operator ++
       * @return
       */
      iterator
      operator ++(int)
      {
        iterator it (*this);
        ++(*this);
        return it;
      }

      /**
       * @brief operator ==
       * @param rhs
       * @return
       */
       inline bool
       operator ==(const iterator &rhs)
       { return _it == rhs._it; }

      /**
       * @brief operator !=
       * @param rhs
       * @return
       */
       inline bool
       operator !=(const iterator &rhs)
       { return ! operator ==(rhs); }

    protected:
       /**
        * @brief _it
        */
       Iterator _it;
    };  // Class iterator

  protected:
    /**
     * @brief _parse
     * @param json
     * @return
     * @see https://tools.ietf.org/html/rfc7159
     * @see https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/JSON/parse
     * @see http://www.ecma-international.org/ecma-262/5.1/#sec-15.12.2
     * @see https://en.wikipedia.org/wiki/List_of_Unicode_characters
     * @see http://en.cppreference.com/w/cpp/language/types
     */
    virtual const wchar_t *
    _parse (const wchar_t *json) = 0;

    /**
     * @brief _assign
     * @param nv
     * @return
     */
    value &
    _assign (value *nv);

    /**
     * If value has parent object, assign to new value to this->_parent->[key],
     * otherwise assign new value to Value object itself.
     *
     * @brief assign
     * @param nv
     * @return
     */
    value &
    _assign (const value & nv);

    /**
     * Assign Value object to member_list or element_list.
     *
     * @brief _assign
     * @param Old value
     * @param New value
     * @return
     */
    virtual value &
    _assign (value *, value *) = 0;

    /**
     * If value has parent object, remove value from it's parent,
     * otherwise do nothing.
     *
     * @brief _assign
     * @param u
     * @return
     */
    value &
    _assign (const undefined &) noexcept;

    /**
     * @brief _set_key
     * @param key
     * @param charc
     */
    inline void
    _set_key (const wchar_t *key, size_t charc) noexcept
    {
       delete[] _key;
       _key = wcsncpy (new wchar_t[charc + 1] (), key, charc);
    }

    /**
     * @brief _set_index
     * @param index
     */
    inline void
    _set_index (const size_t & index) noexcept
    { _index = index; }

    /**
     * @brief setParent
     * @param parent
     */
    inline void
    _set_parent (json *parent) noexcept
    { _parent = parent; }

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
     * @brief _readp
     */
    const wchar_t *_readp;

    /**
     * @brief _parent
     */
    json *_parent;

    /**
     * @brief _key
     */
    const wchar_t * _key;

    /**
     * @brief _index
     */
    size_t _index;

    /**
     * @brief value
     * @param parent
     */
    value (json *parent);

    /**
     * @brief str_value
     * @param offset
     * @return
     */
    virtual const wchar_t *
    _to_string (wchar_t *offset = 0) /* TODO: noexcept */ const = 0;

    /**
     * @brief _clone  Called by copy constructor
     * @param other
     * @return
     */
    virtual value *
    _clone (const value &other) = 0;

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
    value::_literal
    _is_literal (const int _try = 0) const noexcept;

    /**
     * @brief _at json::object behavior: if key does not exist, assign key with value of type undefined.
     * @param key
     * @return
     */
    virtual value &
    _at (const wchar_t *key)  = 0;

    /**
     * @brief _at
     * @param index
     * @return
     */
    virtual value &
    _at (size_t index) = 0;

    /**
     * @brief _clear
     */
    virtual void
    _clear () = 0;

    /**
     * @brief _erase
     * @param v
     * @return
     */
    virtual value &
    _erase (const value &v) noexcept = 0;

    /**
     * @brief _literal_value
     */
    static const struct literal_value
    {
      const wchar_t * const str_value;
      const size_t len;
      const value::_literal ltr_value;

    } __ltr_value[3]; 
  };  // Class value

   inline const wchar_t *
   __call__parse (value *v, const wchar_t *readp)
   { return v->_parse (readp); }

   inline void
   __call__set_key (value *v, const wchar_t *keyp, size_t charc)
   { v->_set_key (keyp, charc); }

   inline void
   __call__set_index (value *v, const size_t & index)
   { v->_set_index (index); }

   inline void
   __call__set_parent (value *v, json *parent)
   { v->_set_parent (parent); }

   inline const wchar_t *
   __call_str_value (value *v, wchar_t *offset)
   { return v->_to_string (offset); }

   inline value &
   __call__erase (value *parent, const value & v)
   {  return parent->_erase (v); }
} // Namespace format

#endif // JSON_VALUE_H
