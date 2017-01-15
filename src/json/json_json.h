#ifndef JSON_JSON_H
#define JSON_JSON_H

#include "json_value.h"
#include "json_leaf.h"
#include "json_undefined.h"
// #include "json_shared_undefined.h" // (.bss+0x0):-1: error: multiple definition of `Shared_Undefined::__instance'

#include <unordered_map>
#include <vector>
#include <initializer_list>

#define OFFSET  0
#define BEGIN  1

// TODO: namespace JSON {

#ifdef UNIT_TEST
  class json_test;
  class json_leaf_test;
#endif

/**
 * @brief The json class
 */
class Object;
class Array;
class JSON : public Value
{
#ifdef UNIT_TEST
  friend class json_test;
  friend class json_leaf_test;
#endif

  friend const wchar_t * Leaf::stringify ();
  friend class Object;  // For stringify { _parent->_str_value }
  friend class Array;   // For stringify { _parent->_str_value }

public:

  /**
   * @brief JSON
   */
  JSON ();

  /**
   * @brief json
   * @param json
   */
  JSON (const wchar_t *json, const bool _parse = true);

  /**
   * @brief json
   * @param endp
   * @param charc
   */
  JSON (JSON *parent);

  /**
   * @brief clone
   * @param other
   * @return
   */
  virtual Value *
  clone () const
  { return new JSON (*this);  }

  /**
   * @brief JSON
   * @param other
   */
  JSON (const JSON &other);

  /**
   * @brief JSON
   * @param ov
   * @param nv
   */
  JSON (const Value *ov, const JSON &nv);

  /**
   * @brief ~JSON
   */
  virtual ~JSON ();

  /**
   * @brief parse
   * @param readp
   * @return
   */
  virtual const wchar_t *
  parse (const wchar_t *readp);

  /**
   * @brief at
   * @param key
   * @return
   */
  virtual Value &
  at (const wchar_t *key) const
  { return __hasRoot () ? __root->at (key) : /* Shared_Undefined::instance () */  *(new Undefined);  }

  /**
   * @brief at
   * @param index
   * @return
   */
  virtual Value &
  at (size_t index) const
  { return __hasRoot () ? __root->at (index) : *(new Undefined); }

  /**
   * @brief type
   * @return
   */
  virtual inline Value::object_type
  type () const
  { return __hasRoot () ?  __root->type () : Value::object_type::undefined; }

  /**
   * @brief size
   * @return
   */
  virtual inline size_t
  count () const
  { return __hasRoot () ? __root->count () : 0; }

  /**
   * @brief _assign
   * @param j
   * @return
   */
  virtual Value
  & _assign (const JSON & j);

  /**
   * @brief operator =
   * @param j
   * @return
   */
  inline Value &
  operator =(const JSON & j)
  { return _assign (j); }

  /**
   * @brief _assign
   * @param nv
   * @return
   */
  virtual Value &
  _assign (const Value & v) override;

  /**
   * @brief operator =
   * @param v
   * @return
   */
  inline Value &
  operator =(const Value & v)
  { return _assign (v); }

  /**
   * @brief assign
   * @param ov Old value
   * @param nv New value
   * @return
   */
  virtual Value &
  assign (Value *, Value *) override
  { return *this; }

  /**
   * @brief iterator
   * @return
   */
  virtual JSON_Iterator *
  iterator () const override
  { return __root ? __root->iterator () : 0; /* TODO: new Leaf_Iterator (new Undefined);  // FIXME: leak */ }

  /**
   * @brief stringify
   * @return
   */
  virtual const wchar_t *
  stringify () noexcept override
  { return strValue (); }

  /**
   * @brief strLength
   * @return
   */
  virtual size_t
  strLength () const noexcept override
  { return __hasRoot () ? __root->strLength () : 0; }

  /**
   * @brief strValue
   * @return
   */
  virtual const wchar_t *
  strValue (wchar_t *offset = 0) const
  { return __hasRoot () ? __root->strValue (offset) : L""; }

  /**
   * @brief erase
   * @param v
   * @return
   */
  virtual Value &
  erase (const Value &v) noexcept override
  { return __hasRoot() ? __root->erase (v) : *this; }

  /**
   * @brief clone
   * @param old
   * @return
   */
  virtual Value *
  clone (const Value *) const override
  { return new JSON (*this); }

protected:

  /**
   * @brief _at
   * @param key
   * @return
   */
  virtual Value &
  _at (const wchar_t *key) override
  { return __hasRoot() ? (*__root)[key] : *(new Undefined); }

  /**
   * @brief _at
   * @param index
   * @return
   */
  virtual Value &
  _at (size_t index) override
  { return __hasRoot() ? (*__root)[index] : *(new Undefined) ;}

  /**
   * @brief _make_value
   * @return
   */
  Value *
  _make_value ();

  /**
   * @brief _clear
   */
  virtual void
  _clear ()
  {}

  /**
   * @brief _clone
   * @return
   */
  virtual Value *
  clone (const Value &) override
  { return this; }

  /**
   * @brief _str_value
   */
  mutable wchar_t *_str_value[2];

private:

  /**
   * @brief __value
   */
  Value *__root;

  /**
   * @brief __hasRoot
   * @return
   */
  inline bool
  __hasRoot () const noexcept
  { return ! __root == 0; }

public:

  /**
   * @brief The error class
   */
  class error : public std::exception {
    public:
      /**
        * @brief error
        * @param message
        */
      error (const char * const message = 0) : std::exception (), _message (message) {}

      /**
       * @brief what
       * @return
       */
      virtual const char *
      what ()
      { return _message == 0 ? "" : _message; }

    protected:
      const char * const _message;
  }; // class error

  /**
   * @brief The syntax_error class
   */
  class syntax_error : public error {
    public:
    /**
     * @brief syntax_error
     * @param message
     */
    syntax_error (const char * const message = 0) : error (message) {}
  }; // class syntax_error

  /**
   * @brief The out_of_range class
   */
  class out_of_range : public error {
    public:
    /**
     * @brief out_of_range
     * @param message
     */
    out_of_range (const char * const message = 0) : error (message) {}
  };  // class out_of_range




};  // class json

// } namespace

#endif // JSON_JSON_H
