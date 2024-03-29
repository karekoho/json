﻿#ifndef JSON_ARRAY_TEST
#define JSON_ARRAY_TEST

#include "unit_test.h"
#include "json_mock_value.h"

namespace format
{
  namespace json
  {
    namespace test
    {
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test_strValue", &json_array_test::test__to_string));
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test_strValue", &json_array_test::test_str_length));
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test_ctor_dtor", &json_array_test::test_ctor_dtor));
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test_parse", &json_array_test::test__parse));
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test_index", &json_array_test::test_index));
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test_operator_at_key", &json_array_test::test_operator_at_key));
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test_const_operator_at_key", &json_array_test::test_const_operator_at_key));
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test_operator_at_index", &json_array_test::test_operator_at_index));
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test_const_operator_at_index", &json_array_test::test_const_operator_at_index));
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test_assign_all_values", &json_array_test::test_assign_all_values));
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test__clear", &json_array_test::test__clear));
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test_erase", &json_array_test::test__erase));
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test_count", &json_array_test::test_count));
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test__assign_value_ptr_value_ptr", &json_array_test::test__assign_value_ptr_value_ptr));
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test__clone_const_value_ref", &json_array_test::test__clone_const_value_ref));
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test_type", &json_array_test::test_type));
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test_operator_assign_wchar_t_ptr", &json_array_test::test_operator_assign_wchar_t_ptr));
      // s->addTest (new CppUnit::TestCaller<json_array_test> ("test_operator_assign_initializer_list", &json_array_test::test_operator_assign_initializer_list));

      class array_test: public unit_test {};

      TEST_F (array_test, ctor_dtor)
      {
        const wchar_t * json_text = L"[ 1, [ 2, 3 ] ]";
        mock_array src = json_text;

        json parent;

        mock_array a[] = {
          mock_array (),
          mock_array (L"[]"),
          mock_array (& parent),
          mock_array { new mock_array { new number () } }, // [[0]]
          mock_array (json_text),
          mock_array (src) // 5.
        };
  //      array src = L"[true]";
  //      array copy = src;

  //      CPPUNIT_ASSERT_MESSAGE ("array",
  //                              & copy != & src);

  //      CPPUNIT_ASSERT_MESSAGE ("array",
  //                              & copy[(size_t) 0] != & src[(size_t) 0]);

  //      CPPUNIT_ASSERT_EQUAL_MESSAGE ("array::count ()",
  //                                    (size_t) 1,
  //                                    copy.length ());

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("array::count ()", static_cast<size_t> (1), a[3].size ());
        ///
        ASSERT_THAT (a[3].size (), Eq (1));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("array[index][index].type ()", value::number_t, a[3][static_cast<size_t> (0)][static_cast<size_t> (0)].type ());
        ///
        ASSERT_THAT (a[3][static_cast<size_t> (0)][static_cast<size_t> (0)].type (), Eq (value::number_t));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("a[3][(size_t) 0].parent ()", dynamic_cast<json *> (& a[3]), a[3][static_cast<size_t> (0)].parent ());
        ///
        ASSERT_THAT (a[3][static_cast<size_t> (0)].parent (), dynamic_cast<json *> (& a[3]));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("array at size", (size_t) 2, a[4][1].size ());
        ///
        ASSERT_THAT (a[4][1].size (), Eq (2));

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("array copy at size", (size_t) 2, a[5][1].size ());
        ///
        ASSERT_THAT (a[5][1].size (), Eq (2));
      }

