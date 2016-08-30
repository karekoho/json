#ifndef JSON_TEST_H
#define JSON_TEST_H

#include <json_value_test_interface.h>
#include "json_value_parse_mock.h"

/// Test number 1
class json_test : public json_value_test_interface
{
public:

  virtual void test_smoke () {}

  void test_lookahead ()
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
  }

  void test_string () /// value_test has the same
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
  }

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

  void test_make_value ()
  {
  }

  void test_is_literal ()   /// value_test has the same
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

#endif // JSON_TEST_H
