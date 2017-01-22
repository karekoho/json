#ifndef TEST_SELECTOR
#define TEST_SELECTOR

#include <unit_test.h>

/**
 * @brief The test_selector struct
 */
struct test_selector
{
  /**
   * @brief indexes
   * @return
   */
  static std::vector<int> *
  indexes (char *list)
  {
    return 0;
  }

  /**
   * @brief _suite
   * @return
   */
  static CppUnit::Test *
  tests (CppUnit::Test *test, std::vector<int> & indexes)
  {
    return 0;
  }
};

#endif // TEST_SELECTOR

