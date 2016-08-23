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

// #ifdef UNIT_TEST
//    virtual const char *parse (const char *json) { return json + _charc; }
//#else
    virtual const char *parse (const char *json);
// #endif
    virtual const value & at (const char *key) const;
    virtual inline otype type () const { return value::otype::object; }
    virtual inline size_t size () const { return 0; }

    protected:

    size_t _pairc;

    std::unordered_map<std::string, value *> _members;

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
  };

  /**
   * @brief The string class
   */
  class string : public value {
    public:

    string (const char *json);
    string (const char *endp, value *parent = 0, size_t charc = 0);
  };

  /**
   * @brief The number class
   */
  class number : public value {
    public:
    number (const char *json);
    number (const char *endp, value *parent = 0, size_t charc = 0);
  };

  class boolean : public value {
    public:
    boolean (const char *json);
    boolean (const char *endp, value *parent = 0, size_t charc = 0);

  };

  /**
   * @brief The null class
   */
  class null : public value {
    public:
    null (const char *json);
    null (const char *endp, value *parent = 0, size_t charc = 0);
  };

private:

  value *__value;
};

/// }



#endif // JSON_H
