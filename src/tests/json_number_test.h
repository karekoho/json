#ifndef JSON_NUMBER_TEST
#define JSON_NUMBER_TEST

#include "json_value_test_interface.h"

/// Test number 5
class json_number_test : public json_value_test_interface {

  // json_value_test_interface interface
public:
  virtual void test_smoke()
  {
  }
  virtual void test_parse_1()
  {
  }
  virtual void test_size_1()
  {
  }
  virtual void test_at_1()
  {
  }
  virtual void test_value_1()
  {
  }
  virtual void test_debug_1()
  {
  }

  static CppUnit::Test *suite()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json number test");

//    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_smoke", &json_number_test::test_smoke));
      s->addTest (new CppUnit::TestCaller<json_number_test> ("test_parse_1", &json_number_test::test_parse_1));
//    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_size_1", &json_number_test::test_size_1));
//    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_get_1", &json_number_test::test_get_1));
//    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_value_1", &json_number_test::test_value_1));
//    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_debug_1", &json_object_test::test_debug_1));

    return s;
  }
};

#endif // json_number_test

