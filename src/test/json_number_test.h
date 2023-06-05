#ifndef JSON_NUMBER_TEST
#define JSON_NUMBER_TEST

#include "unit_test.h"
#include "json_mock_value.h"
#include <cstring>
#include <climits>

namespace format
{
  namespace json
  {
    namespace test
    {
      //s->addTest (new CppUnit::TestCaller<json_number_test> ("test_ctor_dtor", &json_number_test::test_ctor_dtor));
      //s->addTest (new CppUnit::TestCaller<json_number_test> ("test__to_string", &json_number_test::test__to_string));
      //s->addTest (new CppUnit::TestCaller<json_number_test> ("test_parse", &json_number_test::test__parse));
      //s->addTest (new CppUnit::TestCaller<json_number_test> ("test_digits", &json_number_test::test_digits));
      //s->addTest (new CppUnit::TestCaller<json_number_test> ("test_frag", &json_number_test::test_frag));
      //s->addTest (new CppUnit::TestCaller<json_number_test> ("test_exp", &json_number_test::test_exp));
      //s->addTest (new CppUnit::TestCaller<json_number_test> ("test_atof", &json_number_test::test_atof));
      //s->addTest (new CppUnit::TestCaller<json_number_test> ("test_atoll", &json_number_test::test_atoll));
      //s->addTest (new CppUnit::TestCaller<json_number_test> ("test_calculate", &json_number_test::test_calculate));
      //s->addTest (new CppUnit::TestCaller<json_number_test> ("test_assign_all_values", &json_number_test::test_assign_all_values));
      //s->addTest (new CppUnit::TestCaller<json_number_test> ("test__clone_const_value_ref", &json_number_test::test__clone_const_value_ref));
      //s->addTest (new CppUnit::TestCaller<json_number_test> ("test_str_length", &json_number_test::test_str_length));
      //s->addTest (new CppUnit::TestCaller<json_number_test> ("test__clear", &json_number_test::test__clear));
      //s->addTest (new CppUnit::TestCaller<json_number_test> ("test_type", &json_number_test::test_type));
      //s->addTest (new CppUnit::TestCaller<json_number_test> ("test___integral_length", &json_number_test::test___integral_length));
      //s->addTest (new CppUnit::TestCaller<json_number_test> ("test___to_string_ll", &json_number_test::test___to_string_ll));
      //s->addTest (new CppUnit::TestCaller<json_number_test> ("test___to_string_ld", &json_number_test::test___to_string_ld));

      /// Removed operator =(long double | long long)
      // //s->addTest (new CppUnit::TestCaller<json_number_test> ("test_assign_operator_long", &json_number_test::test_operator_assign_long));
      // //s->addTest (new CppUnit::TestCaller<json_number_test> ("test_assign_operator_double", &json_number_test::test_operator_assign_double));

      class number_test : public unit_test
      {
        public:
        static bool
        absoluteToleranceCompare (long double a, long double b, int ulp)
        {
            // See https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
            // The machine epsilon has to be scaled to the magnitude of the values used
            // and multiplied by the desired precision in ULPs (units in the last place)
            return std::fabs (a - b) <= std::numeric_limits<long double>::epsilon () * std::fabs (a + b) * ulp
                // unless the result is subnormal
                || std::fabs (a - b) < std::numeric_limits<long double>::min ();
        }
      };

