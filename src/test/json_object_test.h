#ifndef JSON_OBJECT_TEST_H
#define JSON_OBJECT_TEST_H

#include "unit_test.h"

namespace format
{
  namespace json
  {
    namespace test
    {
      // 0.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_erase", &json_object_test::test__erase));
      // 1.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_smoke", &json_object_test::test_ctor_dtor));
      // 2.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_assign_all_values", &json_object_test::test_assign_all_values));
      // 3.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_key", &json_object_test::test_key));
      // 4.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test__parse", &json_object_test::test__parse));
      // 5.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_operator_at_key", &json_object_test::test_operator_at_key));
      // 7.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_const_operator_at_key", &json_object_test::test_const_operator_at_key));
      // 8.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_operator_at_index", &json_object_test::test_operator_at_index));
      // 9.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_const_operator_at_index", &json_object_test::test_const_operator_at_index));
      // 10.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test__pair", &json_object_test::test__pair));
      // 11.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test__clear", &json_object_test::test__clear));
      // 12.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_strLength", &json_object_test::test_str_length));
      // 13.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test__to_string", &json_object_test::test__to_string));
      // 14.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_count", &json_object_test::test_count));
      // 15.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test__assign_value_ptr_value_ptr", &json_object_test::test__assign_value_ptr_value_ptr));
      // 16.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test__clone_const_value_ref", &json_object_test::test__clone_const_value_ref));
      // 17.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_type", &json_object_test::test_type));
      // 18.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_operator_assign_wchar_t_ptr", &json_object_test::test_operator_assign_wchar_t_ptr));
      // 19.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_operator_assign_initializer_list", &json_object_test::test_operator_assign_initializer_list));

      class object_test : public unit_test
      { };

      TEST_F (object_test, _erase)
      {
        object o;

        value *v[3]= {
          new boolean (),
          new boolean (),
          new boolean ()
        };

        __call__set_key (v[0], L"key_1", 5);
        __call__set_key (v[1], L"key_2", 5);
        __call__set_key (v[2], L"key_3", 5);

        o._member_list = { { v[0]->key (), v[0] }, { v[1]->key (), v[1] } };

        struct assert
        {
          value *val;
          size_t size;
          int assert_status;
        };

        std::vector<struct assert> test = {
          { v[2], 2, PASS_T },
          { v[1], 1, PASS_T },
          { v[0], 0, PASS_T },
        };

        TEST_IT_START

          (void) o._erase (*(*it).val);
          size_t size = o.size ();

          // Original assertion:
          /// ASSERT_EQUAL_IDX ("o.count ()", (*it).size, size);
          ///
          ASSERT_THAT (size, Eq ((*it).size))
              << ERR_IDX_MSG << _idx[0];

        TEST_IT_END

        // TODO: move to test_operator_assign_undefined
        // Original assertion:
        /// CPPUNIT_ASSERT_EQUAL_MESSAGE ("object.count ()", static_cast<size_t> (1), (object (L"{\"0\":0,\"1\":1}") [L"0"] = undefined ()).size ());
        ///
        ASSERT_THAT ((object (L"{\"0\":0,\"1\":1}") [L"0"] = undefined ()).size (), Eq (1));

        delete v[2];
      }

      TEST_F (object_test, ctor_dtor)
      {
        const wchar_t * json_text = L"{ \"1\": { \"2\": 2 } }";
        object src = json_text;

        json parent;

        object o[] = {
          object (),
          object (L"{}"),
          object (& parent),
          object {{ L"0", new object {{ L"1", new number () }} }}, // { "0": { "1": 0 } }
          object (json_text),
          object (src) // 5.
        };

  //      object src  = L"{\"key\":true}";
  //      object copy = src;

  //      CPPUNIT_ASSERT_EQUAL_MESSAGE ("object::type ()",
  //                                    json::object_t, src.type ());

  //      CPPUNIT_ASSERT_MESSAGE ("object",
  //                              & copy != & src);

  //      CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.count ()",
  //                                    (size_t) 1,
  //                                    copy.length ());

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("object::count ()", static_cast<size_t> (1), o[3].size ());
        ///
        ASSERT_THAT (o[3].size (), Eq (1));

        // Original assertion:
        /// CPPUNIT_ASSERT_EQUAL_MESSAGE ("object[key][key].type ()", value::number_t, o[3][L"0"][L"1"].type ());
        ///
        ASSERT_THAT (o[3][L"0"][L"1"].type (), Eq (value::number_t));

        // Original assertion:
        /// CPPUNIT_ASSERT_EQUAL_MESSAGE ("o[3][L\"0\"].parent ()", dynamic_cast<json *> (& o[3]), o[3][L"0"].parent ());
        ///
        ASSERT_THAT (o[3][L"0"].parent (), Eq (dynamic_cast<json *> (& o[3])));

        // Original assertion:
        /// CPPUNIT_ASSERT_MESSAGE ("o[3][L\"0\"].key ()", o[3][L"0"].key () == std::wstring (L"0"));
        ///
        ASSERT_THAT (o[3][L"0"].key (), StrEq (L"0"));

        // Original assertion:
        /// CPPUNIT_ASSERT_EQUAL_MESSAGE ("object at size", (size_t) 1, o[4][L"1"].size ());
        ///
        ASSERT_THAT (o[4][L"1"].size (), Eq (1));

        // Original assertion:
        /// CPPUNIT_ASSERT_EQUAL_MESSAGE ("object copy at size", (size_t) 1, o[5][L"1"].size ());
        ///
        ASSERT_THAT (o[5][L"1"].size (), Eq (1));
      }

      TEST_F (object_test, assign_all_values)
      {
        object_accessor object_parent;

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
          int assert_status[2];
        };

