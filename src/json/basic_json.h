#ifndef JSON_H
#define JSON_H

#include "value.h"

#include <unordered_map>
#include <vector>

/// TODO: namespace  {

/**
 * @brief The json class
 */
class json : public value
{
public:

  json (const char *json);
  json (const char *endp, value *parent = 0, size_t charc = 0);

  virtual ~json ();

  virtual const char *parse (const char *readp);
  virtual const value & at (const char *key) const;
  virtual value::otype type () const;
  virtual size_t size () const;

  /**
   * @brief The object class
   */
  class object : public value {
    public:

    object (const char *json);
    object (const char *endp, value *parent = 0, size_t charc = 0);

    virtual ~object (){}

    virtual const char *parse (const char *json);

    virtual const value & at (const char *key) const;
    virtual inline otype type () const { return value::otype::object; }
    virtual inline size_t size () const { return 0; }

    protected:

    size_t _pairc;

    /**
     * @brief _member_list
     */
    std::unordered_map<std::string, value *> _member_list;

    void _pair ();
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

    number (const char *json);
    number (const char *endp, value *parent = 0, size_t charc = 0);

  protected:
    mutable double _value;
  };

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
    undefined (const char *json);
    undefined (const char *endp, value *parent = 0, size_t charc = 0);

    /**
     * @brief value
     * @return
     */
    inline const char * value () const { return ""; }
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

  value *__value;
};

/// }



#endif // JSON_H