      TEST_F (number_test, ctor_dtor)
      {
        json parent;

        long double max_double = std::numeric_limits<long double>::max ();

        mock_number src[] = {
          mock_number (),
          mock_number (100),
          mock_number (max_double),
          mock_number (L"100"),
          mock_number (L"100.1"),
          mock_number (& parent),
        };

        mock_number copy[] = {
            mock_number (src[0]),
            mock_number (src[1]),
            mock_number (src[2]),
            mock_number (src[3]),
            mock_number (src[4]),
            mock_number (src[5]),
            mock_number (number (100))
        };

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("number::type ()", json::number_t, src[0].type ());
        ///
        ASSERT_THAT (src[0].type (), Eq (json::number_t));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("number default value", (int) 0, (int) src[0].get ());
        ///
        ASSERT_THAT (src[0].get (), Eq (0));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("number int value", (int) 100, (int) src[1].get ());
        ///
        ASSERT_THAT (src[1].get (), Eq (100));

        // Original assertion:
        ///CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE ("number double value", max_double, src[2].get (), delta);
        ///
        ASSERT_THAT ((double) src[2].get (), DoubleEq (max_double));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("parsed number int value", (int) 100, (int) src[3].get ());
        ///
        ASSERT_THAT (src[3].get (), Eq (100));

        // Original assertion:
        ///CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE ("parsed number float value", (float) 100.1, (float) src[4].get (), delta);
        ///
        ASSERT_THAT ((float) src[4].get (), FloatEq ((float) 100.1));


        // Test copies
        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("copy", & copy[0] != & src[0]);
        ///
        ASSERT_NE (& copy[0], & src[0]); // First fix

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("number default value", (int) 0, (int) copy[0].get ());
        ///
        ASSERT_THAT ((int) copy[0].get (), Eq (0));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("number int value", (int) 100, (int) copy[1].get ());
        ///
        ASSERT_THAT ((int) copy[1].get (), Eq (100));

        // Original assertion:
        ///CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE ("number double value", max_double, copy[2].get (), delta);
        ///
        ASSERT_THAT ((double) copy[2].get (), DoubleEq (max_double));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("parsed number int value", (int) 100, (int) copy[3].get ());
        ///
        ASSERT_THAT ((int) copy[3].get (), Eq (100));

        // Original assertion:
        ///CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE ("parsed number float value", (float) 100.1, (float) copy[4].get (), delta);
        ///
        ASSERT_THAT ((float) copy[4].get (), FloatEq ((float) 100.1));

        // TODO: what is the correct place for these?
        json j = new object { { L"0", new number ((float) 101.1) },
                              { L"1", new number (10) } };

        // Original assertion:
        ///CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE ("as double", (float) 101.1, j[L"0"].as<float> (), delta);
        ///
        ASSERT_THAT ( j[L"0"].as<float> (), FloatEq ((float) 101.1));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("as int", 10, j[L"1"].as<int> ());
        ///
        ASSERT_THAT (j[L"1"].as<int> (), Eq (10));

        ASSERT_THAT (copy[6].get (), Eq (100));
      }

      TEST_F (number_test, _to_string)
      {
        struct assert
        {
          double d;
          const wchar_t *s[3];
          const wchar_t *output[5];
          int assert_status;
        };

        std::vector<struct assert > test = {
          //{ 100, { L"200", L"200.5" }, { L"100", L"100.000000", L"200", L"200.500000" }, PASS }

          { 100.0, { L"200", L"200.0", L"200.500000" },
          { L"100", L"100", L"200", L"200", L"200.5" },
          PASS_T },

          { 0.0, { L"0", L"0", L"0.500001" },
          { L"0", L"0", L"0", L"0", L"0.500001" },
          PASS_T }

        };

        TEST_IT_START

          mock_number n[5] = {
            mock_number ((long long) (*it).d),
            mock_number ((long double) (*it).d),
            mock_number ((*it).s[0]),
            mock_number ((*it).s[1]),
            mock_number ((*it).s[2]),
          };

        if (! MEM_DEBUG)
          {
            // Original assertion:
            ///CPPUNIT_ASSERT_MESSAGE ("n[0]._to_string ()", wcscmp ((*it).output[0], n[0]._to_string ()) == 0);
            ///
            ASSERT_THAT (n[0]._to_string (), StrEq ((*it).output[0]))
                << ERR_IDX_MSG << _idx[0];

            // Original assertion:
            ///CPPUNIT_ASSERT_MESSAGE ("n[1]._to_string ()", wcscmp ((*it).output[1], n[1]._to_string ()) == 0);
            ///
            ASSERT_THAT (n[1]._to_string (), StrEq ((*it).output[1]))
                << ERR_IDX_MSG << _idx[0];

            // Original assertion:
            ///CPPUNIT_ASSERT_MESSAGE ("n[2]._to_string ()", wcscmp ((*it).output[2], n[2]._to_string ()) == 0);
            ///
            ASSERT_THAT (n[2]._to_string (), StrEq ((*it).output[2]))
                << ERR_IDX_MSG << _idx[0];

            // Original assertion:
            ///CPPUNIT_ASSERT_MESSAGE ("n[3]._to_string ()", wcscmp ((*it).output[3], n[3]._to_string ()) == 0);
            ASSERT_THAT (n[3]._to_string (), StrEq ((*it).output[3]))
                << ERR_IDX_MSG << _idx[0];

            // Original assertion:
            ///CPPUNIT_ASSERT_MESSAGE ("n[4]._to_string ()", wcscmp ((*it).output[4], n[4]._to_string ()) == 0); // FIXME
            ///
            ASSERT_THAT (n[4]._to_string (), StrEq ((*it).output[4]))
                << ERR_IDX_MSG << _idx[0];
          }
        else
          std::cerr << "\n\nWARNING: "<< __FILE__ << ": " << __LINE__ << ": *** MEM_DEBUG IS ON!!! ***\n" << std::endl;

        TEST_IT_END
      }

