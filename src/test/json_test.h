#ifndef JSON_TEST_H
#define JSON_TEST_H


#include "json_mock_value.h"
#include "unit_test.h"

namespace format
{
  namespace json
  {
    namespace test
    {
      // s->addTest (new CppUnit::TestCaller<json_test> ("test_ctor_dtor", &json_test::test_ctor_dtor));
      // s->addTest (new CppUnit::TestCaller<json_test> ("test__to_string", &json_test::test__to_string));
      // s->addTest (new CppUnit::TestCaller<json_test> ("test__parse", &json_test::test__parse));
      // s->addTest (new CppUnit::TestCaller<json_test> ("test_make_value", &json_test::test_make_value));
      // s->addTest (new CppUnit::TestCaller<json_test> ("test__assign_to_parent", &json_test::test__assign_to_parent));
      // s->addTest (new CppUnit::TestCaller<json_test> ("test_assign_all_values", &json_test::test_assign_all_values));
      // s->addTest (new CppUnit::TestCaller<json_test> ("test_parse_revive", &json_test::test_parse_revive));
      // s->addTest (new CppUnit::TestCaller<json_test> ("test_count", &json_test::test_count));
      // s->addTest (new CppUnit::TestCaller<json_test> ("test__assign_value_ptr_value_ptr", &json_test::test__assign_value_ptr_value_ptr));
      // s->addTest (new CppUnit::TestCaller<json_test> ("test__clone_const_value_ref", &json_test::test__clone_const_value_ref));
      // s->addTest (new CppUnit::TestCaller<json_test> ("test_operator_at_key", &json_test::test_operator_at_key));
      // s->addTest (new CppUnit::TestCaller<json_test> ("test_operator_at_index", &json_test::test_operator_at_index));
      // s->addTest (new CppUnit::TestCaller<json_test> ("test_str_length", &json_test::test_str_length));
      // s->addTest (new CppUnit::TestCaller<json_test> ("test__clear", &json_test::test__clear));
      // s->addTest (new CppUnit::TestCaller<json_test> ("test__erase", &json_test::test__erase));
      // s->addTest (new CppUnit::TestCaller<json_test> ("test_type", &json_test::test_type));
      // s->addTest (new CppUnit::TestCaller<json_test> ("test_operator_assign_object_ptr", &json_test::test_operator_assign_object_ptr));
      // s->addTest (new CppUnit::TestCaller<json_test> ("test_operator_assign_array_ptr", &json_test::test_operator_assign_array_ptr));

      class json_test : public unit_test {

      public:

        static value *
        fn_reviver (const wchar_t *, value *v)
        {
          switch (v->type ())
            {
              case  value::value_t::null_t:
                return new format::json::undefined ();

              case value::value_t::object_t:
              case value::value_t::array_t:
                return new null;

              default:
                return v;
            }
        }

        static void
        example_1 ()
        {
          json j = L"{\
            \"Image\": {\
                \"Width\":  800,\
                \"Height\": 600,\
                \"Title\":  \"View from 15th Floor\",\
                \"Thumbnail\": {\
                    \"Url\":    \"http://www.example.com/image/481989943\",\
                    \"Height\": 125,\
                    \"Width\":  100\
                },\
                \"Animated\" : false,\
                \"IDs\": [116, 943, 234, 38793]\
              }\
          }";

          std::wcout << j.get () << std::endl;
          std::wcout << j[L"Image"].get () << std::endl;
          std::wcout << j[L"Image"][L"Thumbnail"].get () << std::endl;
          std::wcout << j[L"Image"][L"Thumbnail"][L"Url"].get () << std::endl;
          std::wcout << j[L"Image"][L"Animated"].get () << std::endl;
          std::wcout << j[L"Image"][L"IDs"].get () << std::endl;

          object & o = static_cast<object &> (j[L"Image"]);

          for (auto it = o.begin (); it != o.end (); ++it)
            std::wcout << dynamic_cast<value &> (*(it)).get () << std::endl;
        }
      };

