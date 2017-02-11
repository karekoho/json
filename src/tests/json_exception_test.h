#ifndef JSON_EXCEPTION_TEST
#define JSON_EXCEPTION_TEST

#include <unit_test.h>

/**
 * 14.
 * @brief The json_test class
 */
class json_exception_test : public unit_test
{
public:

  void
  test_ctor_1 ()
  {
  }

  void
  test_ctor_2 ()
  {
  }

  void
  test_ctor_3 ()
  {
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

    // s->addTest (new CppUnit::TestCaller<json_exception_test> ("test_ctor_1", &json_exception_test::test_ctor_1));
    s->addTest (new CppUnit::TestCaller<json_exception_test> ("test_ctor_2", &json_exception_test::test_ctor_1));
    s->addTest (new CppUnit::TestCaller<json_exception_test> ("test_ctor_3", &json_exception_test::test_ctor_1));

    return s;
  }

};

#endif // JSON_EXCEPTION_TEST

