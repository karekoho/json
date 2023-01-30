#ifndef JSON_EXCEPTION_TEST
#define JSON_EXCEPTION_TEST

#include "unit_test.h"

namespace format
{
  namespace json
  {
    namespace test
    {
      //s->addTest (new CppUnit::TestCaller<json_syntax_error_test> ("test_ctor_1", &json_syntax_error_test::test_ctor_1));

      class syntax_error_test : public unit_test {};

      TEST_F (syntax_error_test, ctor)
      {
        struct assert
        {
          const wchar_t *token;
          const char *output;
          size_t charc;
          int assert_status;
        };

        std::vector<struct assert > test = {
          { L"\u0061b\u0063d", "a:'\u0061b\u0063d'", 0, PASS_T },   // abcd, 97-100
          { L"\u0061b\u0063d", "a:'\u0061'", 1, PASS_T },           // a:'a'
        };

        TEST_IT_START

          json_syntax_error e ("a:", (*it).token, (*it).charc);

          const char *output = e.what ();

          // Original assertion:
          ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("e.what ()", 0, strcmp ((*it).output, output));
          ///
          ASSERT_THAT (output, StrEq ((*it).output))
              << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }
    }
  } // Namespace json
} // Namespace format
#endif // JSON_EXCEPTION_TEST

