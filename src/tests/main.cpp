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

#define DBG(...) fprintf (stderr, __VA_ARGS__)

#define TESTC 9   // Test count

int main(int argc, char *argv[])
{
    int test_num    = 0;
    int first_test  = 0;
    int last_test   = TESTC;

    struct _test {
      CppUnit::Test *test;
      bool is_added;
      _test (CppUnit::Test * _test = 0, bool _is_added = false) : test (_test), is_added (_is_added) {}

    } tests[] = {
      { json_value_test::suite () },        // 0
      { json_test::suite () },              // 1
      { json_object_test::suite () },       // 2
      { json_array_test::suite () },        // 3
      { json_string_test::suite () },       // 4
      { json_number_test::suite () },       // 5
      { json_boolean_test::suite () },      // 6
      { json_null_test::suite () },         // 7
      { json_undefined_test::suite () }     // 8
    };

    CppUnit::TextUi::TestRunner runner;

    if (argc == 1)
      {
        while (first_test < last_test)
          {
            runner.addTest (tests[first_test].test);
            tests[first_test].is_added = true;
            first_test++;
          }
      }
    else
      {
        for (int idx = 1; idx < argc; idx++)
          {
            test_num = atoi (argv[idx]);

            if (test_num >= -1 && test_num < last_test)
              {
                runner.addTest (tests[test_num].test);
                tests[test_num].is_added = true;
                std::cout << tests[test_num].test->getName () << std::endl;
              }
            else
              {
                std::cerr << "tests: " << 0 << " - " << TESTC - 1 << std::endl;
                return 1;
              }
          }
      }

    try
      {
        runner.run ();
      }
    catch (...)
      {
        DBG ("%s: cought exception of unknown type\n", argv[0]);
      }

    for (int idx = 0; idx < last_test; idx++)
      if (tests[idx].is_added == false)
        delete tests[idx].test;

    return 0;
}

