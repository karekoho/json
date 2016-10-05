#ifndef JSON_ARRAY_TEST
#define JSON_ARRAY_TEST

#include "json_value_test_interface.h"

/// Test number 3
class json_array_test : public json_value_test_interface
{
public:

  virtual void
  test_ctor_dtor ()
  {
    JSON *p[] = { 0, new JSON };

    for (size_t pidx = 0; pidx < 2; pidx++)
      {
        Array *a[] = {
          new Array,
          new Array ("[]"),
          new Array (p[pidx]),
        };

        delete a[0];
        delete a[1];
        delete a[2];
      }

    delete p[1];

    Array src = "[true]";
    Array copy = src;

    CPPUNIT_ASSERT_MESSAGE ("array", & copy != & src);
    CPPUNIT_ASSERT_MESSAGE ("array", & copy._element_list.at (0) != & src._element_list.at (0));
    CPPUNIT_ASSERT_EQUAL_MESSAGE ("array._element_list.size ()", (size_t) 1, copy._element_list.size ());
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
          ASSERT_EQUAL_IDX ("array.size", (*it).size, a->count ());

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

      if (a->count () > 0)
        {
          for (size_t idx = 0; idx < a->_element_list.size (); idx++)
            {
              Value *v = a->_element_list.at (idx);
              ASSERT_EQUAL_IDX ("value.index", idx, v->index ());
            }
        }
      delete a;
    TEST_IT_END
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

    Array old_value;

    struct assert {
      Value *new_value;
      Value::object_type type;
      const char *key;
      size_t index;
      size_t count;
      int assert_status[3];
    };

    std::vector<struct assert > test = {
      { new Array ("[true,false]"), Value::array, "key_2",  0, 1,  { PASS, PASS, PASS }  },
      { new Object ("{\"k1\":true,\"k2\":false}"), Value::object, "key_1",  0, 2,  { PASS, PASS, FAIL }},
      { new String ("\"x\""), Value::string, "key_3",  0, 3,  { PASS, PASS, FAIL }  },
      { new Number (), Value::number, "key_4",  0, 4, { PASS, PASS, FAIL } },
      { new Boolean (true), Value::boolean, "key_5",  0, 5, { PASS, PASS, FAIL } },
      { new Null (), Value::null, "key_6",  0, 6, { PASS, PASS, FAIL } }
    };
      arr_parent._element_list.reserve (6);

      for (size_t pidx = 0; pidx < 3; pidx++)
        {
          obj_parent._member_list.clear ();
          arr_parent._element_list.clear ();
          old_value._parent = parents[pidx];

          for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++) {\
            try {\
                if ((*it).assert_status[pidx] == SKIP) { continue; }\
                if ((*it).assert_status[pidx] > PASS) { this->_errorc[EXPECTED]++; }

          /// old_value: value from Value[key], any value

          old_value._element_list.clear ();
          arr_parent._element_list.push_back (new Undefined);
          old_value.setKey ((*it).key, strlen ((*it).key) /* (*it).keylen */);

          (*it).index  = arr_parent._element_list.size () - 1;
          old_value.setIndex ((*it).index);

          // Value *new_value = 0;

          if ((*it).new_value->type () == Value::array)
            {
              Array *new_a_value = static_cast<Array *>((*it).new_value);
              // old_value._assign (*new_a_value);
              old_value = *new_a_value;
              // new_value = new_a_value;
            }
          else
            {
              // old_value._assign (*(*it).new_value);
              old_value = *(*it).new_value;
              // new_value = (*it).new_value;
            }

          JSON *parent = old_value._parent;

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

                  ASSERT_EQUAL_IDX ("arr_parent[index].type", av->type (), (*it).type);
                  // ASSERT_EQUAL_IDX ("arr_parent[index].value", av, new_value);
                }
            }
          else
            {
              ASSERT_EQUAL_IDX ("old_value.size ()", (size_t) 2, old_value.count ());
            }
          TEST_IT_END;
        }
  }

  virtual void test_size_1 () {}

  virtual void
  test_at ()
  {
    Array a;

    a._element_list.push_back (new Boolean (true));

    struct assert
    {
      size_t index;
      Value::object_type type;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { 0, Value::object_type::boolean, PASS },
      { 1, Value::object_type::undefined, FAIL }
    };

    TEST_IT_START

        const Value & v = a.at ((*it).index);

        ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());

    TEST_IT_END;
  }

  virtual void
  test__at ()
  {
    Array a;

    a._element_list.push_back (new Boolean (true));

    struct assert
    {
      size_t index;
      Value::object_type type;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { 0, Value::object_type::boolean, PASS },
      { 1, Value::object_type::undefined, PASS }
    };

    TEST_IT_START

      const Value & v = a._at ((*it).index);

      ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());

    TEST_IT_END;
  }

  virtual void
  test__clear ()
  {
    Array a = "[true, false]";
    a._clear ();

    CPPUNIT_ASSERT_EQUAL_MESSAGE ("array._element_list.size ()", (size_t) 0, a._element_list.size ());
  }

  virtual void
  test_stringify () override
  {
    // parents: 0, array
    // []
    // [\"x\",100,true,null]
  }

  virtual void
  test_strLength () override
  {
    // assert: [] = 2,
    // assert: [null] = 2 + 4 = 6,
    // assert: [null,null] = 2 + (2 * 4) + 1 = 11;
    // assert: [null,[]] = 2 + 4 + 1 + 2 = 9

    struct assert
    {
      const char *input;
      size_t length;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { "[]", 2, PASS },
      { "[null]", 6, PASS },
      { "[null,null]", 11, PASS },
      { "[null,[]]", 9, PASS },
    };

    TEST_IT_START

        Array a = (*it).input;

        ASSERT_EQUAL_IDX ("a.strLength ()", (*it).length, a.strLength ());

    TEST_IT_END;
  }

  virtual void
  test_strValue () override
  {
    Array p;

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
      { "[]", { "[]", "[\"x\",[]" }, PASS },  // <-- last closing ] intentionally missing
      { "[false,[true]]", { "[false,[true]]", "[\"x\",[false,[true]]" }, PASS },  // <-- last closing ] intentionally missing
    };

    TEST_IT_START

        for (size_t pidx = 0; pidx < 2; pidx++)
          {
            char *str_value = 0;

            size_t len = strlen ((*it).output[pidx]);

            Array a;

            a._parent = parent[pidx];

            if (a._parent)
              {
                str_value = new char[len +1 ] ();
                str_value = strncpy (str_value,  "[\"x\",", 5);

                p._str_value[BEGIN]   = str_value;
                p._str_value[CURSOR]  = str_value + 5;
              }

            (void) a.parse ((*it).input);

            const char *output = a.strValue ();

            if (a._parent == 0)
              {
                ASSERT_EQUAL_IDX ("strlen (output)", len, strlen (output));
                CPPUNIT_ASSERT_MESSAGE ("strcmp (output, (*it).output[0])", strcmp (output, (*it).output[0]) == 0);
              }
            else
              {
                ASSERT_EQUAL_IDX ("strlen (p._str_value[BEGIN])", len, strlen (p._str_value[BEGIN]));
                CPPUNIT_ASSERT_MESSAGE ("strcmp (output, (*it).output[1])", strcmp (p._str_value[BEGIN], (*it).output[1]) == 0);
              }

            // std::cout << p._str_value[BEGIN]  << output  << std::endl;

            delete[] str_value;
          }

    TEST_IT_END;

  }

  virtual void
  test_erase () override
  {
    Array a;

    Value *v[3]= {
      new Boolean (),
      new Boolean (),
      new Boolean ()
    };

    v[0]->setIndex (0);
    v[1]->setIndex (1);
    v[2]->setIndex (2);

    a._element_list = { v[0], v[1] };

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

         (void) a.erase (*(*it).value);
         size_t size = a.count ();

         ASSERT_EQUAL_IDX ("a.count ()", (*it).size, size);

     TEST_IT_END;
  }

  virtual void test_operator_assign () {}
  virtual void test_operator_at () {}

  virtual void test_value_1 () {}
  virtual void test_debug_1 () {}

  /**
   * Test number 3
   * @brief suite
   * @return
   */
  static CppUnit::Test *
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json array test");

    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_strValue", &json_array_test::test_strValue));
    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_strValue", &json_array_test::test_strLength));
    // return s;

    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_ctor_dtor", &json_array_test::test_ctor_dtor));
    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_parse_1", &json_array_test::test_parse_1));
    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_index", &json_array_test::test_index));

    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_at", &json_array_test::test_at));
    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_at", &json_array_test::test__at));

    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_assign_all_values", &json_array_test::test_assign_all_values));
    s->addTest (new CppUnit::TestCaller<json_array_test> ("test__clear", &json_array_test::test__clear));

    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_erase", &json_array_test::test_erase));

//    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_size_1", &json_array_test::test_size_1));
//    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_get_1", &json_array_test::test_get_1));
//    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_value_1", &json_array_test::test_value_1));
//    s->addTest (new CppUnit::TestCaller<json_array_test> ("test_debug_1", &json_array_test::test_debug_1));

    return s;
  }



};

#endif // JSON_ARRAY_TEST

