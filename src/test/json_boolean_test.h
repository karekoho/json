#ifndef JSON_BOOLEAN_TEST
#define JSON_BOOLEAN_TEST

#include "unit_test.h"
#include "json_mock_value.h"

namespace format
{
  namespace json
  {
    namespace test
    {
      //s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test_ctor_dtor", &json_boolean_test::test_ctor_dtor));
      //s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test_assign_all_values", &json_boolean_test::test_assign_all_values));
      //s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test__parse", &json_boolean_test::test__parse));
      //s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test_str_length", &json_boolean_test::test_str_length));
      //s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test__to_string", &json_boolean_test::test__to_string));
      //s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test__clear", &json_boolean_test::test__clear));
      //s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test_type", &json_boolean_test::test_type));
               /// Removed operator =(boolean & b), operator =(bool b)
      // //s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test__clone_const_value_ref", &json_boolean_test::test__clone_const_value_ref));
      // //s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test_operator_assign_bool", &json_boolean_test::test_operator_assign_bool));

      class boolean_test : public unit_test {};

      TEST_F (boolean_test, ctor_dtor)
      {
        json *parent = new json ();

        mock_boolean b[] = {
          mock_boolean (),
          mock_boolean (true),
          mock_boolean (parent, true)
        };

        // TODO: what is the correct place for these?
        json j = new object { { L"0", new mock_boolean () },
                              { L"1", new mock_boolean (true) },
                              { L"2", new mock_boolean (parent, true) },
                              { L"3", new mock_boolean (b[1]) }, // copy
                              { L"4", new mock_boolean (b[2]) }, // copy
                            };

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("as boolean", j[L"0"].as<bool> () == false);
        ///
        EXPECT_FALSE (j[L"0"].as<bool> ());

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("as boolean", j[L"1"].as<bool> () == true);
        ///
        EXPECT_TRUE (j[L"1"].as<bool> ());

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("as boolean", j[L"2"].as<bool> () == true);
        ///
        EXPECT_TRUE (j[L"2"].as<bool> ());

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("as boolean", j[L"3"].as<bool> () == true);
        ///
        EXPECT_TRUE (j[L"3"].as<bool> ());

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("as boolean", j[L"4"].as<bool> () == true);
        ///
        EXPECT_TRUE (j[L"4"].as<bool> ());

        delete parent;
      }

      TEST_F (boolean_test, assign_all_values)
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

        boolean b (true);

        std::vector<struct assert > test = {
          /// Removed operator =(boolean & b), operator =(bool b)
          //{ & b, value::boolean_t, L"0",  0, 1, { PASS, PASS } },
          //{ __VALUE[value::null_t], value::null_t, L"1",  0, 2, { PASS, FAIL } }
        };

        mock_boolean *old_value = nullptr;

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
                    old_value = new mock_boolean (parents[pidx], false);

                    old_value->_set_key ((*it).key, wcslen ((*it).key));

                    if ((*it).new_value->type () == value::boolean_t)
                      //*old_value = *(static_cast<mock_boolean *>((*it).new_value));
                      old_value = static_cast<mock_boolean *>((*it).new_value);
                    else
                      *(static_cast<value *>(old_value)) = *(*it).new_value;

                    json *parent = parents[pidx];

                    if (parent)
                      {
                        // Original assertion:
                        ///ASSERT_EQUAL_IDX ("parent->count ()", (*it).count, parent->size ());
                        ///
                        ASSERT_THAT (parent->size (), Eq ((*it).count))
                            << ERR_IDX_MSG << _idx[0];

                        // Original assertion:
                        ///ASSERT_EQUAL_IDX ("(*parent)[(*it).key].type ()", (*parent)[(*it).key].type (), (*it).type);
                        ///
                        ASSERT_THAT ((*parent)[(*it).key].type (), Eq ((*it).type))
                            << ERR_IDX_MSG << _idx[0];
                      }
                    else if ((*it).new_value->type () == value::boolean_t)
                      {
                        // Original assertion:
                        ///ASSERT_EQUAL_IDX ("old_value.value ()", (bool) true, old_value->get ());
                        ///
                        ASSERT_TRUE (old_value->get ())
                            << ERR_IDX_MSG << _idx[0];
                        delete old_value;
                      }
                   }
                 catch (format::json::json_error & e)
                  {
                    this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl;
                    delete old_value;
                  }
               }
              //(void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]);

              // Original assertion:
              ///CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
              ///
              ASSERT_THAT (this->_errorc[ACTUAL], Eq (this->_errorc[EXPECTED]));

            }
      }

      TEST_F (boolean_test, _parse)
      {
        struct assert
        {
          const wchar_t *input;
          bool value;
          size_t charc;
          int assert_status;
        };

        std::vector<struct assert > test = {
          { L"false ", false, 5, PASS_T },
          { L"true ", true, 4, PASS_T }
        };

        TEST_IT_START
            mock_boolean b ((*it).value);

            // Original assertion:
            ///ASSERT_EQUAL_IDX ("readp", (*it).input + (*it).charc, b._parse ((*it).input));
            ///
            ASSERT_THAT (b._parse ((*it).input), Eq ((*it).input + (*it).charc))
                << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (boolean_test, str_length)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("boolean::str_length ()", (size_t) 5, boolean (false)._str_length ());
        ///
        ASSERT_THAT (mock_boolean (false)._str_length (), Eq (5));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("boolean::str_length ()", (size_t) 4, boolean (true)._str_length ());
        ///
        ASSERT_THAT (mock_boolean (true)._str_length (), Eq (4));
      }

      TEST_F (boolean_test, _to_string)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("boolean::_to_string ()", boolean (false)._to_string () == std::wstring (L"false"));
        ///
        ASSERT_THAT (mock_boolean (false)._to_string (), StrEq (L"false"));

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("boolean::_to_string ()", boolean (true)._to_string () == std::wstring (L"true"));
        ///
        ASSERT_THAT (mock_boolean (true)._to_string (), StrEq (L"true"));
      }

      TEST_F (boolean_test, _clear)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_ASSERTION_PASS ("boolean::_clear is nop");
      }

      TEST_F (boolean_test, _type)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("value::type ()", value::boolean_t, boolean ().type ());
        ///
        ASSERT_THAT ( boolean ().type (), Eq (value::boolean_t));
      }
    }
  } // Namespace json
} // Namespace format
#endif // JSON_BOOLEAN_TEST

