#ifndef JSON_TEST_H
#define JSON_TEST_H

#include <json_value_test_interface.h>
#include "json_mock_value.h"

namespace format
{
  /**
   * 1.
   * @brief The json_test class
   */
  class json_test : public json_value_test_interface
  {
  public:

    virtual void
    test_ctor_dtor () override
    {
      json parent;

      json j[] = {
        json (),
        json (L"{\"0\":0}"),
        json (parent),

        json (new object {}),
        json (new array {}),

        //json (object {{}}),
        //json (array {}),
        //json (json ())
      };

      json copy = j[1];

      CPPUNIT_ASSERT_MESSAGE ("json",
                              & copy != & j[1]);

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("value::type ()",
                                    value::boolean_t,
                                    (j[(size_t) 0][L"0"] = boolean ())[L"0"].type ());

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.count ()",
                                    (size_t) 1,
                                    copy.length ());

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("json::type () (1)",
                                    value::object_t,
                                    j[3].type ());

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("json::type () (2)",
                                    value::array_t,
                                    j[4].type ());

      /*CPPUNIT_ASSERT_EQUAL_MESSAGE ("json::type () (3)",
                                    value::object_t,
                                    j[5].type ());

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("json::type () (4)",
                                    value::array_t,
                                    j[6].type ());*/

      delete json::parse (L"{}");
    }

    virtual void
    test_parse_1 () override
    {
      struct assert
      {
          const wchar_t *starp;
          value::value_t type;
          int assert_status;
      };

      std::vector<struct assert > test = {
          { L" {} ", value::value_t::object_t, PASS },
          { L" [] ", value::value_t::array_t, PASS },
          { L" \"x\" ", value::value_t::string_t, PASS },
          { L" 100 ", value::value_t::number_t, PASS },
          { L" null ", value::value_t::null_t, PASS },
          { L" true ", value::value_t::boolean_t, PASS },
          { L" false ", value::value_t::boolean_t, PASS },

          { L"{\"k\":\"v\"} ", value::value_t::object_t, PASS },
          { L" { \"k\" : \"v\" } ", value::value_t::object_t, PASS },
          { L"[\"v\"] ", value::value_t::array_t, PASS },
          { L" [ \"v\", [\"vv\"] ] ", value::value_t::array_t, PASS },

          /// errors
          { L" x ", value::value_t::undefined_t, FAIL },
          { L" {} , ", value::value_t::undefined_t, FAIL },
          { L", {} ", value::value_t::undefined_t, FAIL },
          { L" truee ", value::value_t::undefined_t, FAIL },
      };

      json *j = 0;

      TEST_IT_START
            const wchar_t *startp = (*it).starp;
            size_t charc = wcslen (startp);

            j = new json ();

            const wchar_t * readp = j->_parse (startp);

            ASSERT_EQUAL_IDX ("json.readp", (*it).starp + (charc), readp);
            ASSERT_EQUAL_IDX ("*(json.readp)", (wchar_t) 0, *readp);
            ASSERT_EQUAL_IDX ("json.type ()", (*it).type, j->type ());

            delete j;
          }
        catch (format::json_syntax_error & se)
          {
            this->_errorc[ACTUAL]++; std::cerr << se.what () << std::endl;
            delete j;
          }