      TEST_F (json_test, ctor_dtor)
      {
        json parent;

        json j[] = {
          json (),
          json (L"{\"0\":0}"),
          json (parent),

          json (new object {}),
          json (new array {}),
        };

        // Copy
        json copy (j[1]);

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("value::type ()", value::boolean_t, (j[(size_t) 0][L"0"] = boolean ())[L"0"].type ());
        ///
        ASSERT_THAT ((j[(size_t) 0][L"0"] = boolean ())[L"0"].type (), Eq (value::boolean_t));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.count ()", static_cast<size_t> (1), copy.size ());
        ///
        ASSERT_THAT (copy.size (), Eq (static_cast<size_t> (1)));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("json::type () (1)", value::object_t, j[3].type ());
        ///
        ASSERT_THAT (j[3].type (), Eq (value::object_t));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("json::type () (2)", value::array_t, j[4].type ());
        ///
        ASSERT_THAT (j[4].type (), Eq (value::array_t));

  //      CPPUNIT_ASSERT_EQUAL_MESSAGE ("json::type () (3)",
  //                                    value::object_t,
  //                                    j[5].type ());

  //      CPPUNIT_ASSERT_EQUAL_MESSAGE ("json::type () (4)",
  //                                    value::array_t,
  //                                    j[6].type ());

        // Delete
        delete json::parse (L"{}");

        // Assing
        copy = L"[]";

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.type ()", value::array_t, copy.type ());
        ///
        ASSERT_THAT (copy.type (), Eq (value::array_t));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.length ()", static_cast<size_t> (0), copy.size ());
        ///
        ASSERT_THAT (copy.size (), Eq (0));
      }

      TEST_F (json_test, _parse)
      {
        struct assert
        {
          const wchar_t *starp;
          value::value_t type;
          int assert_status;
        };

        std::vector<struct assert > test = {
            { L" {} ", value::value_t::object_t, PASS_T },
            { L" [] ", value::value_t::array_t, PASS_T },
            { L" \"x\" ", value::value_t::string_t, PASS_T },
            { L" 100 ", value::value_t::number_t, PASS_T },
            { L" null ", value::value_t::null_t, PASS_T },
            { L" true ", value::value_t::boolean_t, PASS_T },
            { L" false ", value::value_t::boolean_t, PASS_T },

            { L"{\"k\":\"v\"} ", value::value_t::object_t, PASS_T },
            { L" { \"k\" : \"v\" } ", value::value_t::object_t, PASS_T },
            { L"[\"v\"] ", value::value_t::array_t, PASS_T },
            { L" [ \"v\", [\"vv\"] ] ", value::value_t::array_t, PASS_T },
            //{ L" [1,[2,3],4] ", value::value_t::array_t, PASS },

            /// errors
            { L" x ", value::value_t::undefined_t, FAIL_T },
            { L" {} , ", value::value_t::undefined_t, FAIL_T },
            { L", {} ", value::value_t::undefined_t, FAIL_T },
            { L" truee ", value::value_t::undefined_t, FAIL_T },
        };

        mock_json *j = nullptr;

        TEST_IT_START
              const wchar_t *startp = (*it).starp;
              size_t charc = wcslen (startp);

              j = new mock_json ();

              const wchar_t * readp = j->_parse (startp);

              // Original assertion:
              ///ASSERT_EQUAL_IDX ("json.readp", (*it).starp + (charc), readp);
              ///
              ASSERT_THAT (readp, Eq ((*it).starp + (charc)))
                  << ERR_IDX_MSG << _idx[0];

               // Original assertion:
              ///ASSERT_EQUAL_IDX ("*(json.readp)", static_cast<wchar_t> (0), *readp);
              ///
              ASSERT_THAT (*readp, Eq (static_cast<wchar_t> (0)))
                  << ERR_IDX_MSG << _idx[0];

               // Original assertion:
              ///ASSERT_EQUAL_IDX ("json.type ()", (*it).type, j->type ());
              ///
              ASSERT_THAT (j->type (), Eq ((*it).type))
                  << ERR_IDX_MSG << _idx[0];

              delete j;
            }
          catch (format::json::json_syntax_error & se)
            {
              this->_errorc[ACTUAL]++; std::cerr << se.what () << std::endl;
              delete j;
            } 
          // Original assertion:
          ///CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
          ///
          ASSERT_THAT (this->_errorc[ACTUAL], Eq (this->_errorc[EXPECTED]));
        }
      }

