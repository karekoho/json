#ifndef JSON_ARRAY_TEST
#define JSON_ARRAY_TEST

#include "json_test.h"

namespace format
{
  namespace json
  {
  /**
   * 3.
   * @brief The json_array_test class
   */
  class json_array_test : public json_test
  {
  public:

    virtual void
    test_ctor_dtor () override
    {
      const wchar_t * json_text = L"[ 1, [ 2, 3 ] ]";
      array src = json_text;

      json parent;

      array a[] = {
        array (),
        array (L"[]"),
        array (& parent),
        array { new array { new number () } }, // [[0]]
        array (json_text),
        array (src) // 5.
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

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("array::count ()",
                                    static_cast<size_t> (1),
                                    a[3].size ());

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("array[index][index].type ()",
                                    value::number_t,
                                    a[3][static_cast<size_t> (0)][static_cast<size_t> (0)].type ());

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("a[3][(size_t) 0].parent ()",
                                    dynamic_cast<json *> (& a[3]),
                                    a[3][static_cast<size_t> (0)].parent ());

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("array at size",
                                    (size_t) 2, a[4][1].size ());

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("array copy at size",
                                    (size_t) 2, a[5][1].size ());
    }

    virtual void
    test__parse () override
    {
      struct assert {
        const wchar_t *startp;
        size_t size;
        value::value_t type;
        int moveback;
        int assert_status;
      };

      std::vector<struct assert> test = {
        { L"[]", 0, value::value_t::array_t, 0, PASS },
        { L"[ ] ", 0, value::value_t::array_t, 1, PASS },
        { L"[\t] ", 0, value::value_t::array_t, 1, PASS },
        { L"[\r] ", 0, value::value_t::array_t, 1, PASS },
        { L"[\n] ", 0, value::value_t::array_t, 1, PASS },
        { L"[\"x\"]", 1, value::value_t::array_t, 0, PASS },
        { L"[\"x\",\"x\"] ", 2, value::value_t::array_t, 1, PASS },
        { L"[\"x\",\"x\",[\"x\"]] ", 3,  value::value_t::array_t, 1, PASS },
        //{ L"[\"x\",\"x\",[\"x\"],\"x\"]", 4,  value::value_t::array_t, 0, PASS },

        // errors
        { L"[", 0, value::value_t::undefined_t, 0, FAIL },
        { L"[ ", 0, value::value_t::undefined_t, 0, FAIL },
        { L"]", 0, value::value_t::undefined_t, 0, FAIL },
        { L"[, ", 0, value::value_t::undefined_t, 0, FAIL },
        { L"[ x ", 0, value::value_t::undefined_t, 0, FAIL },
        { L"", 0, value::value_t::undefined_t, 0, FAIL },
        { L" ", 0, value::value_t::undefined_t, 0, FAIL },
        { L"x", 0, value::value_t::undefined_t, 0, FAIL },
      };

      json *p[] = { nullptr, new json () };
      array *a = nullptr;

      TEST_IT_START
          for (size_t pidx = 0; pidx < 2; pidx++)
            {
              const wchar_t *startp = (*it).startp;
              size_t charc = wcslen (startp);
              a = new array (p[pidx]);

              const wchar_t *readp = a->_parse (startp);

              ASSERT_EQUAL_IDX ("array.readp", (startp + charc) - (*it).moveback, readp);
              ASSERT_EQUAL_IDX ("*(array.readp - 1)", L']', *(readp - 1));
              ASSERT_EQUAL_IDX ("array.size", (*it).size, a->size ());

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

      (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]);
      CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
    }

    void
    test_index ()
    {
      struct assert {
        const wchar_t *startp;
        int assert_status;
      };

      std::vector<struct assert > test = {
        { L"[]", PASS },
        { L"[ ] ", PASS },
        { L"[\"a\",\"b\",\"c\"]", PASS },
      };

      TEST_IT_START
        const wchar_t *startp = (*it).startp;
        array *a = new array ();

        (void) a->_parse (startp);

        if (a->size () > 0)
          {
            for (size_t idx = 0; idx < a->_element_list.size (); idx++)
              {
                value *v = a->_element_list.at (idx);
                ASSERT_EQUAL_IDX ("value.index", idx, v->index ());
              }
          }
        delete a;
      TEST_IT_END
    }

    virtual void
    test_assign_all_values () override
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

      array a (L"[true,false]");

      std::vector<struct assert > test = {
        { & a, value::array_t, L"key_2",  0, 1,  { PASS, PASS } },
        { __VALUE[value::object_t], value::object_t, L"key_1",  0, 2,  { PASS, FAIL } },
//        { __VALUE[value::string_t], value::string_t, L"key_3",  0, 3,  { PASS, PASS, FAIL } },
//        { __VALUE[value::number_t], value::number_t, L"key_4",  0, 4, { PASS, PASS, FAIL } },
//        { __VALUE[value::boolean_t], value::boolean_t, L"key_5",  0, 5, { PASS, PASS, FAIL } },
//        { __VALUE[value::null_t], value::null_t, L"key_6",  0, 6, { PASS, PASS, FAIL } }
      };

        array *old_value = nullptr;

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
                    old_value = new array (parents[pidx]);
                    old_value->_set_key ((*it).key, wcslen ((*it).key));

                    if ((*it).new_value->type () == value::array_t)
                      *old_value = *(dynamic_cast<array *>((*it).new_value));
                    else
                      *(dynamic_cast<value *>(old_value)) = *(*it).new_value;

                    json *parent = parents[pidx]; // old_value->_parent;

                    if (parent)
                      {
                        ASSERT_EQUAL_IDX ("old_value.parent.count ()", (*it).count, parent->size ());
                        value & ov =  object_parent[(*it).key];
                        ASSERT_EQUAL_IDX ("obj_parent[key].type", ov.type (), (*it).type);
                      }
                    else
                      {
                        ASSERT_EQUAL_IDX ("old_value.size ()", static_cast<size_t> (2), old_value->size ());
                        delete old_value;
                      }
                  }
                catch (format::json::json_error & se)
                  {
                    this->_errorc[ACTUAL]++; std::cerr << se.what () << std::endl;
                    delete old_value;
                  }
              }

