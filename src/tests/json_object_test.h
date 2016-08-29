#ifndef JSON_OBJECT_TEST_H
#define JSON_OBJECT_TEST_H

#include <json_value_test_interface.h>

/**
 * Test number 1
 * @brief The json_object_test class
 */
class json_object_test : public json_value_test_interface
{
public:

  virtual void test_smoke () {}

  virtual
  void test_parse_1 ()
  {
    Object *p = new Object (0, 0);

    struct assert {
      const char *startp;
      size_t size;
      value::otype type;
      value *parent;
      size_t moveback;
      int assert_status;
    };

    std::vector<struct assert > test = {
      { "{ \"k\" : \"v\" } ", 1, value::string, p, 1, PASS },
      { "{ \"k\" : \"v\", \"q\" : \"p\" } ", 2, value::string, p, 1, PASS },
      { "{ \"k\": \"v\", \"q\" : \"p\",\"K\":\"v\" } ", 3, value::string, p, 1, PASS },
      { "{ \"k\": \"p\" ,\"q\" : \"p\", \"K\" :\"v\",\"Q\":\"p\" } ", 4, value::string, p, 1, PASS },
      { "{}", 0, value::undefined, p, 0, PASS },
      { "{ } ", 0, value::undefined, p, 1, PASS },
      { "{ \"k\" : { } }", 1, value::object, p, 0, PASS },
      { "{ \"k\" : {\"kk\" : \"v\"}}", 1, value::object, p, 0, PASS },
      { "{ \"k\" : {\"kk\" : {\"kkk\" : \"v\"}}", 1, value::object, p, 0, PASS },
      { "{ \"k\" : null } ", 1, value::null, p, 1, PASS },

      // errors
      { "{ , }", 0, value::undefined, p, 0, FAIL },   // json::syntax_error
      { "{ : }", 0, value::undefined, p, 0, FAIL },   // json::syntax_error

      { "", 0, value::undefined, 0, 0, FAIL },   // json::syntax_error
  };

    TEST_IT_START;

      const char *startp = (*it).startp;

      size_t charc = strlen (startp);

      Object *o = new Object (startp + charc, (*it).parent);

      const char *readp = o->parse (startp);

      ASSERT_EQUAL_IDX ("value.readp", (startp + charc) - (*it).moveback, readp);
      ASSERT_EQUAL_IDX ("*(value.readp -1)", '}', *(readp - 1));
      ASSERT_EQUAL_IDX ("value.size", (*it).size, o->size ());
      ASSERT_EQUAL_IDX ("value.type", (*it).type, o->at ("k").type ());

      delete o;

    TEST_IT_END;

    delete p;
  }

  virtual void test_size_1() {}
  virtual void test_at_1() {}
  virtual void test_value_1() {}
  virtual void test_debug_1() {}

  void
  test__pair ()
  {
    Object *p = new Object (0, 0);

    struct assert {
      const char *startp;
      bool status;
      int assert_status;
    };

    std::vector<struct assert > test = {
      { " \"foo\" : \"bar\" ", true, PASS },
      { " }" , false , PASS },

      // errors
      { " ", false, FAIL},            // json::syntax_error
      { " \"foo  ", false, FAIL },    // json::syntax_error
      { " \"foo\" ", false, FAIL },   // json::syntax_error
      { " \"foo\" : ", false, SKIP }, // FAIL: json::syntax_error
    };

    TEST_IT_START;

      const char *startp = (*it).startp;

      Object *o = new Object (startp + strlen (startp), p);

      o->_readp = startp;
      bool status = o->_pair ();

      // readp = o->parse (startp);

      ASSERT_EQUAL_IDX ("status", (*it).status, status);

      delete o;

    TEST_IT_END;
  }

  void test__value () {}

  static CppUnit::Test*
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json object test");

//    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_smoke", &json_object_test::test_smoke));
      s->addTest (new CppUnit::TestCaller<json_object_test> ("test_parse_1", &json_object_test::test_parse_1));
//    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_size_1", &json_object_test::test_size_1));
//    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_get_1", &json_object_test::test_get_1));
//    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_value_1", &json_object_test::test_value_1));
//    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_debug_1", &json_object_test::test_debug_1));

     s->addTest (new CppUnit::TestCaller<json_object_test> ("test_pair_1", &json_object_test::test__pair));
 //     s->addTest (new CppUnit::TestCaller<json_object_test> ("test_pair_1", &json_object_test::test__value));

     return s;
  }

};

#endif // JSON_OBJECT_TEST_H
