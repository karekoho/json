#ifndef JSON_TEST_H
#define JSON_TEST_H

#include <json_value_test_interface.h>
#include "json_value_parse_mock.h"
namespace format {
/**
 * 1.
 * @brief The json_test class
 */
class json_test : public json_value_test_interface
{
public:

  void
  example_free_1 ()
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

    (void) j.get ();
    (void) j[L"Image"].get ();
    (void) j[L"Image"][L"Thumbnail"].get ();
    (void) j[L"Image"][L"Thumbnail"][L"Url"].get ();
    (void) j[L"Image"][L"Animated"].get ();
    (void) j[L"Image"][L"IDs"].get ();
  }

  virtual void
  test_ctor_dtor ()
  {
    json p;

    json j[] = {
      json (),
      json (L"{\"key\":true}"),
      json (p)
    };

    json copy = j[1];

    CPPUNIT_ASSERT_MESSAGE ("json", & copy != & j[1]);
    CPPUNIT_ASSERT_EQUAL_MESSAGE ("json.count ()", (size_t) 1, copy.count ());
  }

  virtual void
  test_parse_1 ()
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

    TEST_IT_START

      const wchar_t *startp = (*it).starp;

      size_t charc = wcslen (startp);
      json *j = new json ();

      const wchar_t * readp = j->_parse (startp);

      ASSERT_EQUAL_IDX ("json.readp", (*it).starp + (charc), readp);
      ASSERT_EQUAL_IDX ("*(json.readp)", (wchar_t) 0, *readp);
      ASSERT_EQUAL_IDX ("json.type ()", (*it).type, j->type ());

      delete j;

