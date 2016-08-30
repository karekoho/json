#ifndef JSON_H
#define JSON_H

#include "json_value.h"

#include <unordered_map>
#include <vector>

/// TODO: namespace  {

#ifdef UNIT_TEST
  class json_test;
  class json_object_test;
#endif

/**
 * @brief The json class
 */
class Undefined;
class json : public value
{
#ifdef UNIT_TEST
  friend class json_test;
  friend class json_object_test;
#endif
public:

  json (const char *json = 0);
  json (const char *endp, value *parent, size_t charc = 0);

  virtual ~json ();

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
  virtual const value & at (const char *key) const;

  /**
   * @brief type
   * @return
   */
  virtual inline value::otype type () const { return __value == 0 ? value::otype::undefined : __value->type (); }

  /**
   * @brief size
   * @return
   */
  virtual inline size_t size () const { return  type () == value::undefined ? 0 :__value->size (); }

protected:

  /**
   * @brief _make_value
   * @return
   */
  value *_make_value ();

private:

  /**
   * @brief __value
   */
  value *__value;

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
      virtual const char * what () { return _message == 0 ? std::exception::what () : _message; }

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
    syntax_error (const char * const message) : error (message) {}
  }; /// class syntax_error

  /**
   * @brief The out_of_range class
   */
  class out_of_range : public std::out_of_range {};
  /// class out_of_range

}; /// class json
/// } namespace

#endif // JSON_H
