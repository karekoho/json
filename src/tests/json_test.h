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

  virtual void
  test_ctor_dtor ()
  {
    JSON p;

    JSON j[] = {
      JSON (),
      JSON ("{\"key\":true}"),
      JSON (p)
    };

    JSON copy = j[1];

    CPPUNIT_ASSERT_MESSAGE ("json", & copy != & j[1]);
    CPPUNIT_ASSERT_EQUAL_MESSAGE ("json.count ()", (size_t) 1, copy.count ());
  }

  virtual void
  test_parse_1 ()
  {
    struct assert {
        const char *starp;
        Value::object_type type;
        int assert_status;
    };

    std::vector<struct assert > test = {
        { " {} ", Value::object_type::object, PASS },
        { " [] ", Value::object_type::array, PASS },
        { " \"x\" ", Value::object_type::string, PASS },
        { " 100 ", Value::object_type::number, PASS },
        { " null ", Value::object_type::null, PASS },
        { " true ", Value::object_type::boolean, PASS },
        { " false ", Value::object_type::boolean, PASS },

        { "{\"k\":\"v\"} ", Value::object_type::object, PASS },
        { " { \"k\" : \"v\" } ", Value::object_type::object, PASS },
        { "[\"v\"] ", Value::object_type::array, PASS },
        { " [ \"v\", [\"vv\"] ] ", Value::object_type::array, PASS },

        /// errors
        { " x ", Value::object_type::undefined, FAIL },
        { " {} , ", Value::object_type::undefined, FAIL },
        { ", {} ", Value::object_type::undefined, FAIL },
        { " truee ", Value::object_type::undefined, FAIL },
    };

    TEST_IT_START

      const char *startp = (*it).starp;

      size_t charc = strlen (startp);
      JSON *j = new JSON ();

      const char * readp = j->parse (startp);

      ASSERT_EQUAL_IDX ("json.readp", (*it).starp + (charc), readp);
      ASSERT_EQUAL_IDX ("*(json.readp)", (char) 0, *readp);
      ASSERT_EQUAL_IDX ("json.type ()", (*it).type, j->type ());

      delete j;

    TEST_IT_END;
  }

  void test_make_value ()
  {
    JSON j;

    struct assert {
        const char *starp;
        Value::object_type type;
        size_t move;
        int assert_status;
    };

    std::vector<struct assert > test = {
        { "{} ", Value::object_type::object, 2, PASS },
        { "[] ", Value::object_type::array, 2, PASS },
        { "\"x\" ", Value::object_type::string, 3, PASS },
        { "10 ", Value::object_type::number, 2, PASS },
        { "-10 ", Value::object_type::number, 3, PASS },
        { "true ", Value::object_type::boolean, 4, PASS },
        { "false ", Value::object_type::boolean, 5, PASS },
        { "null ", Value::object_type::null, 4, PASS },
        { "x ", Value::object_type::undefined, 0, PASS },
        { "", Value::object_type::undefined, 0, PASS },
    };

    TEST_IT_START

        const char *startp = (*it).starp;

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

    struct assert {
        // const char *startp;
        const char *key;
        size_t index;
        Value *value[2];
        Value::object_type type;
        int assert_status;
    };

    std::vector<struct assert > test = {
      { /* "{}" , */ "ok", 0, { new Object (&op), new Object (&ap) }, Value::object, PASS },
      { /* "[]", */ "ak", 1, { new Array (&op), new Array (&ap) }, Value::array, PASS },
      { /* "\"x\"", */ "sk", 2, { new String (&op, 3), new String (&ap, 3) }, Value::string, PASS },
      { /* "100", */ "dk", 3, { new Number (&op), new Number (&ap) }, Value::number, PASS },
      { /* "", */ "bk", 4, { new Boolean (&op, true), new Boolean (&ap, true) }, Value::boolean, PASS },
      { /* "", */ "nk", 5, { new Null (&op), new Null (&ap) }, Value::null, PASS },
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
  virtual void test_strValue () override  {}

  virtual void test__clear () {}

  virtual void test_operator_assign () {}
  virtual void test_operator_at () {}

  virtual void test_size_1 () {}
  virtual void test_at () {}
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



    s->addTest (new CppUnit::TestCaller<json_test> ("test_smoke", &json_test::test_ctor_dtor));
    //return s;
    s->addTest (new CppUnit::TestCaller<json_test> ("test_parse_1", &json_test::test_parse_1));

//    s->addTest (new CppUnit::TestCaller<json_test> ("test_lookahead", &json_test::test_lookahead));   // value_test has the same
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_is_literal", &json_test::test_is_literal)); // value_test has the same
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_is_quoted", &json_test::test_string));      // value_test has the same

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
