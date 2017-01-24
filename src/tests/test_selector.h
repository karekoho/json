#ifndef TEST_SELECTOR
#define TEST_SELECTOR

// #include <unit_test.h>

#include <vector>
#include <cstring>
#include <cstdlib>

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
    char *saveptr = 0;
    char *token = 0;
    char *input = strdupa (list);

    std::vector<int> *idxv = new std::vector<int> ();

    for (size_t idx = 0; ; idx++, input = 0)
      {
        token = strtok_r (input, ",", & saveptr);

        if (token == 0)
          break;

        idxv->push_back (atoi (token));
      }

    return idxv;
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

