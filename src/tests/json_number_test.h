#ifndef JSON_NUMBER_TEST
#define JSON_NUMBER_TEST

#include "json_value_test_interface.h"

/// Test number 5
class json_number_test : public json_value_test_interface {

  // json_value_test_interface interface
public:

  virtual void
  test_smoke() {}

  virtual void
  test_parse_1 ()
  {
    Number n;

    struct assert {
        const char *starp;
        size_t move;
        double dval;

        int assert_status;
    };

    std::vector<struct assert > test = {
        { "0", 1, 5, PASS },
        { "5 ", 1, 5, PASS },
        { "-5]", 2, -5, PASS },
        { "5.5 }", 3, 5.5, PASS },
        { "0.5, ", 3, 0.5, PASS },
        { "-0.5 ,", 4, -0.5, PASS },
        { "5e2", 3, 500, PASS },
        { "5E2}", 3, 500, PASS },
        { "5E+2 ] ", 4, 500, PASS },
        { "5E-2, ", 4, -500, PASS },

        { "x", 1, 0, FAIL },
        { "0", 1, 0, FAIL },
        { "05", 2, 0, FAIL },
        { "+5", 2, 0, FAIL },
    };

    TEST_IT_START

        const char *startp = (*it).starp;

    TEST_IT_END;
  }

  virtual void test_size_1() {}

  virtual void test_at_1() {}

  virtual void test_value_1() {}

  virtual void test_debug_1() {}

  void
  test_digits ()
  {
    Number n;

    struct assert {
        const char *starp;
        size_t move;
        int assert_status;
    };

    std::vector<struct assert > test = {
        { "123", 3, PASS },
        { "123x", 3, PASS },
        { "0.", 2, PASS },
        { "123 ", 3, PASS },

        { "01 ", 2, FAIL },

        /// TODO: assert digitp[0][0] = startp
        /// TODO: assert endp = start + move
    };

    TEST_IT_START

        const char *startp = (*it).starp;

    TEST_IT_END;
  }

  void
  test_frag ()
  {
    Number n;

    struct assert {
        const char *starp;
        size_t move;
        int assert_status;
    };

    std::vector<struct assert > test = {

        { "5.123 ", 4, PASS },
        { "5.123}", 4, PASS },
        { "5.123e", 4, PASS },
        { "5.123E", 4, PASS },

    };

     /// TODO: assert endp = start + move
     /// TODO: assert digitp[0][1] = endp

    TEST_IT_START

        const char *startp = (*it).starp;

    TEST_IT_END;

  }

  void
  test_exp ()
  {
    Number n;

    struct assert {
        const char *starp;
        size_t move;
        int assert_status;
    };

    std::vector<struct assert > test = {

        { "2e2 ", 1, PASS },
        { "2E3}", 1, PASS },
        { "2e+4]", 2, PASS },
        { "2e-5", 2, PASS },

        { "2e-05", 3, FAIL },
        { "2e-x", 3, FAIL },
    };

    /// TODO: assert endp = starp + move
    /// TODO: assert digitp[1][0] = startp
    /// TODO: assert digitp[1][1] = endp
    /// TODO: assert exp eNUM

    TEST_IT_START

        const char *startp = (*it).starp;

    TEST_IT_END;
  }

  void
  test_atof ()
  {
    struct assert {
        const char *starp;
        double dval;
        int assert_status;
    };

    std::vector<struct assert > test = {
        { "5.5 ", 5.5, PASS },
        { "55.55", 55.55, PASS },
    };
  }

  void
  test_atoll ()
  {
    struct assert {
        const char *starp;
        long long llval;
        int assert_status;
    };

    std::vector<struct assert > test = {
        { "55 ", 55, PASS },
        { "5555", 5555, PASS },
    };
  }

  static CppUnit::Test *
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json number test");

//    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_smoke", &json_number_test::test_smoke));
      s->addTest (new CppUnit::TestCaller<json_number_test> ("test_parse_1", &json_number_test::test_parse_1));
//    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_size_1", &json_number_test::test_size_1));
//    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_get_1", &json_number_test::test_get_1));
//    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_value_1", &json_number_test::test_value_1));
//    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_debug_1", &json_object_test::test_debug_1));

      s->addTest (new CppUnit::TestCaller<json_number_test> ("test_digits", &json_number_test::test_digits));
      s->addTest (new CppUnit::TestCaller<json_number_test> ("test_frag", &json_number_test::test_frag));
      s->addTest (new CppUnit::TestCaller<json_number_test> ("test_exp", &json_number_test::test_exp));
      s->addTest (new CppUnit::TestCaller<json_number_test> ("test_atof", &json_number_test::test_atof));
      s->addTest (new CppUnit::TestCaller<json_number_test> ("test_atoll", &json_number_test::test_atoll));

    return s;
  }
};

#endif // json_number_test

