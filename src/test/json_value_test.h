#ifndef JSON_INTERFACE_TEST_H
#define JSON_INTERFACE_TEST_H

#include "json_value_test_interface.h"
#include "json_mock_value.h"

#include "unit_test.h"

namespace format
{
  namespace json
  {
    namespace test
    {
      class json_value_test : public unit_test {};

      TEST_F (json_value_test, assign_copy)
      {
        json j[] = {
          L"{}",
          L"[]"
        };

        struct assert
        {
          value *val;
          value::value_t type;  // old, current
          int assert_status;
        };

        std::vector<struct assert> test = {
          { __VALUE[value::undefined_t], value::undefined_t, PASS_T },
          { __VALUE[value::object_t], value::object_t, PASS_T },
          { __VALUE[value::array_t], value::array_t, PASS_T },
          { __VALUE[value::string_t], value::string_t, PASS_T },
          { __VALUE[value::number_t], value::number_t, PASS_T },
          { __VALUE[value::boolean_t], value::boolean_t, PASS_T },
          { __VALUE[value::null_t], value::null_t, PASS_T }
        };

        for (size_t hdx = 0; hdx < 2; hdx++)
          {
            _idx[0] = 0;

            TEST_IT_START

                for (size_t jdx = 0; jdx < 2; jdx++)
                  {
                    j[hdx][L"0"] = *(*it).val;   // Undefined <-- Object, Object <-- Array, ...

                    // Original assertion:
                    //ASSERT_EQUAL_IDX ("value::type ()",
                      //                (*it).type,
                      //                j[hdx][L"0"].type ());

                    ASSERT_THAT (j[hdx][L"0"].type (), Eq ((*it).type))
                        << ERR_IDX_MSG << _idx[0];
                  }
            TEST_IT_END
          }
      }

      TEST_F (json_value_test, operator_assign_undefined)
      {
        boolean b;

        array a = { new boolean () }; //L"[true]";

        struct assert
        {
          value *val;
          size_t size;    // Array::_element_list.size ()
          int assert_status;
        };

        std::vector<struct assert> test = {
          { & b, 1, PASS_T }, // No parent
          { & (a[(size_t) 0]), 0, PASS_T }  // Has parent
        };

        TEST_IT_START
            *(*it).val = format::json::undefined ();

            // Original assertion:
            //ASSERT_EQUAL_IDX ("array::count ()",
              //                (*it).size,
              //                a.size ());

            ASSERT_THAT ((*it).size, Eq (a.size ()))
                << ERR_IDX_MSG << _idx[0];

        TEST_IT_END

        json j = new object {
                  { L"Image",
                    new object {
                      { L"Width", new number ((long long) 800) },
                      { L"Height", new number ((long long) 600) },
                      { L"Title", new string (L"View from 15th Floor") },
                      { L"Thumbnail", new object {
                          { L"Url", new string (L"http://www.example.com/image/481989943") },
                          { L"Height", new number ((long long) 125) },
                          { L"Width", new number ((long long) 100) },
                        }
                      },
                      { L"Animated", new boolean (false) },
                      { L"IDs", new array { new number ((long long) 116), new number ((long long) 943), new number ((long long) 234), new number ((long long) 38793) } }
                    }
                  }
                };

//        j[L"Image"][L"Thumbnail"][L"Url"] = undefined ();
//        j[L"Image"][L"Thumbnail"][L"Height"] = undefined ();
//        j[L"Image"][L"Thumbnail"][L"Width"] = undefined ();
//        j[L"Image"][L"Thumbnail"] = undefined ();

//        j[L"Image"][L"Width"] = undefined ();
//        j[L"Image"][L"Height"] = undefined ();
//        j[L"Image"][L"Title"] = undefined ();

//        j[L"Image"][L"Animated"] = undefined ();
//        j[L"Image"][L"IDs"][(size_t) 3] = undefined ();
//        j[L"Image"][L"IDs"] = undefined ();

//        CPPUNIT_ASSERT_EQUAL_MESSAGE ("j[L\"Image\"].count ()", // PASS
//                                      (size_t) 0,
//                                      j[L"Image"].count ());
      }