      TEST_F (number_test, _parse)
      {
        struct assert
        {
          const wchar_t *starp;
          size_t move;
          double dval;
          int assert_status;
        };

        std::vector<struct assert > test = {
            { L"0", 1, 0, PASS_T },
            { L"0 ", 1, 0, PASS_T },
            { L"1 ", 1, 1, PASS_T },
            { L"10 ", 2, 10, PASS_T },
            { L"00", 1, 0, PASS_T },
            { L"05", 1, 0, PASS_T },
            { L"-2]", 2, -2, PASS_T },
            { L"-10]", 3, -10, PASS_T },
            { L"3.3 }", 3, (double) 3.3, PASS_T },
            { L"0.4, ", 3, (double) 0.4, PASS_T },
            { L"-0.5 ,", 4, (double) -0.5, PASS_T },
            { L"6e2", 3, 600, PASS_T },
            { L"7E2}", 3, 700, PASS_T },
            { L"8E+2 ] ", 4, 800, PASS_T },
            { L"1.79769e+308", 12, 1.79769e+308, PASS_T },
            { L"9E-2, ", 4, (double) 0.09, PASS_T },

            { L"x", 1, 0, FAIL_T },   // NaN
            //{ L"00", 1, 0, FAIL },
            //{ L"05", 2, 0, FAIL },
            { L"+5", 2, 0, FAIL_T },  // Positive sign is not allowed
            { L"2e", 2, 0, FAIL_T },  // Multiplier of ten is not specified
            { L"2eX", 2, 0, FAIL_T }, // Multiplier of ten is NaN
        };

        // SEE: https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
        //double delta = std::numeric_limits<double>::epsilon ();

        for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++)
          {
            mock_number n;
            try
              {
                if ((*it).assert_status == SKIP_T) { continue; }
                if ((*it).assert_status > PASS_T) { this->_errorc[EXPECTED]++; }
                const wchar_t *startp = (*it).starp;
                const wchar_t *readp = n._parse (startp);

                // Original assertion:
                ///ASSERT_EQUAL_IDX ("n._readp", startp + (*it).move, readp);
                ///
                ASSERT_THAT (readp, Eq (startp + (*it).move))
                    << ERR_IDX_MSG << _idx[0];
                // ASSERT_EQUAL_IDX ("number.value ()", (*it).dval, (double) n.get ());

                // Original assertion:
                ///CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE ("number.value ()", (*it).dval, (double) n.get (), delta);
                ///
                ASSERT_THAT ((double) n.get (), DoubleEq ((*it).dval))
                    << ERR_IDX_MSG << _idx[0];
                // std::cerr << n.get () << std::endl;

                n._value.long_double = 0;

                n._digitp[DOUBLE][START]  = nullptr;
                n._digitp[DOUBLE][END]    = nullptr;
                n._digitp[EXP][START]     = nullptr;
                n._digitp[EXP][END]       = nullptr;

              } catch (json_syntax_error &e) {
                this->_errorc[ACTUAL]++;
                std::cerr << e.what () << std::endl;
              }
           }
        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
        ///
        ASSERT_THAT (this->_errorc[ACTUAL], Eq (this->_errorc[EXPECTED]));
      }

