#ifndef JSON_ARRAY_TEST
#define JSON_ARRAY_TEST

#include "json_value_test_interface.h"

/// Test number 4
class json_array_test : public json_value_test_interface {

  // json_value_test_interface interface
public:

  virtual void test_smoke () {}

  virtual void test_parse_1 ()
  {
    Array *p = new Array (0);

    struct assert {
      const char *startp;
      // bool status;
      size_t size;
      Value::object_type type;
      Value *parent;
      int moveback;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { "[]", 0, Value::object_type::array, p, 0, PASS },
      { "[ ] ", 0, Value::object_type::array, p, 1, PASS },
      { "[\"x\"]", 1, Value::object_type::array, p, 0, PASS },
      { "[\"x\",\"x\"] ", 2, Value::object_type::array, p, 1, PASS },
      { "[\"x\",\"x\",[\"x\"]] ", 3,  Value::object_type::array, p, 1, PASS },

      // errors
      { "[ ", 0, Value::object_type::undefined, p, 0, FAIL },
      { "[, ", 0, Value::object_type::undefined, p, 0, FAIL },
      { "[ x ", 0, Value::object_type::undefined, p, 0, FAIL },

      { "", 0, Value::object_type::undefined, 0, 0, FAIL },
    };

    TEST_IT_START

        const char *startp = (*it).startp;
        size_t charc =strlen (startp);
        Array *a = new Array (startp + charc , (*it).parent);

        const char *readp = a->parse (startp);

        ASSERT_EQUAL_IDX ("array.readp", (startp + charc) - (*it).moveback, readp);
        ASSERT_EQUAL_IDX ("*(array.readp - 1)", ']', *(readp - 1));
        ASSERT_EQUAL_IDX ("array.size", (*it).size, a->size ());

        delete a;

    TEST_IT_END;

    delete p;
  }

  virtual void test_size_1 () {}
  virtual void test_at_1() {}
  virtual void test_value_1() {}
  virtual void test_debug_1() {}

  static CppUnit::Test *suite()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json array test");

//    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_smoke", &json_array_test::test_smoke));
      s->addTest (new CppUnit::TestCaller<json_array_test> ("test_parse_1", &json_array_test::test_parse_1));
//    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_size_1", &json_array_test::test_size_1));
//    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_get_1", &json_array_test::test_get_1));
//    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_value_1", &json_array_test::test_value_1));
//    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_debug_1", &json_array_test::test_debug_1));

    return s;
  }
};

#endif // JSON_ARRAY_TEST

