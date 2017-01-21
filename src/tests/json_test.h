#ifndef JSON_TEST_H
#define JSON_TEST_H

#include <json_value_test_interface.h>
#include "json_value_parse_mock.h"

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
    JSON j = L"{\
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

    (void) j.value ();
    (void) j[L"Image"].value ();
    (void) j[L"Image"][L"Thumbnail"].value ();
    (void) j[L"Image"][L"Thumbnail"][L"Url"].value ();
    (void) j[L"Image"][L"Animated"].value ();
    (void) j[L"Image"][L"IDs"].value ();
  }

  virtual void
  test_ctor_dtor ()
  {
    JSON p;

    JSON j[] = {
      JSON (),
      JSON (L"{\"key\":true}"),
      JSON (p)
    };

    JSON copy = j[1];

    CPPUNIT_ASSERT_MESSAGE ("json", & copy != & j[1]);
    CPPUNIT_ASSERT_EQUAL_MESSAGE ("json.count ()", (size_t) 1, copy.count ());
  }

  virtual void
  test_parse_1 ()
  {
    struct assert
    {
        const wchar_t *starp;
        Value::object_type type;
        int assert_status;
    };

    std::vector<struct assert > test = {
        { L" {} ", Value::object_type::object, PASS },
        { L" [] ", Value::object_type::array, PASS },
        { L" \"x\" ", Value::object_type::string, PASS },
        { L" 100 ", Value::object_type::number, PASS },
        { L" null ", Value::object_type::null, PASS },
        { L" true ", Value::object_type::boolean, PASS },
        { L" false ", Value::object_type::boolean, PASS },

        { L"{\"k\":\"v\"} ", Value::object_type::object, PASS },
        { L" { \"k\" : \"v\" } ", Value::object_type::object, PASS },
        { L"[\"v\"] ", Value::object_type::array, PASS },
        { L" [ \"v\", [\"vv\"] ] ", Value::object_type::array, PASS },

        /// errors
        { L" x ", Value::object_type::undefined, FAIL },
        { L" {} , ", Value::object_type::undefined, FAIL },
        { L", {} ", Value::object_type::undefined, FAIL },
        { L" truee ", Value::object_type::undefined, FAIL },
    };

    TEST_IT_START

      const wchar_t *startp = (*it).starp;

      size_t charc = wcslen (startp);
      JSON *j = new JSON ();

      const wchar_t * readp = j->parse (startp);

      ASSERT_EQUAL_IDX ("json.readp", (*it).starp + (charc), readp);
      ASSERT_EQUAL_IDX ("*(json.readp)", (wchar_t) 0, *readp);
      ASSERT_EQUAL_IDX ("json.type ()", (*it).type, j->type ());

      delete j;

    TEST_IT_END;
  }

  void test_make_value ()
  {
    JSON j;

    struct assert {
        const wchar_t *starp;
        Value::object_type type;
        size_t move;
        int assert_status;
    };

    std::vector<struct assert > test = {
        { L"{} ", Value::object_type::object, 2, PASS },
        { L"[] ", Value::object_type::array, 2, PASS },
        { L"\"x\" ", Value::object_type::string, 3, PASS },
        { L"10 ", Value::object_type::number, 2, PASS },
        { L"-10 ", Value::object_type::number, 3, PASS },
        { L"true ", Value::object_type::boolean, 4, PASS },
        { L"false ", Value::object_type::boolean, 5, PASS },
        { L"null ", Value::object_type::null, 4, PASS },
        { L"x ", Value::object_type::undefined, 0, PASS },
        { L"", Value::object_type::undefined, 0, PASS },
    };

    TEST_IT_START

        const wchar_t *startp = (*it).starp;

        //j._endp = startp + strlen (startp);
        j._readp = startp;

        Value *v = j._make_value ();

        ASSERT_EQUAL_IDX ("json._readp", startp + (*it).move , j._readp);
        ASSERT_EQUAL_IDX ("value.type ()", (*it).type , v->type ());

    TEST_IT_END;
  }

  void
  test__assign_to_parent ()
  {
    Object op;
    Array ap;

    struct assert
    {
        const wchar_t *key;
        size_t index;
        Value *value[2];
        Value::object_type type;
        int assert_status;
    };

    std::vector<struct assert > test = {
      { L"ok", 0, { new Object (&op), new Object (&ap) }, Value::object, PASS },
      { L"ak", 1, { new Array (&op), new Array (&ap) }, Value::array, PASS },
      { L"sk", 2, { new String (&op, 3), new String (&ap, 3) }, Value::string, PASS },
      { L"dk", 3, { new Number (&op), new Number (&ap) }, Value::number, PASS },
      { L"bk", 4, { new Boolean (&op, true), new Boolean (&ap, true) }, Value::boolean, PASS },
      { L"nk", 5, { new Null (&op), new Null (&ap) }, Value::null, PASS },
    };

    size_t x =0;

    TEST_IT_START

        Value & oov = op._at ((*it).key);
        Value & aov = ap._at ((*it).index);

        ASSERT_EQUAL_IDX ("value.type ()", Value::undefined, oov.type ());
        ASSERT_EQUAL_IDX ("value.type ()", Value::undefined, aov.type ());

        op.assign (& oov, (*it).value[0]);
        ap.assign (& aov, (*it).value[1]);

        ASSERT_EQUAL_IDX ("parent._at (key)", (*it).type, op._at ((*it).key).type ());
        ASSERT_EQUAL_IDX ("parent._at (index)", (*it).type, ap._at ((*it).index).type ());

        x++;
        // (*it).value->parse ((*it).startp);

    TEST_IT_END;
  }

  virtual void
  test_assign_all_values ()
  {
    JSON json;

    struct assert
    {
        Value *value;
        Value::object_type type;
        int assert_status;
    };

    std::vector<struct assert > test = {
      { new JSON, Value::undefined, PASS },
      { new Object, Value::object, PASS },
      { new Array, Value::array, PASS },
      { new String, Value::string, PASS },
      { new Number, Value::number, PASS },
      { new Boolean, Value::boolean, PASS },
      { new Null, Value::null, PASS },
    };

    TEST_IT_START

        json._assign (*(*it).value);
        json = *(*it).value;

        ASSERT_EQUAL_IDX ("json.__value->type ()", (*it).type, json.__root->type ());

    TEST_IT_END;
  }



  virtual void test_stringify () override {}

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

      JSON j = (*it).input;

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

  virtual void test_size_1 () {}


  virtual void
  test_at ()  // TODO
  {
    struct assert
    {
      const wchar_t *input;
      Value::object_type type;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { L"{}", Value::object_type::boolean, PASS },
      { L"[]", Value::object_type::boolean, PASS }
     };

     TEST_IT_START
      // TODO: object.at(key)
      // TODO: object.at(index)
      // TODO: object[key]
      // TODO: object[index]
     TEST_IT_END;
  }

  virtual void test_value_1 () {}
  virtual void test_debug_1 () {}

  virtual void test_erase () override {}

  /**
   * 1.
   * @brief suite
   * @return
   */
  static CppUnit::Test*
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json test");

    s->addTest (new CppUnit::TestCaller<json_test> ("test_strValue", &json_test::test_strValue));
//    s->addTest (new CppUnit::TestCaller<json_test> ("example_free_1", &json_test::example_free_1));
    s->addTest (new CppUnit::TestCaller<json_test> ("test_smoke", &json_test::test_ctor_dtor));
    s->addTest (new CppUnit::TestCaller<json_test> ("test_parse_1", &json_test::test_parse_1));
    s->addTest (new CppUnit::TestCaller<json_test> ("test_make_value", &json_test::test_make_value));
    s->addTest (new CppUnit::TestCaller<json_test> ("test__assign_to_parent", &json_test::test__assign_to_parent));
    s->addTest (new CppUnit::TestCaller<json_test> ("test_assign_all_values", &json_test::test_assign_all_values));

//    s->addTest (new CppUnit::TestCaller<json_test> ("test_size_1", &json_test::test_size_1));
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_get_1", &json_test::test_get_1));
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_value_1", &json_test::test_value_1));
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_debug_1", &json_test::test_debug_1));

    return s;
  }
};

#endif // JSON_TEST_H
