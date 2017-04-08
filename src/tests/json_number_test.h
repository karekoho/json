#ifndef JSON_NUMBER_TEST
#define JSON_NUMBER_TEST

#include "json_leaf_test.h"

namespace format
{
  /**
   * 5.
   * @brief The json_number_test class
   */
  class json_number_test : public json_leaf_test
  {
  public:

    virtual void
    test_ctor_dtor ()
    {
      json *p[] = { 0, new json };

      for (size_t pidx = 0; pidx < 2; pidx++)
        {
          number n[] = {
            number (),
            number (10),
            number (L"10"),
            number (p[pidx]),
          };
        }

      delete p[1];

      number src[] = {
        number (10),
        number (L"100")
      };

      number copy[] = {
          number (src[0]),
          number (src[1])
      };

      // double d[] = { copy[0].value (), copy[1].value () };

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("number::type ()", json::number_t, src[0].type ());
      CPPUNIT_ASSERT_MESSAGE ("number", & copy[0] != & src[0]);
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("src[1]._double_value", (double) 0, src[1]._double_value);
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy[0].value ()", (double) 10, copy[0].get ());
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy[1].value ()", (double) 100, copy[1].get ());
    }

    virtual void
    test_parse_1 ()
    {
      number n;

      struct assert
      {
        const wchar_t *starp;
        size_t move;
        double dval;
        int assert_status;
      };

      std::vector<struct assert > test = {
          { L"0", 1, 0, PASS },
          { L"0 ", 1, 0, PASS },
          { L"1 ", 1, 1, PASS },
          { L"00", 1, 0, PASS },
          { L"05", 1, 0, PASS },
          { L"-2]", 2, -2, PASS },
          { L"3.3 }", 3, 3.3, PASS },
          { L"0.4, ", 3, 0.4, PASS },
          { L"-0.5 ,", 4, -0.5, PASS },
          { L"6e2", 3, 600, PASS },
          { L"7E2}", 3, 700, PASS },
          { L"8E+2 ] ", 4, 800, PASS },
          { L"9E-2, ", 4, 0.09, PASS },

          { L"x", 1, 0, FAIL },   // NaN
          //{ L"00", 1, 0, FAIL },
          //{ L"05", 2, 0, FAIL },
          { L"+5", 2, 0, FAIL },  // Positive sign is not allowed
          { L"2e", 2, 0, FAIL },  // Multiplier of ten is not specified
          { L"2eX", 2, 0, FAIL }, // Multiplier of ten is NaN
      };

      TEST_IT_START
        const wchar_t *startp = (*it).starp;
        const wchar_t *readp = n._parse (startp);

        n._double_valuep = 0;

        ASSERT_EQUAL_IDX ("n._readp", startp + (*it).move, readp);
        ASSERT_EQUAL_IDX ("n.value ()", (*it).dval, n.get ());

      TEST_IT_END;
    }

    void
    test_digits ()
    {
      number n;

      struct assert
      {
        const wchar_t *starp;
        size_t move;
        int peek;
        int assert_status;
      };

      std::vector<struct assert > test = {
          { L"123", 3, 0, PASS },
          { L"123x", 3, L'x', PASS },
          { L"0.", 1, L'.', PASS },
          { L"123 ", 3, L' ', PASS },

          { L"", 0, -1, PASS },
          { L"x", 0, -1, PASS },
      };

      TEST_IT_START

          const wchar_t *startp = (*it).starp;

          n._readp = startp;
          // n._endp = startp + strlen (startp);

          int peek  = n._digits ();

          ASSERT_EQUAL_IDX ("readp", startp + (*it).move, n._readp);
          ASSERT_EQUAL_IDX ("peek", (*it).peek, peek);

      TEST_IT_END;
    }

