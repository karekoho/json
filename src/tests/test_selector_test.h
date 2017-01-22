#ifndef TEST_SELECTOR_TEST
#define TEST_SELECTOR_TEST

#include "unit_test.h"

/**
 * 13.
 *
 * @brief The test_selector_test class
 */
class test_selector_test : public unit_test
{
public:

  void
  test_indexes ()
  {

  }

  void
  test_tests()
  {

  }

  /**
   * 13.
   *
   * @brief suite
   * @return
   */
  static CppUnit::Test *
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("test selector test");

    s->addTest (new CppUnit::TestCaller<test_selector_test> ("test_indexes", &test_selector_test::test_indexes));
    s->addTest (new CppUnit::TestCaller<test_selector_test> ("test_testts", &test_selector_test::test_tests));

    return s;
  }
};

#endif // TEST_SELECTOR_TEST

