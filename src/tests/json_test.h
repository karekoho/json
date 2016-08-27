#ifndef JSON_TEST_H
#define JSON_TEST_H

#include <json_value_test_interface.h>

/// Test number 1
class json_test : public json_value_test_interface
{
public:

  virtual void test_smoke () {}

  virtual void test_parse_1 ()
  {
    struct assert {
        const char *starp;
        size_t move;
        char endch;
        value::otype type;
        int assert_status;
    };

    std::vector<struct assert > test = {
        { "{ \"foo\" : \"ru\" } ", 17 - 2, '}',   value::otype::object, PASS },      // 17 - quotes
        { " { \"bar\" : \"ul\" } ", 17 - 2, '}',  value::otype::object, PASS },     // Space skipped in parse
        { "[ \"ru\" ] ", 7, ']',  value::otype::array, PASS },
        { " [ \"als\" ] ", 8, ']',  value::otype::array, PASS }
    };

    TEST_IT_START

      const char *startp = (*it).starp;

      json *j = new json (startp + strlen (startp), 0, (*it).move);

      const char * readp = j->parse (startp);

      // std::cout << readp -1 << std::endl;

      ASSERT_EQUAL_IDX ("readp", (*it).endch, *(readp - 1));
      ASSERT_EQUAL_IDX ("object type", (*it).type, j->type ());

      delete j;

    TEST_IT_END;
  }

  virtual void test_size_1 () {}
  virtual void test_at_1 () {}
  virtual void test_value_1 () {}
  virtual void test_debug_1 () {}

  static CppUnit::Test*
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json test");

//    s->addTest (new CppUnit::TestCaller<json_test> ("test_smoke", &json_test::test_smoke));
    s->addTest (new CppUnit::TestCaller<json_test> ("test_parse_1", &json_test::test_parse_1));
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_size_1", &json_test::test_size_1));
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_get_1", &json_test::test_get_1));
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_value_1", &json_test::test_value_1));
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_debug_1", &json_test::test_debug_1));

    return s;
  }
};

#endif // JSON_TEST_H