      TEST_F (json_test, _to_string)
      {
        struct assert
        {
          const wchar_t *input;
          const wchar_t *output[2];
          int assert_status;
        };

        std::vector<struct assert> test = {
          { L"{\"1\":{\"2\":{\"3\":\"three\"},\"4\":\"four\",\"5\":\"\"}}",
            { L"{\"1\":{\"2\":{\"3\":\"three\"},\"4\":\"four\",\"5\":\"\"}}",
              L"{\"3\":\"three\"}"  }, PASS_T },

          { L"[\"1\",[\"2\",[3],\"4\"]]",
            { L"[\"1\",[\"2\",[3],\"4\"]]",
              L"4" }, PASS_T },
        };

        TEST_IT_START

          mock_json j = (*it).input;

          size_t len[2] = {
            wcslen ((*it).output[0]),
            wcslen ((*it).output[1])
          };

          const wchar_t *value[2] = { j._to_string (),
                                      j[L"1"][L"2"].stringify ()
                                    };

          // Original assertion:
          ///ASSERT_EQUAL_IDX ("_to_string ()", len[0], wcslen (value[0]));
          ///
          ASSERT_THAT (wcslen (value[0]), Eq (len[0]))
              << ERR_IDX_MSG << _idx[0];

          // Original assertion:
          ///ASSERT_EQUAL_IDX ("stringify ()", len[1], wcslen (value[1]));
          ///
          ASSERT_THAT (wcslen (value[1]), Eq (len[1]))
              << ERR_IDX_MSG << _idx[0];

          delete [] value[0];
          delete [] value[1];

        TEST_IT_END
      }

      TEST_F (json_test, make_value)
      {
        mock_json j;

        struct assert
        {
            const wchar_t *starp;
            value::value_t type;
            size_t move;
            int assert_status;
        };

        std::vector<struct assert > test = {
            { L"{} ", value::value_t::object_t, 2, PASS_T },
            { L"[] ", value::value_t::array_t, 2, PASS_T },
            { L"\"x\" ", value::value_t::string_t, 3, PASS_T },
            { L"10 ", value::value_t::number_t, 2, PASS_T },
            { L"-10 ", value::value_t::number_t, 3, PASS_T },
            { L"true ", value::value_t::boolean_t, 4, PASS_T },
            { L"false ", value::value_t::boolean_t, 5, PASS_T },
            { L"null ", value::value_t::null_t, 4, PASS_T },
            { L"x ", value::value_t::no_value_t, 0, PASS_T },
            { L"", value::value_t::no_value_t, 0, PASS_T },
        };

        TEST_IT_START

            const wchar_t *startp = (*it).starp;

            j._readp = startp;

            value *v = j._make_value ();

            // Original assertion:
            ///ASSERT_EQUAL_IDX ("json._readp", startp + (*it).move , j._readp);
            ///
            ASSERT_THAT (j._readp, Eq (startp + (*it).move))
                << ERR_IDX_MSG << _idx[0];

            // Original assertion:
            ///ASSERT_EQUAL_IDX ("value.type ()", (*it).type , v->type ());
            ///
            ASSERT_THAT (v->type (), Eq ((*it).type))
                << ERR_IDX_MSG << _idx[0];

            if (v->type () != value::no_value_t)
              delete v;

        TEST_IT_END
      }

