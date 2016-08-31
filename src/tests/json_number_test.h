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
        { "0", 1, 0, PASS },
        { "1 ", 1, 1, PASS },
        { "-2]", 2, -2, PASS },
        { "3.3 }", 3, 3.3, PASS },
        { "0.4, ", 3, 0.4, PASS },
        { "-0.5 ,", 4, -0.5, PASS },
        { "5e2", 3, 500, PASS },
        { "5E2}", 3, 500, PASS },
        { "5E+2 ] ", 4, 500, PASS },
        { "5E-2, ", 4, -500, PASS },

        { "x", 1, 0, FAIL },
        { "00", 1, 0, FAIL },
        { "05", 2, 0, FAIL },
        { "+5", 2, 0, FAIL },
    };

    TEST_IT_START

        const char *startp = (*it).starp;

        const char *readp = n.parse (startp);

        // std::cout << n._calculate (n._digitp) << std::endl; // uncaught exception of type std::length_error - basic_string::_M_create
        // std::cout << n.value () << std::endl; output: 0

        ASSERT_EQUAL_IDX ("readp", startp + (*it).move, readp);

        /// TODO: assert value () = dval

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
        int peek;
        int assert_status;
    };

    std::vector<struct assert > test = {
        { "123", 3, 0, PASS },
        { "123x", 3, 'x', PASS },
        { "0.", 1, '.', PASS },
        { "123 ", 3, ' ', PASS },

        { "", 0, -1, PASS },
        { "x", 0, -1, PASS },
    };

    TEST_IT_START

        const char *startp = (*it).starp;

        n._readp = startp;
        n._endp = startp + strlen (startp);

        int peek  = n._digits ();

        ASSERT_EQUAL_IDX ("readp", startp + (*it).move, n._readp);
        ASSERT_EQUAL_IDX ("peek", (*it).peek, peek);

    TEST_IT_END;
  }

  void
  test_frag ()
  {
    Number n;

    struct assert {
        const char *starp;
        size_t move;
        int peek;
        int assert_status;
    };

    std::vector<struct assert > test = {

        { "5.123 ", 5, ' ', PASS },
        { "5.123}", 5, '}', PASS },
        // { "5.123e", 5, 'e', PASS },
        //{ "5.123E", 5, 'E', PASS },

        { "5.", 2, 0, FAIL },
        { "5.E", 2, 'E', FAIL },
    };

    TEST_IT_START

        const char *startp = (*it).starp;
        const char *endp = startp + (*it).move;

        n._readp = startp + 1;
        n._endp = startp + strlen (startp);

        n._frag ();

        ASSERT_EQUAL_IDX ("readp", endp, n._readp);
        ASSERT_EQUAL_IDX ("peek", (*it).peek, (int)*(n._readp));
        ASSERT_EQUAL_IDX ("digitp[0][1]", endp, n._digitp[0][1]);

    TEST_IT_END;
  }

  void
  test_exp ()
  {
    Number n;

    struct assert {
        const char *starp;
        size_t move[2];
        int peek;
        long long atoll;
        int assert_status;
    };

    std::vector<struct assert > test = {

        { "2e2 ", { 2, 3 }, ' ', 2, PASS },
        { "2E3}", { 2, 3 }, '}', 3, PASS },
        { "2e+4]", { 2, 4 }, ']', 4, PASS },
        { "2e-5", { 2, 4 }, 0, -5, PASS },
        { "2e-00005", { 2, 8 }, 0, -5, PASS },

        { "2e", { 0, 0 }, 0, 0, FAIL },
        { "2e ", { 0, 0 }, 0, 0, FAIL },
        { "2e.", { 0, 0 }, 0, 0, FAIL },
        { "2e+", { 0, 0 }, 0, 0, FAIL },
    };

    TEST_IT_START

        const char *startp = (*it).starp;
        const char *endp = startp + (*it).move[1];

        n._readp = startp + 1;
        n._endp = startp + strlen (startp);

        n._exp ();

        ASSERT_EQUAL_IDX ("n._readp", endp, n._readp);
        ASSERT_EQUAL_IDX ("*(n._readp)", (int) *endp, (*it).peek);
        ASSERT_EQUAL_IDX ("n._digitp[1][0]", startp + (*it).move[0], n._digitp[1][0]);
        ASSERT_EQUAL_IDX ("n._digitp[1][1]", startp + (*it).move[1], n._digitp[1][1]);

        std::string s (n._digitp[1][0], n._digitp[1][1]);

        ASSERT_EQUAL_IDX ("n._llexp", (*it).atoll, atoll (s.c_str ()));

    TEST_IT_END;
  }

  void
  test_calculate ()
  {
    Number n;

    struct assert {
        const char *starp[2];
        size_t move[2];
        double dval;
        int assert_status;
    };

    std::vector<struct assert > test = {
      { { "5", "" }, { 1, 1 }, 5, PASS },
      { { "5", "0" }, { 1, 1 }, 5, PASS },
      { { "2", "1" }, { 1, 1 }, 20, PASS },
      { { "2", "2" }, { 1, 1 }, 200, PASS },
      { { "2", "-2" }, { 1, 2 }, 0.02, PASS },
    };

    TEST_IT_START

      const char *digitp[2][2] = {
        { (*it).starp[0], (*it).starp[0] + (*it).move[0] },
        { (*it).starp[1], (*it).starp[1] + (*it).move[1] }
      };

      double d = n._calculate (digitp);
      // std::cerr << d << " " << *(n._double_valuep) << std::endl;

      ASSERT_EQUAL_IDX ("n._calculate ()", (*it).dval, d);
      ASSERT_EQUAL_IDX ("n._double_valuep", d, *(n._double_valuep));

    TEST_IT_END;
  }

  void
  test_atof ()
  {
    Number n;

    struct assert {
        const char *starp;
        double dval;
        int assert_status;
    };

    std::vector<struct assert > test = {
        { "5.5", 5.5, PASS },
        { "55.55", 55.55, PASS },
    };


    TEST_IT_START

      const char *digitp[] = { (*it).starp, (*it).starp + strlen ((*it).starp) };

      double d = n._atof (digitp);

      ASSERT_EQUAL_IDX ("n._atof ()", (*it).dval, d);

    TEST_IT_END;
  }

  void
  test_atoll ()
  {
    Number n;

    struct assert {
        const char *starp;
        long long llval;
        int assert_status;
    };

    std::vector<struct assert > test = {
        { "55", 55, PASS },
        { "5555", 5555, PASS },
    };

    TEST_IT_START

      const char *digitp[] = { (*it).starp, (*it).starp + strlen ((*it).starp) };

      long long ll = n._atoll (digitp);

      ASSERT_EQUAL_IDX ("n._atoll ()", (*it).llval, ll);

    TEST_IT_END;
  }

  static CppUnit::Test *
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json number test");

 //    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_calculate", &json_number_test::test_calculate));

//    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_smoke", &json_number_test::test_smoke));
      s->addTest (new CppUnit::TestCaller<json_number_test> ("test_parse_1", &json_number_test::test_parse_1));
      // return s;
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