            (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]); \
            CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
          }
    }

    virtual void
    test_operator_at_key () override
    {
      array a;
      a._element_list.push_back (new boolean (true));

      struct assert
      {
        const wchar_t *key;
        value::value_t type;
        int assert_status;
      };

      std::vector<struct assert> test = {
        { L"0", value::value_t::boolean_t, PASS },
        { L"1", value::value_t::undefined_t, PASS },
        { L"x", value::value_t::boolean_t, PASS }   // Converted to 0
      };

      TEST_IT_START

          value & v = a[((*it).key)]; // Array::_at("key") tries to convert "key" to size_t

          ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());

      TEST_IT_END
    }

    virtual void
    test_const_operator_at_key () override
    {
      const array a = L"[ true ]";

      struct assert
      {
        const wchar_t *key;
        value::value_t type;
        int assert_status;
      };

      std::vector<struct assert> test = {
        { L"0", value::value_t::boolean_t, PASS },
        { L"1", value::value_t::undefined_t, FAIL },
      };

      TEST_IT_START

          const value & v = a[((*it).key)]; // Array::_at("key") tries to convert "key" to size_t

          ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());

      TEST_IT_END
    }

    virtual void
    test_operator_at_index () override
    {
      array a;
      a._element_list.push_back (new boolean (true));

      struct assert
      {
        size_t index;
        value::value_t type;
        int assert_status;
      };

      std::vector<struct assert> test = {
        { 0, value::value_t::boolean_t, PASS },
        { 1, value::value_t::undefined_t, PASS }
      };

      TEST_IT_START

        value & v = a [(*it).index];

        ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());

      TEST_IT_END
    }

    virtual void
    test_const_operator_at_index () override
    {
      const array a = L"[ true ]";

      struct assert
      {
        size_t index;
        value::value_t type;
        int assert_status;
      };

      std::vector<struct assert> test = {
        { 0, value::value_t::boolean_t, PASS },
        { 1, value::value_t::undefined_t, FAIL }
      };

      TEST_IT_START

        const value & v = a [(*it).index];

        ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());

      TEST_IT_END
    }

    virtual void
    test__clear () override
    {
      array a = L"[true, false]";
      a._clear ();

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("array._element_list.size ()", static_cast<size_t> (0), a._element_list.size ());
    }


    virtual void
    test_str_length () override
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
        { L"[]", 2, PASS },
        { L"[null]", 6, PASS },
        { L"[null,null]", 11, PASS },
        { L"[null,[]]", 9, PASS },
      };

      TEST_IT_START

          array a = (*it).input;

          ASSERT_EQUAL_IDX ("a.strLength ()", (*it).length, a._str_length ());

      TEST_IT_END
    }

    virtual void
    test__to_string () override
    {
      array p;

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
            L"[\"x\",[]" }, PASS },  // <-- last closing ] intentionally missing
        { L"[false,[true]]",
          { L"[false,[true]]",  // Without parent
            L"[\"x\",[false,[true]]" }, PASS },  // <-- last closing ] intentionally missing
      };

      TEST_IT_START

          for (size_t pidx = 0; pidx < 2; pidx++)
            {
              wchar_t *str_value = nullptr;

              size_t len = wcslen ((*it).output[pidx]);

              array a;

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
                  ASSERT_EQUAL_IDX ("strlen (output)", len, wcslen (output));
                  CPPUNIT_ASSERT_MESSAGE ("strcmp (output, (*it).output[0])", wcscmp (output, (*it).output[0]) == 0);
                }
              else
                {
                  ASSERT_EQUAL_IDX ("strlen (p._str_value[BEGIN])", len, wcslen (_str_value[BEGIN]));
                  CPPUNIT_ASSERT_MESSAGE ("strcmp (output, (*it).output[1])", wcscmp (_str_value[BEGIN], (*it).output[1]) == 0);
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

    virtual void
    test__erase () override
    {
      array a;

      value *v[3]= {
        new boolean (),
        new boolean (),
        new boolean ()
      };

      __call__set_index (v[0], 0);
      __call__set_index (v[1], 1);
      __call__set_index (v[2], 2);

      a._element_list = { v[0], v[1] };

      struct assert
      {
        value *val;
        size_t size;
        int assert_status;
      };

       std::vector<struct assert> test = {
          { v[2], 2, PASS },
          { v[1], 1, PASS },
          { v[0], 0, PASS },
       };

       TEST_IT_START
           (void) a._erase (*(*it).val);
           size_t size = a.size ();

           ASSERT_EQUAL_IDX ("array::count ()", (*it).size, size);
       TEST_IT_END

       // TODO: move to test_operator_assign_undefined
       CPPUNIT_ASSERT_EQUAL_MESSAGE ("array::count ()",
                                     static_cast<size_t> (1),
                                     (array (L"[0,1]") [static_cast<size_t> (0)] = undefined ()).size ());
       delete v[2];
    }

    virtual void
    test_count () override
    {
      array a (L"[1]");
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("array::count ()",
                                    static_cast<size_t> (1),
                                    a.size ());
    }

    virtual void
    test_type () override
    {
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("value::type ()",
                                    value::array_t,
                                    array ().type ());
    }

    virtual void
    test__assign_value_ptr_value_ptr () override
    {
      array a = L"[false]";

      boolean *nv = new boolean (true);

      a._assign (& a[static_cast<size_t> (0)], nv);

      CPPUNIT_ASSERT_MESSAGE ("nv->index () == 0",
                              nv->index () == 0);

      CPPUNIT_ASSERT_MESSAGE ("& a[(size_t) 0] == nv",
                              & a[static_cast<size_t> (0)] == nv);

      CPPUNIT_ASSERT_MESSAGE ("a[(size_t) 0].parent () == & a",
                              a[static_cast<size_t> (0)].parent () == & a);
    }

    virtual void
    test__clone_const_value_ref () override
    {
      array src = L"[1,[2,3]]";
      array copy = L"[0,1,2]";

      copy._clear ();
      (void) copy._clone (src);

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.length ()",
                                    static_cast<size_t> (2),
                                    copy.size ());

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.at length ()",
                                    static_cast<size_t> (2),
                                    copy[1].size ());

      CPPUNIT_ASSERT_MESSAGE ("copy[(size_t) 0].parent () == & copy",
                              copy[static_cast<size_t> (0)].parent () == & copy);
    }

    void
    test_operator_assign_wchar_t_ptr ()
    {
      array a (L"[0,1]");
      a = L"[2]";

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("a.length ()",
                                    static_cast<size_t> (1),
                                    a.size ());
    }

    void
    test_operator_assign_initializer_list ()
    {
      array a (L"[0,1]");
      a = L"[2]";

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("a.length ()",
                                    static_cast<size_t> (1),
                                    a.size ());
    }

    /**
     * 3.
     * @brief suite
     * @return
     */
    static CppUnit::Test *
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json array test");

      /* 0. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_strValue", &json_array_test::test__to_string));
      /* 1. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_strValue", &json_array_test::test_str_length));
      /* 2. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_ctor_dtor", &json_array_test::test_ctor_dtor));
      /* 3. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_parse", &json_array_test::test__parse));
      /* 4. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_index", &json_array_test::test_index));
      /* 5. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_operator_at_key", &json_array_test::test_operator_at_key));
      /* 6. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_const_operator_at_key", &json_array_test::test_const_operator_at_key));
      /* 7. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_operator_at_index", &json_array_test::test_operator_at_index));
      /* 8. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_const_operator_at_index", &json_array_test::test_const_operator_at_index));
      /* 9. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_assign_all_values", &json_array_test::test_assign_all_values));
      /* 10. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test__clear", &json_array_test::test__clear));
      /* 11. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_erase", &json_array_test::test__erase));
      /* 12. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_count", &json_array_test::test_count));
      /* 13. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test__assign_value_ptr_value_ptr", &json_array_test::test__assign_value_ptr_value_ptr));
      /* 14. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test__clone_const_value_ref", &json_array_test::test__clone_const_value_ref));
      /* 15. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_type", &json_array_test::test_type));
      /* 16. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_operator_assign_wchar_t_ptr", &json_array_test::test_operator_assign_wchar_t_ptr));
      /* 17. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_operator_assign_initializer_list", &json_array_test::test_operator_assign_initializer_list));

      return s;
    }
  };
} // Namespace json
} // Namespace format
#endif // JSON_ARRAY_TEST

