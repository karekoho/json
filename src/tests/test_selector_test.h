#ifndef TEST_SELECTOR_TEST
#define TEST_SELECTOR_TEST

#include "unit_test.h"
#include "test_selector.h"

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
    struct assert
    {
        const char *input;
        size_t size;
        int assert_status;
    };

    std::vector<struct assert> test = {
        { "", 0,  PASS },
        { "1", 1,  PASS },
        { "1,1,2,3", 4, PASS }
    };

    TEST_IT_START

      std::vector<int> *idxv = test_selector::indexes ((*it).input);

      ASSERT_EQUAL_IDX ("idxv->size ()", (*it).size, idxv->size ());

      delete idxv;

    TEST_IT_END;
  }

  void
  test_tests ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("test selector test");

    s->addTest (new CppUnit::TestCaller<test_selector_test> ("test_stub_1", &test_selector_test::test_stub_1));
    s->addTest (new CppUnit::TestCaller<test_selector_test> ("test_stub_2", &test_selector_test::test_stub_1));
    s->addTest (new CppUnit::TestCaller<test_selector_test> ("test_stub_3", &test_selector_test::test_stub_1));

    struct assert
    {
        std::vector<int> idxv;
        int childCount;
        int assert_status;
    };

    std::vector<struct assert> test = {
      { { 0 } , 3,  PASS },
      // { { 0 , 0, 2 }, 2,  PASS } // FIXME: LEAK, by 0x43A2DE: test_selector::tests(CppUnit::Test*, std::vector<int, std::allocator<int> >&) (test_selector.h:47)
    };

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

    TEST_IT_START

      CppUnit::Test *t = test_selector::tests (s, (*it).idxv);

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("t->countTestCases ()", (*it).childCount,  t->countTestCases ());

    TEST_IT_END;

    delete s;
  }

  void
  test_stub_1 ()
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
    s->addTest (new CppUnit::TestCaller<test_selector_test> ("test_tests", &test_selector_test::test_tests));

    return s;
  }
};

#endif // TEST_SELECTOR_TEST

