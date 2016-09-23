#ifndef JSON_VALUE_PARSE_MOCK_H
#define JSON_VALUE_PARSE_MOCK_H

#include "unit_test.h"

class json_value_parse_mock : public Value
{
public:

    Value::object_type _type;

    json_value_parse_mock (JSON *parent, size_t charc, Value::object_type type = object_type::null)
      // : json (endp, parent, charc),
      : Value (parent),
        _type (type)
    {
    }



    virtual ~json_value_parse_mock () {}

    virtual const char *parse (const char *readp) { return readp; }
    virtual Value & at (const char *) const { return *(new Undefined);}
    virtual Value & at (size_t) const { return *(new Undefined); }
    virtual Value::object_type type () const { return _type;}
    virtual size_t size () const { return 0;}

    // Value interface
protected:
    virtual  Value &_at(const char *) { return *this; }
protected:
  virtual void _clear() override
  {
  }

    virtual Value *_clone(const Value &) override
    {
      return this;
    }

    // Value interface
public:
    virtual Value *_clone () override
    {
      return 0;
    }
};

#endif // JSON_VALUE_PARSE_MOCK_H
