#ifndef JSON_H
#define JSON_H

#include "value.h"

#include <unordered_map>
#include <vector>

/// TODO: namespace  {

#ifdef UNIT_TEST
  class json_object_test;
#endif

/**
 * @brief The json class
 */
class undefined;
class json : public value
{
#ifdef UNIT_TEST
  friend class json_object_test;
#endif
public:

  json (const char *json);
  json (const char *endp, value *parent = 0, size_t charc = 0);

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

private:
  /**
   * @brief __value
   */
  value *__value;

public:
  /**
   * @brief The object class
   */
  value * v(){
    return new json::object(0,0);
  }

  class object : public value {
#ifdef UNIT_TEST
  friend class json_object_test;
#endif

  public:

    object (const char *json);
    object (const char *endp, value *parent = 0, size_t charc = 0);

    virtual ~object (){}

    virtual const char *parse (const char *json);

    virtual const value & at (const char *key) const;
    virtual inline otype type () const { return value::otype::object; }
    virtual inline size_t size () const { return _member_list.size (); }

    protected:

    size_t _pairc;

    /**
     * @brief _member_list
     */
    std::unordered_map<std::string, value *> _member_list;

    bool _pair ();

    value *_value ();
  };

  /**
   * @brief The array class
   */
  class array : public value {
    public:

    array (const char *json);
    array (const char *endp, value *parent = 0, size_t charc = 0);

    virtual ~array () {}

    virtual const char *parse ( const char *json);
    virtual const value & at (const char *key) const;
    virtual inline otype type () const { return value::otype::array;  }
    virtual inline size_t size () const { return 0; }

  protected:
    /**
     * @brief _element_list
     */
    std::vector<array *> _element_list;
    /**
     * @brief _debug_value
     */
    std::string _debug_value;
  };

  /**
   * @brief The string class
   */
  class string : public value {
    public:

    string (const char *json) : value::value (json) {}

    string (const char *endp, value *parent = 0, size_t charc = 0) : value::value (endp, parent, charc) {}

    virtual const char *
    parse (const char *json)
    {
//      if (_parent == 0) { TODO: validate }
      _readp = json;

      return json + _charc;
    }

    virtual const value & at (const char *key) const { return *this; }

    virtual inline otype type () const { return value::otype::string; }

    virtual inline size_t size () const { return _value.length (); }

    const char *
    value () const {

      if (_value.empty () && _readp && _charc > 0) {
          _value.assign (_readp + 1, _charc - 2);
        }

      return _value.c_str ();
    }

  protected:
    /**
     * @brief _value
     */
    mutable std::string _value;
  };

  /**
   * @brief The number class
   */
  class number : public value {
    public:

    number (const char *json)
      : value::value (json),
        _value (0),
        _digitp {{0,0,0},{0,0,0}},
        _exp (0)
    {
    }

    number (const char *endp, value *parent = 0, size_t charc = 0)
      : value::value (endp, parent, charc),
        _value (0),
        _digitp {{0,0,0},{0,0,0}},
        _exp (0)
    {
    }

    virtual const char *parse (const char *json) { return json; }

    virtual const value & at (const char *key) const { return *this; }

    virtual inline otype type () const { return value::otype::number; }

    virtual size_t size () const { return _value == 0 ? 0 : 1; }

    double value () const { return 0; }

  protected:
    /**
     * @brief _value
     */
    mutable double _value;
    /**
     * @brief _digitp
     */
    mutable const char *_digitp[2][3];

    /**
     * @brief _exp Power of 10
     */
    unsigned long int _exp;
  };

  /**
   * @brief The boolean class
   */
  class boolean : public value {
    public:

    boolean (const char *json);
    boolean (const char *endp, value *parent = 0, size_t charc = 0);

    /**
     * @brief value
     * @return
     */
    inline bool value () const { return _value; }

  protected:
    bool _value;
  };

  /**
   * @brief The null class
   */
  class null : public value {
    public:

    null (const char *json);
    null (const char *endp, value *parent = 0, size_t charc = 0);

    /**
     * @brief value
     * @return
     */
    inline const char * value () const { return ""; }
  };

  /**
   * @brief The undefined class
   */
  class undefined : public value {
    public:
    undefined () : value::value (0, 0, 0) {}
    undefined (const char *json) : value::value (json) {}
    undefined (const char *endp, value *parent = 0, size_t charc = 0) : value::value (endp, parent,charc) {}

    virtual const char *parse (const char *json) { return json + _charc; }

    virtual inline const value & at (const char *key) const { return *this; }

    virtual inline otype type () const { return value::otype::undefined; }

    virtual inline size_t size () const { return 0; }

    /**
     * @brief value
     * @return
     */
    inline const char * value () const { return "undefined"; }
  };

  /**
   * @brief The error class
   */
  class error : public std::exception {
    public:
      /**
        * @brief error
        * @param message
        */
      error (const char * const message) : _message (message) {}

      virtual const char * what () { return _message; }

    protected:
      const char * const _message;
  };

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
  };

private:

  // static undefined __default;
};

/// }



#endif // JSON_H
