#ifndef JSON_H
#define JSON_H

#include <value.h>

/// TODO: namespace  {

class json : public value
{
public:
  json ();

  virtual const char *parse(const char *readp);
  virtual const value &at(const char *key) const;
  virtual value::otype type() const;
  virtual size_t size() const;
};

/// }



#endif // JSON_H
