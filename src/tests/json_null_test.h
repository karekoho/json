#ifndef JSON_NULL_TEST
#define JSON_NULL_TEST

#include "json_value_test_interface.h"

/// Test number 7
class json_null_test : public json_value_test_interface
{
  // json_value_test_interface interface
public:

  virtual void
  test_ctor_dtor ()
  {
  }

  virtual void test_parse_1 () {}

  virtual void test_size_1 () {}

  virtual void test_at () {}

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
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json null test");

    s->addTest (new CppUnit::TestCaller<json_null_test> ("test_ctor_dtor", &json_null_test::test_ctor_dtor));
    s->addTest (new CppUnit::TestCaller<json_null_test> ("test_assign_all_values", &json_null_test::test_assign_all_values));

    return s;
  }
};

#endif // JSON_NULL_TEST

