#ifndef OBJECT_H
#define OBJECT_H

#include "json_json.h"

/**
 * @brief The object class
 */
class Object : public json {
#ifdef UNIT_TEST
friend class json_object_test;
#endif

public:

  explicit Object (const char *json = 0);
  Object (const char *endp, value *parent = 0, size_t charc = 0);

  virtual ~Object (){}

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

#endif // OBJECT_H