    TEST_IT_END;
  }

  void test_make_value ()
  {
    json j;

    struct assert {
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

        //j._endp = startp + strlen (startp);
        j._readp = startp;

        value *v = j._make_value ();

        ASSERT_EQUAL_IDX ("json._readp", startp + (*it).move , j._readp);
        ASSERT_EQUAL_IDX ("value.type ()", (*it).type , v->type ());

    TEST_IT_END;
  }

  void
  test__assign_to_parent ()
  {
    object op;
    array ap;

    struct assert
    {
        const wchar_t *key;
        size_t index;
        value *val[2];
        value::value_t type;
        int assert_status;
    };

    std::vector<struct assert > test = {
      { L"ok", 0, { new object (&op), new object (&ap) }, value::object_t, PASS },
      { L"ak", 1, { new array (&op), new array (&ap) }, value::array_t, PASS },
      { L"sk", 2, { new string (&op, 3), new string (&ap, 3) }, value::string_t, PASS },
      { L"dk", 3, { new number (&op), new number (&ap) }, value::number_t, PASS },
      { L"bk", 4, { new boolean (&op, true), new boolean (&ap, true) }, value::boolean_t, PASS },
      { L"nk", 5, { new null (&op), new null (&ap) }, value::null_t, PASS },
    };

    size_t x =0;

    TEST_IT_START

        value & oov = op._at ((*it).key);
        value & aov = ap._at ((*it).index);

        ASSERT_EQUAL_IDX ("value.type ()", value::undefined_t, oov.type ());
        ASSERT_EQUAL_IDX ("value.type ()", value::undefined_t, aov.type ());

        op._assign (& oov, (*it).val[0]);
        ap._assign (& aov, (*it).val[1]);

        ASSERT_EQUAL_IDX ("parent._at (key)", (*it).type, op._at ((*it).key).type ());
        ASSERT_EQUAL_IDX ("parent._at (index)", (*it).type, ap._at ((*it).index).type ());

        x++;
        // (*it).value->parse ((*it).startp);

    TEST_IT_END;
  }

  virtual void
  test_assign_all_values ()
  {
    json j;

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

        j._assign (*(*it).val);
        j = *(*it).val;

        ASSERT_EQUAL_IDX ("json.__value->type ()", (*it).type, j.__root->type ());

    TEST_IT_END;
  }



  //virtual void test_stringify () override {}

  virtual void test_strLength () override {}

  virtual void
  test_strValue () override
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
          const wchar_t *value[2] = { j.strValue (),
                                      j[L"1"][L"2"].strValue ()
                                    };

          ASSERT_EQUAL_IDX ("wcslen (value[0])", len[0], wcslen (value[0]));
          ASSERT_EQUAL_IDX ("wcslen (value[1])", len[1], wcslen (value[1]));
        }
    TEST_IT_END;

  }

  virtual void test__clear () {}

  virtual void test_operator_assign () {}
  virtual void test_operator_at () {}

  //virtual void test_size_1 () {}


  virtual void
  test_operator_at_key ()  // TODO
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
      // TODO: object.at(key)
      // TODO: object.at(index)
      // TODO: object[key]
      // TODO: object[index]
     TEST_IT_END;
  }

  virtual void
  test_operator_at_index ()
  {
  }

  virtual void test_value_1 () {}
  virtual void test_debug_1 () {}

  virtual void test_erase () override {}

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

    std::vector<struct assert> test = {
      { L"{\"0\":{},\"1\":[],\"2\":\"2\",\"3\":3,\"4\":false,\"5\":null}", {
          { new object, new array, new string, new number, new boolean , new null },
          { new null, new null, new string, new number, new boolean }
        }, PASS },

      { L"[{},\[],\"2\",3,false,null]", {
          { new object, new array, new string, new number, new boolean, new null },
          { new null, new null, new string, new number, new boolean }
        }, PASS },
      };

     reviver reviver[2] = { 0, fn_reviver };

     TEST_IT_START

      for (size_t rev_idx = 1; rev_idx < 2; rev_idx++) // Iterate reviver
        {

          value *jv = json::_parse ((*it).input, reviver[rev_idx]);

          size_t output_size = (*it).output[rev_idx].size ();

          for (size_t val_idx = 0; val_idx < output_size; val_idx++) // Iterate values
            {
              value *ov = (*it).output[rev_idx].at (val_idx);
              value & jvv = *jv;
              CPPUNIT_ASSERT_EQUAL_MESSAGE ("jv->count ()", output_size, jv->count ());
              // CPPUNIT_ASSERT_EQUAL_MESSAGE ("jv->at ().type ()", ov->type (), jv->at (std::to_wstring (val_idx).c_str ()).type ());
              CPPUNIT_ASSERT_EQUAL_MESSAGE ("jv->at ().type ()", ov->type (), jvv[std::to_wstring (val_idx).c_str ()].type ());
            }
        }

     TEST_IT_END;
  }

  static value *
  fn_reviver (const wchar_t *key, value *v)
  {
    switch (v->type ()) {
      case  value::value_t::null_t:
        return new format::undefined;

      case value::value_t::object_t:
      case value::value_t::array_t:
        return new null;

      default:
        return v;
      }
  }

  /**
   * 1.
   * @brief suite
   * @return
   */
  static CppUnit::Test*
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json test");

/*0.*/  s->addTest (new CppUnit::TestCaller<json_test> ("test_strValue", &json_test::test_strValue));
//  s->addTest (new CppUnit::TestCaller<json_test> ("example_free_1", &json_test::example_free_1));
    s->addTest (new CppUnit::TestCaller<json_test> ("test_smoke", &json_test::test_ctor_dtor));
    s->addTest (new CppUnit::TestCaller<json_test> ("test_parse_1", &json_test::test_parse_1));
    s->addTest (new CppUnit::TestCaller<json_test> ("test_make_value", &json_test::test_make_value));
    s->addTest (new CppUnit::TestCaller<json_test> ("test__assign_to_parent", &json_test::test__assign_to_parent));
    s->addTest (new CppUnit::TestCaller<json_test> ("test_assign_all_values", &json_test::test_assign_all_values));
/*6.*/  s->addTest (new CppUnit::TestCaller<json_test> ("test_parse_revive", &json_test::test_parse_revive));

//    s->addTest (new CppUnit::TestCaller<json_test> ("test_size_1", &json_test::test_size_1));
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_get_1", &json_test::test_get_1));
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_value_1", &json_test::test_value_1));
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_debug_1", &json_test::test_debug_1));

    return s;
  }
};
}
#endif // JSON_TEST_H
