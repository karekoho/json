#ifndef JSON_OBJECT_TEST_H
#define JSON_OBJECT_TEST_H

#include <json_value_test_interface.h>

/**
 * Test number 2
 * @brief The json_object_test class
 */
class json_object_test : public json_value_test_interface
{
public:

  virtual void test_smoke () {}

  virtual
  void test_parse_1 ()
  {
    json::object *o = 0;
    json::object *p = 0;

    struct assert {
      const char *input;
      size_t size;
      value::otype type;
      int assert_status;
    };

    std::vector<struct assert > test = {
      { "{ \"k\" : \"v\" } ", 1, value::string, PASS },
      { "{ \"k\" : \"v\", \"q\" : \"p\" } ", 2, value::string, PASS },
      { "{ \"k\": \"v\", \"q\" : \"p\",\"K\":\"v\" } ", 3, value::string, PASS },
      { "{ \"k\": \"p\" ,\"q\" : \"p\", \"K\" :\"v\",\"Q\":\"p\" } ", 4, value::string, PASS },
      { "{}", 0, value::undefined, PASS },
      { "{ \"k\" : { } }", 1, value::object, PASS },
      { "{ \"k\" : {\"kk\" : \"v\"}}", 1, value::object, PASS },
      { "{ \"k\" : {\"kk\" : {\"kkk\" : \"v\"}}", 1, value::object, PASS },
      { "{ \"k\" : null } ", 1, value::null, PASS },

      // errors
      { "{ , }", 0, value::undefined, FAIL },   // json::syntax_error
    };

    TEST_IT_START;

    this->_startp = (*it).input;
    this->_charc = strlen (this->_startp);

    o = new json::object (this->_startp + this->_charc, p);

    this->_readp = o->parse (this->_startp);

    ASSERT_EQUAL_IDX ("value.size", (*it).size, o->size ());
    ASSERT_EQUAL_IDX ("value.type", (*it).type, o->at ("k").type ());

    delete o;

    TEST_IT_END;
  }

  virtual void test_size_1() {}
  virtual void test_at_1() {}
  virtual void test_value_1() {}
  virtual void test_debug_1() {}

  void
  test__pair ()
  {
    json::object *o = 0;

    struct assert {
      const char *input;
      bool status;
      int assert_status;
    };

    std::vector<struct assert > test = {
      { " \"foo\" : \"bar\" ", true, PASS },
      { " }" , false , PASS },

      // errors
      { " ", false, FAIL },            // json::syntax_error
      { " \"foo  ", false, FAIL },    // json::syntax_error
      { " \"foo\" ", false, FAIL },   // json::syntax_error
    };

    TEST_IT_START;

    this->_startp = (*it).input;
    this->_charc = strlen (this->_startp);

    o = new json::object (this->_startp + this->_charc, 0);
    o->_readp = this->_startp;
    bool status = o->_pair ();
    // readp = o->parse (startp);

    // CPPUNIT_ASSERT_EQUAL_MESSAGE ("status", (*it).status, status);
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