        object o (L"{\"0\":true,\"1\":false}");

        std::vector<struct assert > test = {
          { & o,  value::object_t, L"0",  0, 1,  { PASS_T, PASS_T } },
          { __VALUE[value::array_t], value::array_t, L"1",  0, 2,  { PASS_T, FAIL_T } },
  //        { __VALUE[value::string_t], value::string_t, L"2",  0, 3,  { PASS, FAIL } },
  //        { __VALUE[value::number_t], value::number_t, L"3",  0, 4, { PASS, FAIL } },
  //        { __VALUE[value::boolean_t], value::boolean_t, L"4",  0, 5, { PASS, FAIL } },
  //        { __VALUE[value::null_t], value::null_t, L"5",  0, 6, { PASS, FAIL } }
        };

        object *old_value = nullptr;

        for (size_t pidx = 0; pidx < 2; pidx++)
          {
            this->_idx[0] = 0;

            for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++)
              {
                try
                  {
                    if ((*it).assert_status[pidx] == SKIP_T) { continue; }
                    if ((*it).assert_status[pidx] > PASS_T) { this->_errorc[EXPECTED]++; }

                    /** old_value: value from value[key] */
                    old_value = new object (parents[pidx]);

                    old_value->_set_key ((*it).key, wcslen ((*it).key));

                    if ((*it).new_value->type () == value::object_t)
                      *old_value = *(dynamic_cast<object *>((*it).new_value));
                    else
                      *(dynamic_cast<value *>(old_value)) = *(*it).new_value;

                    json *parent = parents[pidx];

                    if (parent)
                      {
                        // Original assertion:
                        ///ASSERT_EQUAL_IDX ("parent->count ()", (*it).count, parent->size ());
                        ///ASSERT_EQUAL_IDX ("obj_parent[key].type", object_parent[(*it).key].type (), (*it).type);
                        ///
                        ASSERT_THAT (parent->size (), Eq ((*it).count))
                            << ERR_IDX_MSG << _idx[0];

                        ASSERT_THAT (object_parent[(*it).key].type (), Eq ((*it).type))
                            << ERR_IDX_MSG << _idx[0];
                      }
                    else
                      {
                        // Original assertion:
                        ///ASSERT_EQUAL_IDX ("old_value.size ()", static_cast<size_t> (2), old_value->size ());
                        ///
                        ASSERT_THAT (old_value->size (), Eq (2))
                            << ERR_IDX_MSG << _idx[0];

                        delete old_value;
                      }
                  }
                catch (std::exception & e)
                  {
                    this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl;
                    delete old_value;
                  }
              }
            (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]); \

