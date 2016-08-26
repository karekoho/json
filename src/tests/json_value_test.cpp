#include "json_value_test.h"
#include "json_value_parse_mock.h"

void
json_value_test::test_lookahead ()
{
    size_t charc = 0;
    // size_t idx = 0;

    const char *startp = 0;

    struct assert {
        const char *input;
        char readp;
    };

    std::vector<struct assert > test = {
        { "", 0 },
        { "   ", 0 },
        { "x", 'x' },
        { " \
            a", 'a' },
        { "   \"b", '"' },
        { "   \n\r\tc ", 'c' },
        { "   5", '5' }
    };


    for (auto it = test.begin (); it != test.end (); it++) {
        startp = (*it).input;
        charc = strlen (startp);

        json_value_parse_mock *m  = new json_value_parse_mock (startp + charc, 0, 0);

        m->_startp = m->_readp = startp;

        m->_look_ahead ();

        CPPUNIT_ASSERT_EQUAL_MESSAGE ("test_lookahead", (*it).readp , *(m->_readp));

        delete m;
    }
}

// void json_value_test::test_lexeme () {}

void
json_value_test::test_is_literal ()
{
  size_t charc = 0;
  // size_t idx = 0;

  const char *startp = 0;

  struct assert {
      const char *input;
      value::_literal value_type;
  };

  std::vector<struct assert > test = {
    {"", value::_literal::no_value},
    {"   ", value::_literal::no_value},
    {"xxx   ", value::_literal::no_value},
    {"xxxxxx   ", value::_literal::no_value},
    {"true    ", value::_literal::true_value},
    {"false    ", value::_literal::false_value},
    {"null   ", value::_literal::null_value}

  };

  for (auto it = test.begin (); it != test.end (); it++) {
      startp = (*it).input;
      charc = strlen (startp);

      json_value_parse_mock *m  = new json_value_parse_mock (startp + charc, 0, 0);

      m->_startp = m->_readp = startp;

      value::_literal ltr = m->_is_literal ();

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("literal value", (*it).value_type , ltr);

      delete m;
  }
}

void
json_value_test::test_string ()
{
    long int charc = 0;
    char endc;
    const char *startp = 0;

    struct assert {
        const char *input;
        long int charc;
    };

    std::vector<struct assert > test = {
        { " ", 0 },
        { "\"", -1 },
        { "\" x\"", 4 },
        { "\" xx", -4 }
//        { "\"\
//           x\"", 14 },
//        { "   \"b", '"' },
//        { "   \n\r\tc ", 'c' },
//        { "   5", '5' }
    };


    for (auto it = test.begin (); it != test.end (); it++) {
        startp = (*it).input;
        charc = strlen (startp);

        json_value_parse_mock *m  = new json_value_parse_mock (startp + charc, 0, 0);

        m->_startp = m->_readp = startp;

        m->_look_ahead ();

        charc = m->_string (endc);

        // CPPUNIT_ASSERT_EQUAL_MESSAGE ("readp", startp , m->_readp); //   FAIL: { "\"", -1 }
        CPPUNIT_ASSERT_EQUAL_MESSAGE ("charc", (*it).charc , charc);

        delete m;
    }
}

// void json_value_test::test_is_number () { }

CppUnit::Test *
json_value_test::suite ()
{
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json value test");

    s->addTest (new CppUnit::TestCaller<json_value_test> ("test_lookahead", &json_value_test::test_lookahead));
//    s->addTest (new CppUnit::TestCaller<json_value_test> ("test_lexeme", &json_value_test::test_lexeme));
    s->addTest (new CppUnit::TestCaller<json_value_test> ("test_is_literal", &json_value_test::test_is_literal));
    s->addTest (new CppUnit::TestCaller<json_value_test> ("test_is_quoted", &json_value_test::test_string));
//    s->addTest (new CppUnit::TestCaller<json_value_test> ("test_is_number", &json_value_test::test_is_number));

    return s;
}
