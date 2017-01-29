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
    if (indexes.size () <= 1)
      return test;

    CppUnit::TestSuite *s = new CppUnit::TestSuite (test->getName ()); // FIXME: LEAK

    /* ==1617== LEAK SUMMARY:
    ==1617==    definitely lost: 64 bytes in 1 blocks
    ==1617==    indirectly lost: 35 bytes in 2 blocks
    ==1617==      possibly lost: 0 bytes in 0 blocks
    ==1617==    still reachable: 72,704 bytes in 1 blocks
    ==1617==         suppressed: 0 bytes in 0 blocks
    ==1617== Rerun with --leak-check=full to see details of leaked memory
    ==1617==
    ==1617== For counts of detected and suppressed errors, rerun with: -v
    ==1617== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0) */

    for (auto it = indexes.begin () + 1; it != indexes.end (); ++it)  // Pass the first (test) index
      try
        {
          s->addTest (test->getChildTestAt (*it));
        }
      catch (std::exception &e)
        {
          std::cerr << e.what () << std::endl;
        }

    return s;
  }
};

#endif // TEST_SELECTOR

