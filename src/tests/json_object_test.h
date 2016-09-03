#ifndef JSON_OBJECT_TEST_H
#define JSON_OBJECT_TEST_H

#include <json_value_test_interface.h>

/**
 * Test number 2
 * @brief The json_object_test class
 */
class json_object_test : public json_value_test_interface
{
public:

  virtual void test_ctor_dtor ()
  {
    const char * input = "{}";

    JSON *p[] = { 0, new JSON (0, 0) };

    for (size_t pidx = 0; pidx < 2; pidx++)
      {
        Object *o[] = {
          new Object (),
          new Object (input),
          new Object (p[pidx], 0),
        };

        delete o[0];
        delete o[1];
        delete o[2];
      }

    delete p[1];
  }

  virtual
  void test_parse_1 ()
  {
    struct assert {
      const char *startp;
      size_t size;
      Value::object_type type;
      size_t moveback;
      int assert_status;
    };

    JSON *p[] = { 0, new JSON (0,0) };

    std::vector<struct assert > test = {
      { "{}", 0, Value::undefined, 0, PASS },
      { "{ } ", 0, Value::undefined, 1, PASS },
      { "{\"k\":\"v\"} ", 1, Value::string, 1, PASS },
      { "{ \"k\" : \"v\" } ", 1, Value::string, 1, PASS },
      { "{ \"k\" : \"v\", \"q\" : \"p\" } ", 2, Value::string, 1, PASS },
      { "{ \"k\": \"v\", \"q\" : \"p\",\"K\":\"v\" } ", 3, Value::string, 1, PASS },
      { "{ \"k\": \"p\" ,\"q\" : \"p\", \"K\" :\"v\",\"Q\":\"p\" } ", 4, Value::string, 1, PASS },

      { "{ \"k\" : { } }", 1, Value::object, 0, PASS },
      { "{ \"k\" : {\"kk\" : \"v\"}}", 1, Value::object, 0, PASS },
      { "{ \"k\" : {\"kk\" : {\"kkk\" : \"v\"}}", 1, Value::object, 0, PASS },
      { "{ \"k\" : null } ", 1, Value::null, 1, PASS },

      // errors
      { "", 0, Value::undefined, 0, FAIL },   // json::syntax_error
      { " ", 0, Value::undefined, 0, FAIL },   // json::syntax_error
      { "x", 0, Value::undefined, 0, FAIL },   // json::syntax_error
      { "{", 0, Value::undefined, 0, FAIL },   // json::syntax_error
      { "}", 0, Value::undefined, 0, FAIL },   // json::syntax_error
      { "{ , }", 0, Value::undefined, 0, FAIL },   // json::syntax_error
      { "{ : }", 0, Value::undefined, 0, FAIL },   // json::syntax_error
    };

    TEST_IT_START;
      for (int pidx = 0; pidx < 2; pidx++)
        {
          const char *startp = (*it).startp;

          size_t charc = strlen (startp);

          Object *o = new Object (/* (*it).parent */ p[pidx], 0);

          const char *readp = o->parse (startp);

          ASSERT_EQUAL_IDX ("value.readp", (startp + charc) - (*it).moveback, readp);
          ASSERT_EQUAL_IDX ("*(value.readp -1)", '}', *(readp - 1));
          ASSERT_EQUAL_IDX ("value.size", (*it).size, o->size ());

          if (o->size () > 0)
            {
              ASSERT_EQUAL_IDX ("value.type", (*it).type, o->at ("k").type ());
            }

          delete o;
        }
    TEST_IT_END;

    delete p[1];
  }

  virtual void test_size_1 () {}

  virtual void
  test_at_1 ()
  {
    Object o;

    o._member_list.emplace ("key1", new Boolean (true));

    struct assert {
      const char *key;
      Value::object_type type;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { "key1", Value::object_type::boolean, PASS },
      { "key2", Value::object_type::undefined, FAIL }
    };

    TEST_IT_START

      const Value & v = o.at ((*it).key);

      ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());

    TEST_IT_END;
  }

  virtual void
  test_at_2 ()
  {
    Object o;

    o._member_list.emplace ("key1", new Boolean (true));

    struct assert {
      const char *key;
      Value::object_type type;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { "key1", Value::object_type::boolean, PASS },
      { "key2", Value::object_type::undefined, PASS }
    };

    TEST_IT_START

      const Value & _v = o._at ((*it).key);

      ASSERT_EQUAL_IDX ("_v.type ()", (*it).type, _v.type ());

    TEST_IT_END;
  }


  virtual void test_value_1 () {}
  virtual void test_debug_1 () {}

  void
  test__pair ()
  {
    Object *p = new Object (0, 0);

    struct assert {
      const char *startp;
      bool status;
      int assert_status;
    };

    std::vector<struct assert > test = {
      { " \"foo\" : \"bar\" ", true, PASS },
      { " }" , false , PASS },

      // errors
      { " ", false, FAIL},            // json::syntax_error
      { " \"foo  ", false, FAIL },    // json::syntax_error
      { " \"foo\" ", false, FAIL },   // json::syntax_error
      { " \"foo\" : ", false, SKIP }, // FAIL: json::syntax_error
    };

    TEST_IT_START;

      const char *startp = (*it).startp;

      Object *o = new Object (p,0);

      o->_readp = startp;
      bool status = o->_pair ();

      // readp = o->parse (startp);

      ASSERT_EQUAL_IDX ("status", (*it).status, status);

      delete o;

    TEST_IT_END;
  }


  static CppUnit::Test*
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json object test");

     s->addTest (new CppUnit::TestCaller<json_object_test> ("test_smoke", &json_object_test::test_ctor_dtor));
  //    return s;
      s->addTest (new CppUnit::TestCaller<json_object_test> ("test_parse_1", &json_object_test::test_parse_1));
 //     return s;
//    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_size_1", &json_object_test::test_size_1));
      s->addTest (new CppUnit::TestCaller<json_object_test> ("test_at_1", &json_object_test::test_at_1));
      s->addTest (new CppUnit::TestCaller<json_object_test> ("test_at_1", &json_object_test::test_at_2));

//    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_value_1", &json_object_test::test_value_1));
//    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_debug_1", &json_object_test::test_debug_1));

     s->addTest (new CppUnit::TestCaller<json_object_test> ("test_pair_1", &json_object_test::test__pair));
//     s->addTest (new CppUnit::TestCaller<json_object_test> ("test_pair_1", &json_object_test::test__value));

     return s;
  }

};

#endif // JSON_OBJECT_TEST_H