            // Original assertion:
            ///CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
            ///
            ASSERT_THAT (this->_errorc[ACTUAL], Eq (this->_errorc[EXPECTED]));
          }
      }

      TEST_F (object_test, _parse)
      {
        struct assert {
          const wchar_t *startp;
          size_t size;
          value::value_t type;
          size_t moveback;
          int assert_status;
        };

        json *p[] = { nullptr, new json () };

        std::vector<struct assert > test = {
          { L"{}", 0, value::undefined_t, 0, PASS_T },
          { L"{ } ", 0, value::undefined_t, 1, PASS_T },
          { L"{\"k\":\"v\"} ", 1, value::string_t, 1, PASS_T },
          { L"{ \"k\" : \"v\" } ", 1, value::string_t, 1, PASS_T },
          { L"{\"k\":\"v\",\"q\":\"p\"} ", 2, value::string_t, 1, PASS_T },
          { L"{ \"k\": \"v\", \"q\" : \"p\",\"K\":\"v\" } ", 3, value::string_t, 1, PASS_T },
          { L"{ \"k\": \"p\" ,\"q\" : \"p\", \"K\" :\"v\",\"Q\":\"p\" } ", 4, value::string_t, 1, PASS_T },

          { L"{ \"k\" : { } }", 1, value::object_t, 0, PASS_T },
          { L"{ \"k\" : {\"kk\" : \"v\"}}", 1, value::object_t, 0, PASS_T },
          { L"{ \"k\" : {\"kk\" : {\"kkk\" : \"v\"}}", 1, value::object_t, 0, PASS_T },
          { L"{ \"k\" : null } ", 1, value::null_t, 1, PASS_T },

          // errors
          { L"", 0, value::undefined_t, 0, FAIL_T },   // json::syntax_error
          { L" ", 0, value::undefined_t, 0, FAIL_T },   // json::syntax_error
          { L"x", 0, value::undefined_t, 0, FAIL_T },   // json::syntax_error
          { L"{", 0, value::undefined_t, 0, FAIL_T },   // json::syntax_error
          { L"}", 0, value::undefined_t, 0, FAIL_T },   // json::syntax_error
          { L"{ , }", 0, value::undefined_t, 0, FAIL_T },   // json::syntax_error
          { L"{ : }", 0, value::undefined_t, 0, FAIL_T },   // json::syntax_error
        };

        object *o = nullptr;

        TEST_IT_START
          for (int pidx = 0; pidx < 2; pidx++)
            {
              const wchar_t *startp = (*it).startp;

              size_t charc = wcslen (startp);

              o = new object (p[pidx]);

              const wchar_t *readp = o->_parse (startp);

              // Original assertion:
              ///ASSERT_EQUAL_IDX ("value.readp", (startp + charc) - (*it).moveback, readp);
              ///ASSERT_EQUAL_IDX ("*(value.readp -1)", L'}', *(readp - 1));
              ///ASSERT_EQUAL_IDX ("value.size", (*it).size, o->size ());
              ///
              ASSERT_THAT (readp, Eq ((startp + charc) - (*it).moveback))
                  << ERR_IDX_MSG << _idx[0];

              ASSERT_THAT (*(readp - 1), L'}')
                  << ERR_IDX_MSG << _idx[0];

              ASSERT_THAT (o->size (), (*it).size)
                  << ERR_IDX_MSG << _idx[0];

              if (o->size () > 0)
                {
                  object & oo = *o;

                  // Original assertion:
                  ///ASSERT_EQUAL_IDX ("value.type", (*it).type, oo[L"k"].type ());
                  ///ASSERT_EQUAL_IDX ("*(value.key)", static_cast<wchar_t> (L'k'), *(oo[(L"k")].key ()));
                  ///
                  ASSERT_THAT (oo[L"k"].type (), Eq ((*it).type))
                      << ERR_IDX_MSG << _idx[0];

                  ASSERT_THAT (*(oo[(L"k")].key ()), Eq (static_cast<wchar_t> (L'k')))
                      << ERR_IDX_MSG << _idx[0];
                }
              delete o;
            }
          }
         catch (format::json::json_syntax_error & se)
          {
            this->_errorc[ACTUAL]++; std::cerr << se.what () << std::endl;
            delete o;
          }
        }

        // Original assertion:
        ///(void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]); \
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
        ///
        ASSERT_THAT (this->_errorc[ACTUAL], Eq (this->_errorc[EXPECTED]));

        delete p[1];
      }

      TEST_F (object_test, key)
      {
        struct assert
        {
          const wchar_t *startp;
          int assert_status;
        };

        std::vector<struct assert > test = {
          { L"{}", PASS_T },
          { L"{ } ", PASS_T },
          { L"{\"key1\":\"v\",\"key2\":\"v\",\"key3\":\"v\"} ", PASS_T },
        };

        TEST_IT_START
          const wchar_t *startp = (*it).startp;

          object *o = new object ();

          (void) o->_parse (startp);

          if (o->size () > 0)
            {
              size_t idx= 0;

              for (auto it = o->_member_list.begin (); it != o->_member_list.end (); ++it, idx++)
                {
                  const wchar_t *k = (*it).first.c_str ();
                  object & oo = *o;

                  // Original assertion:
                  ///ASSERT_EQUAL_IDX ("value::key ()", 0, wcscmp (k, oo[k].key ()));
                  ///
                  ASSERT_THAT (oo[k].key (), StrEq (k))
                      << ERR_IDX_MSG << _idx[0];
                }
            }
          delete o;

        TEST_IT_END
      }

      TEST_F (object_test, operator_at_key)
      {
        object o;

        o._member_list.emplace (L"0", new boolean (true));

        struct assert {
          const wchar_t *key;
          value::value_t type;
          int assert_status;
        };

        std::vector<struct assert> test = {
          { L"0", value::value_t::boolean_t, PASS_T },
          { L"1", value::value_t::undefined_t, PASS_T }
        };

        TEST_IT_START

          value & v = o[((*it).key)];

          // Original assertion:
          ///ASSERT_EQUAL_IDX ("value::type ()", (*it).type, v.type ());
          ///
          ASSERT_THAT (v.type (), Eq ((*it).type))
              << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (object_test, const_operator_at_key)
      {
        const object o = L"{ \"0\": true }";

        struct assert {
          const wchar_t *key;
          value::value_t type;
          int assert_status;
        };

        std::vector<struct assert> test = {
          { L"0", value::value_t::boolean_t, PASS_T },
          { L"1", value::value_t::undefined_t, FAIL_T }
        };

        TEST_IT_START

          const value & v = o[((*it).key)];

          // Original assertion:
          ///ASSERT_EQUAL_IDX ("value::type ()", (*it).type, v.type ());
          ///
          ASSERT_THAT (v.type (), Eq ((*it).type))
              << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (object_test, test_operator_at_index)
      {
        object o;

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("o[size_t].type ()", value::undefined_t, o[static_cast<size_t> (0)].type ());
        ///
        ASSERT_THAT (o[static_cast<size_t> (0)].type (), Eq (value::undefined_t));
      }

      TEST_F (object_test, const_operator_at_index)
      {
        bool actual = false;

        try
          {
            const object o;
            const value & v = o[static_cast<size_t> (0)];

          } catch (const json_out_of_range & e) {
            std::cerr << e.what () << std::endl;
            actual = true;
          }

        // Original assertion
        ///CPPUNIT_ASSERT_EQUAL (true, actual);
        ///
        ASSERT_THAT (actual, Eq (true));
      }

      TEST_F (object_test, _pair)
      {
        object  p;

        struct assert
        {
          const wchar_t *startp;
          bool status;
          int assert_status;
        };

        std::vector<struct assert > test = {
          { L" \"foo\" : \"bar\" ", true, PASS_T },
          { L" }" , false , PASS_T },

          // errors
          { L" ", false, FAIL_T},            // json::syntax_error
          { L" \"foo  ", false, FAIL_T },    // json::syntax_error
          { L" \"foo\" ", false, FAIL_T },   // json::syntax_error
          { L" \"foo\" : ", false, SKIP_T }, // FAIL: json::syntax_error
        };

        object *o = nullptr;

        TEST_IT_START
            const wchar_t *startp = (*it).startp;

            o = new object (& p);
            o->_readp = startp;

            bool status = o->_pair ();

            // Original assertion
            ///ASSERT_EQUAL_IDX ("status", (*it).status, status);
            ///
            ASSERT_THAT (status, Eq ((*it).status))
                << ERR_IDX_MSG << _idx[0];

            delete o;
          }
        catch (format::json::json_syntax_error & se)
          {
            this->_errorc[ACTUAL]++; std::cerr << se.what () << std::endl;
             delete o;
           }
         }

         //(void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]);
         // Original assertion:
         ///CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
         ///
         ASSERT_THAT (this->_errorc[ACTUAL], Eq (this->_errorc[EXPECTED]));
      }

      TEST_F (object_test, _clear)
      {
        object o = L"{\"a\":true,\"b\":false}";
        o._clear ();

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("object::_member_list.size ()", static_cast<size_t> (0), o._member_list.size ());
        ///
        ASSERT_THAT (o._member_list.size (), Eq (0));
      }

      TEST_F (object_test, _str_length)
      {
        // assert: {} = 2,
        // assert: {\"a\":null} = 2 + 3 + 1 + 4 = 10,
        // assert: {\"a\":null,\"b\":null} =  2 + 2 * (3 + 1 + 4) + 1  = 19
        // assert: {\"a\":null,\"b\":{}} = 2 + 3 + 1 + 4 + 1 + 3 + 1 + 2 = 17

        struct assert
        {
          const wchar_t *input;
          size_t length;
          int assert_status;
        };

        std::vector<struct assert> test = {
          { L"{}", 2, PASS_T },
          { L"{\"a\":null}", 10, PASS_T },
          { L"{\"a\":null,\"b\":null}", 19, PASS_T },
          { L"{\"a\":null,\"b\":{}}", 17, PASS_T }
        };

        TEST_IT_START

            object o = (*it).input;

            // Original assertion:
            ///ASSERT_EQUAL_IDX ("object::str_length ()", (*it).length, o._str_length ());
            ///
            ASSERT_THAT (o._str_length (), Eq ((*it).length));

        TEST_IT_END
      }

      TEST_F (object_test, _to_string)
      {
        object p;

        json *parent[] = {
          nullptr, &p
        };

        struct assert
        {
          const wchar_t *input;
          const wchar_t *output[2];
          int assert_status;
        };

        wchar_t * _str_value[2] = { nullptr, nullptr };

        std::vector<struct assert> test = {
          { L"{}",
            { L"{}",  // Without parent
              L"{\"a\":null,\"b\":{}" }, PASS_T },  // <-- last closing } intentionally missing

          /// !!! UNORDERED MAP HAS KEYS ARE IN DIFFERENT ORDER !!!:
          /// {"c":null,"d":{}} --> {"d":{},"c":null}
          { L"{\"c\":null,\"d\":{}}",
            { L"{\"d\":{},\"c\":null}", // Without parent
              L"{\"a\":null,\"b\":{\"d\":{},\"c\":null}" }, PASS_T },  // <-- last closing ] intentionally missing
        };

        TEST_IT_START

          for (size_t pidx = 0; pidx < 2; pidx++)
            {
              wchar_t *str_value = nullptr;

              size_t len = wcslen ((*it).output[pidx]);

              object o (parent[pidx]);

              if (o.parent ())
                {
                  str_value = new wchar_t[len +1 ] ();
                  str_value = wcsncpy (str_value,  L"{\"a\":null,\"b\":", 14);

                 _str_value[BEGIN]   = str_value;
                 _str_value[OFFSET]  = str_value + 14;
                }

              (void) o._parse ((*it).input);

              const wchar_t *output = o._to_string (o._parent ? _str_value[OFFSET] : nullptr);

              if (o._parent == nullptr)
                {
                  // Original assertion:
                  ///ASSERT_EQUAL_IDX ("strlen (output)", len, wcslen (output));
                  ///CPPUNIT_ASSERT_MESSAGE ("strcmp (output, (*it).output[0])", wcscmp (output, (*it).output[0]) == 0);
                  ///
                  ASSERT_THAT (wcslen (output), Eq (len))
                      << ERR_IDX_MSG << _idx[0];

                  ASSERT_THAT (output, StrEq ((*it).output[0]));
                }
              else
                {
                  // Original assertion:
                  ///ASSERT_EQUAL_IDX ("strlen (p._str_value[BEGIN])", len, wcslen (_str_value[BEGIN]));
                  ///CPPUNIT_ASSERT_MESSAGE ("strcmp (output, (*it).output[1])", wcscmp (_str_value[BEGIN], (*it).output[1]) == 0);
                  ///
                  ASSERT_THAT (wcslen (_str_value[BEGIN]), Eq (len))
                      << ERR_IDX_MSG << _idx[0];

                  ASSERT_THAT (_str_value[BEGIN], StrEq ((*it).output[1]));
                }

              if (o._parent)
                {
                  delete[] str_value;
                  _str_value[BEGIN] = nullptr;
                }
              else
                delete [] output;
          }

        TEST_IT_END
      }

      TEST_F (object_test, _count)
      {
        object o = L"{\"1\":1}";

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("object::count ()", static_cast<size_t> (1), o.size ());
        ///
        ASSERT_THAT (o.size (), Eq (1));
      }

      TEST_F (object_test, _assign_value_ptr_value_ptr)
      {
        object o = L"{\"0\":false}";

        boolean *nv = new boolean (true);

        o._assign (& o[L"0"], nv);

        // Original assertion
        ///CPPUNIT_ASSERT_MESSAGE ("nv->key () == std::wstring (L\"0\")", nv->key () == std::wstring (L"0"));
        ///CPPUNIT_ASSERT_MESSAGE ("o[L\"0\"] == nv", & o[L"0"] == nv);
        ///CPPUNIT_ASSERT_MESSAGE ("o[L\"0\"].parent () == & o", o[L"0"].parent () == & o);
        ///
        ASSERT_THAT (nv->key (), StrEq (L"0"));

        ASSERT_THAT (& o[L"0"], Eq (nv));
        //TODO: ASSERT_THAT (o[L"0"], Address (nv));

        ASSERT_THAT (o[L"0"].parent (), Eq (& o));
        //TODO: ASSERT_THAT (o[L"0"].parent (), Address (o));
      }

      TEST_F (object_test, _clone_const_value_ref)
      {
        //object src = L"{\"2\":2}";
        object src = L"{\"2\":{\"3\":3}}";
        object copy = L"{\"0\":0,\"1\":1}";

        copy._clear ();
        (void) copy._clone (src);

        // Original assertion
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.length ()",static_cast<size_t> (1), copy.size ());
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.at length ()",static_cast<size_t> (1), copy[L"2"].size ());
        ///CPPUNIT_ASSERT_MESSAGE ("copy[L\"2\"].parent () == & copy", copy[L"2"].parent () == & copy);
        ///
        ASSERT_THAT (copy.size (), Eq (1));

        ASSERT_THAT (copy[L"2"].size (), Eq (1));

        ASSERT_THAT (copy[L"2"].parent (), Eq (& copy));
      }

      TEST_F (object_test, type)
      {
        // Original assertion
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("value::type ()", value::object_t, object ().type ());
        ///
        ASSERT_THAT (object ().type (), Eq (value::object_t));
      }

      TEST_F (object_test, operator_assign_wchar_t_ptr)
      {
        object o (L"{\"0\":0,\"1\":1}");
        o = L"{\"3\":3}";

        // Original assertion
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("o.length ()", static_cast<size_t> (1), o.size ());
        ///
        ASSERT_THAT (o.size (), Eq (1));
      }

      TEST_F (object_test, operator_assign_initializer_list)
      {
        object o (L"{\"0\":0,\"1\":1}");
        o = { { L"3", new number (static_cast<long long> (3)) } };

        // Original assertion
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("o.length ()", static_cast<size_t> (1), o.size ());
        ///
        ASSERT_THAT (o.size (), Eq (1));
      }

    }
  /**
   * 2.
   * @brief The json_object_test class
   */
  class json_object_test : public unit_test
  {
  public:

    virtual void
    test_ctor_dtor () //override
    {
//      const wchar_t * json_text = L"{ \"1\": { \"2\": 2 } }";
//      object src = json_text;

//      json parent;

//      object o[] = {
//        object (),
//        object (L"{}"),
//        object (& parent),
//        object {{ L"0", new object {{ L"1", new number () }} }}, // { "0": { "1": 0 } }
//        object (json_text),
//        object (src) // 5.
//      };

////      object src  = L"{\"key\":true}";
////      object copy = src;

////      CPPUNIT_ASSERT_EQUAL_MESSAGE ("object::type ()",
////                                    json::object_t, src.type ());

////      CPPUNIT_ASSERT_MESSAGE ("object",
////                              & copy != & src);

////      CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.count ()",
////                                    (size_t) 1,
////                                    copy.length ());

//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("object::count ()",
//                                    static_cast<size_t> (1),
//                                    o[3].size ());

//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("object[key][key].type ()",
//                                    value::number_t,
//                                    o[3][L"0"][L"1"].type ());

//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("o[3][L\"0\"].parent ()",
//                                    dynamic_cast<json *> (& o[3]),
//                                    o[3][L"0"].parent ());

//      CPPUNIT_ASSERT_MESSAGE ("o[3][L\"0\"].key ()",
//                              o[3][L"0"].key () == std::wstring (L"0"));

//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("object at size",
//                                    (size_t) 1, o[4][L"1"].size ());

//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("object copy at size",
//                                    (size_t) 1, o[5][L"1"].size ());
    }

    virtual
    void test__parse () //override // 4.
    {
//      struct assert {
//        const wchar_t *startp;
//        size_t size;
//        value::value_t type;
//        size_t moveback;
//        int assert_status;
//      };

//      json *p[] = { nullptr, new json () };

//      std::vector<struct assert > test = {
//        { L"{}", 0, value::undefined_t, 0, PASS_T },
//        { L"{ } ", 0, value::undefined_t, 1, PASS_T },
//        { L"{\"k\":\"v\"} ", 1, value::string_t, 1, PASS_T },
//        { L"{ \"k\" : \"v\" } ", 1, value::string_t, 1, PASS_T },
//        { L"{\"k\":\"v\",\"q\":\"p\"} ", 2, value::string_t, 1, PASS_T },
//        { L"{ \"k\": \"v\", \"q\" : \"p\",\"K\":\"v\" } ", 3, value::string_t, 1, PASS_T },
//        { L"{ \"k\": \"p\" ,\"q\" : \"p\", \"K\" :\"v\",\"Q\":\"p\" } ", 4, value::string_t, 1, PASS_T },

//        { L"{ \"k\" : { } }", 1, value::object_t, 0, PASS_T },
//        { L"{ \"k\" : {\"kk\" : \"v\"}}", 1, value::object_t, 0, PASS_T },
//        { L"{ \"k\" : {\"kk\" : {\"kkk\" : \"v\"}}", 1, value::object_t, 0, PASS_T },
//        { L"{ \"k\" : null } ", 1, value::null_t, 1, PASS_T },

//        // errors
//        { L"", 0, value::undefined_t, 0, FAIL_T },   // json::syntax_error
//        { L" ", 0, value::undefined_t, 0, FAIL_T },   // json::syntax_error
//        { L"x", 0, value::undefined_t, 0, FAIL_T },   // json::syntax_error
//        { L"{", 0, value::undefined_t, 0, FAIL_T },   // json::syntax_error
//        { L"}", 0, value::undefined_t, 0, FAIL_T },   // json::syntax_error
//        { L"{ , }", 0, value::undefined_t, 0, FAIL_T },   // json::syntax_error
//        { L"{ : }", 0, value::undefined_t, 0, FAIL_T },   // json::syntax_error
//      };

//      object *o = nullptr;

//      TEST_IT_START
//        for (int pidx = 0; pidx < 2; pidx++)
//          {
//            const wchar_t *startp = (*it).startp;

//            size_t charc = wcslen (startp);

//            o = new object (p[pidx]);

//            const wchar_t *readp = o->_parse (startp);

//            ASSERT_EQUAL_IDX ("value.readp", (startp + charc) - (*it).moveback, readp);
//            ASSERT_EQUAL_IDX ("*(value.readp -1)", L'}', *(readp - 1));
//            ASSERT_EQUAL_IDX ("value.size", (*it).size, o->size ());

//            if (o->size () > 0)
//              {
//                object & oo = *o;

//                ASSERT_EQUAL_IDX ("value.type", (*it).type, oo[L"k"].type ());
//                ASSERT_EQUAL_IDX ("*(value.key)", static_cast<wchar_t> (L'k'), *(oo[(L"k")].key ()));
//              }
//            delete o;
//          }
//        }
//       catch (format::json::json_syntax_error & se)
//        {
//          this->_errorc[ACTUAL]++; std::cerr << se.what () << std::endl;
//          delete o;
//        }
//      }

//      (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]); \
//      CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);

//      delete p[1];
    }

    void
    test_key ()
    {
//      struct assert
//      {
//        const wchar_t *startp;
//        int assert_status;
//      };

//      std::vector<struct assert > test = {
//        { L"{}", PASS_T },
//        { L"{ } ", PASS_T },
//        { L"{\"key1\":\"v\",\"key2\":\"v\",\"key3\":\"v\"} ", PASS_T },
//      };

//      TEST_IT_START
//        const wchar_t *startp = (*it).startp;

//        object *o = new object ();

//        (void) o->_parse (startp);

//        if (o->size () > 0)
//          {
//            size_t idx= 0;

//            for (auto it = o->_member_list.begin (); it != o->_member_list.end (); ++it, idx++)
//              {
//                const wchar_t *k = (*it).first.c_str ();
//                object & oo = *o;

//                ASSERT_EQUAL_IDX ("value::key ()",
//                                  0,
//                                  wcscmp (k, oo[k].key ()));
//              }
//          }
//        delete o;

//      TEST_IT_END
    }

    virtual void
    test_operator_at_key () //override
    {
//      object o;

//      o._member_list.emplace (L"0", new boolean (true));

//      struct assert {
//        const wchar_t *key;
//        value::value_t type;
//        int assert_status;
//      };

//      std::vector<struct assert> test = {
//        { L"0", value::value_t::boolean_t, PASS_T },
//        { L"1", value::value_t::undefined_t, PASS_T }
//      };

//      TEST_IT_START

//        value & v = o[((*it).key)];

//        ASSERT_EQUAL_IDX ("value::type ()",
//                          (*it).type,
//                          v.type ());

//      TEST_IT_END
    }

    virtual void
    test_const_operator_at_key () //override
    {
//      const object o = L"{ \"0\": true }";

//      struct assert {
//        const wchar_t *key;
//        value::value_t type;
//        int assert_status;
//      };

//      std::vector<struct assert> test = {
//        { L"0", value::value_t::boolean_t, PASS_T },
//        { L"1", value::value_t::undefined_t, FAIL_T }
//      };

//      TEST_IT_START

//        const value & v = o[((*it).key)];

//        ASSERT_EQUAL_IDX ("value::type ()",
//                          (*it).type,
//                          v.type ());

//      TEST_IT_END
    }

    virtual void
    test_operator_at_index () //override
    {
//      object o;
//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("o[size_t].type ()", value::undefined_t, o[static_cast<size_t> (0)].type ());
    }

    virtual void
    test_const_operator_at_index () //override
    {
//      bool actual = false;

//      try
//        {
//          const object o;
//          const value & v = o[static_cast<size_t> (0)];

//        } catch (const json_out_of_range & e) {
//          std::cerr << e.what () << std::endl;
//          actual = true;
//        }

//      CPPUNIT_ASSERT_EQUAL (true, actual);
    }

    void
    test__pair ()
    {
//      object  p;

//      struct assert
//      {
//        const wchar_t *startp;
//        bool status;
//        int assert_status;
//      };

//      std::vector<struct assert > test = {
//        { L" \"foo\" : \"bar\" ", true, PASS_T },
//        { L" }" , false , PASS_T },

//        // errors
//        { L" ", false, FAIL_T},            // json::syntax_error
//        { L" \"foo  ", false, FAIL_T },    // json::syntax_error
//        { L" \"foo\" ", false, FAIL_T },   // json::syntax_error
//        { L" \"foo\" : ", false, SKIP_T }, // FAIL: json::syntax_error
//      };

//      object *o = nullptr;

//      TEST_IT_START
//          const wchar_t *startp = (*it).startp;

//          o = new object (& p);
//          o->_readp = startp;

//          bool status = o->_pair ();

//          ASSERT_EQUAL_IDX ("status", (*it).status, status);

//          delete o;
//        }
//      catch (format::json::json_syntax_error & se)
//        {
//          this->_errorc[ACTUAL]++; std::cerr << se.what () << std::endl;
//           delete o;
//         }
//       }

//       (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]);

//       CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
    }

    virtual void
    test_assign_all_values () //override
    {
//      object_accessor object_parent;

//      json *parents[] = {
//        & object_parent,
//        nullptr
//      };

//      struct assert
//      {
//        value *new_value;
//        value::value_t type;
//        const wchar_t *key;
//        size_t index;
//        size_t count;
//        int assert_status[2];
//      };

//      object o (L"{\"0\":true,\"1\":false}");

//      std::vector<struct assert > test = {
//        { & o,  value::object_t, L"0",  0, 1,  { PASS_T, PASS_T } },
//        { __VALUE[value::array_t], value::array_t, L"1",  0, 2,  { PASS_T, FAIL_T } },
////        { __VALUE[value::string_t], value::string_t, L"2",  0, 3,  { PASS, FAIL } },
////        { __VALUE[value::number_t], value::number_t, L"3",  0, 4, { PASS, FAIL } },
////        { __VALUE[value::boolean_t], value::boolean_t, L"4",  0, 5, { PASS, FAIL } },
////        { __VALUE[value::null_t], value::null_t, L"5",  0, 6, { PASS, FAIL } }
//      };

//      object *old_value = nullptr;

//      for (size_t pidx = 0; pidx < 2; pidx++)
//        {
//          this->_idx[0] = 0;

//          for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++)
//            {
//              try
//                {
//                  if ((*it).assert_status[pidx] == SKIP_T) { continue; }
//                  if ((*it).assert_status[pidx] > PASS_T) { this->_errorc[EXPECTED]++; }

//                  /** old_value: value from value[key] */
//                  old_value = new object (parents[pidx]);

//                  old_value->_set_key ((*it).key, wcslen ((*it).key));

//                  if ((*it).new_value->type () == value::object_t)
//                    *old_value = *(dynamic_cast<object *>((*it).new_value));
//                  else
//                    *(dynamic_cast<value *>(old_value)) = *(*it).new_value;

//                  json *parent = parents[pidx];

//                  if (parent)
//                    {
//                      ASSERT_EQUAL_IDX ("parent->count ()", (*it).count, parent->size ());
//                      ASSERT_EQUAL_IDX ("obj_parent[key].type", object_parent[(*it).key].type (), (*it).type);
//                    }
//                  else
//                    {
//                      ASSERT_EQUAL_IDX ("old_value.size ()", static_cast<size_t> (2), old_value->size ());
//                      delete old_value;
//                    }
//                }
//              catch (std::exception & e)
//                {
//                  this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl;
//                  delete old_value;
//                }
//            }
//          (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]); \

//          CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
//        }
    }

    virtual void
    test__clear () //override
    {
//      object o = L"{\"a\":true,\"b\":false}";
//      o._clear ();

//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("object::_member_list.size ()",
//                                    static_cast<size_t> (0),
//                                    o._member_list.size ());
    }

    virtual void
    test_str_length () //override
    {
//      // assert: {} = 2,
//      // assert: {\"a\":null} = 2 + 3 + 1 + 4 = 10,
//      // assert: {\"a\":null,\"b\":null} =  2 + 2 * (3 + 1 + 4) + 1  = 19
//      // assert: {\"a\":null,\"b\":{}} = 2 + 3 + 1 + 4 + 1 + 3 + 1 + 2 = 17

//      struct assert
//      {
//        const wchar_t *input;
//        size_t length;
//        int assert_status;
//      };

//      std::vector<struct assert> test = {
//        { L"{}", 2, PASS_T },
//        { L"{\"a\":null}", 10, PASS_T },
//        { L"{\"a\":null,\"b\":null}", 19, PASS_T },
//        { L"{\"a\":null,\"b\":{}}", 17, PASS_T }
//      };

//      TEST_IT_START

//          object o = (*it).input;

//          ASSERT_EQUAL_IDX ("object::str_length ()",
//                            (*it).length,
//                            o._str_length ());
//      TEST_IT_END
    }

    virtual void
    test__to_string () //override
    {
//      object p;

//      json *parent[] = {
//        nullptr, &p
//      };

//      struct assert
//      {
//        const wchar_t *input;
//        const wchar_t *output[2];
//        int assert_status;
//      };

//      wchar_t * _str_value[2] = { nullptr, nullptr };

//      std::vector<struct assert> test = {
//        { L"{}",
//          { L"{}",  // Without parent
//            L"{\"a\":null,\"b\":{}" }, PASS_T },  // <-- last closing } intentionally missing

//        /// !!! UNORDERED MAP HAS KEYS ARE IN DIFFERENT ORDER !!!:
//        /// {"c":null,"d":{}} --> {"d":{},"c":null}
//        { L"{\"c\":null,\"d\":{}}",
//          { L"{\"d\":{},\"c\":null}", // Without parent
//            L"{\"a\":null,\"b\":{\"d\":{},\"c\":null}" }, PASS_T },  // <-- last closing ] intentionally missing
//      };

//      TEST_IT_START

//        for (size_t pidx = 0; pidx < 2; pidx++)
//          {
//            wchar_t *str_value = nullptr;

//            size_t len = wcslen ((*it).output[pidx]);

//            object o (parent[pidx]);

//            if (o.parent ())
//              {
//                str_value = new wchar_t[len +1 ] ();
//                str_value = wcsncpy (str_value,  L"{\"a\":null,\"b\":", 14);

//               _str_value[BEGIN]   = str_value;
//               _str_value[OFFSET]  = str_value + 14;
//              }

//            (void) o._parse ((*it).input);

//            const wchar_t *output = o._to_string (o._parent ? _str_value[OFFSET] : nullptr);

//            if (o._parent == nullptr)
//              {
//                ASSERT_EQUAL_IDX ("strlen (output)", len, wcslen (output));
//                CPPUNIT_ASSERT_MESSAGE ("strcmp (output, (*it).output[0])", wcscmp (output, (*it).output[0]) == 0);
//              }
//            else
//              {
//                ASSERT_EQUAL_IDX ("strlen (p._str_value[BEGIN])", len, wcslen (_str_value[BEGIN]));
//                CPPUNIT_ASSERT_MESSAGE ("strcmp (output, (*it).output[1])", wcscmp (_str_value[BEGIN], (*it).output[1]) == 0);
//              }

//            if (o._parent)
//              {
//                delete[] str_value;
//                _str_value[BEGIN] = nullptr;
//              }
//            else
//              delete [] output;
//        }

//      TEST_IT_END
    }

    virtual void
    test__erase () //override
    {
//      object o;

//      value *v[3]= {
//        new boolean (),
//        new boolean (),
//        new boolean ()
//      };

//      __call__set_key (v[0], L"key_1", 5);
//      __call__set_key (v[1], L"key_2", 5);
//      __call__set_key (v[2], L"key_3", 5);

//      o._member_list = { { v[0]->key (), v[0] }, { v[1]->key (), v[1] } };

//      struct assert
//      {
//        value *val;
//        size_t size;
//        int assert_status;
//      };

//      std::vector<struct assert> test = {
//        { v[2], 2, PASS_T },
//        { v[1], 1, PASS_T },
//        { v[0], 0, PASS_T },
//      };

//      TEST_IT_START

//        (void) o._erase (*(*it).val);
//        size_t size = o.size ();

//        ASSERT_EQUAL_IDX ("o.count ()", (*it).size, size);

//      TEST_IT_END

//      // TODO: move to test_operator_assign_undefined
//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("object.count ()",
//                                    static_cast<size_t> (1),
//                                    (object (L"{\"0\":0,\"1\":1}") [L"0"] = undefined ()).size ());
//      delete v[2];
    }

    virtual void
    test_count () //override
    {
//      object o = L"{\"1\":1}";
//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("object::count ()",
//                                    static_cast<size_t> (1),
//                                    o.size ());
    }

    virtual void
    test__assign_value_ptr_value_ptr () //override
    {
//      object o = L"{\"0\":false}";

//      boolean *nv = new boolean (true);

//      o._assign (& o[L"0"], nv);

//      CPPUNIT_ASSERT_MESSAGE ("nv->key () == std::wstring (L\"0\")",
//                              nv->key () == std::wstring (L"0"));

//      CPPUNIT_ASSERT_MESSAGE ("o[L\"0\"] == nv",
//                              & o[L"0"] == nv);

//      CPPUNIT_ASSERT_MESSAGE ("o[L\"0\"].parent () == & o",
//                              o[L"0"].parent () == & o);
    }

    virtual void
    test__clone_const_value_ref () //override
    {
//      //object src = L"{\"2\":2}";
//      object src = L"{\"2\":{\"3\":3}}";
//      object copy = L"{\"0\":0,\"1\":1}";

//      copy._clear ();
//      (void) copy._clone (src);

//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.length ()",
//                                    static_cast<size_t> (1),
//                                    copy.size ());

//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.at length ()",
//                                    static_cast<size_t> (1),
//                                    copy[L"2"].size ());

//      CPPUNIT_ASSERT_MESSAGE ("copy[L\"2\"].parent () == & copy",
//                              copy[L"2"].parent () == & copy);
    }

    virtual void
    test_type () //override
    {
//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("value::type ()",
//                                    value::object_t,
//                                    object ().type ());
    }

    void
    test_operator_assign_wchar_t_ptr ()
    {
//      object o (L"{\"0\":0,\"1\":1}");
//      o = L"{\"3\":3}";

//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("o.length ()",
//                                    static_cast<size_t> (1),
//                                    o.size ());
    }

    void
    test_operator_assign_initializer_list ()
    {
//      object o (L"{\"0\":0,\"1\":1}");
//      o = { { L"3", new number (static_cast<long long> (3)) } };

//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("o.length ()",
//                                    static_cast<size_t> (1),
//                                    o.size ());
    }

    /**
     * 2.
     *
     * @brief suite
     * @return
     *
    static CppUnit::Test*
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json object test");

      // 0.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_erase", &json_object_test::test__erase));
      // 1.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_smoke", &json_object_test::test_ctor_dtor));
      // 2.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_assign_all_values", &json_object_test::test_assign_all_values));
      // 3.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_key", &json_object_test::test_key));
      // 4.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test__parse", &json_object_test::test__parse));
      // 5.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_operator_at_key", &json_object_test::test_operator_at_key));
      // 7.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_const_operator_at_key", &json_object_test::test_const_operator_at_key));
      // 8.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_operator_at_index", &json_object_test::test_operator_at_index));
      // 9.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_const_operator_at_index", &json_object_test::test_const_operator_at_index));
      // 10.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test__pair", &json_object_test::test__pair));
      // 11.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test__clear", &json_object_test::test__clear));
      // 12.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_strLength", &json_object_test::test_str_length));
      // 13.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test__to_string", &json_object_test::test__to_string));
      // 14.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_count", &json_object_test::test_count));
      // 15.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test__assign_value_ptr_value_ptr", &json_object_test::test__assign_value_ptr_value_ptr));
      // 16.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test__clone_const_value_ref", &json_object_test::test__clone_const_value_ref));
      // 17.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_type", &json_object_test::test_type));
      // 18.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_operator_assign_wchar_t_ptr", &json_object_test::test_operator_assign_wchar_t_ptr));
      // 19.  s->addTest (new CppUnit::TestCaller<json_object_test> ("test_operator_assign_initializer_list", &json_object_test::test_operator_assign_initializer_list));

       return s;
    }*/
  };
} // Namespace json
} // Namespace format
#endif // JSON_OBJECT_TEST_H