    void
    test_frag ()
    {
      number n;

      struct assert
      {
        const wchar_t *starp;
        size_t move;
        int peek;
        int assert_status;
      };

      std::vector<struct assert > test = {

          { L"5.123 ", 5, L' ', PASS },
          { L"5.123}", 5, L'}', PASS },
          // { "5.123e", 5, 'e', PASS },
          // { "5.123E", 5, 'E', PASS },

          { L"5.", 2, 0, FAIL },
          { L"5.E", 2, L'E', FAIL },
      };

      TEST_IT_START

          const wchar_t *startp = (*it).starp;
          const wchar_t *endp = startp + (*it).move;

          n._readp = startp + 1;
          // n._endp = startp + strlen (startp);

          n._frag ();

          ASSERT_EQUAL_IDX ("readp", endp, n._readp);
          ASSERT_EQUAL_IDX ("peek", (*it).peek, (int)*(n._readp));
          ASSERT_EQUAL_IDX ("digitp[0][1]", endp, n._digitp[0][1]);

      TEST_IT_END;
    }

    void
    test_exp ()
    {
      number n;

      struct assert {
          const wchar_t *starp;
          size_t move[2];
          int peek;
          long long atoll;
          int assert_status;
      };

      std::vector<struct assert > test = {

          { L"2e2 ", { 2, 3 }, L' ', 2, PASS },
          { L"2E3}", { 2, 3 }, L'}', 3, PASS },
          { L"2e+4]", { 2, 4 }, L']', 4, PASS },
          { L"2e-5", { 2, 4 }, 0, -5, PASS },
          { L"2e-00005", { 2, 8 }, 0, -5, PASS },

          { L"2e", { 0, 0 }, 0, 0, FAIL },
          { L"2e ", { 0, 0 }, 0, 0, FAIL },
          { L"2e.", { 0, 0 }, 0, 0, FAIL },
          { L"2e+", { 0, 0 }, 0, 0, FAIL },
      };

      TEST_IT_START

          const wchar_t *startp = (*it).starp;
          const wchar_t *endp = startp + (*it).move[1];

          n._readp = startp + 1;
          // n._endp = startp + strlen (startp);

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
      number n;

      struct assert {
          const wchar_t *starp[2];
          size_t move[2];
          double dval;
          int assert_status;
      };

      std::vector<struct assert > test = {
        { { 0, 0 }, { 0, 0 }, 0, PASS },
        { { L"", L"" }, { 0, 0 }, 0, PASS },
        { { L"5", L"" }, { 1, 1 }, 5, PASS },
        { { L"5", L"0" }, { 1, 1 }, 5, PASS },
        { { L"2", L"1" }, { 1, 1 }, 20, PASS },
        { { L"2", L"2" }, { 1, 1 }, 200, PASS },
        { { L"2", L"-2" }, { 1, 2 }, 0.02, PASS },
      };

      TEST_IT_START

        const wchar_t *digitp[2][2] = {
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
      number n;

      struct assert {
          const wchar_t *starp;
          double dval;
          int assert_status;
      };

      std::vector<struct assert > test = {
          { L"5.5", 5.5, PASS },
          { L"55.55", 55.55, PASS },
      };


      TEST_IT_START

        const wchar_t *digitp[] = { (*it).starp, (*it).starp + wcslen ((*it).starp) };

        double d = n._atof (digitp);

        ASSERT_EQUAL_IDX ("n._atof ()", (*it).dval, d);

      TEST_IT_END;
    }

    void
    test_atoll ()
    {
      number n;

      struct assert {
          const wchar_t *starp;
          long long llval;
          int assert_status;
      };

      std::vector<struct assert > test = {
          { L"55", 55, PASS },
          { L"5555", 5555, PASS },
      };

      TEST_IT_START

        const wchar_t *digitp[] = { (*it).starp, (*it).starp + wcslen ((*it).starp) };

        long long ll = n._atoll (digitp);

        ASSERT_EQUAL_IDX ("n._atoll ()", (*it).llval, ll);

      TEST_IT_END;
    }

    virtual void
    test_assign_all_values ()
    {
      object_accessor object_parent;

      json *parents[] = {
        & object_parent,
        0
      };

      struct assert
      {
        value *new_value;
        value::value_t type;
        const wchar_t *key;
        size_t index;
        size_t count;
        int assert_status[3];
      };

      number n (10);

      std::vector<struct assert > test = {
        { & n, value::number_t, L"0",  0, 1, { PASS, PASS } },
        { __VALUE[value::boolean_t], value::boolean_t, L"1",  0, 2, { PASS, FAIL } },
      };

      number *old_value = 0;

      for (size_t pidx = 0; pidx < 2; pidx++)
        {
          this->_idx[0] = 0;
          for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++)
            {
              try
                {
                    if ((*it).assert_status[pidx] == SKIP) { continue; }\
                    if ((*it).assert_status[pidx] > PASS) { this->_errorc[EXPECTED]++; }

                    /** old_value: value from value[key] */
                    old_value = new number (parents[pidx]);
                    old_value->_double_valuep = 0;

                    old_value->_set_key ((*it).key, wcslen ((*it).key));

                    if ((*it).new_value->type () == value::number_t)
                      *old_value = *(dynamic_cast<number *>((*it).new_value));
                    else
                      *(dynamic_cast<value *>(old_value)) = *(*it).new_value;

                    json *parent = parents[pidx];

                    if (parent)
                      {
                        ASSERT_EQUAL_IDX ("parent->count ()",
                                          (*it).count,
                                          parent->length ());

                        ASSERT_EQUAL_IDX ("(*parent)[(*it).key].type ()",
                                          (*parent)[(*it).key].type (),
                                          (*it).type);
                      }
                    else if ((*it).new_value->type () == value::number_t)
                      {
                        ASSERT_EQUAL_IDX ("old_value->get ()", (double) 10, old_value->get ());
                        delete old_value;
                      }
                  }
                catch (format::json_error & e)
                  {
                    this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl;
                    delete old_value;
                  }
            }
          (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]); \
          CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
        }
      }

