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

  // value * __make_value (const char **readp, const char *endp);

  public:
  /**
   * @brief The object class
   */
  class object : public value {
#ifdef UNIT_TEST
  friend class json_object_test;
  friend value * __make_value (value *member);
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
  }; /// class object

  /**
   * @brief The array class
   */
  class array : public value {
#ifdef UNIT_TEST
//  friend class json_array_test;
  friend value * __make_value (value *member);
#endif
    public:

    array (const char *json);
    array (const char *endp, value *parent = 0, size_t charc = 0);

    virtual ~array () {}

    virtual const char *parse ( const char *json);
    virtual const value & at (const char *key) const;
    virtual inline otype type () const { return value::otype::array; }
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
  }; /// class array

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

    /// value interface
    virtual inline const value & at (const char *key) const { return *this; }

    virtual inline otype type () const { return value::otype::string; }

    virtual inline size_t size () const { return _string_value.length (); }

    const char *
    value () const {

      if (_string_value.empty () && _readp && _charc > 0) {
          _string_value.assign (_readp + 1, _charc - 2);
        }

      return _string_value.c_str ();
    }

  protected:
    /**
     * @brief _value
     */
    mutable std::string _string_value;
  }; /// class string

  /**
   * @brief The number class
   */
  class number : public value {
    public:

    explicit number (const double value = 0)
      : value::value (0),
        _double_value (value),
        _digitp {{0,0,0},{0,0,0}},
        _exp (0)
    {
    }

    number (const char *json)
      : value::value (json),
        _double_value (0),
        _digitp {{0,0,0},{0,0,0}},
        _exp (0)
    {
    }

    number (const char *endp, value *parent = 0, size_t charc = 0)
      : value::value (endp, parent, charc),
        _double_value (0),
        _digitp {{0,0,0},{0,0,0}},
        _exp (0)
    {
    }

    /// value interface
    virtual const char *parse (const char *json) { return json; }
    virtual const value & at (const char *key) const { return *this; }
    virtual inline otype type () const { return value::otype::number; }
    virtual size_t size () const { return _double_value == 0 ? 0 : 1; }

    /**
     * @brief value
     * @return
     */
    double value () const { return _double_value; }

  protected:
    /**
     * @brief _value
     */
    mutable double _double_value;
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

    explicit boolean (const bool value) : value::value (0, 0, 0), _boolean_value (value) {}
    boolean (const char *json) : value::value (json), _boolean_value (false) {}
    boolean (const char *endp, value *parent = 0, size_t charc = 0) : value::value (endp, parent, charc), _boolean_value (false) {}

    /// value interface
    virtual inline const char *parse(const char *json) { return json + _charc;}
    virtual inline const value &at(const char *key) const { return *this; }
    virtual inline otype type () const { return value::otype::boolean; }
    virtual inline size_t size() const { return 0;}

    /**
     * @brief value
     * @return
     */
    inline bool value () const { return _boolean_value; }

  protected:

    bool _boolean_value;


  }; /// class number

  /**
   * @brief The null class
   */
  class null : public value {
    public:

    null () : value::value (0, 0, 0) {}
    null (const char *json) : value::value (json) {}
    null (const char *endp, value *parent = 0, size_t charc = 0) : value::value (endp, parent, charc) {}

    /// value interface
    virtual inline const char *parse (const char *json) { return json + 4; }
    virtual inline const value & at (const char *key) const { return *this; }
    virtual inline value::otype type() const { return value::otype::null; }
    virtual inline size_t size() const { return 0; }

    /**
     * @brief value
     * @return
     */
    inline const char * value () const { return ""; }
  }; /// class null

  /**
   * @brief The undefined class
   */
  class undefined : public value {
    public:

    undefined () : value::value (0, 0, 0) {}
    undefined (const char *json) : value::value (json) {}
    undefined (const char *endp, value *parent = 0, size_t charc = 0) : value::value (endp, parent,charc) {}

    /// value interface
    virtual const char *parse (const char *json) { return json + _charc; }
    virtual inline const value & at (const char *key) const { return *this; }
    virtual inline otype type () const { return value::otype::undefined; }
    virtual inline size_t size () const { return 0; }

    /**
     * @brief value
     * @return
     */
    inline const char * value () const { return "undefined"; }
  }; /// class undefined

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
