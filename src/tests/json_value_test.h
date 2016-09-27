#ifndef JSON_INTERFACE_TEST_H
#define JSON_INTERFACE_TEST_H

#include <json_value_test_interface.h>
#include "json_value_parse_mock.h"

/// Test number 0
class json_value_test : public json_value_test_interface
{
public:
    virtual void test_ctor_dtor() {}
    virtual void test_parse_1(){}
    virtual void test_size_1(){}
    virtual void test_at(){}
    virtual void test_value_1(){}
    virtual void test_debug_1(){}

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

        json_value_parse_mock *m  = new json_value_parse_mock;

        m->_startp = m->_readp = startp;

        m->_look_ahead ();

        ASSERT_EQUAL_IDX ("value.readp", (*it).readp , *(m->_readp));

        delete m;

      TEST_IT_END;
    }

    void test_lexeme ();

    void test_string () // Moved to json_test
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
          { "\"x\"", 3, PASS },
          { "\" x\"", 4, PASS },
          { "\" xx", -4, PASS }
          /* { "\"\
             x\"", 14 },
          { "   \"b", '"' },
          { "   \n\r\tc ", 'c' },
          { "   5", '5' } */
      };

      TEST_IT_START

          const char *startp = (*it).startp;
          long int charc = strlen (startp);

          json_value_parse_mock *m  = new json_value_parse_mock;

          m->_startp = m->_readp = startp;

          m->_look_ahead ();

          charc = m->_string (endc);

          // CPPUNIT_ASSERT_EQUAL_MESSAGE ("readp", startp , m->_readp); //   FAIL: { "\"", -1 }
          ASSERT_EQUAL_IDX ("charc", (*it).charc , charc);

          delete m;

      TEST_IT_END;
    }

    void test_is_literal ()
    {
      struct assert {
          const char *startp;
          Value::_literal value_type;
          int assert_status;
      };

      std::vector<struct assert> test = {
        { "", Value::_literal::no_value, PASS },
        { "   ", Value::_literal::no_value, PASS },
        { "xxx   ", Value::_literal::no_value, PASS },
        { "xxxxxx   ", Value::_literal::no_value, PASS },
        { "true    ", Value::_literal::true_value, PASS },
        { "false    ", Value::_literal::false_value, PASS },
        { "null   ", Value::_literal::null_value, PASS }
      };

      TEST_IT_START

          const char *startp = (*it).startp;

          json_value_parse_mock *m  = new json_value_parse_mock;

          m->_startp = m->_readp = startp;

          Value::_literal ltr = m->_is_literal ();

          ASSERT_EQUAL_IDX ("literal value", (*it).value_type , ltr);

          delete m;

      TEST_IT_END;
    }

    void
    test__str_append ()
    {
      char *dst = new char[8 + 1]();
      char *startp = dst;

      struct assert {
          const char *src;
          size_t charc[2];
          int assert_status;
      };

      std::vector<struct assert> test = {
        { "",  { 0, 0 }, PASS },
        { "a",  { 1, 1 }, PASS },
        { "bb",  { 2, 3 }, PASS },
        { "\"ccc\"",  { 5, 8 }, PASS },
      };

      TEST_IT_START

          dst = Value::_str_append (dst, (*it).src, (*it).charc[0]);

          ASSERT_EQUAL_IDX ("dst", startp + (*it).charc[1], dst);

      TEST_IT_END;

      CPPUNIT_ASSERT_MESSAGE ("starp", strcmp ("abb\"ccc\"", startp) == 0);

      delete[] startp;
    }

    virtual void test_operator_assign () {}
    virtual void test_operator_at () {}
    virtual void test_assign_all_values (){}
    virtual void test__clear() {}

    static CppUnit::Test*
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json value test");

      s->addTest (new CppUnit::TestCaller<json_value_test> ("test_lookahead", &json_value_test::test_lookahead));
      s->addTest (new CppUnit::TestCaller<json_value_test> ("test_is_literal", &json_value_test::test_is_literal));
      s->addTest (new CppUnit::TestCaller<json_value_test> ("test_is_quoted", &json_value_test::test_string));

      s->addTest (new CppUnit::TestCaller<json_value_test> ("test__str_append", &json_value_test::test__str_append));
      return s;
    }
};

#endif // JSON_INTERFACE_TEST_H