      TEST_F (json_test, _assign_to_parent)
      {
        mock_object object_parent;
        mock_array array_parent;

        struct assert
        {
            const wchar_t *key;
            size_t index;
            value *val[2];
            value::value_t type;
            int assert_status;
        };

        std::vector<struct assert > test = {
          { L"ok", 0, { new mock_object (& object_parent), new mock_object (& array_parent) }, value::object_t, PASS_T },
          { L"ak", 1, { new mock_array (& object_parent), new mock_array (& array_parent) }, value::array_t, PASS_T },
          { L"sk", 2, { new mock_string (& object_parent, 3), new mock_string (& array_parent, 3) }, value::string_t, PASS_T },
          { L"dk", 3, { new mock_number (& object_parent), new mock_number (& array_parent) }, value::number_t, PASS_T },
          { L"bk", 4, { new mock_boolean (& object_parent, true), new mock_boolean (& array_parent, true) }, value::boolean_t, PASS_T },
          { L"nk", 5, { new mock_null (& object_parent), new mock_null (& array_parent) }, value::null_t, PASS_T },
        };

        size_t x = 0;

        TEST_IT_START

            value & oov = object_parent[(*it).key];
            value & aov = array_parent[(*it).index];

            // Original assertion:
            ///ASSERT_EQUAL_IDX ("value.type ()", value::undefined_t, oov.type ());
            ///
            ASSERT_THAT (oov.type (), Eq (value::undefined_t))
                << ERR_IDX_MSG << _idx[0];

            // Original assertion:
            ///ASSERT_EQUAL_IDX ("value.type ()", value::undefined_t, aov.type ());
            ///
            ASSERT_THAT (aov.type (), Eq (value::undefined_t))
                << ERR_IDX_MSG << _idx[0];

            object_parent.assign (& oov, (*it).val[0]);
            array_parent.assign (& aov, (*it).val[1]);

            // Original assertion:
            ///ASSERT_EQUAL_IDX ("parent._at (key)", (*it).type, object_parent[(*it).key].type ());
            ///
            ASSERT_THAT (object_parent[(*it).key].type (), Eq ((*it).type))
                << ERR_IDX_MSG << _idx[0];

            // Original assertion:
            ///ASSERT_EQUAL_IDX ("parent._at (index)", (*it).type, array_parent[(*it).index].type ());
            ///
            ASSERT_THAT (array_parent[(*it).index].type (), Eq ((*it).type))
                << ERR_IDX_MSG << _idx[0];

            x++;

        TEST_IT_END
      }

      TEST_F (json_test, assign_all_values)
      {
        /* json j;
        struct assert
        {
            value *val;
            value::value_t type;
            int assert_status;
        };

        std::vector<struct assert > test = {
          { new json, value::undefined_t, PASS },
          { new object, value::object_t, PASS },
          { new array, value::array_t, PASS },
          { new string, value::string_t, PASS },
          { new number, value::number_t, PASS },
          { new boolean, value::boolean_t, PASS },
          { new null, value::null_t, PASS },
        };

        TEST_IT_START
            j = *(*it).val;
            ASSERT_EQUAL_IDX ("json.__value->type ()", (*it).type, j.__root->type ());
        TEST_IT_END; */
      }

      TEST_F (json_test, parse_revive)
      {
        // input:   L{\"0\":{},\"1\":[],\"2\":\"2\",\"3\":3,\"4\":false,\"5\":null}
        // output:  input
        // output:  L{\"0\":{},\"1\":[],\"2\":\"3\",\"3\":4,\"4\":true}

        struct assert
        {
          const wchar_t *input;
          std::vector<value *> output[2];
          int assert_status;
        };

        std::vector<struct assert> test = {
          { L"{\"0\":{},\"1\":[],\"2\":\"2\",\"3\":3,\"4\":false,\"5\":null}", {
              { __VALUE[value::object_t], __VALUE[value::array_t], __VALUE[value::string_t], __VALUE[value::number_t], __VALUE[value::boolean_t] , __VALUE[value::null_t] },
              { __VALUE[value::null_t], __VALUE[value::null_t], __VALUE[value::string_t], __VALUE[value::number_t], __VALUE[value::boolean_t] }
            }, PASS_T },

          { L"[{},\[],\"2\",3,false,null]", {
              { __VALUE[value::object_t], __VALUE[value::array_t], __VALUE[value::string_t], __VALUE[value::number_t], __VALUE[value::boolean_t] , __VALUE[value::null_t] },
              { __VALUE[value::null_t], __VALUE[value::null_t], __VALUE[value::string_t], __VALUE[value::number_t], __VALUE[value::boolean_t] }
            }, PASS_T },
          };

         reviver reviver[2] = { nullptr, fn_reviver };

         TEST_IT_START

          for (size_t rev_idx = 1; rev_idx < 2; rev_idx++) // Iterate reviver
            {
              value *jv = json::parse ((*it).input, reviver[rev_idx]);

              size_t output_size = (*it).output[rev_idx].size ();

              for (size_t val_idx = 0; val_idx < output_size; val_idx++) // Iterate values
                {
                  value *ov = (*it).output[rev_idx].at (val_idx);
                  value & jvv = *jv;

                  // Original assertion:
                  ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("jv->count ()", output_size, jv->size ());
                  ///
                  ASSERT_THAT (jv->size (), Eq (output_size))
                      << ERR_IDX_MSG << _idx[0];

                  // Original assertion:
                  ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("jv->at ().type ()", ov->type (), jvv[ std::to_wstring (val_idx).c_str () ].type ());
                  ///
                  ASSERT_THAT (ov->type (), Eq (jvv[ std::to_wstring (val_idx).c_str () ].type ()))
                      << ERR_IDX_MSG << _idx[0];
                }
              delete jv;
            }
         TEST_IT_END
      }

