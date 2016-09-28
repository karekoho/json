#ifndef JSON_JSON_H
#define JSON_JSON_H

#include "json_value.h"
#include "json_leaf.h"
#include "json_undefined.h"

#include <unordered_map>
#include <vector>

/// TODO: namespace  {

#ifdef UNIT_TEST
  class json_test;
  class json_leaf_test;
#endif

/**
 * @brief The json class
 */
class Undefined;
class JSON : public Value
{
#ifdef UNIT_TEST
  friend class json_test;
  friend class json_leaf_test;
#endif

  friend const char * Leaf::stringify ();

public:

  /**
   * @brief JSON
   */
  JSON ();

  /**
   * @brief json
   * @param json
   */
  JSON (const char *json, const bool _parse = true);

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
  virtual Value *_clone () { return new JSON (*this); }

  /**
   * @brief JSON
   * @param other
   */
  JSON (const JSON &other);

  /**
   * @brief ~JSON
   */
  virtual ~JSON ();

  /**
   * @brief parse
   * @param readp
   * @return
   */
  virtual const char *parse (const char *readp);

  /**
   * @brief at
   * @param key
   * @return
   */
  virtual Value & at (const char *key) const { return type () == Value::undefined ? *(new Undefined) : __root->at (key); }

  /**
   * @brief at
   * @param index
   * @return
   */
  virtual Value & at (size_t index) const { return type () == Value::undefined ? *(new Undefined) : __root->at (index); }

  /**
   * @brief type
   * @return
   */
  virtual inline Value::object_type type () const { return __root == 0 ? Value::object_type::undefined : __root->type (); }

  /**
   * @brief size
   * @return
   */
  virtual inline size_t count () const { return  type () == Value::undefined ? 0 :__root->count (); }

  /**
   * @brief _assign
   * @param j
   * @return
   */
  virtual Value & _assign (JSON & j);

  /**
   * @brief operator =
   * @param j
   * @return
   */
  inline Value & operator =(JSON & j) { return _assign (j); }

  /**
   * @brief _assign
   * @param nv
   * @return
   */
  virtual Value & _assign (Value & v) override;

  /**
   * @brief operator =
   * @param v
   * @return
   */
  inline Value & operator =(Value & v) { return _assign (v); }

  /**
   * @brief assign
   * @return
   */
  virtual Value &assign (Value *, Value *) override { return *this; }

  /**
   * @brief iterator
   * @return
   */
  virtual Iterator *iterator () const override;

  virtual const char *stringify () noexcept override;

  virtual size_t strLength () const noexcept override;

  virtual const char * strValue () const { return ""; }

protected:

  /**
   * @brief _at
   * @param key
   * @return
   */
  virtual Value &_at (const char *key);

  /**
   * @brief _make_value
   * @return
   */
  Value *_make_value ();

  /**
   * @brief _clear
   */
  virtual void _clear () {}

  /**
   * @brief _clone
   * @return
   */
  virtual Value *_clone (const Value &) override { return this; }

  /**
   * @brief _str_value
   */
  mutable char *_str_value[2];

private:

  /**
   * @brief __value
   */
  Value *__root;

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
      virtual const char * what () { return _message == 0 ? "" : _message; }

    protected:
      const char * const _message;
  }; /// class error

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
  }; /// class syntax_error

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
  };
  /// class out_of_range

}; /// class json
/// } namespace

#endif // JSON_JSON_H
