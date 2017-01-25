#ifndef TEST_SELECTOR
#define TEST_SELECTOR

#include <unit_test.h>

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

    std::vector<int> *idxv = new std::vector<int> ();

    char *token = strtok_r (strdupa (list), ",", & saveptr);

    while (token)
      {
        idxv->push_back (atoi (token));
        token = strtok_r (0, ",", & saveptr);
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
    if (indexes.empty ())
      return test;

    CppUnit::TestSuite *s = new CppUnit::TestSuite (test->getName ());

    for (auto it = indexes.begin () + 1; it != indexes.end (); ++it)  // Pass the first (test) index
      s->addTest (test->getChildTestAt (*it));

    /// TODO: delete old test
    return s;
  }
};

#endif // TEST_SELECTOR