      TEST_F (number_test, _digits)
      {
        struct assert
        {
          const wchar_t *starp;
          size_t move;
          int peek;
          int assert_status;
        };

        std::vector<struct assert > test = {
            { L"123", 3, 0, PASS_T },
            { L"123x", 3, L'x', PASS_T },
            { L"0.", 1, L'.', PASS_T },
            { L"123 ", 3, L' ', PASS_T },

            { L"", 0, -1, PASS_T },
            { L"x", 0, -1, PASS_T },
        };

        TEST_IT_START

            mock_number n;
            const wchar_t *startp = (*it).starp;

            n._readp = startp;
            // n._endp = startp + strlen (startp);

            int peek  = n._digits ();

            // Original assertion:
            ///ASSERT_EQUAL_IDX ("readp", startp + (*it).move, n._readp);
            ///
            ASSERT_THAT (n._readp, startp + (*it).move)
                << ERR_IDX_MSG << _idx[0];

            // Original assertion:
            ///ASSERT_EQUAL_IDX ("peek", (*it).peek, peek);
            ///
            ASSERT_THAT (peek, (*it).peek)
                << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (number_test, _frag)
      {
        struct assert
        {
          const wchar_t *starp;
          size_t move;
          int peek;
          int assert_status;
        };

        std::vector<struct assert > test = {

            { L"5.123 ", 5, L' ', PASS_T },
            { L"5.123}", 5, L'}', PASS_T },
            // { "5.123e", 5, 'e', PASS },
            // { "5.123E", 5, 'E', PASS },

            { L"5.", 2, 0, FAIL_T },
            { L"5.E", 2, L'E', FAIL_T },
        };


        for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++)
          {
            mock_number n;
            try
              {
                if ((*it).assert_status == SKIP_T) { continue; }
                if ((*it).assert_status > PASS_T) { this->_errorc[EXPECTED]++; }
                const wchar_t *startp = (*it).starp;
                const wchar_t *endp = startp + (*it).move;

                n._readp = startp + 1;

                n._frag ();

                // Original assertion:
                ///ASSERT_EQUAL_IDX ("readp", endp, n._readp);
                ///
                ASSERT_THAT (n._readp, Eq (endp))
                    << ERR_IDX_MSG << _idx[0];

                // Original assertion:
                ///ASSERT_EQUAL_IDX ("peek", (*it).peek, (int)*(n._readp));
                ///
                ASSERT_THAT ((int)*(n._readp), Eq ((*it).peek))
                    << ERR_IDX_MSG << _idx[0];

                // Original assertion:
                ///ASSERT_EQUAL_IDX ("digitp[0][1]", endp, n._digitp[0][1]);
                ///
                ASSERT_THAT (n._digitp[0][1], Eq (endp))
                    << ERR_IDX_MSG << _idx[0];
              }
            catch (json_syntax_error &e)
              {
                this->_errorc[ACTUAL]++;
                std::cerr << e.what () << std::endl;
              }
            }
        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
        ///
        ASSERT_THAT (this->_errorc[ACTUAL], this->_errorc[EXPECTED]);
      }

