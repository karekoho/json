#ifndef JSON_H
#define JSON_H

#include <value.h>

/// TODO: namespace  {

class json : public value
{
public:

  json (const char *json);
  json(const char *json, const char *endp, value *parent, size_t lexlen);

  virtual const char *parse (const char *readp);
  virtual const value &at (const char *key) const;
  virtual value::otype type () const;
  virtual size_t size () const;

private:

  value *__value;
};

/// }



#endif // JSON_H