      TEST_F (array_test, _parse)
      {
        struct assert {
          const wchar_t *startp;
          size_t size;
          value::value_t type;
          int moveback;
          int assert_status;
        };

        std::vector<struct assert> test = {
          { L"[]", 0, value::value_t::array_t, 0, PASS_T },
          { L"[ ] ", 0, value::value_t::array_t, 1, PASS_T },
          { L"[\t] ", 0, value::value_t::array_t, 1, PASS_T },
          { L"[\r] ", 0, value::value_t::array_t, 1, PASS_T },
          { L"[\n] ", 0, value::value_t::array_t, 1, PASS_T },
          { L"[\"x\"]", 1, value::value_t::array_t, 0, PASS_T },
          { L"[\"x\",\"x\"] ", 2, value::value_t::array_t, 1, PASS_T },
          { L"[\"x\",\"x\",[\"x\"]] ", 3,  value::value_t::array_t, 1, PASS_T },
          //{ L"[\"x\",\"x\",[\"x\"],\"x\"]", 4,  value::value_t::array_t, 0, PASS },

          // errors
          { L"[", 0, value::value_t::undefined_t, 0, FAIL_T },
          { L"[ ", 0, value::value_t::undefined_t, 0, FAIL_T },
          { L"]", 0, value::value_t::undefined_t, 0, FAIL_T },
          { L"[, ", 0, value::value_t::undefined_t, 0, FAIL_T },
          { L"[ x ", 0, value::value_t::undefined_t, 0, FAIL_T },
          { L"", 0, value::value_t::undefined_t, 0, FAIL_T },
          { L" ", 0, value::value_t::undefined_t, 0, FAIL_T },
          { L"x", 0, value::value_t::undefined_t, 0, FAIL_T },
        };

        json *p[] = { nullptr, new json () };
        mock_array *a = nullptr;

        TEST_IT_START
            for (size_t pidx = 0; pidx < 2; pidx++)
              {
                const wchar_t *startp = (*it).startp;
                size_t charc = wcslen (startp);
                a = new mock_array (p[pidx]);

                const wchar_t *readp = a->_parse (startp);

                // Original assertion:
                ///ASSERT_EQUAL_IDX ("array.readp", (startp + charc) - (*it).moveback, readp);
                ///ASSERT_EQUAL_IDX ("*(array.readp - 1)", L']', *(readp - 1));
                ///ASSERT_EQUAL_IDX ("array.size", (*it).size, a->size ());
                ///
                ASSERT_THAT (readp, Eq ((startp + charc) - (*it).moveback))
                    << ERR_IDX_MSG << _idx[0];

                ASSERT_THAT (*(readp - 1),  Eq (L']'))
                    << ERR_IDX_MSG << _idx[0];

                ASSERT_THAT (a->size (), Eq ((*it).size))
                    << ERR_IDX_MSG << _idx[0];

                delete a;
              }
            }
          catch (format::json::json_syntax_error & se)
            {
              this->_errorc[ACTUAL]++; std::cerr << se.what () << std::endl;
              delete a;
            }
          }

        delete p[1];

        // Original assertion:
        ///(void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]);
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
        ///
        ASSERT_THAT (this->_errorc[ACTUAL], Eq (this->_errorc[EXPECTED]));
      }

      TEST_F (array_test, index)
      {
        struct assert {
          const wchar_t *startp;
          int assert_status;
        };

        std::vector<struct assert > test = {
          { L"[]", PASS_T },
          { L"[ ] ", PASS_T },
          { L"[\"a\",\"b\",\"c\"]", PASS_T },
        };

        TEST_IT_START
          const wchar_t *startp = (*it).startp;
          mock_array *a = new mock_array ();

          (void) a->_parse (startp);

          if (a->size () > 0)
            {
              for (size_t idx = 0; idx < a->_element_list.size (); idx++)
                {
                  value *v = a->_element_list.at (idx);
                  // Orinal assertion:
                  ///ASSERT_EQUAL_IDX ("value.index", idx, v->index ());
                  ///
                  ASSERT_THAT (v->index (), Eq (idx))
                      << ERR_IDX_MSG << _idx[0];
                }
            }
          delete a;
        TEST_IT_END
      }

