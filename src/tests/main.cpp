// #include <QCoreApplication>

#include <unit_test.h>
#include <json_test.h>

#define DBG(...) fprintf (stderr, __VA_ARGS__)

#define TESTC 1  // 1 tests

int main(int argc, char *argv[])
{
    int test_num    = 0;
    int first_test  = 0;
    int last_test   = TESTC;  // Don't run async tests

    CppUnit::Test *tests[] = {
      json_test::suite ()                  // 0
    };

    bool tests_added[] = {
      false  // 0
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

            if (test_num >= -1 && test_num < last_test + 4)
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

