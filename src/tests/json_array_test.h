#ifndef JSON_ARRAY_TEST
#define JSON_ARRAY_TEST

#include "json_value_test_interface.h"

/// Test number 4
class json_array_test : public json_value_test_interface {

  // json_value_test_interface interface
public:

  virtual void
  test_ctor_dtor ()
  {
    const char * input = "{}";

    JSON *p[] = { 0, new JSON () };

    for (size_t pidx = 0; pidx < 2; pidx++)
      {
        Array *a[] = {
          new Array (),
          new Array (input),
          new Array (p[pidx]),
        };

        delete a[0];
        delete a[1];
        delete a[2];
      }

    delete p[1];
  }

  virtual void
  test_parse_1 ()
  {
    struct assert {
      const char *startp;
      size_t size;
      Value::object_type type; 
      int moveback;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { "[]", 0, Value::object_type::array, 0, PASS },
      { "[ ] ", 0, Value::object_type::array, 1, PASS },
      { "[\"x\"]", 1, Value::object_type::array, 0, PASS },
      { "[\"x\",\"x\"] ", 2, Value::object_type::array, 1, PASS },
      { "[\"x\",\"x\",[\"x\"]] ", 3,  Value::object_type::array, 1, PASS },

      // errors
      { "[", 0, Value::object_type::undefined, 0, FAIL },
      { "[ ", 0, Value::object_type::undefined, 0, FAIL },
      { "]", 0, Value::object_type::undefined, 0, FAIL },
      { "[, ", 0, Value::object_type::undefined, 0, FAIL },
      { "[ x ", 0, Value::object_type::undefined, 0, FAIL },
      { "", 0, Value::object_type::undefined, 0, FAIL },
      { " ", 0, Value::object_type::undefined, 0, FAIL },
      { "x", 0, Value::object_type::undefined, 0, FAIL },
    };

    JSON *p[] = { 0, new JSON () };

    TEST_IT_START
      for (size_t pidx = 0; pidx < 2; pidx++)
        {
          const char *startp = (*it).startp;
          size_t charc =strlen (startp);
          Array *a = new Array (p[pidx]);

          const char *readp = a->parse (startp);

          ASSERT_EQUAL_IDX ("array.readp", (startp + charc) - (*it).moveback, readp);
          ASSERT_EQUAL_IDX ("*(array.readp - 1)", ']', *(readp - 1));
          ASSERT_EQUAL_IDX ("array.size", (*it).size, a->size ());

          delete a;
        }
    TEST_IT_END;
  }

  void
  test_index ()
  {
    struct assert {
      const char *startp;
      // const char *key;
      int assert_status;
    };

    std::vector<struct assert > test = {
      { "[]", PASS },
      { "[ ] ", PASS },
      { "[\"a\",\"b\",\"c\"]", PASS },
    };

    TEST_IT_START;
      const char *startp = (*it).startp;
      Array *a = new Array ();

      (void) a->parse (startp);

      if (a->size () > 0)
        {
          for (size_t idx = 0; idx < a->_element_list.size(); idx++)
            {
              Value *v = a->_element_list.at(idx);
              ASSERT_EQUAL_IDX ("value.index", idx, v->index ());
            }
        }
      delete a;
    TEST_IT_END
  }

  virtual void
  test_assign_all_values ()
  {
  }

  virtual void test_size_1 () {}
  virtual void test_at_1() {}
  virtual void test_value_1() {}
  virtual void test_debug_1() {}

  static CppUnit::Test *suite()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json array test");

      s->addTest (new CppUnit::TestCaller<json_array_test> ("test_smoke", &json_array_test::test_ctor_dtor));
      s->addTest (new CppUnit::TestCaller<json_array_test> ("test_parse_1", &json_array_test::test_parse_1));
       s->addTest (new CppUnit::TestCaller<json_array_test> ("test_index", &json_array_test::test_index));
//    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_size_1", &json_array_test::test_size_1));
//    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_get_1", &json_array_test::test_get_1));
//    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_value_1", &json_array_test::test_value_1));
//    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_debug_1", &json_array_test::test_debug_1));

    return s;
  }
};

#endif // JSON_ARRAY_TEST

