#ifndef JSON_UNDEFINED_TEST
#define JSON_UNDEFINED_TEST

#include "json_value_test_interface.h"

/// Test number 8
class json_undefined_test : public json_value_test_interface
{
  // json_value_test_interface interface
public:

  virtual void test_ctor_dtor () {}

  virtual void test_parse_1 () {}

  virtual void test_size_1 () {}

  virtual void test_at_1 () {}

  virtual void
  test_assign_all_values ()
  {
    /// TODO: IF ov.parent: success
    /// TODO: ELSE: fail
  }

  virtual void test_value_1 () {}

  virtual void test_debug_1 () {}

  static CppUnit::Test *
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json undefined test");
    return s;
  }
};

#endif // JSON_UNDEFINED_TEST