      TEST_F (json_test, count)
      {
        json j[2] = {
          json (),
          json (L"{}")
        };

        for (size_t idx = 0; idx < 2; idx++)
           // Original assertion:
          ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("json::count ()", static_cast<size_t> (0), j[idx].size ());
          ///
          ASSERT_THAT (j[idx].size (), Eq (0))
              << ERR_IDX_MSG << idx;
      }

      TEST_F (json_test, _assign_value_ptr_value_ptr)
      { /*CPPUNIT_ASSERT_ASSERTION_PASS ();*/ }

      TEST_F (json_test, _clone_const_value_ref)
      { /*CPPUNIT_ASSERT_ASSERTION_PASS ();*/ }

      TEST_F (json_test, operator_at_key)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE (  "json[key]::type ()", value::undefined_t, json ()[L"0"].type ());
        ///
        ASSERT_THAT (json ()[L"0"].type (), Eq (value::undefined_t));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE (  "json[key]::type ()", value::boolean_t, json (L"{\"0\":true}")[L"0"].type ());
        ///
        ASSERT_THAT (json (L"{\"0\":true}")[L"0"].type (), Eq (value::boolean_t));
      }

      TEST_F (json_test, operator_at_index)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE (  "json[index]::type ()", value::undefined_t, json ()[static_cast<size_t> (0)].type ());
        ///
        ASSERT_THAT (json ()[static_cast<size_t> (0)].type (), Eq (value::undefined_t));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE (  "json[index]::type ()", value::boolean_t, json (L"[true]")[static_cast<size_t> (0)].type ());
        ///
        ASSERT_THAT (json (L"[true]")[static_cast<size_t> (0)].type (), value::boolean_t);
      }

      TEST_F (json_test, str_length)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("json[index]::str_length ()", static_cast<size_t> (3), /* json (L"{\"0\":\"x\"}")[L"0"].str_length () */ __call__str_length (& (json(L"{\"0\":\"x\"}")[L"0"])));
        ///
        ASSERT_THAT (mock_value::_str_length (& (json (L"{\"0\":\"x\"}")[L"0"])), Eq (3));
      }

      TEST_F (json_test, _clear)
      { /*CPPUNIT_ASSERT_ASSERTION_PASS ("json::_clear is nop");*/ }

      TEST_F (json_test, _erase)
      { /*CPPUNIT_ASSERT_ASSERTION_PASS ("json::_erase is nop");*/ }

      TEST_F (json_test, type)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("value::type ()", value::undefined_t, json ().type ());
        ///
        ASSERT_THAT (json ().type (), Eq (value::undefined_t));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("value::type ()", value::object_t, json (L"{}").type ());
        ///
        ASSERT_THAT (json (L"{}").type (), Eq (value::object_t));
      }

      TEST_F (json_test, operator_assign_object_ptr)
      {
        object *o[] = { nullptr, new object () };

        json j (o[0]);
        j = o[1];

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("o[1] == j.__root", o[1] == j.__root);
        ///
        ASSERT_THAT (j.root (), Eq (o[1]));
      }

      TEST_F (json_test, operator_assign_array_ptr)
      {
        array *a[] = { nullptr, new array () };

        json j (a[0]);
        j = a[1];

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("a[1] == j.__root", a[1] == j.__root);
        ///
        ASSERT_THAT (j.root (), Eq (a[1]));
      }
    }
  } // Namespace json
} // Namespace format
#endif // JSON_TEST_H