      TEST_F (array_test, assign_all_values)
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
          int assert_status[2];
        };

        mock_array a (L"[true,false]");

        std::vector<struct assert > test = {
          { & a, value::array_t, L"key_2",  0, 1,  { PASS_T, PASS_T } },
          { __VALUE[value::object_t], value::object_t, L"key_1",  0, 2,  { PASS_T, FAIL_T } },
  //        { __VALUE[value::string_t], value::string_t, L"key_3",  0, 3,  { PASS, PASS, FAIL } },
  //        { __VALUE[value::number_t], value::number_t, L"key_4",  0, 4, { PASS, PASS, FAIL } },
  //        { __VALUE[value::boolean_t], value::boolean_t, L"key_5",  0, 5, { PASS, PASS, FAIL } },
  //        { __VALUE[value::null_t], value::null_t, L"key_6",  0, 6, { PASS, PASS, FAIL } }
        };

          mock_array *old_value = nullptr;

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
                      old_value = new mock_array (parents[pidx]);
                      old_value->_set_key ((*it).key, wcslen ((*it).key));

                      if ((*it).new_value->type () == value::array_t)
                        *old_value = *(dynamic_cast<mock_array *>((*it).new_value));
                      else
                        *(dynamic_cast<value *>(old_value)) = *(*it).new_value;

                      json *parent = parents[pidx]; // old_value->_parent;

                      if (parent)
                        {
                          // Original assertion:
                          ///ASSERT_EQUAL_IDX ("old_value.parent.count ()", (*it).count, parent->size ());
                          ///
                          ASSERT_THAT (parent->size (), Eq ((*it).count))
                              << ERR_IDX_MSG << _idx[0];

                          value & ov =  object_parent[(*it).key];

                          // Original assertion:
                          ///ASSERT_EQUAL_IDX ("obj_parent[key].type", ov.type (), (*it).type);
                          ///
                          ASSERT_THAT (ov.type (), Eq ((*it).type))
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
                  catch (format::json::json_error & se)
                    {
                      this->_errorc[ACTUAL]++; std::cerr << se.what () << std::endl;
                      delete old_value;
                    }
                }

              // Original assertion:
              ///(void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]); \
              ///CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
              ///
              ASSERT_THAT (this->_errorc[ACTUAL], Eq (this->_errorc[EXPECTED]));
            }
      }

      TEST_F (array_test, operator_at_key)
      {
        mock_array a;
        a._element_list.push_back (new boolean (true));

        struct assert
        {
          const wchar_t *key;
          value::value_t type;
          int assert_status;
        };

        std::vector<struct assert> test = {
          { L"0", value::value_t::boolean_t, PASS_T },
          { L"1", value::value_t::undefined_t, PASS_T },
          { L"x", value::value_t::boolean_t, PASS_T }   // Converted to 0
        };

        TEST_IT_START

            value & v = a[((*it).key)]; // Array::_at("key") tries to convert "key" to size_t

            // Original assertion:
            ///ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());
            ///
            ASSERT_THAT (v.type (), Eq ((*it).type))
                << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (array_test, const_operator_at_key)
      {
        const array a = L"[ true ]";

        struct assert
        {
          const wchar_t *key;
          value::value_t type;
          int assert_status;
        };

        std::vector<struct assert> test = {
          { L"0", value::value_t::boolean_t, PASS_T },
          { L"1", value::value_t::undefined_t, FAIL_T },
        };

        TEST_IT_START

            const value & v = a[((*it).key)]; // Array::_at("key") tries to convert "key" to size_t

            // Original assertion:
            ///ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());
            ///
            ASSERT_THAT (v.type (), Eq ((*it).type))
                << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (array_test, operator_at_index)
      {
        mock_array a;
        a._element_list.push_back (new boolean (true));

        struct assert
        {
          size_t index;
          value::value_t type;
          int assert_status;
        };

        std::vector<struct assert> test = {
          { 0, value::value_t::boolean_t, PASS_T },
          { 1, value::value_t::undefined_t, PASS_T }
        };

        TEST_IT_START

          value & v = a [(*it).index];

          // Original assertion:
          ///ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());
          ///
          ASSERT_THAT (v.type (), Eq ((*it).type))
              << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (array_test, const_operator_at_index)
      {
        const array a = L"[ true ]";

        struct assert
        {
          size_t index;
          value::value_t type;
          int assert_status;
        };

        std::vector<struct assert> test = {
          { 0, value::value_t::boolean_t, PASS_T },
          { 1, value::value_t::undefined_t, FAIL_T }
        };

        TEST_IT_START

          const value & v = a [(*it).index];

          // Original assertion:
          ///ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());
          ///
          ASSERT_THAT (v.type (), Eq ((*it).type))
              << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (array_test, _clear)
      {
        mock_array a = L"[true, false]";
        a._clear ();

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("array._element_list.size ()", static_cast<size_t> (0), a._element_list.size ());
        ///
        ASSERT_THAT (a._element_list.size (), Eq (0));
      }

      TEST_F (array_test, str_length)
      {
        // assert: [] = 2,
        // assert: [null] = 2 + 4 = 6,
        // assert: [null,null] = 2 + (2 * 4) + 1 = 11;
        // assert: [null,[]] = 2 + 4 + 1 + 2 = 9

        struct assert
        {
          const wchar_t *input;
          size_t length;
          int assert_status;
        };

        std::vector<struct assert> test = {
          { L"[]", 2, PASS_T },
          { L"[null]", 6, PASS_T },
          { L"[null,null]", 11, PASS_T },
          { L"[null,[]]", 9, PASS_T },
        };

        TEST_IT_START

            mock_array a = (*it).input;

            // Original assertion:
            ///ASSERT_EQUAL_IDX ("a.strLength ()", (*it).length, a._str_length ());
            ///
            ASSERT_THAT (a._str_length (), Eq ((*it).length))
                << ERR_IDX_MSG << _idx[0];

        TEST_IT_END
      }

      TEST_F (array_test, _to_string)
      {
        mock_array p;

        json *parent[] = {
          nullptr, & p
        };

        struct assert
        {
          const wchar_t *input;
          const wchar_t *output[2];
          int assert_status;
        };

        wchar_t * _str_value[2] = { nullptr, nullptr };

        std::vector<struct assert> test = {
          { L"[]",
            { L"[]",  // Without parent
              L"[\"x\",[]" }, PASS_T },  // <-- last closing ] intentionally missing
          { L"[false,[true]]",
            { L"[false,[true]]",  // Without parent
              L"[\"x\",[false,[true]]" }, PASS_T },  // <-- last closing ] intentionally missing
        };

        TEST_IT_START

            for (size_t pidx = 0; pidx < 2; pidx++)
              {
                wchar_t *str_value = nullptr;

                size_t len = wcslen ((*it).output[pidx]);

                mock_array a;

                a._parent = parent[pidx];

                if (a._parent)
                  {
                    str_value = new wchar_t[len +1 ] ();
                    str_value = wcsncpy (str_value,  L"[\"x\",", 5);

                    _str_value[BEGIN]   = str_value;
                    _str_value[OFFSET]  = str_value + 5;
                  }

                (void) a._parse ((*it).input);

                const wchar_t *output = a._to_string (a._parent ? _str_value[OFFSET] : nullptr);

                if (a._parent == nullptr)
                  {
                    // Original assertion:
                    ///ASSERT_EQUAL_IDX ("strlen (output)", len, wcslen (output));
                    ///CPPUNIT_ASSERT_MESSAGE ("strcmp (output, (*it).output[0])", wcscmp (output, (*it).output[0]) == 0);
                    ///
                    ASSERT_THAT (wcslen (output), Eq (len))
                        << ERR_IDX_MSG << _idx[0];

                    ASSERT_THAT (output, StrEq ((*it).output[0]))
                        << ERR_IDX_MSG << _idx[0];
                  }
                else
                  {
                    // Original assertion:
                    ///ASSERT_EQUAL_IDX ("strlen (p._str_value[BEGIN])", len, wcslen (_str_value[BEGIN]));
                    ///CPPUNIT_ASSERT_MESSAGE ("strcmp (output, (*it).output[1])", wcscmp (_str_value[BEGIN], (*it).output[1]) == 0);
                    ///
                    ASSERT_THAT (wcslen (_str_value[BEGIN]), Eq (len))
                        << ERR_IDX_MSG << _idx[0];

                    ASSERT_THAT (_str_value[BEGIN], StrEq ((*it).output[1]))
                        << ERR_IDX_MSG << _idx[0];
                  }

                if (a._parent)
                  {
                    delete[] str_value;
                    _str_value[BEGIN] = nullptr;
                  }
                else
                  delete [] output;
              }
        TEST_IT_END
      }

      TEST_F (array_test, _erase)
      {
        mock_array a;

        value *v[3]= {
          new boolean (),
          new boolean (),
          new boolean ()
        };

        mock_array::_set_index (v[0], 0);
        mock_array::_set_index (v[1], 1);
        mock_array::_set_index (v[2], 2);

        a._element_list = { v[0], v[1] };

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
             (void) a._erase (*(*it).val);
             size_t size = a.size ();

             // Original assertion:
             ///ASSERT_EQUAL_IDX ("array::count ()", (*it).size, size);
             ///
             ASSERT_THAT (size, Eq ((*it).size))
                 << ERR_IDX_MSG << _idx[0];

         TEST_IT_END

         // TODO: move to test_operator_assign_undefined
         // Original assertion:
         ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("array::count ()", static_cast<size_t> (1), (array (L"[0,1]") [static_cast<size_t> (0)] = undefined ()).size ());
         ///
         ASSERT_THAT ((array (L"[0,1]") [static_cast<size_t> (0)] = undefined ()).size (), Eq (1));
         delete v[2];
      }

      TEST_F (array_test, count)
      {
        array a (L"[1]");

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("array::count ()", static_cast<size_t> (1), a.size ());
        ///
        ASSERT_THAT (a.size (), Eq (1));
      }

      TEST_F (array_test, type)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("value::type ()", value::array_t, array ().type ());
        ///
        ASSERT_THAT (array ().type (), Eq (value::array_t));
      }

      TEST_F (array_test, _assign_value_ptr_value_ptr)
      {
        mock_array a = L"[false]";

        boolean *nv = new boolean (true);

        a._assign (& a[static_cast<size_t> (0)], nv);

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("nv->index () == 0", nv->index () == 0);
        ///CPPUNIT_ASSERT_MESSAGE ("& a[(size_t) 0] == nv", & a[static_cast<size_t> (0)] == nv);
        ///CPPUNIT_ASSERT_MESSAGE ("a[(size_t) 0].parent () == & a", a[static_cast<size_t> (0)].parent () == & a);
        ///
        ASSERT_THAT (nv->index (), Eq (0));
        ASSERT_THAT (& a[static_cast<size_t> (0)], nv);
        ASSERT_THAT (a[static_cast<size_t> (0)].parent (), & a);
      }

      TEST_F (array_test, operator_assign_wchar_t_ptr)
      {
        mock_array src = L"[1,[2,3]]";
        mock_array copy = L"[0,1,2]";

        copy._clear ();
        (void) copy._clone (src);

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.length ()", static_cast<size_t> (2), copy.size ());
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.at length ()", static_cast<size_t> (2), copy[1].size ());
        ///CPPUNIT_ASSERT_MESSAGE ("copy[(size_t) 0].parent () == & copy", copy[static_cast<size_t> (0)].parent () == & copy);
        ///
        ASSERT_THAT (copy.size (), 2);
        ASSERT_THAT (copy[1].size (), 2);
        ASSERT_THAT (copy[static_cast<size_t> (0)].parent (), & copy);
      }

      TEST_F (array_test, operator_assign_initializer_list)
      {
        array a (L"[0,1]");
        a = L"[2]";

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("a.length ()", static_cast<size_t> (1), a.size ());
        ///
        ASSERT_THAT (a.size (), 1);
      }
    }
  } // Namespace json
} // Namespace format
#endif // JSON_ARRAY_TEST

