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

  virtual void
  test_ctor_dtor ()
  {
    JSON *p[] = { 0, new JSON () };

    for (size_t pidx = 0; pidx < 2; pidx++)
      {
        Object o[] = {
          Object (),
          Object ("{}"),
          Object (p[pidx]),
        };
      }

    delete p[1];

    Object src  = "{\"key\":true}";
    Object copy = src;

    CPPUNIT_ASSERT_MESSAGE ("object", & copy != & src);
    CPPUNIT_ASSERT_EQUAL_MESSAGE ("object._member_list.size ()", (size_t) 1, copy._member_list.size ());
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

    JSON *p[] = { 0, new JSON () };

    std::vector<struct assert > test = {
      { "{}", 0, Value::undefined, 0, PASS },
      { "{ } ", 0, Value::undefined, 1, PASS },
      { "{\"k\":\"v\"} ", 1, Value::string, 1, PASS },
      { "{ \"k\" : \"v\" } ", 1, Value::string, 1, PASS },
      { "{\"k\":\"v\",\"q\":\"p\"} ", 2, Value::string, 1, PASS },
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

          Object *o = new Object (p[pidx]);

          const char *readp = o->parse (startp);

          ASSERT_EQUAL_IDX ("value.readp", (startp + charc) - (*it).moveback, readp);
          ASSERT_EQUAL_IDX ("*(value.readp -1)", '}', *(readp - 1));
          ASSERT_EQUAL_IDX ("value.size", (*it).size, o->count ());

          if (o->count () > 0)
            {
              ASSERT_EQUAL_IDX ("value.type", (*it).type, o->at ("k").type ());
              ASSERT_EQUAL_IDX ("*(value.key)", (char) 'k', *(o->at ("k").key ()));
            }

          delete o;
        }
    TEST_IT_END;

    delete p[1];
  }

  void
  test_key ()
  {
    struct assert {
      const char *startp;
      // const char *key;
      int assert_status;
    };

    std::vector<struct assert > test = {
      { "{}", PASS },
      { "{ } ", PASS },
      { "{\"key1\":\"v\",\"key2\":\"v\",\"key3\":\"v\"} ", PASS },
    };

    TEST_IT_START;
      const char *startp = (*it).startp;

      Object *o = new Object ();

      (void) o->parse (startp);

      if (o->count () > 0)
        {
          size_t idx= 0;

          for (auto it = o->_member_list.begin (); it != o->_member_list.end (); ++it, idx++)
            {
              const char *k = (*it).first.c_str ();

              ASSERT_EQUAL_IDX ("value.key", 0, strcmp (k, o->at (k).key ()));
            }
        }

      delete o;

    TEST_IT_END
  }

  virtual void test_size_1 () {}

  virtual void
  test_at ()
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
  test__at ()
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
    Object *p = new Object ();

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

      Object *o = new Object (p);

      o->_readp = startp;
      bool status = o->_pair ();

      // readp = o->parse (startp);

      ASSERT_EQUAL_IDX ("status", (*it).status, status);

      delete o;

    TEST_IT_END;
  }


  virtual void
  test_assign_all_values ()
  {
    Object obj_parent;
    Array arr_parent;

    JSON *parents[] = {
      & obj_parent,
      & arr_parent,
      0
    };

    // Object old_value;

    struct assert {
      Value *new_value;
      Value::object_type type;
      const char *key;
      size_t index;
      size_t count;
      int assert_status[3];
    };

    std::vector<struct assert > test = {
      { new Object ("{\"k1\":true,\"k2\":false}"), Value::object, "key_1",  0, 1,  { PASS, PASS, PASS } },
      { new Array ("[]"), Value::array, "key_2",  0, 2,  { PASS, PASS, FAIL } },
      { new String ("\"x\""), Value::string, "key_3",  0, 3,  { PASS, PASS, FAIL } },
      { new Number (), Value::number, "key_4",  0, 4, { PASS, PASS, FAIL } },
      { new Boolean (true), Value::boolean, "key_5",  0, 5, { PASS, PASS, FAIL } },
      { new Null (), Value::null, "key_6",  0, 6, { PASS, PASS, FAIL } }
    };

    // arr_parent._element_list.reserve (6);

    for (size_t pidx = 0; pidx < 3; pidx++)
      {
          obj_parent._member_list.clear ();
          arr_parent._element_list.clear ();
          // old_value._parent = parents[pidx];

          for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++) {\
            try {\
                if ((*it).assert_status[pidx] == SKIP) { continue; }\
                if ((*it).assert_status[pidx] > PASS) { this->_errorc[EXPECTED]++; }

          /// old_value: value from Value[key], any value
          Object *old_value = new Object;
          old_value->_parent = parents[pidx];

          old_value->_member_list.clear ();
          arr_parent._element_list.push_back (new Undefined);
          old_value->setKey ((*it).key, strlen ((*it).key));

          (*it).index  = arr_parent._element_list.size () - 1;
          old_value->setIndex ((*it).index);

          // Value *new_value = 0;

          if ((*it).new_value->type () == Value::object)
            {
              Object *new_o_value = static_cast<Object *>((*it).new_value);
              old_value->_assign (*new_o_value);
              *old_value = *new_o_value;
              // new_value = new_o_value;
            }
          else
            {
              old_value->_assign (*(*it).new_value);
              *old_value = *(*it).new_value;
              // new_value = (*it).new_value;
            }

          JSON *parent = old_value->_parent;

          if (parent)
            {
              ASSERT_EQUAL_IDX ("old_value.parent.count ()", (*it).count, parent->count ());

              if (parent->type () == Value::object)
                {
                  Value *ov =  obj_parent._member_list.at ((*it).key);

                  ASSERT_EQUAL_IDX ("obj_parent[key].type", ov->type (), (*it).type);
                  // ASSERT_EQUAL_IDX ("obj_parent[key].value", ov, new_value);
                }
              else
                {
                  Value *av =  arr_parent._element_list.at ((*it).index);

                  ASSERT_EQUAL_IDX ("arr_parent[key].type", av->type (), (*it).type);
                  // ASSERT_EQUAL_IDX ("arr_parent[key].value", av, new_value);
                }
            }
          else
            {
              ASSERT_EQUAL_IDX ("old_value.size ()", /* new_value->count () */ (size_t) 2, old_value->count ());
            }

          delete old_value;
          old_value = 0;

          TEST_IT_END;
        }
  }

  virtual void
  test_operator_assign ()
  {
    // TODO: assign key => boolean to object_1: object_1[key] = boolean
    // TODO: assign object_2 to object_1: object_1 => object_2
  }

  virtual void
  test__clear ()
  {

    Object o = "{\"a\":true,\"b\":false}";
    o._clear ();

    CPPUNIT_ASSERT_EQUAL_MESSAGE ("object._member_list.size ()", (size_t) 0, o._member_list.size ());
  }

  virtual void test_operator_at () {}

  virtual void test_stringify () override {}

  virtual void
  test_strLength () override
  {
    // assert: {} = 2,
    // assert: {\"a\":null} = 2 + 3 + 1 + 4 = 10,
    // assert: {\"a\":null,\"b\":null} =  2 + 2 * (3 + 1 + 4) + 1  = 19
    // assert: {\"a\":null,\"b\":{}} = 2 + 3 + 1 + 4 + 1 + 3 + 1 + 2 = 17

    struct assert
    {
      const char *input;
      size_t length;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { "{}", 2, PASS },
      { "{\"a\":null}", 10, PASS },
      { "{\"a\":null,\"b\":null}", 19, PASS },
      { "{\"a\":null,\"b\":{}}", 17, PASS }
    };

    TEST_IT_START

        Object o = (*it).input;

        ASSERT_EQUAL_IDX ("o.strLength ()", (*it).length, o.strLength ());

    TEST_IT_END;
  }

  virtual void
  test_strValue () override
  {
    // return;
    Object p;

    JSON *parent[] = {
      0, &p
    };

    struct assert
    {
      const char *input;
      const char *output[2];
      int assert_status;
    };

    std::vector<struct assert> test = {
      { "{}", { "{}", "{\"a\":null,\"b\":{}" }, PASS },  // <-- last closing } intentionally missing

      /// !!! UNORDERED MAP HAS KEYS ARE IN DIFFERENT ORDER !!!:
      /// {"c":null,"d":{}} --> {"d":{},"c":null}
      { "{\"c\":null,\"d\":{}}", { "{\"d\":{},\"c\":null}", "{\"a\":null,\"b\":{\"d\":{},\"c\":null}" }, PASS },  // <-- last closing ] intentionally missing
    };

    TEST_IT_START

      for (size_t pidx = 0; pidx < 2; pidx++)
        {
          char *str_value = 0;

          size_t len = strlen ((*it).output[pidx]);

          Object o;

          o._parent = parent[pidx];

          if (o._parent)
            {
              str_value = new char[len +1 ] ();
              str_value = strncpy (str_value,  "{\"a\":null,\"b\":", 14);

              p._str_value[BEGIN]   = str_value;
              p._str_value[CURSOR]  = str_value + 14;
            }

          (void) o.parse ((*it).input);

          const char *output = o.strValue ();

          if (o._parent == 0)
            {
              // std::cout  << output  << std::endl;
              ASSERT_EQUAL_IDX ("strlen (output)", len, strlen (output));
              CPPUNIT_ASSERT_MESSAGE ("strcmp (output, (*it).output[0])", strcmp (output, (*it).output[0]) == 0);
            }
          else
            {
              // std::cout << p._str_value[BEGIN]  << std::endl;
              ASSERT_EQUAL_IDX ("strlen (p._str_value[BEGIN])", len, strlen (p._str_value[BEGIN]));
              CPPUNIT_ASSERT_MESSAGE ("strcmp (output, (*it).output[1])", strcmp (p._str_value[BEGIN], (*it).output[1]) == 0);
            }

            delete[] str_value;
      }

    TEST_IT_END;
  }

  virtual void
  test_erase () override
  {
    Object o;

    Value *v[3]= {
      new Boolean (),
      new Boolean (),
      new Boolean ()
    };

    v[0]->setKey ("key_1", 5);
    v[1]->setKey ("key_2", 5);
    v[2]->setKey ("key_3", 5);

    o._member_list = { { v[0]->key (), v[0] }, { v[1]->key (), v[1] } };

    struct assert
    {
      Value *value;
      size_t size;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { v[2], 2, PASS },
      { v[1], 1, PASS },
      { v[0], 0, PASS },
    };

    TEST_IT_START

      (void) o.erase (*(*it).value);
      size_t size = o.count ();

      ASSERT_EQUAL_IDX ("o.count ()", (*it).size, size);

    TEST_IT_END;
  }

  /**
   * Test number 2
   *
   * @brief suite
   * @return
   */
  static CppUnit::Test*
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json object test");

    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_erase", &json_object_test::test_erase));
    // return s;

    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_smoke", &json_object_test::test_ctor_dtor));
    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_assign_all_values", &json_object_test::test_assign_all_values));
    // return s;

    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_parse_1", &json_object_test::test_key));
    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_key", &json_object_test::test_parse_1));

//    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_size_1", &json_object_test::test_size_1));
    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_at_1", &json_object_test::test_at));
    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_at_1", &json_object_test::test__at));

//    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_value_1", &json_object_test::test_value_1));
//    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_debug_1", &json_object_test::test_debug_1));

    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_pair_1", &json_object_test::test__pair));
    s->addTest (new CppUnit::TestCaller<json_object_test> ("test__clear", &json_object_test::test__clear));

    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_strLength", &json_object_test::test_strLength));
    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_strvalue", &json_object_test::test_strValue));
//     s->addTest (new CppUnit::TestCaller<json_object_test> ("test_pair_1", &json_object_test::test__value));

     return s;
  }
};

#endif // JSON_OBJECT_TEST_H
