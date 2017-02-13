#ifndef JSON_EXCEPTION_TEST
#define JSON_EXCEPTION_TEST

#include <unit_test.h>
#include "json_exception_test.h"

/**
 * 14.
 * @brief The json_test class
 */
class json_syntax_error_test:public unit_test
{
public:

  // void test_ctor_1 () {}

  void
  test_ctor_2 ()
  {
    struct assert
    {
      const char *output;
      int assert_status;
    };

    std::vector<struct assert > test = {
      { "a:'b'", PASS }
    };

    TEST_IT_START;

      JSON_Syntax_Error e ("a:", L'b');

      const char *output = e.what ();

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("e.what ()", 0, strcmp ((*it).output, output));

    TEST_IT_END
  }

  void
  test_ctor_3 ()
  {
    struct assert
    {
      const char *output;
      size_t charc;
      int assert_status;
    };

    std::vector<struct assert > test = {
      { "a:'abcd'", 0, PASS },
      { "a:'ab'", 2, PASS }
    };

    TEST_IT_START;

      JSON_Syntax_Error e ("a:", L"abcd", (*it).charc);

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

    s->addTest (new CppUnit::TestCaller<json_syntax_error_test> ("test_ctor_2", &json_syntax_error_test::test_ctor_2));
    s->addTest (new CppUnit::TestCaller<json_syntax_error_test> ("test_ctor_3", &json_syntax_error_test::test_ctor_3));

    return s;
  }

};

#endif // JSON_EXCEPTION_TEST

