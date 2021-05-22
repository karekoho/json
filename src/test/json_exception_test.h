#ifndef JSON_EXCEPTION_TEST
#define JSON_EXCEPTION_TEST

#include "unit_test.h"

namespace format
{
  namespace json
  {
    /**
     * 14.
     * @brief The json_test class
     */
    class json_syntax_error_test : public unit_test
    {
    public:
      void
      test_ctor_1 ()
      {
        struct assert
        {
          const wchar_t *token;
          const char *output;
          size_t charc;
          int assert_status;
        };

        std::vector<struct assert > test = {
          { L"\u0061b\u0063d", "a:'\u0061b\u0063d'", 0, PASS },   // abcd, 97-100
          { L"\u2208b\u220Bd", "a:'\u2208b\u220Bd'", 0, PASS },   // ∈, 98, ∋, 100 NOTE: Fails in valgrind container
          { L"\u0061b\u0063d", "a:'\u0061'", 1, PASS },           // a:'a'
          { L"\u2208b\u220Bd", "a:'\u2208b'", 2, PASS },          // a:'∈b' NOTE: Fails in valgrind container
        };

        TEST_IT_START

          json_syntax_error e ("a:", (*it).token, (*it).charc);

          const char *output = e.what ();

          CPPUNIT_ASSERT_EQUAL_MESSAGE ("e.what ()", 0, strcmp ((*it).output, output));

        TEST_IT_END
      }

      /**
       * 14.
       * @brief suite
       * @return
       */
      static CppUnit::Test *
      suite ()
      {
        CppUnit::TestSuite *s = new CppUnit::TestSuite ("json exception test");

        /* 0. */  s->addTest (new CppUnit::TestCaller<json_syntax_error_test> ("test_ctor_1", &json_syntax_error_test::test_ctor_1));

        return s;
      }
    };
  } // Namespace json
} // Namespace format
#endif // JSON_EXCEPTION_TEST