    virtual void
    test_str_value () override
    {
      struct assert
      {
        double d;
        const wchar_t *s[2];
        const wchar_t *output[3];
        int assert_status;
      };

      std::vector<struct assert > test = {
      { 100, { L"200", L"200.5" }, { L"100.000000", L"200", L"200.500000" }, PASS }
      };

      TEST_IT_START

        number n[3] = {
          number ((*it).d),
          number ((*it).s[0]),
          number ((*it).s[1]),
        };

        CPPUNIT_ASSERT_MESSAGE ("n[0].strValue ()", wcscmp((*it).output[0], n[0]._to_str ()) == 0);
        CPPUNIT_ASSERT_MESSAGE ("n[1].strValue ()", wcscmp((*it).output[1], n[1]._to_str ()) == 0);
        CPPUNIT_ASSERT_MESSAGE ("n[2].strValue ()", wcscmp((*it).output[2], n[2]._to_str ()) == 0);

      TEST_IT_END;
    }

    virtual void test_str_length () override {}
    virtual void test__clear () override {}
    virtual void test_type () override {}

    /**
     * 5.
     * @brief suite
     * @return
     */
    static CppUnit::Test *
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json number test");

      /* 0. */  s->addTest (new CppUnit::TestCaller<json_number_test> ("test_strValue", &json_number_test::test_str_value));
      /* 1. */  s->addTest (new CppUnit::TestCaller<json_number_test> ("test_ctor_dtor", &json_number_test::test_ctor_dtor));
      /* 2. */  s->addTest (new CppUnit::TestCaller<json_number_test> ("test_parse_1", &json_number_test::test_parse_1));
      /* 3. */  s->addTest (new CppUnit::TestCaller<json_number_test> ("test_digits", &json_number_test::test_digits));
      /* 4. */  s->addTest (new CppUnit::TestCaller<json_number_test> ("test_frag", &json_number_test::test_frag));
      /* 5. */  s->addTest (new CppUnit::TestCaller<json_number_test> ("test_exp", &json_number_test::test_exp));
      /* 6. */  s->addTest (new CppUnit::TestCaller<json_number_test> ("test_atof", &json_number_test::test_atof));
      /* 7. */  s->addTest (new CppUnit::TestCaller<json_number_test> ("test_atoll", &json_number_test::test_atoll));
      /* 8. */  s->addTest (new CppUnit::TestCaller<json_number_test> ("test_calculate", &json_number_test::test_calculate));
      /* 9. */  s->addTest (new CppUnit::TestCaller<json_number_test> ("test_assign_all_values", &json_number_test::test_assign_all_values));

      /* 10.   s->addTest (new CppUnit::TestCaller<json_number_test> ("", &json_number_test::test_str_length));
         11.   s->addTest (new CppUnit::TestCaller<json_number_test> ("", &json_number_test::test__clear)); */

      return s;
    }
  }; // Namespace format
}
#endif // json_number_test

