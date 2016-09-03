#ifndef JSON_TEST_H
#define JSON_TEST_H

#include <json_value_test_interface.h>
#include "json_value_parse_mock.h"

/// Test number 1
class json_test : public json_value_test_interface
{
public:

  virtual void
  test_ctor_dtor ()
  {
    const char * input = "{}";

    JSON j[] = {
      JSON (),
      JSON (0, 0)
    };

    (void) j[0].parse (input);
    (void) j[1].parse (input);
  }

  virtual void
  test_parse_1 ()
  {
    struct assert {
        const char *starp;
        Value::object_type type;
        int assert_status;
    };

    std::vector<struct assert > test = {
        { " {} ", Value::object_type::object, PASS },
        { " [] ", Value::object_type::array, PASS },
        { " \"x\" ", Value::object_type::string, PASS },
        { " 100 ", Value::object_type::number, PASS },
        { " null ", Value::object_type::null, PASS },
        { " true ", Value::object_type::boolean, PASS },
        { " false ", Value::object_type::boolean, PASS },

        { "{\"k\":\"v\"} ", Value::object_type::object, PASS },
        { " { \"k\" : \"v\" } ", Value::object_type::object, PASS },
        { "[\"v\"] ", Value::object_type::array, PASS },
        { " [ \"v\", [\"vv\"] ] ", Value::object_type::array, PASS },

        /// errors
        { " x ", Value::object_type::undefined, FAIL },
        { " {} , ", Value::object_type::undefined, FAIL },
        { ", {} ", Value::object_type::undefined, FAIL },
        { " truee ", Value::object_type::undefined, FAIL },
    };

    TEST_IT_START

      const char *startp = (*it).starp;

      size_t charc = strlen (startp);
      JSON *j = new JSON (0, 0);

      const char * readp = j->parse (startp);

      ASSERT_EQUAL_IDX ("json.readp", (*it).starp + (charc), readp);
      ASSERT_EQUAL_IDX ("*(json.readp)", (char) 0, *readp);
      ASSERT_EQUAL_IDX ("json.type ()", (*it).type, j->type ());

      delete j;

    TEST_IT_END;
  }

  void test_make_value ()
  {
    JSON j;
    struct assert {
        const char *starp;
        Value::object_type type;
        size_t move;
        int assert_status;
    };

    std::vector<struct assert > test = {
        { "{} ", Value::object_type::object, 2, PASS },
        { "[] ", Value::object_type::array, 2, PASS },
        { "\"x\" ", Value::object_type::string, 3, PASS },
        { "10 ", Value::object_type::number, 2, PASS },
        { "-10 ", Value::object_type::number, 3, PASS },
        { "true ", Value::object_type::boolean, 4, PASS },
        { "false ", Value::object_type::boolean, 5, PASS },
        { "null ", Value::object_type::null, 4, PASS },
        { "x ", Value::object_type::undefined, 0, PASS },
        { "", Value::object_type::undefined, 0, PASS },
    };

    TEST_IT_START

        const char *startp = (*it).starp;

        //j._endp = startp + strlen (startp);
        j._readp = startp;

        Value *v = j._make_value ();

        ASSERT_EQUAL_IDX ("json._readp", startp + (*it).move , j._readp);
        ASSERT_EQUAL_IDX ("value.type ()", (*it).type , v->type ());

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

    s->addTest (new CppUnit::TestCaller<json_test> ("test_smoke", &json_test::test_ctor_dtor));
    s->addTest (new CppUnit::TestCaller<json_test> ("test_parse_1", &json_test::test_parse_1));

//    s->addTest (new CppUnit::TestCaller<json_test> ("test_lookahead", &json_test::test_lookahead));   // value_test has the same
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_is_literal", &json_test::test_is_literal)); // value_test has the same
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_is_quoted", &json_test::test_string));      // value_test has the same

    s->addTest (new CppUnit::TestCaller<json_test> ("test_make_value", &json_test::test_make_value));

//    s->addTest (new CppUnit::TestCaller<json_test> ("test_size_1", &json_test::test_size_1));
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_get_1", &json_test::test_get_1));
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_value_1", &json_test::test_value_1));
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_debug_1", &json_test::test_debug_1));

    return s;
  }
};

/* void test_is_literal ()   /// value_test has the same
{
  struct assert {
      const char *startp;
      value::_literal value_type;
      int assert_status;
  };

  std::vector<struct assert> test = {
    { "", value::_literal::no_value, PASS },
    { "   ", value::_literal::no_value, PASS },
    { "xxx   ", value::_literal::no_value, PASS },
    { "xxxxxx   ", value::_literal::no_value, PASS },
    { "true    ", value::_literal::true_value, PASS },
    { "false    ", value::_literal::false_value, PASS },
    { "null   ", value::_literal::null_value, PASS }
  };

  TEST_IT_START

      const char *startp = (*it).startp;

      json_value_parse_mock *m  = new json_value_parse_mock (startp + strlen (startp), 0, 0);

      m->_startp = m->_readp = startp;

      value::_literal ltr = m->_is_literal ();

      ASSERT_EQUAL_IDX ("literal value", (*it).value_type , ltr);

      delete m;

  TEST_IT_END;
} */

/* void test_lookahead ()  /// value_test has the same
{
  struct assert {
      const char *startp;
      char readp;
      int assert_status;
  };

  std::vector<struct assert > test = {
      { "", 0, PASS},
      { "   ", 0, PASS },
      { "x", 'x', PASS },
      { " \
          a", 'a', PASS },
      { "   \"b", '"', PASS },
      { "   \n\r\tc ", 'c', PASS },
      { "   5", '5', PASS }
  };

  TEST_IT_START

    const char *startp = (*it).startp;

    json_value_parse_mock *m  = new json_value_parse_mock (startp + strlen (startp), 0, 0);

    m->_startp = m->_readp = startp;

    m->_look_ahead ();

    ASSERT_EQUAL_IDX ("value.readp", (*it).readp , *(m->_readp));

    delete m;

  TEST_IT_END;
} */

/* void test_string () /// value_test has the same
{
  char endc;

  struct assert {
      const char *startp;
      long int charc;
      int assert_status;
  };

  std::vector<struct assert > test = {
      { " ", 0, PASS},
      { "\"", -1, PASS },
      { "\" x\"", 4, PASS },
      { "\" xx", -4, PASS }
//        { "\"\
//           x\"", 14 },
//        { "   \"b", '"' },
//        { "   \n\r\tc ", 'c' },
//        { "   5", '5' }
  };

  TEST_IT_START

      const char *startp = (*it).startp;
      long int charc = strlen (startp);

      json_value_parse_mock *m  = new json_value_parse_mock (startp + charc, 0, 0);

      m->_startp = m->_readp = startp;

      m->_look_ahead ();

      charc = m->_string (endc);

      // CPPUNIT_ASSERT_EQUAL_MESSAGE ("readp", startp , m->_readp); //   FAIL: { "\"", -1 }
      ASSERT_EQUAL_IDX ("charc", (*it).charc , charc);

      delete m;

  TEST_IT_END;
} */


#endif // JSON_TEST_H
