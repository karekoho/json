#ifndef JSON_JSON_H
#define JSON_JSON_H

#include "json_value.h"
#include "json_leaf.h"
#include "json_exception.h"
// #include "json_undefined.h"
#include "json_shared_undefined.h" // (.bss+0x0):-1: error: multiple definition of `Shared_Undefined::__instance'

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

  typedef Value * (*Reviver)(const wchar_t *, Value *);

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
   * @brief parse
   * @param json
   * @param reviver
   * @return
   * @see http://stackoverflow.com/questions/1174169/function-passed-as-template-argument
   */
  static Value *
  parse (const wchar_t *json, Reviver r)
  { return new JSON (json, r); }

  /**
   * @brief at
   * @param key
   * @return
   */
  //virtual Value &
  //at (const wchar_t *key) const
  //{ return __hasRoot () ? __root->at (key) : Shared_Undefined::instance (); }

  /**
   * @brief at
   * @param index
   * @return
   */
  //virtual Value &
  //at (size_t index) const
  //{ return __hasRoot () ? __root->at (index) : Shared_Undefined::instance (); }

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
  _assign (Value *, Value *) override
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
  { return __hasRoot() ? (*__root)[key] : Shared_Undefined::instance (); }

  /**
   * @brief _at
   * @param index
   * @return
   */
  virtual Value &
  _at (size_t index) override
  { return __hasRoot() ? (*__root)[index] : Shared_Undefined::instance (); }

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
   * @brief _call_reviver
   * @param v
   * @param key
   * @param index
   * @return
   */
  Value *
  _call_reviver (Value *v, const wchar_t *key, size_t index = 0) const;

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
   * @brief _reviver
   */
  Reviver __reviver;

  /**
   * @brief JSON
   * @param json
   * @param r
   */
  JSON (const wchar_t *json, Reviver r);

  /**
   * @brief __hasRoot
   * @return
   */
  inline bool
  __hasRoot () const noexcept
  { return ! __root == 0; }
};
// } namespace

#endif // JSON_JSON_H