        (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]);
        CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
      }
    }

    void
    test_make_value ()
    {
      json j;

      struct assert
      {
          const wchar_t *starp;
          value::value_t type;
          size_t move;
          int assert_status;
      };

      std::vector<struct assert > test = {
          { L"{} ", value::value_t::object_t, 2, PASS },
          { L"[] ", value::value_t::array_t, 2, PASS },
          { L"\"x\" ", value::value_t::string_t, 3, PASS },
          { L"10 ", value::value_t::number_t, 2, PASS },
          { L"-10 ", value::value_t::number_t, 3, PASS },
          { L"true ", value::value_t::boolean_t, 4, PASS },
          { L"false ", value::value_t::boolean_t, 5, PASS },
          { L"null ", value::value_t::null_t, 4, PASS },
          { L"x ", value::value_t::no_value_t, 0, PASS },
          { L"", value::value_t::no_value_t, 0, PASS },
      };

      TEST_IT_START

          const wchar_t *startp = (*it).starp;

          j._readp = startp;

          value *v = j._make_value ();

          ASSERT_EQUAL_IDX ("json._readp", startp + (*it).move , j._readp);
          ASSERT_EQUAL_IDX ("value.type ()", (*it).type , v->type ());

          if (v->type () != value::no_value_t)
            delete v;

      TEST_IT_END;
    }

    void
    test__assign_to_parent ()
    {
      object_accessor object_parent;
      array_accessor array_parent;

      struct assert
      {
          const wchar_t *key;
          size_t index;
          value *val[2];
          value::value_t type;
          int assert_status;
      };

      std::vector<struct assert > test = {
        { L"ok", 0, { new object_accessor (& object_parent), new object_accessor (& array_parent) }, value::object_t, PASS },
        { L"ak", 1, { new array_accessor (& object_parent), new array_accessor (& array_parent) }, value::array_t, PASS },
        { L"sk", 2, { new string_accessor (& object_parent, 3), new string_accessor (& array_parent, 3) }, value::string_t, PASS },
        { L"dk", 3, { new number_accessor (& object_parent), new number_accessor (& array_parent) }, value::number_t, PASS },
        { L"bk", 4, { new boolean_accessor (& object_parent, true), new boolean_accessor (& array_parent, true) }, value::boolean_t, PASS },
        { L"nk", 5, { new null_accessor (& object_parent), new null_accessor (& array_parent) }, value::null_t, PASS },
      };

      size_t x = 0;

      TEST_IT_START

          value & oov = object_parent[(*it).key];
          value & aov = array_parent[(*it).index];

          ASSERT_EQUAL_IDX ("value.type ()", value::undefined_t, oov.type ());
          ASSERT_EQUAL_IDX ("value.type ()", value::undefined_t, aov.type ());

          object_parent.assign (& oov, (*it).val[0]);
          array_parent.assign (& aov, (*it).val[1]);

          ASSERT_EQUAL_IDX ("parent._at (key)", (*it).type, object_parent[(*it).key].type ());
          ASSERT_EQUAL_IDX ("parent._at (index)", (*it).type, array_parent[(*it).index].type ());

          x++;

      TEST_IT_END;
    }

    virtual void
    test_assign_all_values () override
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

    virtual void
    test_str_value () override
    {
      struct assert
      {
        const wchar_t *input;
        const wchar_t *output[2];
        int assert_status;
      };

      std::vector<struct assert> test = {
        { L"{\"1\":{\"2\":{\"3\":\"three\"},\"4\":\"four\"}}",
          { L"{\"1\":{\"2\":{\"3\":\"three\"},\"4\":\"four\"}}",
            L"{\"3\":\"three\"}"  }, PASS },

        { L"[\"1\",[\"2\",[\"3\"],\"4\"]]",
          { L"[\"1\",[\"2\",[\"3\"],\"4\"]]",
            L"\"4\"" }, PASS },
      };

      TEST_IT_START

        json j = (*it).input;

        size_t len[2] = { wcslen ((*it).output[0]), wcslen ((*it).output[1]) };

        for (uint mdx = 0; mdx < 2; mdx++)
          {
            const wchar_t *value[2] = { j.str_value (),
                                        j[L"1"][L"2"].str_value ()
                                      };

            ASSERT_EQUAL_IDX ("wcslen (value[0])", len[0], wcslen (value[0]));
            ASSERT_EQUAL_IDX ("wcslen (value[1])", len[1], wcslen (value[1]));
          }
      TEST_IT_END;
    }

    virtual void
    test_operator_at_key () override  // TODO
    {
      struct assert
      {
        const wchar_t *input;
        value::value_t type;
        int assert_status;
      };

      std::vector<struct assert> test = {
        { L"{}", value::value_t::boolean_t, PASS },
        { L"[]", value::value_t::boolean_t, PASS }
       };

       TEST_IT_START
        // TODO: object[key]
        // TODO: object[index]
       TEST_IT_END;
    }

    void
    test_parse_revive ()
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

      /* std::vector<struct assert> test = {
        { L"{\"0\":{},\"1\":[],\"2\":\"2\",\"3\":3,\"4\":false,\"5\":null}", {
            { new object, new array, new string, new number, new boolean , new null },
            { new null, new null, new string, new number, new boolean }
          }, PASS },

        { L"[{},\[],\"2\",3,false,null]", {
            { new object, new array, new string, new number, new boolean, new null },
            { new null, new null, new string, new number, new boolean }
          }, PASS },
        }; */

      std::vector<struct assert> test = {
        { L"{\"0\":{},\"1\":[],\"2\":\"2\",\"3\":3,\"4\":false,\"5\":null}", {
            { __VALUE[value::object_t], __VALUE[value::array_t], __VALUE[value::string_t], __VALUE[value::number_t], __VALUE[value::boolean_t] , __VALUE[value::null_t] },
            { __VALUE[value::null_t], __VALUE[value::null_t], __VALUE[value::string_t], __VALUE[value::number_t], __VALUE[value::boolean_t] }
          }, PASS },

        { L"[{},\[],\"2\",3,false,null]", {
            { __VALUE[value::object_t], __VALUE[value::array_t], __VALUE[value::string_t], __VALUE[value::number_t], __VALUE[value::boolean_t] , __VALUE[value::null_t] },
            { __VALUE[value::null_t], __VALUE[value::null_t], __VALUE[value::string_t], __VALUE[value::number_t], __VALUE[value::boolean_t] }
          }, PASS },
        };

       reviver reviver[2] = { 0, fn_reviver };

       TEST_IT_START

        for (size_t rev_idx = 1; rev_idx < 2; rev_idx++) // Iterate reviver
          {
            value *jv = json::parse ((*it).input, reviver[rev_idx]);

            size_t output_size = (*it).output[rev_idx].size ();

            for (size_t val_idx = 0; val_idx < output_size; val_idx++) // Iterate values
              {
                value *ov = (*it).output[rev_idx].at (val_idx);
                value & jvv = *jv;

                CPPUNIT_ASSERT_EQUAL_MESSAGE ("jv->count ()",
                                              output_size,
                                              jv->length ());

                CPPUNIT_ASSERT_EQUAL_MESSAGE ("jv->at ().type ()",
                                              ov->type (),
                                              jvv[ std::to_wstring (val_idx).c_str () ].type ());
              }
            delete jv;
          }
       TEST_IT_END;
    }

    static value *
    fn_reviver (const wchar_t *, value *v)
    {
      switch (v->type ())
        {
          case  value::value_t::null_t:
            return new format::undefined ();

          case value::value_t::object_t:
          case value::value_t::array_t:
            return new null;

          default:
            return v;
        }
    }

    void
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

    virtual void
    test_count () override
    {
      json j[2] = {
        json (),
        json (L"{}")
      };

      for (size_t idx = 0; idx < 2; idx++)
        CPPUNIT_ASSERT_EQUAL_MESSAGE ("json::count ()", (size_t) 0, j[idx].length ());
    }

    virtual void test_operator_at_index () override {}
    virtual void test_str_length () override {}
    virtual void test__clear () override {}
    virtual void test_erase () override {}
    virtual void test_type () override {}

    /**
     * 1.
     * @brief suite
     * @return
     */
    static CppUnit::Test*
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json test");

      /* 0. */  s->addTest (new CppUnit::TestCaller<json_test> ("test_ctor_dtor", &json_test::test_ctor_dtor));
      /* 1. */  s->addTest (new CppUnit::TestCaller<json_test> ("test_str_value", &json_test::test_str_value));
      /* 2. */  s->addTest (new CppUnit::TestCaller<json_test> ("test_parse_1", &json_test::test_parse_1));
      /* 3. */  s->addTest (new CppUnit::TestCaller<json_test> ("test_make_value", &json_test::test_make_value));
      /* 4. */  s->addTest (new CppUnit::TestCaller<json_test> ("test__assign_to_parent", &json_test::test__assign_to_parent));
      /* 5. */  s->addTest (new CppUnit::TestCaller<json_test> ("test_assign_all_values", &json_test::test_assign_all_values));
      /* 6. */  s->addTest (new CppUnit::TestCaller<json_test> ("test_parse_revive", &json_test::test_parse_revive));
      /* 7. */  s->addTest (new CppUnit::TestCaller<json_test> ("test_count", &json_test::test_count));

      /* 8. */  //s->addTest (new CppUnit::TestCaller<json_test> ("example_1", &json_test::example_1));

      return s;
    }
  };
}
#endif // JSON_TEST_H
