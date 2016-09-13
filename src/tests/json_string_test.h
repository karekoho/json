#ifndef JSON_STRING_TEST_H
#define JSON_STRING_TEST_H

#include "json_value_test_interface.h"

/// Test number 4
class json_string_test : public json_value_test_interface
{
public:
    virtual void
    test_ctor_dtor ()
    {
    }

    virtual void
    test_parse_1 ()
    {
      JSON *p[] = { 0, new JSON () };

      struct assert
      {
        const char *startp;
        size_t charc;
        char endc;
        int assert_status;
      };

      std::vector<struct assert > test = {
          { "\"\"", 0, (char) 0, PASS },
          { "\"xxx\"", 3, (char) 0, PASS },
          { "\" xxx \"", 5, (char) 0, PASS },
          { "\" xxx \" ", 5, ' ', PASS },
      };

      TEST_IT_START
          for (int pidx = 0; pidx < 2; pidx++)
            {
              const char *startp = (*it).startp;
              size_t move = (*it).charc + 2;

              String *s = new String (p[pidx], move);

              std::string ss = s->value ();

              CPPUNIT_ASSERT_MESSAGE ("string.empty ()", ss.empty () );

              const char *readp = s->parse (startp);
              ss = s->value ();

              // std::cout << readp << "" << ss.length () << " " << ss << std::endl;

              ASSERT_EQUAL_IDX ("string.readp", readp, startp + move);
              ASSERT_EQUAL_IDX ("*(string.readp)", (char)* readp, (*it).endc);
              ASSERT_EQUAL_IDX ("string.length", (*it).charc, ss.length () );

              delete s;
            }
       TEST_IT_END;

       delete p[1];
    }

    virtual void
    test_assign_all_values ()
    {
    }

    virtual void test_size_1() {}
    virtual void test_at_1() {}
    virtual void test_value_1() {}
    virtual void test_debug_1() {}

    static CppUnit::Test*
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json string test");

      // s->addTest (new CppUnit::TestCaller<json_string_test> ("test_smoke", &json_string_test::test_smoke));
      s->addTest (new CppUnit::TestCaller<json_string_test> ("test_parse_1", &json_string_test::test_parse_1));

      return s;
    }
};

#endif // JSON_STRING_TEST_H
