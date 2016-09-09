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

    JSON *p[] = { 0, new JSON () };

    for (size_t pidx = 0; pidx < 2; pidx++)
      {
        Object *o[] = {
          new Object (),
          new Object (input),
          new Object (p[pidx]),
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

    JSON *p[] = { 0, new JSON () };

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

          Object *o = new Object (/* (*it).parent */ p[pidx]);

          const char *readp = o->parse (startp);

          ASSERT_EQUAL_IDX ("value.readp", (startp + charc) - (*it).moveback, readp);
          ASSERT_EQUAL_IDX ("*(value.readp -1)", '}', *(readp - 1));
          ASSERT_EQUAL_IDX ("value.size", (*it).size, o->size ());

          if (o->size () > 0)
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

      if (o->size () > 0)
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
      &obj_parent,
      &arr_parent,
      0
    };

    Object old_value;

    struct assert {
      Value *new_value;
      Value::object_type type;
      const char *key;
      size_t keylen;
      size_t index;
      size_t count;
      int assert_status[3];
    };

    std::vector<struct assert > test = {
      { new Object ("{\"k\":true}"), Value::object, "o_key",  5, 0, 1,  { PASS, PASS, PASS }},
//      { new Array (), { FAIL, PASS }, SKIP },
//      { new String (), { FAIL, PASS }, SKIP },
//      { new Number (), { FAIL, PASS }, SKIP },
//      { new Boolean (true), { FAIL, PASS }, SKIP },
//      { new Null (), { FAIL, PASS }, SKIP },
//      { new Undefined (), { PASS, PASS }, SKIP },
    };
      arr_parent._element_list.reserve (7);

      for (size_t pidx = 0; pidx < 3; pidx++)
        {
          old_value._parent = parents[pidx];
          old_value._member_list.clear ();

          obj_parent._member_list.clear ();
          arr_parent._element_list.clear ();

          for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++) {\
            try {\
                if ((*it).assert_status[pidx] == SKIP) { continue; }\
                if ((*it).assert_status[pidx] > PASS) { this->_errorc[EXPECTED]++; }

          /// old_value: value from Value[key], any value

          arr_parent._element_list.push_back (new Undefined);
          old_value.setKey ((*it).key, (*it).keylen);

          (*it).index  = arr_parent._element_list.size () - 1;
          old_value.setIndex ((*it).index);

          Value *new_value = 0;

          switch ((*it).new_value->type ())
            {
            case Value::object:
              {
                Object *new_o_value = static_cast<Object *>((*it).new_value);
                old_value.assign (*new_o_value);
                new_value = new_o_value;
                break;
              }
            case Value::array:
              {
                Array *new_a_value = static_cast<Array *>((*it).new_value);
//                old_value.assign (*new_a_value);
                new_value = new_a_value;
                break;
              }
            case Value::string:
              {
                String *new_s_value = static_cast<String *>((*it).new_value);
                // old_value.assign (*new_s_value);
                new_value = new_s_value;
                break;
              }
            case Value::number:
              {
                Number *new_n_value = static_cast<Number *>((*it).new_value);
                // old_value.assign (*new_n_value);
                new_value = new_n_value;
                break;
              }
            case Value::boolean:
              {
                Boolean *new_b_value = static_cast<Boolean *>((*it).new_value);
                // old_value.assign (*new_b_value);
                new_value = new_b_value;
                break;
              }
            case Value::null:
              {
                Null *new_nl_value = static_cast<Null *>((*it).new_value);
                // old_value.assign (*new_nl_value);
                new_value = new_nl_value;
                break;
              }
            case Value::undefined:
              {
                Undefined *new_u_value = static_cast<Undefined *>((*it).new_value);
                // old_value.assign (*new_u_value);
                new_value = new_u_value;
                break;
              }
            default:
              break;
            }

          JSON *parent = old_value._parent;

          if (parent)
            {
              ASSERT_EQUAL_IDX ("old_value.parent.count ()", (size_t) 1, parent->size ());

              if (parent->type () == Value::object)
                {

                  Value *ov =  obj_parent._member_list.at ((*it).key);

                  ASSERT_EQUAL_IDX ("obj_parent[key].type", ov->type (), (*it).type);
                  ASSERT_EQUAL_IDX ("obj_parent[key].value", ov, (*it).new_value);
                }
              else
                {
                  Value *av =  arr_parent._element_list.at ((*it).index);
                  ASSERT_EQUAL_IDX ("arr_parent[key].type", av->type (), (*it).type);
                  ASSERT_EQUAL_IDX ("arr_parent[key].value", av, (*it).new_value);

                }
            }
          else
            {

            }

///       TODO: if old_value.parent: assert old_value.parent.count = 1 else: assert old_value.count () == 1
///       TODO: if old_value.parent && old_value.parent.type == object: assert old_value.parent._at(key) == (*it).new_value
///       TODO: if old_value.parent && old_value.parent.type == array: assert old_value.parent._at(index) == (*it).new_value

          TEST_IT_END;
        }
  }

  static CppUnit::Test*
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json object test");

    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_assign_all_values", &json_object_test::test_assign_all_values));
    //return s;

     s->addTest (new CppUnit::TestCaller<json_object_test> ("test_smoke", &json_object_test::test_ctor_dtor));
  //    return s;
      s->addTest (new CppUnit::TestCaller<json_object_test> ("test_parse_1", &json_object_test::test_key));
      s->addTest (new CppUnit::TestCaller<json_object_test> ("test_key", &json_object_test::test_parse_1));
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