      TEST_F (json_value_test, _lookahead)
      {
        struct assert {
            const wchar_t *startp;
            wchar_t readp;
            int assert_status;
        };

        std::vector<struct assert > test = {
            { L"", 0, PASS_T},
            { L"   ", 0, PASS_T },
            { L"x", 'x', PASS_T },
            { L" \
                a", 'a', PASS_T },
            { L"   \"b", '"', PASS_T },
            { L"   \n\r\tc ", 'c', PASS_T },
            { L"   5", '5', PASS_T }
        };

        TEST_IT_START

          const wchar_t *startp = (*it).startp;

          format::json::json_mock_value m;

          m._readp = startp;

          m._look_ahead ();

          // Original assertion:
          // ASSERT_EQUAL_IDX ("value.readp", (*it).readp , *(m->_readp));

          ASSERT_THAT (*(m._readp), Eq ((*it).readp))
              << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (json_value_test, _string)
      {
        wchar_t endc;

        struct assert {
            const wchar_t *startp;
            long charc;
            wchar_t endc;
            int assert_status;
        };

        std::vector<struct assert > test = {
            { L" ", 0, 0, PASS_T },
            { L"\"x\"", 1 + 2, 0, PASS_T },
            { L"\" x\"", 2 + 2, 0, PASS_T },
            { L"\"", -1, 0, PASS_T },
            { L"\" xx", -4, 0, PASS_T },

            // Inner quotes
            { L"\"x\"\"", 1 + 3, 0, PASS_T },
            { L"\"x\"\"     ", 1 + 3, 0, PASS_T },
            { L"\"x\"\"\"", 1 + 4, 0, PASS_T },
            { L"\"x\"\"y\"", 2 + 4, 0, PASS_T },

            // Read until structural character
            // String is read until :,}] right after \" or after \"whitespace
            // Length of string is the last \" before the structural character
            { L"\"x\"\"     , ", 1 + 3, ',', PASS_T },
            { L"\"x\"\"\"     : ", 1 + 4, ':', PASS_T },
            { L"\"x\"\"y\"     } ", 2 + 4, '}', PASS_T },
            { L"\"x\"\"y\"     ] ", 2 + 4, ']', PASS_T },

            { L"\"x:\",\"     : ", 2 + 2, ',', PASS_T },      // , right after \"
            { L"\"x,\"\":\"     , ", 2 + 3, ':', PASS_T },    // : right after \"
            { L"\"x]\"\" } \"     ] ", 2 + 3, '}', PASS_T },  // } after \"1 x whitespace
            { L"\"x}\"\"] \"     } ", 2 + 3, ']', PASS_T },   // ] rigth after \"
            { L"\"x}\"\"x] \"     } ", 6 + 3, '}', PASS_T },  // } after \"5 x whitespace

            // No clean whitespace between \" and structural character
            { L"\"x\"\"x  :\"     , ", 5 + 4, ',', PASS_T },
            { L"\"x\"\" x :\"     , ", 5 + 4, ',', PASS_T },
            { L"\"x\"\"  x:\"     , ", 5 + 4, ',', PASS_T },

            // json_pointer test failure
            { L"\"k\"l\": 6", 2 + 3, ':', PASS_T },

            // Unescaped control characters --> error
            { L"\"\u0000\"", -1, '\u0000', PASS_T },
            { L"\"\u001F\"", -1, '\u001F', PASS_T },
            { L"\"xx\u001F\"", -3, '\u001F', PASS_T },

            // Escaped control characters
            { L"\"\\u0000\"", 8, 0, PASS_T },
            { L"\"\\u001F\"", 8, 0, PASS_T },
            { L"\"xx\\u001F\"", 10, 0, PASS_T },
        };

        TEST_IT_START

            const wchar_t *startp = (*it).startp;
            long charc = static_cast<long> (wcslen (startp));

            json_mock_value m;

            m._readp = startp;

            m._look_ahead ();

            charc = m._string (endc);

            // Original assertion:
            //ASSERT_EQUAL_IDX ("charc", (*it).charc , charc);
            //ASSERT_EQUAL_IDX ("endc", (*it).endc , endc);

            ASSERT_THAT (charc, Eq ((*it).charc))
                << ERR_IDX_MSG << _idx[0];

            ASSERT_THAT (endc, Eq ((*it).endc))
                << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (json_value_test, _is_literal)
      {
        struct assert {
            const wchar_t *startp;
            value::_literal value_type;
            int assert_status;
        };

        std::vector<struct assert> test = {
          { L"", value::_literal::no_literal, PASS_T },
          { L"   ", value::_literal::no_literal, PASS_T },
          { L"xxx   ", value::_literal::no_literal, PASS_T },
          { L"xxxxxx   ", value::_literal::no_literal, PASS_T },
          { L"true    ", value::_literal::true_value, PASS_T },
          { L"false    ", value::_literal::false_value, PASS_T },
          { L"null   ", value::_literal::null_value, PASS_T }
        };

        TEST_IT_START

            const wchar_t *startp = (*it).startp;

            json_mock_value m;

            m._readp = startp;

            value::_literal ltr = m._is_literal ();

            // Original assertion:
            //ASSERT_EQUAL_IDX ("literal value", (*it).value_type , ltr);

            ASSERT_THAT (ltr, Eq ((*it).value_type))
                << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (json_value_test, _str_append)
      {
        wchar_t *dst = new wchar_t[8 + 1]();
        wchar_t *startp = dst;

        struct assert {
            const wchar_t *src;
            size_t charc[2];
            int assert_status;
        };

        std::vector<struct assert> test = {
          { L"",  { 0, 0 }, PASS_T },
          { L"a",  { 1, 1 }, PASS_T },
          { L"bb",  { 2, 3 }, PASS_T },
          { L"\"ccc\"",  { 5, 8 }, PASS_T },
        };

        TEST_IT_START

            dst = value::_str_append (dst, (*it).src, (*it).charc[0]);

            // Original assertion:
            //ASSERT_EQUAL_IDX ("dst", startp + (*it).charc[1], dst);

            ASSERT_THAT (dst, Eq (startp + (*it).charc[1]))
                << ERR_IDX_MSG << _idx[0];

        TEST_IT_END

        //CPPUNIT_ASSERT_MESSAGE ("starp", wcscmp (L"abb\"ccc\"", startp) == 0);

        delete[] startp;
      }

      TEST_F (json_value_test, _quote_value)
      {
        struct assert {
            value *v;
            const wchar_t *quoted_string;
            int assert_status;
        };

        std::vector<struct assert> test = {
          { new object (L"{}"), L"{}", PASS_T },
          { new array (L"[]"), L"[]", PASS_T },
          { new number ((long long) 100), L"100", PASS_T },
          { new string (), L"\"\"" , PASS_T },
          { new string (L""), L"\"\"" , PASS_T },
          { new string (L" "), L"\" \"", PASS_T },
          { new string (L"a"), L"\"a\"", PASS_T },
          { new boolean (true), L"true", PASS_T },
          { new null (), L"null", PASS_T },
          { new undefined (), L"", PASS_T },
        };

        TEST_IT_START

            wchar_t *dst = new wchar_t[64 + 1] ();
            wchar_t *const startp = dst;

            value *v = (*it).v;

            //const wchar_t *str = v->_to_string ();
            //size_t len = v->_str_length ();

            value::_quote_value (dst, v);

            // Original assertion:
            //ASSERT_EQUAL_IDX ("startp", 0, wcscmp ((*it).quoted_string, startp));

            ASSERT_THAT (startp, StrEq ((*it).quoted_string))
                << ERR_IDX_MSG << _idx[0];

            delete[] startp;
            delete v;

        TEST_IT_END
      }

      TEST_F (json_value_test, operator_equal_value_t)
      { }

      TEST_F (json_value_test, operator_assign_double)
      { }

      TEST_F (json_value_test, operator_assign_bool)
      { }

      TEST_F (json_value_test, operator_assign_nullptr)
      { }

      TEST_F (json_value_test, assign_value_ptr)
      {
        json j[] = {
          L"{}",
          L"[]"
        };

        struct assert
        {
          value *val;
          value::value_t type;  // old, current
          int assert_status;
        };

        for (size_t hdx = 0; hdx < 2; hdx++)
          {
            std::vector<struct assert> test = {
              { new object (), value::object_t, PASS_T },
              { new array (), value::array_t, PASS_T },
              { new string (), value::string_t, PASS_T },
              { new number (), value::number_t, PASS_T },
              { new boolean (), value::boolean_t, PASS_T },
              { new null (), value::null_t, PASS_T },
              { new format::json::unique_undefined (), value::undefined_t, PASS_T }
            };

            _idx[0] = 0;

            TEST_IT_START
                j[hdx][L"0"] = (*it).val;   // Undefined <-- Object, Object <-- Array, ...

                // Original assertion:
                //ASSERT_EQUAL_IDX ("value::type ()",
                  //                (*it).type,
                  //                j[hdx][L"0"].type ());

                ASSERT_THAT (j[hdx][L"0"].type (), Eq ((*it).type))
                    << ERR_IDX_MSG << _idx[0];

            TEST_IT_END
          }
      }

      TEST_F (json_value_test, _assign_value_ptr_value_ptr)
      { }

      TEST_F (json_value_test, _clone_const_value_ref)
      { }

      TEST_F (json_value_test, operator_assign_long)
      { }

      TEST_F (json_value_test, as_is_not_pointer)
      {
        struct assert
        {
          const wchar_t *json_text;
          double      dval;
          long        lval;
          bool        bval;
          const wchar_t *cval;
          int assert_status;
        };

        std::vector<struct assert > test = {
          { L"{ \"a\" : 101.1 }", 101.1, 101, true, L"", PASS_T },
          { L"{ \"a\" : 101 }", 101.0, 101, true, L"", PASS_T },
          { L"{ \"a\" : 1 }", 1.0, 1, true, L"", PASS_T },
          { L"{ \"a\" : 0 }", 0.0, 0, false, L"", PASS_T },
          { L"{ \"a\" : true }", 1.0, 1, true, L"", PASS_T },
          { L"{ \"a\" : false }", 0.0, 0, false, L"", PASS_T },
          { L"{ \"a\" : \"char\" }", 1.0, 1, true, L"char", PASS_T }, // This works because string is first converted to boolean, then to numeric type
          { L"{ \"a\" : null }", 0.0, 0, false, L"", FAIL_T },
          { L"{ \"a\" : {} }", 0.0, 0, false, L"", FAIL_T },
          { L"{ \"notfound\" : {} }", 0.0, 0, false, L"", FAIL_T }
        };

        TEST_IT_START

          json j ((*it).json_text);
          value & v = j[L"a"];

          double d = v.as<double> ();
          long l = v.as<long> ();
          bool b = v.as<bool> ();

          // object o = v.as<object> (); //  ok, won't compile
          // object & ro = v.as<object &> (); // ok, no matching call
          // object & rro = v.as<object &&> (); // ok, no matching call

          // Original assertion:
          // SEE: https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
          //CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE ("as double", (*it).dval, d, std::numeric_limits<double>::epsilon());
          //CPPUNIT_ASSERT_MESSAGE ("as long", l == (*it).lval);
          //CPPUNIT_ASSERT_MESSAGE ("as boolean", b == (*it).bval);

          ASSERT_THAT (d, DoubleEq ((*it).dval))
              << ERR_IDX_MSG << _idx[0];

          ASSERT_THAT (l, Eq ((*it).lval))
              << ERR_IDX_MSG << _idx[0];

          ASSERT_THAT (b, Eq ((*it).bval))
              << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (json_value_test, test_as_is_pointer)
      {
        struct assert
        {
          const wchar_t *json_text;
          double      dval;
          long        lval;
          bool        bval;
          const wchar_t *cval;
          int assert_status;
        };

        std::vector<struct assert > test = {
          { L"{ \"a\" : 101.1 }", 101.1, 101, true, L"", FAIL_T },
          { L"{ \"a\" : 101 }", 101.0, 101, true, L"", FAIL_T },
          { L"{ \"a\" : 1 }", 1.0, 1, true, L"", FAIL_T },
          { L"{ \"a\" : 0 }", 0.0, 0, false, L"", FAIL_T },
          { L"{ \"a\" : true }", 1.0, 1, true, L"", FAIL_T },
          { L"{ \"a\" : false }", 0.0, 0, false, L"", FAIL_T },
          { L"{ \"a\" : \"char\" }", 1.0, 1, true, L"char", PASS_T },
          { L"{ \"a\" : null }", 0.0, 0, false, L"", PASS_T },
          { L"{ \"a\" : {} }", 0.0, 0, false, L"", FAIL_T },
          { L"{ \"notfound\" : {} }", 0.0, 0, false, L"", FAIL_T }
        };

        TEST_IT_START

          json j ((*it).json_text);
          value & v = j[L"a"];

          const wchar_t * c = v.as<const wchar_t *> ();
          // object *op = v.as<object *> (); // ok, no matching call

          // Original assertion:
          //CPPUNIT_ASSERT_MESSAGE ("as wchar_t", wcscmp (c, (*it).cval) == 0);

          ASSERT_THAT (c, StrEq ((*it).cval))
              << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

    }

      /**
       * 0.
       * @brief suite
       * @return
       *
      static CppUnit::Test *
      suite ()
      {
        CppUnit::TestSuite *s = new CppUnit::TestSuite ("json value test");

        // 0.   s->addTest (new CppUnit::TestCaller<json_value_test> ("test_assign_copy", &json_value_test::test_assign_copy));
        // 1.   s->addTest (new CppUnit::TestCaller<json_value_test> ("test_assign_undefined", &json_value_test::test_operator_assign_undefined));
        // 2.   s->addTest (new CppUnit::TestCaller<json_value_test> ("test_lookahead", &json_value_test::test__lookahead));
        // 3.   s->addTest (new CppUnit::TestCaller<json_value_test> ("test_is_literal", &json_value_test::test__is_literal));
        // 4.   s->addTest (new CppUnit::TestCaller<json_value_test> ("test__string", &json_value_test::test__string));
        // 5.   s->addTest (new CppUnit::TestCaller<json_value_test> ("test__str_append", &json_value_test::test__str_append));
        // 6.   s->addTest (new CppUnit::TestCaller<json_value_test> ("test__quote_value", &json_value_test::test__quote_value));
        // 7.   s->addTest (new CppUnit::TestCaller<json_value_test> ("test_operator_equal_value_t", &json_value_test::test_operator_equal_value_t));

                  /// Removed bool operator ==(const value & v)
        // .   // s->addTest (new CppUnit::TestCaller<json_value_test> ("test_operator_equal_value", &json_value_test::test_operator_equal_value));
                  /// Removed operator =(const wchar_t *json_text);
        // .   // s->addTest (new CppUnit::TestCaller<json_value_test> ("test_operator_assign_wchar_t_ptr", &json_value_test::test_operator_assign_wchar_t_ptr));

        // 8.   s->addTest (new CppUnit::TestCaller<json_value_test> ("test_operator_assign_double", &json_value_test::test_operator_assign_double));
        // 9.   s->addTest (new CppUnit::TestCaller<json_value_test> ("test_operator_assign_bool", &json_value_test::test_operator_assign_bool));
        // 10.   s->addTest (new CppUnit::TestCaller<json_value_test> ("test_operator_assign_nullptr", &json_value_test::test_operator_assign_nullptr));
        // 11.   s->addTest (new CppUnit::TestCaller<json_value_test> ("test_assign_ptr", &json_value_test::test_assign_value_ptr));
        // 12.   s->addTest (new CppUnit::TestCaller<json_value_test> ("test__assign_value_ptr_value_ptr", &json_value_test::test__assign_value_ptr_value_ptr));
        // 13.   s->addTest (new CppUnit::TestCaller<json_value_test> ("test__clone_const_value_ref", &json_value_test::test__clone_const_value_ref));
        // 14.   s->addTest (new CppUnit::TestCaller<json_value_test> ("test_operator_assign_long", &json_value_test::test_operator_assign_long));
        // 15.   s->addTest (new CppUnit::TestCaller<json_value_test> ("test_as_is_not_pointer", &json_value_test::test_as_is_not_pointer));
        // 16.   s->addTest (new CppUnit::TestCaller<json_value_test> ("test_as_is_pointer", &json_value_test::test_as_is_pointer));

        return s;
      }*/
  }
}
#endif // JSON_INTERFACE_TEST_H
