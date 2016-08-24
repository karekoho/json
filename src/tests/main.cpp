// #include <QCoreApplication>

#include <unit_test.h>
#include <json_value_test.h>
#include <json_test.h>
#include <json_object_test.h>
#include <json_string_test.h>

#define DBG(...) fprintf (stderr, __VA_ARGS__)

#define TESTC 4  // 4 tests

int main(int argc, char *argv[])
{
    int test_num    = 0;
    int first_test  = 0;
    int last_test   = TESTC;  // Don't run async tests

    CppUnit::Test *tests[] = {
      json_value_test::suite (),        // 0
      json_test::suite (),              // 1
      json_object_test::suite (),       // 2
      json_string_test::suite ()        // 3

    };

    bool tests_added[] = {
      false,  // 0
      false,
      false,
      false
    };

    CppUnit::TextUi::TestRunner runner;

    if (argc == 1)
      {
        while (first_test < last_test)
          {
            runner.addTest (tests[first_test]);
            tests_added[first_test] = true;
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
                runner.addTest (tests[test_num]);
                tests_added[test_num] = true;
                std::cout << tests[test_num]->getName () << std::endl;
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
      if (tests_added[idx] == false)
        delete tests[idx];

    return 0;
}

