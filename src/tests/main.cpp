#include <unit_test.h>
#include <json_value_test.h>
#include <json_test.h>
#include <json_object_test.h>
#include <json_string_test.h>
#include <json_array_test.h>
#include <json_number_test.h>
#include <json_boolean_test.h>
#include <json_null_test.h>
#include <json_undefined_test.h>
#include <json_leaf_test.h>
#include <json_object_iterator_test.h>
#include <json_array_iterator_test.h>
#include <json_leaf_iterator_test.h>
#include <test_selector_test.h>
#include <json_exception_test.h>

#include <cstdlib>

struct _test_
{
  /**
   * @brief test
   */
  CppUnit::Test *test;
  /**
   * @brief idxv
   */
  std::vector<int> *idxv;

  bool selected;
  /**
   * @brief _test_
   * @param _test
   * @param _idxv
   */
  _test_ (CppUnit::Test * _test = 0, std::vector<int> *_idxv = 0, bool selected = false)
    : test (_test), idxv (_idxv), selected (selected)
  {}
};

std::vector<_test_> tests = {
/* 0. */   { format::json_value_test::suite () },
/* 1. */   { format::json_test::suite () },
/* 2. */   { format::json_object_test::suite () },
/* 3. */   { format::json_array_test::suite () },
/* 4. */   { format::json_string_test::suite () },
/* 5. */   { format::json_number_test::suite () },
/* 6. */   { format::json_boolean_test::suite () },
/* 7. */   { format::json_null_test::suite () },
/* 8. */   { format::json_undefined_test::suite () },
/* 9. */   { format::json_object_iterator_test::suite () },
/* 10. */  { format::json_array_iterator_test::suite () },
/* 11. */  { format::json_leaf_iterator_test::suite () },
/* 12. */  { format::json_leaf_test::suite () },
/* 13. */  { test_selector_test::suite () },
/* 14. */  { json_syntax_error_test::suite () }
};

int
run (CppUnit::TextUi::TestRunner & runner)
{
  try
    {
      runner.run ();
    }
  catch (std::exception &e)
    {
      std::cerr << e.what () << std::endl;
      return EXIT_FAILURE;
    }
  catch (...)
    {
      std::cerr << "cought exception of unknown type" << std::endl;
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

void
clean ()
{
  for (auto & t : tests)
    {
      if (! t.selected)
        delete t.test;

      delete t.idxv;
    }
}

int
main (int argc, char *argv[])
{
  atexit (clean);

  CppUnit::TextUi::TestRunner runner;

  if (argc == 1)
    {
      for (auto & t : tests)
        {
          t.selected = true;
          runner.addTest (t.test);
        }

      return run (runner);
    }

  for (int idx = 1; idx < argc; idx++)
    {
      try
        {
          std::vector<int> *idxv = test_selector::indexes (argv[idx]);
          size_t testn = idxv->at (0);

          runner.addTest (test_selector::tests (tests.at (testn).test, *idxv));

          tests[testn].selected = true;
          tests[testn].idxv = idxv;

          std::cout << tests[testn].test->getName () << std::endl;
        }
      catch (std::out_of_range &)
        {
          std::cerr << "tests: " << 0 << " - " << tests.size () - 1 << std::endl;
          return EXIT_FAILURE;
        }
      catch (std::exception & e)
        {
          std::cerr << e.what () << std::endl;
          return EXIT_FAILURE;
        }
    }

  return run (runner);
}