      TEST_F (number_test, _exp)
      {
        struct assert {
            const wchar_t *starp;
            size_t move[2];
            int peek;
            long long atoll;
            int assert_status;
        };

        std::vector<struct assert > test = {

            { L"2e2 ", { 2, 3 }, L' ', 2, PASS_T },
            { L"2E3}", { 2, 3 }, L'}', 3, PASS_T },
            { L"2e+4]", { 2, 4 }, L']', 4, PASS_T },
            { L"2e-5", { 2, 4 }, 0, -5, PASS_T },
            { L"2e-00005", { 2, 8 }, 0, -5, PASS_T },

            { L"2e", { 0, 0 }, 0, 0, FAIL_T },
            { L"2e ", { 0, 0 }, 0, 0, FAIL_T },
            { L"2e.", { 0, 0 }, 0, 0, FAIL_T },
            { L"2e+", { 0, 0 }, 0, 0, FAIL_T },
        };

        for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++)
          {
            mock_number n;
            try
              {
                if ((*it).assert_status == SKIP_T) { continue; }
                if ((*it).assert_status > PASS_T) { this->_errorc[EXPECTED]++; }
                const wchar_t *startp = (*it).starp;
                const wchar_t *endp = startp + (*it).move[1];

                n._readp = startp + 1;

                n._exp ();

                // Original assertion:
                ///ASSERT_EQUAL_IDX ("n._readp", endp, n._readp);
                ///
                ASSERT_THAT (n._readp, Eq (endp))
                    << ERR_IDX_MSG << _idx[0];

                // Original assertion:
                ///ASSERT_EQUAL_IDX ("*(n._readp)", (int) *endp, (*it).peek);
                ///
                ASSERT_THAT ((*it).peek, Eq ((int) *endp))
                    << ERR_IDX_MSG << _idx[0];

                // Original assertion:
                ///ASSERT_EQUAL_IDX ("n._digitp[1][0]", startp + (*it).move[0], n._digitp[1][0]);
                ///
                ASSERT_THAT (n._digitp[1][0], Eq (startp + (*it).move[0]))
                    << ERR_IDX_MSG << _idx[0];

                // Original assertion:
                ///ASSERT_EQUAL_IDX ("n._digitp[1][1]", startp + (*it).move[1], n._digitp[1][1]);
                ///
                ASSERT_THAT (n._digitp[1][1], Eq (startp + (*it).move[1]))
                    << ERR_IDX_MSG << _idx[0];

                std::string s (n._digitp[1][0], n._digitp[1][1]);

                // Original assertion:
                ///ASSERT_EQUAL_IDX ("n._llexp", (*it).atoll, atoll (s.c_str ()));
                ///
                ASSERT_THAT (atoll (s.c_str ()), Eq ((*it).atoll))
                    << ERR_IDX_MSG << _idx[0];
              }
            catch (json_syntax_error &e)
              {
                 this->_errorc[ACTUAL]++;
                 std::cerr << e.what () << std::endl;
              }
          }
        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
        ///
        ASSERT_THAT (this->_errorc[ACTUAL], this->_errorc[EXPECTED]);
      }

