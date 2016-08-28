#ifndef JSON_STRING_TEST_H
#define JSON_STRING_TEST_H

#include "json_value_test_interface.h"

/// Test number 3
class json_string_test : public json_value_test_interface
{
public:
    virtual void test_smoke (){}

    virtual void test_parse_1 ()
    {
      size_t charc = 0;

      String *s = 0;

      const char *startp = 0;
      const char *readp = 0;

      struct assert {
          const char *startp;
          size_t charc;
          int assert_status;
      };

      std::vector<struct assert > test = {
          { "\"\"", 0, PASS},
          { "\"xxx\"", 3, PASS },
          { "\" xxx \"", 5, PASS },
      };

      TEST_IT_START

        startp = (*it).startp;
        charc = strlen (startp);

        s = new String (startp + charc, 0, charc);

        std::string ss = s->value ();

        CPPUNIT_ASSERT_MESSAGE ("empty", ss.empty () );

        readp = s->parse (startp);
        ss = s->value ();

        // std::cout << readp << "" << ss.length () << " " << ss << std::endl;

        ASSERT_EQUAL_IDX ("string.readp", *readp, (char) 0);
        ASSERT_EQUAL_IDX ("string.length", (*it).charc, ss.length () );

        delete s;

       TEST_IT_END;
    }

    virtual void test_size_1() {}
    virtual void test_at_1() {}
    virtual void test_value_1() {}
    virtual void test_debug_1() {}

    static CppUnit::Test*
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json string test");

       s->addTest (new CppUnit::TestCaller<json_string_test> ("test_parse_1", &json_string_test::test_parse_1));

      return s;
    }
};

#endif // JSON_STRING_TEST_H
