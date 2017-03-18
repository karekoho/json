#ifndef JSON_OBJECT_TEST_H
#define JSON_OBJECT_TEST_H

#include "json_test.h"

namespace format
{
  /**
   * 2.
   * @brief The json_object_test class
   */
  class json_object_test : public json_test
  {
  public:

    virtual void
    test_ctor_dtor () override
    {
      json parent;

      object o[] = {
        object (),
        object (L"{}"),
        object (& parent),
        object {{ L"0", new object {{ L"0", new number () }} }} // {"0":{"0":0}}
      };

      object src  = L"{\"key\":true}";
      object copy = src;

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("object::type ()",
                                    json::object_t, src.type ());

      CPPUNIT_ASSERT_MESSAGE ("object",
                              & copy != & src);

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.count ()",
                                    (size_t) 1,
                                    copy.count ());

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("object::count ()",
                                    (size_t) 1,
                                    o[3].count ());

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("object[key][key].type ()",
                                    value::number_t,
                                    o[3][L"0"][L"0"].type ());
    }

    virtual
    void test_parse_1 () override
    {
      struct assert {
        const wchar_t *startp;
        size_t size;
        value::value_t type;
        size_t moveback;
        int assert_status;
      };

      json *p[] = { 0, new json () };

      std::vector<struct assert > test = {
        { L"{}", 0, value::undefined_t, 0, PASS },
        { L"{ } ", 0, value::undefined_t, 1, PASS },
        { L"{\"k\":\"v\"} ", 1, value::string_t, 1, PASS },
        { L"{ \"k\" : \"v\" } ", 1, value::string_t, 1, PASS },
        { L"{\"k\":\"v\",\"q\":\"p\"} ", 2, value::string_t, 1, PASS },
        { L"{ \"k\": \"v\", \"q\" : \"p\",\"K\":\"v\" } ", 3, value::string_t, 1, PASS },
        { L"{ \"k\": \"p\" ,\"q\" : \"p\", \"K\" :\"v\",\"Q\":\"p\" } ", 4, value::string_t, 1, PASS },

        { L"{ \"k\" : { } }", 1, value::object_t, 0, PASS },
        { L"{ \"k\" : {\"kk\" : \"v\"}}", 1, value::object_t, 0, PASS },
        { L"{ \"k\" : {\"kk\" : {\"kkk\" : \"v\"}}", 1, value::object_t, 0, PASS },
        { L"{ \"k\" : null } ", 1, value::null_t, 1, PASS },

        // errors
        { L"", 0, value::undefined_t, 0, FAIL },   // json::syntax_error
        { L" ", 0, value::undefined_t, 0, FAIL },   // json::syntax_error
        { L"x", 0, value::undefined_t, 0, FAIL },   // json::syntax_error
        { L"{", 0, value::undefined_t, 0, FAIL },   // json::syntax_error
        { L"}", 0, value::undefined_t, 0, FAIL },   // json::syntax_error
        { L"{ , }", 0, value::undefined_t, 0, FAIL },   // json::syntax_error
        { L"{ : }", 0, value::undefined_t, 0, FAIL },   // json::syntax_error
      };

      object *o = 0;

      TEST_IT_START;
        for (int pidx = 0; pidx < 2; pidx++)
          {
            const wchar_t *startp = (*it).startp;

            size_t charc = wcslen (startp);

            o = new object (p[pidx]);

            const wchar_t *readp = o->_parse (startp);

            ASSERT_EQUAL_IDX ("value.readp", (startp + charc) - (*it).moveback, readp);
            ASSERT_EQUAL_IDX ("*(value.readp -1)", L'}', *(readp - 1));
            ASSERT_EQUAL_IDX ("value.size", (*it).size, o->count ());

            if (o->count () > 0)
              {
                object & oo = *o;

                ASSERT_EQUAL_IDX ("value.type", (*it).type, oo[L"k"].type ());
                ASSERT_EQUAL_IDX ("*(value.key)", (wchar_t) L'k', *(oo[(L"k")].key ()));
              }
            delete o;
          }
        }
       catch (format::json_syntax_error & se)
        {
          this->_errorc[ACTUAL]++; std::cerr << se.what () << std::endl;
          delete o;
        }
      }

      (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]); \
      CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);

      delete p[1];
    }

    void
    test_key ()
    {
      struct assert
      {
        const wchar_t *startp;
        int assert_status;
      };

      std::vector<struct assert > test = {
        { L"{}", PASS },
        { L"{ } ", PASS },
        { L"{\"key1\":\"v\",\"key2\":\"v\",\"key3\":\"v\"} ", PASS },
      };

      TEST_IT_START;
        const wchar_t *startp = (*it).startp;

        object *o = new object ();

        (void) o->_parse (startp);

        if (o->count () > 0)
          {
            size_t idx= 0;

            for (auto it = o->_member_list.begin (); it != o->_member_list.end (); ++it, idx++)
              {
                const wchar_t *k = (*it).first.c_str ();
                object & oo = *o;

                ASSERT_EQUAL_IDX ("value::key ()",
                                  0,
                                  wcscmp (k, oo[k].key ()));
              }
          }
        delete o;

      TEST_IT_END
    }

    virtual void
    test_operator_at_key () override
    {
      object o;

      o._member_list.emplace (L"0", new boolean (true));

      struct assert {
        const wchar_t *key;
        value::value_t type;
        int assert_status;
      };

      std::vector<struct assert> test = {
        { L"0", value::value_t::boolean_t, PASS },
        { L"1", value::value_t::undefined_t, PASS }
      };

      TEST_IT_START

        const value & v = o[((*it).key)];

        ASSERT_EQUAL_IDX ("value::type ()",
                          (*it).type,
                          v.type ());

      TEST_IT_END;
    }

    virtual void
    test_operator_at_index () override
    {
      object o;
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("o[size_t].type ()", value::undefined_t, o[(size_t) 0].type ());
    }

    void
    test__pair ()
    {
      object  p;

      struct assert
      {
        const wchar_t *startp;
        bool status;
        int assert_status;
      };

      std::vector<struct assert > test = {
        { L" \"foo\" : \"bar\" ", true, PASS },
        { L" }" , false , PASS },

        // errors
        { L" ", false, FAIL},            // json::syntax_error
        { L" \"foo  ", false, FAIL },    // json::syntax_error
        { L" \"foo\" ", false, FAIL },   // json::syntax_error
        { L" \"foo\" : ", false, SKIP }, // FAIL: json::syntax_error
      };

      object *o = 0;

      TEST_IT_START;
          const wchar_t *startp = (*it).startp;

          o = new object (& p);
          o->_readp = startp;

          bool status = o->_pair ();

          ASSERT_EQUAL_IDX ("status", (*it).status, status);

          delete o;
        }
      catch (format::json_syntax_error & se)
        {
          this->_errorc[ACTUAL]++; std::cerr << se.what () << std::endl;
           delete o;
         }
       }

       (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]);

       CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
    }

    virtual void
    test_assign_all_values () override
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
        int assert_status[2];
      };

      object o (L"{\"0\":true,\"1\":false}");

      std::vector<struct assert > test = {
        { & o,  value::object_t, L"0",  0, 1,  { PASS, PASS } },
        { __VALUE[value::array_t], value::array_t, L"1",  0, 2,  { PASS, FAIL } },
//        { __VALUE[value::string_t], value::string_t, L"2",  0, 3,  { PASS, FAIL } },
//        { __VALUE[value::number_t], value::number_t, L"3",  0, 4, { PASS, FAIL } },
//        { __VALUE[value::boolean_t], value::boolean_t, L"4",  0, 5, { PASS, FAIL } },
//        { __VALUE[value::null_t], value::null_t, L"5",  0, 6, { PASS, FAIL } }
      };

      object *old_value = 0;

      for (size_t pidx = 0; pidx < 2; pidx++)
        {
          this->_idx[0] = 0;

          for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++)
            {
              try
                {
                  if ((*it).assert_status[pidx] == SKIP) { continue; }
                  if ((*it).assert_status[pidx] > PASS) { this->_errorc[EXPECTED]++; }

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
                      ASSERT_EQUAL_IDX ("parent->count ()", (*it).count, parent->count ());
                      ASSERT_EQUAL_IDX ("obj_parent[key].type", object_parent[(*it).key].type (), (*it).type);
                    }
                  else
                    {
                      ASSERT_EQUAL_IDX ("old_value.size ()", (size_t) 2, old_value->count ());
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

          CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
        }
    }

    virtual void
    test__clear () override
    {
      object o = L"{\"a\":true,\"b\":false}";
      o._clear ();

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("object::_member_list.size ()",
                                    (size_t) 0,
                                    o._member_list.size ());
    }

    virtual void
    test_str_length () override
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
        { L"{}", 2, PASS },
        { L"{\"a\":null}", 10, PASS },
        { L"{\"a\":null,\"b\":null}", 19, PASS },
        { L"{\"a\":null,\"b\":{}}", 17, PASS }
      };

      TEST_IT_START

          object o = (*it).input;

          ASSERT_EQUAL_IDX ("object::str_length ()",
                            (*it).length,
                            o.str_length ());
      TEST_IT_END;
    }

    virtual void
    test_str_value () override
    {
      object p;

      json *parent[] = {
        0, &p
      };

      struct assert
      {
        const wchar_t *input;
        const wchar_t *output[2];
        int assert_status;
      };

      std::vector<struct assert> test = {
        { L"{}",
          { L"{}",  // Without parent
            L"{\"a\":null,\"b\":{}" }, PASS },  // <-- last closing } intentionally missing

        /// !!! UNORDERED MAP HAS KEYS ARE IN DIFFERENT ORDER !!!:
        /// {"c":null,"d":{}} --> {"d":{},"c":null}
        { L"{\"c\":null,\"d\":{}}",
          { L"{\"d\":{},\"c\":null}", // Without parent
            L"{\"a\":null,\"b\":{\"d\":{},\"c\":null}" }, PASS },  // <-- last closing ] intentionally missing
      };

      TEST_IT_START

        for (size_t pidx = 0; pidx < 2; pidx++)
          {
            wchar_t *str_value = 0;

            size_t len = wcslen ((*it).output[pidx]);

            object o (parent[pidx]);

            if (o.parent ())
              {
                str_value = new wchar_t[len +1 ] ();
                str_value = wcsncpy (str_value,  L"{\"a\":null,\"b\":", 14);

                p._str_value[BEGIN]   = str_value;
                p._str_value[OFFSET]  = str_value + 14;
              }

            (void) o._parse ((*it).input);

            const wchar_t *output = o.str_value (o._parent ? p._str_value[OFFSET] : 0);

            if (o._parent == 0)
              {
                ASSERT_EQUAL_IDX ("strlen (output)", len, wcslen (output));
                CPPUNIT_ASSERT_MESSAGE ("strcmp (output, (*it).output[0])", wcscmp (output, (*it).output[0]) == 0);
              }
            else
              {
                ASSERT_EQUAL_IDX ("strlen (p._str_value[BEGIN])", len, wcslen (p._str_value[BEGIN]));
                CPPUNIT_ASSERT_MESSAGE ("strcmp (output, (*it).output[1])", wcscmp (p._str_value[BEGIN], (*it).output[1]) == 0);
              }
            if (o._parent)
              {
                delete[] str_value;
                p._str_value[BEGIN] = 0;
              }
        }

      TEST_IT_END;
    }

    virtual void
    test_erase () override
    {
      object o;

      value *v[3]= {
        new boolean (),
        new boolean (),
        new boolean ()
      };

      call__set_key__ (v[0], L"key_1", 5);
      call__set_key__ (v[1], L"key_2", 5);
      call__set_key__ (v[2], L"key_3", 5);

      o._member_list = { { v[0]->key (), v[0] }, { v[1]->key (), v[1] } };

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

        (void) o.erase (*(*it).val);
        size_t size = o.count ();

        ASSERT_EQUAL_IDX ("o.count ()", (*it).size, size);

      TEST_IT_END;

      // TODO: move to test_operator_assign_undefined
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("object.count ()",
                                    (size_t) 1,
                                    (object (L"{\"0\":0,\"1\":1}") [L"0"] = undefined ()).count ());
      delete v[2];
    }

    virtual void
    test_count () override
    {
      object o = L"{\"1\":1}";
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("object::count ()",
                                    (size_t) 1,
                                    o.count ());
    }

    /**
     * 2.
     *
     * @brief suite
     * @return
     */
    static CppUnit::Test*
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json object test");

      /* 0. */ s->addTest (new CppUnit::TestCaller<json_object_test> ("test_erase", &json_object_test::test_erase));
      /* 1. */ s->addTest (new CppUnit::TestCaller<json_object_test> ("test_smoke", &json_object_test::test_ctor_dtor));
      /* 2. */ s->addTest (new CppUnit::TestCaller<json_object_test> ("test_assign_all_values", &json_object_test::test_assign_all_values));
      /* 3. */ s->addTest (new CppUnit::TestCaller<json_object_test> ("test_key", &json_object_test::test_key));
      /* 4. */ s->addTest (new CppUnit::TestCaller<json_object_test> ("test_parse_1", &json_object_test::test_parse_1));
      /* 5. */ s->addTest (new CppUnit::TestCaller<json_object_test> ("test_operator_at_key", &json_object_test::test_operator_at_key));
      /* 6. */ s->addTest (new CppUnit::TestCaller<json_object_test> ("test_operator_at_index", &json_object_test::test_operator_at_index));
      /* 7. */ s->addTest (new CppUnit::TestCaller<json_object_test> ("test_pair_1", &json_object_test::test__pair));
      /* 8. */ s->addTest (new CppUnit::TestCaller<json_object_test> ("test__clear", &json_object_test::test__clear));
      /* 9. */ s->addTest (new CppUnit::TestCaller<json_object_test> ("test_strLength", &json_object_test::test_str_length));
      /* 10. */ s->addTest (new CppUnit::TestCaller<json_object_test> ("test_strvalue", &json_object_test::test_str_value));
      /* 11. */ s->addTest (new CppUnit::TestCaller<json_object_test> ("test_count", &json_object_test::test_count));

       return s;
    }
  };
}
#endif // JSON_OBJECT_TEST_H