      TEST_F (number_test, _atof)
      {
        mock_number n;

        struct assert {
            const wchar_t *starp;
            double dval;
            int assert_status;
        };

        std::vector<struct assert > test = {
            { L"5.5", (long double) 5.5, PASS_T },
            { L"55.55", (long double) 55.55, PASS_T },
        };

        TEST_IT_START

          const wchar_t *digitp[] = { (*it).starp, (*it).starp + wcslen ((*it).starp) };
          double d = n._atof (digitp);

          // Original assertion:
          ///ASSERT_EQUAL_IDX ("n._atof ()", (*it).dval, d);
          ///
          ASSERT_THAT (d, DoubleEq ((*it).dval))
              << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (number_test, _atoll)
      {
        mock_number n;

        struct assert {
            const wchar_t *starp;
            long long llval;
            int assert_status;
        };

        std::vector<struct assert > test = {
            { L"55", 55, PASS_T },
            { L"5555", 5555, PASS_T },
        };

        TEST_IT_START

          const wchar_t *digitp[] = { (*it).starp, (*it).starp + wcslen ((*it).starp) };

          long long ll = n._atoll (digitp);

          // Original assertion:
          ///ASSERT_EQUAL_IDX ("n._atoll ()", (*it).llval, ll);
          ///
          ASSERT_THAT (ll, Eq ((*it).llval))
              << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (number_test, _calculate)
      {
        mock_number n;

        struct assert {
            const wchar_t *starp[2];
            size_t move[2];
            double dval;
            int assert_status;
        };

        std::vector<struct assert > test = {
          { { nullptr, nullptr }, { 0, 0 }, 0, PASS_T },
          { { L"", L"" }, { 0, 0 }, 0, PASS_T },
          { { L"5", L"" }, { 1, 1 }, 5, PASS_T },
          { { L"5", L"0" }, { 1, 1 }, 5, PASS_T },
          { { L"2", L"1" }, { 1, 1 }, 20, PASS_T },
          { { L"2", L"2" }, { 1, 1 }, 200, PASS_T },
          { { L"2", L"-2" }, { 1, 2 }, (long double) 0.02, PASS_T },
        };

        TEST_IT_START

          const wchar_t *digitp[2][2] = {
            { (*it).starp[0], (*it).starp[0] + (*it).move[0] },
            { (*it).starp[1], (*it).starp[1] + (*it).move[1] }
          };

          long double d = n._calculate (digitp);
          // std::cerr << d << " " << *(n._double_valuep) << std::endl;

          // Original assertion:
          ///ASSERT_EQUAL_IDX ("n._calculate ()", (*it).dval, (double) d);
          ///
          ASSERT_THAT ((double) d, DoubleEq ((*it).dval))
            << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (number_test, assign_all_values)
      {
        mock_object object_parent;

        json *parents[] = {
          & object_parent,
          nullptr
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

        mock_number n ((long long) 10);

        std::vector<struct assert > test = {
          /// Removed operator =(const number & n)
          //{ & n, value::number_t, L"0",  0, 1, { PASS, PASS } },
          //{ __VALUE[value::boolean_t], value::boolean_t, L"1",  0, 2, { PASS, FAIL } },
        };

        mock_number *old_value = nullptr;

        for (size_t pidx = 0; pidx < 2; pidx++)
          {
            this->_idx[0] = 0;
            for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++)
              {
                try
                  {
                      if ((*it).assert_status[pidx] == SKIP_T) { continue; }\
                      if ((*it).assert_status[pidx] > PASS_T) { this->_errorc[EXPECTED]++; }

                      /** old_value: value from value[key] */
                      old_value = new mock_number (parents[pidx]);
                      //old_value->_double_valuep = nullptr;

                      old_value->_set_key ((*it).key, wcslen ((*it).key));

                      if ((*it).new_value->type () == value::number_t)
                        //*old_value = *(dynamic_cast<mock_number *>((*it).new_value));
                          old_value = dynamic_cast<mock_number *>((*it).new_value);
                      else
                        *(dynamic_cast<value *>(old_value)) = *(*it).new_value;

                      json *parent = parents[pidx];

                      if (parent)
                        {
                          // Original assertion:
                          ///ASSERT_EQUAL_IDX ("parent->count ()", (*it).count, parent->size ());
                          ///
                          ASSERT_THAT (parent->size (), Eq ((*it).count));

                          // Original assertion:
                          ///ASSERT_EQUAL_IDX ("(*parent)[(*it).key].type ()", (*parent)[(*it).key].type (), (*it).type);
                          ///
                          ASSERT_THAT ((*parent)[(*it).key].type (), Eq ((*it).type))
                              << ERR_IDX_MSG << _idx[0];
                        }
                      else if ((*it).new_value->type () == value::number_t)
                        {
                          // Original assertion:
                          ///ASSERT_EQUAL_IDX ("old_value->get ()", (long double) 10, old_value->get ());
                          ///
                          ASSERT_THAT ((double) old_value->get (), DoubleEq ((double) 10))
                              << ERR_IDX_MSG << _idx[0]; // Second fix

                          delete old_value;
                        }
                    }
                  catch (format::json::json_error & e)
                    {
                      this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl;
                      delete old_value;
                    }
              }
            // Original assertion:
            ///CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
            ///
            ASSERT_THAT (this->_errorc[ACTUAL], this->_errorc[EXPECTED]);
          }
      }

      TEST_F (number_test, _clone_const_value_ref)
      {
        mock_number src[] = {
          mock_number ((float) 100.1),
          mock_number (L"100.1")
        };

        mock_number copy[] = {
            mock_number (src[0]),  // calls _clone (const value &)
            mock_number (src[1])   // calls _clone (const value &)
        };

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy[0].get ()", (float) 100.1, (float) copy[0].get ()); // _double_value && _double_valuep are set
        ///
        ASSERT_THAT ((float) copy[0].get (), FloatEq ((float) 100.1));

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("copy[]._is_double", copy[0]._is_floating_point == true && copy[0]._is_floating_point == copy[1]._is_floating_point);
        ///
        // FIXME: ASSERT_THAT (copy[0]._is_floating_point, IsTrue ()); // :-1: error: Undefined symbols for architecture x86_64:
        EXPECT_TRUE (copy[0]._is_floating_point);
        ASSERT_THAT (copy[0]._is_floating_point, Eq (copy[1]._is_floating_point));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("(long) copy[1].get ()", (float) 100.1, (float) copy[1].get ());
        ///
        ASSERT_THAT ((float) copy[1].get (), FloatEq ((float) 100.1));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("src[1]._double_value", (float) 100.1, (float) src[1]._value.long_double);  // _parse () called but not _calculate ()
        ///
        ASSERT_THAT ((float) src[1]._value.long_double, FloatEq ((float) 100.1));

        const wchar_t *str_value = copy[1].stringify ();

        if (! MEM_DEBUG)
          {
            // Original assertion:
            ///CPPUNIT_ASSERT_MESSAGE ("value[key]::get ()", str_value == std::wstring (L"100.1"));
            ///
            ASSERT_THAT (str_value, StrEq (L"100.1"));
          }
        else
          std::cerr << "\n\nWARNING: "<< __FILE__ << ": " << __LINE__ << ": *** MEM_DEBUG IS ON!!! ***\n" << std::endl;

        delete [] str_value;

        // Copies
        json j = new object { { L"0", new number (src[0]) },
                              { L"1", new number (src[1]) } };

        // SEE: https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
        //float delta = std::numeric_limits<float>::epsilon ();

        // Original assertion:
        ///CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE ("as double", (float) 100.1, j[L"0"].as<float> (), delta);
        ///
        ASSERT_THAT (j[L"0"].as<float> (), FloatEq ((float) 100.1));

        // Original assertion:
        ///CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE ("as double", (float) 100.1, j[L"1"].as<float> (), delta);
        ///
        ASSERT_THAT (j[L"1"].as<float> (), FloatEq ((float) 100.1));
      }

      TEST_F (number_test, _str_length)
      {
        struct assert
        {
          mock_number *n;
          size_t len;
          int assert_status;
        };

        std::vector<struct assert > test = {
          { new mock_number (static_cast<long double>(100)), 3, PASS_T },
          { new mock_number (static_cast<long double>(100.1)), 5 /* + 14 */, PASS_T },     // value in Intel  machine: 100.099999999999994
          { new mock_number (static_cast<long double>(100.099999999999994)), 5 /* + 14 */, PASS_T }, // value in ARM machine: 100.1
          { new mock_number (static_cast<long double>(-10.01)), 6 /* + 14 */, PASS_T },    // value in Intel  machine: -10.0099999999999998

          { new mock_number (L"100"), 3, PASS_T },
          { new mock_number (L"100.1"), 5, PASS_T },
          { new mock_number (L"100.10"), 5, PASS_T },
          { new mock_number (L"100.099999999999994"), 5 /* + 14 */, PASS_T }, // value in ARM machine: 100.1
          { new mock_number (L"-10.01"), 6, PASS_T }
        };

        TEST_IT_START

            if (! MEM_DEBUG)
              {
                // Original assertion:
                ///ASSERT_EQUAL_IDX ("number::str_length ()", (*it).len, (*it).n->_str_length ());
                ///
                ASSERT_THAT ((*it).n->_str_length (), Ge ((*it).len))
                    << ERR_IDX_MSG << _idx[0];
              }
            else
              std::cerr << "\n\nWARNING: "<< __FILE__ << ": " << __LINE__ << ": *** MEM_DEBUG IS ON!!! ***\n" << std::endl;

            delete (*it).n;

        TEST_IT_END
      }

      TEST_F (number_test, _clear)
      {
        mock_number ((long long) 100)._clear ();
      }

      TEST_F (number_test, type)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("value::type ()", value::number_t, number ().type ());
        ///
        ASSERT_THAT (number ().type (), Eq (value::number_t));
      }

      TEST_F (number_test, __integral_length)
      {
        struct assert
        {
          int num;
          size_t len;
          int assert_status;
        };

        std::vector<struct assert > test = {
          { 0, 1, PASS_T },
          { 1, 1, PASS_T },
          { 10, 2, PASS_T },
          { 123, 3, PASS_T },
          { 1000, 4, PASS_T },
          { -1, 2, PASS_T },
          { -10, 3, PASS_T },
          //{ -1000, 5, PASS },
        };

        TEST_IT_START

            size_t len = mock_number::__integral_length ((*it).num);

            // Original assertion:
            ///ASSERT_EQUAL_IDX ("integral length", (*it).len, len);
            ///
            ASSERT_THAT (len, Eq ((*it).len))
                << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (number_test, __to_string_ll)
      {
        struct assert
        {
          long long num;
          size_t len;
          const wchar_t * str;
          int assert_status;
        };

        std::vector<struct assert > test = {
          { 0, 1, L"0", PASS_T },
          { 1, 1, L"1", PASS_T },
          { 10, 2, L"10", PASS_T },
          { 123, 3, L"123", PASS_T },
          { 1000, 4, L"1000", PASS_T },
          { -1, 2, L"-1", PASS_T },
          { -10, 3, L"-10", PASS_T },
          { LLONG_MAX, 19, L"9223372036854775807", PASS_T } // NOTE: LLONG_MAX depends on platform
        };

        TEST_IT_START

            mock_number n;
            size_t len = n.__to_string_ll ((*it).num);
            const wchar_t *str = n._to_string ();
            long long ll = std::stoll (str);

            if ((*it).num < LLONG_MAX)
              {
                // Original assertion:
                ///ASSERT_EQUAL_IDX ("string length", (*it).len, len);
                ///
                ASSERT_THAT (len, (*it).len)
                    << ERR_IDX_MSG << _idx[0];

                // Original assertion:
                ///CPPUNIT_ASSERT_MESSAGE ("string equal", wcscmp ((*it).str, str) == 0);
                ///
                ASSERT_THAT (str, StrEq ((*it).str))
                    << ERR_IDX_MSG << _idx[0];
              }

            // Original assertion:
            ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("long long value", (*it).num, ll);
            ///
            ASSERT_THAT (ll, Eq ((*it).num))
                << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (number_test, __to_string_ld)
      {
        struct assert
        {
          long double num;
          int assert_status;
        };

        std::vector<struct assert > test = {
          { (long double) 0.0, /* 1, L"0" */ PASS_T },
          { (long double) 1.0, PASS_T },
          { (long double) 1.01, PASS_T },
          { (long double) -1.0, PASS_T },
          { (long double) 1.0000001, PASS_T },
          { (long double) DBL_MAX, PASS_T },
          //{ (long double) LDBL_MAX, PASS },       // stold: out of range
          //{ (long double) LDBL_MAX * -1, PASS },  // stold: out of range
          { (long double) ULLONG_MAX, PASS_T }
        };

        TEST_IT_START

            number n;

            (void) n.__to_string_ld ((*it).num);
            const wchar_t *str = n._to_string ();

            if (abs ((*it).num) < LDBL_MAX)
              {
                long double ld = std::stold (str);

                // Original assertion:
                ///CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE ("long double value", (*it).num, ld, delta);
                ///
                ASSERT_THAT (number_test::absoluteToleranceCompare (ld, (*it).num, 6), Eq (true))
                    << ERR_IDX_MSG << _idx[0];
              }
            else
              std::wcerr << "skipped test for " << str << " because of stold: out of range" << std::endl;

        TEST_IT_END
      }
    }
  } // Namespace json
} // Namespace format
#endif // json_number_test

