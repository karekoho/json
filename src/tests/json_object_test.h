#ifndef JSON_OBJECT_TEST_H
#define JSON_OBJECT_TEST_H

#include <json_value_test_interface.h>
namespace format {
/**
 * 2.
 * @brief The json_object_test class
 */
class json_object_test : public json_value_test_interface
{
public:

  virtual void
  test_ctor_dtor ()
  {
    json *p[] = { 0, new json () };

    for (size_t pidx = 0; pidx < 2; pidx++)
      {
        object o[] = {
          object (),
          object (L"{}"),
          object (p[pidx]),
          object {{L"1", new number (1)}}
        };
      }

    delete p[1];

    object src  = L"{\"key\":true}";
    object copy = src;

    CPPUNIT_ASSERT_MESSAGE ("object", & copy != & src);
    CPPUNIT_ASSERT_EQUAL_MESSAGE ("object._member_list.size ()", (size_t) 1, copy._member_list.size ());
  }

  virtual
  void test_parse_1 ()
  {
    struct assert {
      const wchar_t *startp;
      size_t size;
      value::object_type type;
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

    TEST_IT_START;
      for (int pidx = 0; pidx < 2; pidx++)
        {
          const wchar_t *startp = (*it).startp;

          size_t charc = wcslen (startp);

          object *o = new object (p[pidx]);

          const wchar_t *readp = o->parse (startp);

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
    TEST_IT_END;

    delete p[1];
  }

  void
  test_key ()
  {
    struct assert {
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

      (void) o->parse (startp);

      if (o->count () > 0)
        {
          size_t idx= 0;

          for (auto it = o->_member_list.begin (); it != o->_member_list.end (); ++it, idx++)
            {
              const wchar_t *k = (*it).first.c_str ();
              object & oo = *o;
              ASSERT_EQUAL_IDX ("value.key", 0, wcscmp (k, oo[k].key ()));
            }
        }

      delete o;

    TEST_IT_END
  }

  virtual void test_size_1 () {}

  virtual void
  test_operator_at_key ()
  {
    object o;

    o._member_list.emplace (L"0", new Boolean (true));

    struct assert {
      const wchar_t *key;
      value::object_type type;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { L"0", value::object_type::boolean_t, PASS },
      { L"1", value::object_type::undefined_t, PASS }
    };

    TEST_IT_START

      const value & v = o[((*it).key)];

      ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());

    TEST_IT_END;
  }

  virtual void
  test_operator_at_index ()
  {
    object o;
    CPPUNIT_ASSERT_EQUAL_MESSAGE ("o[size_t].type ()", value::undefined_t, o[(size_t) 0].type ());
  }

  virtual void
  test__at ()
  {
    object o;

    o._member_list.emplace (L"key1", new Boolean (true));

    struct assert {
      const wchar_t *key;
      value::object_type type;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { L"key1", value::object_type::boolean_t, PASS },
      { L"key2", value::object_type::undefined_t, PASS }
    };

    TEST_IT_START

      const value & _v = o._at ((*it).key);

      ASSERT_EQUAL_IDX ("_v.type ()", (*it).type, _v.type ());

    TEST_IT_END;
  }


  virtual void test_value_1 () {}
  virtual void test_debug_1 () {}

  void
  test__pair ()
  {
    object *p = new object ();

    struct assert {
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

    TEST_IT_START;

      const wchar_t *startp = (*it).startp;

      object *o = new object (p);

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
    object obj_parent;
    array arr_parent;

    json *parents[] = {
      & obj_parent,
      & arr_parent,
      0
    };

    // Object old_value;

    struct assert {
      value *new_value;
      value::object_type type;
      const wchar_t *key;
      size_t index;
      size_t count;
      int assert_status[3];
    };

    std::vector<struct assert > test = {
      { new object (L"{\"k1\":true,\"k2\":false}"), value::object_t, L"key_1",  0, 1,  { PASS, PASS, PASS } },
      { new array (L"[]"), value::array_t, L"key_2",  0, 2,  { PASS, PASS, FAIL } },
      { new string (L"\"x\""), value::string_t, L"key_3",  0, 3,  { PASS, PASS, FAIL } },
      { new number (), value::number_t, L"key_4",  0, 4, { PASS, PASS, FAIL } },
      { new Boolean (true), value::boolean_t, L"key_5",  0, 5, { PASS, PASS, FAIL } },
      { new null (), value::null_t, L"key_6",  0, 6, { PASS, PASS, FAIL } }
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
          object *old_value = new object;
          old_value->_parent = parents[pidx];

          old_value->_member_list.clear ();
          arr_parent._element_list.push_back (new format::undefined);

          old_value->setKey ((*it).key, wcslen ((*it).key));

          (*it).index  = arr_parent._element_list.size () - 1;
          old_value->setIndex ((*it).index);

          value *new_value = 0;

          if ((*it).new_value->type () == value::object_t)
            {
              object *new_o_value = static_cast<object *>((*it).new_value);

              // old_value->_assign (*new_o_value); // Can't do. *old_value is free'd
              *old_value = *new_o_value;

              new_value = new_o_value;
            }
          else
            {
              // old_value->_assign (*(*it).new_value); // Can't do. *old_value is free'd
              *old_value = *(*it).new_value;

              new_value = (*it).new_value;
            }

          json *parent = parents[pidx];

          if (parent)
            {
              ASSERT_EQUAL_IDX ("old_value.parent.count ()", (*it).count, parent->count ());

              if (parent->type () == value::object_t)
                {
                  value *ov =  obj_parent._member_list.at ((*it).key);

                  ASSERT_EQUAL_IDX ("obj_parent[key].type", ov->type (), (*it).type);
                  // ASSERT_EQUAL_IDX ("obj_parent[key].value", ov, new_value);
                }
              else
                {
                  value *av =  arr_parent._element_list.at ((*it).index);

                  ASSERT_EQUAL_IDX ("arr_parent[key].type", av->type (), (*it).type);
                  // ASSERT_EQUAL_IDX ("arr_parent[key].value", av, new_value);
                }
            }
          else
            {
              ASSERT_EQUAL_IDX ("old_value.size ()", (size_t) 2, old_value->count ());
            }

          TEST_IT_END;
        }

        for (auto it = test.begin (); it != test.end (); ++it)
          delete (*it).new_value;
  }


  virtual void
  test__clear ()
  {
    object o = L"{\"a\":true,\"b\":false}";
    o._clear ();

    CPPUNIT_ASSERT_EQUAL_MESSAGE ("object._member_list.size ()", (size_t) 0, o._member_list.size ());
  }

  virtual void
  test_strLength () override
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

        ASSERT_EQUAL_IDX ("o.strLength ()", (*it).length, o.strLength ());

    TEST_IT_END;
  }

  virtual void
  test_strValue () override
  {
    // return;
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

          object o;

          o._parent = parent[pidx];

          if (o._parent)
            {
              str_value = new wchar_t[len +1 ] ();
              str_value = wcsncpy (str_value,  L"{\"a\":null,\"b\":", 14);

              p._str_value[BEGIN]   = str_value;
              p._str_value[OFFSET]  = str_value + 14;
            }

          (void) o.parse ((*it).input);

          const wchar_t *output = o.strValue (o._parent ? p._str_value[OFFSET] : 0);

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

          //if (o._parent == 0) delete[] str_value;
      }

    TEST_IT_END;
  }

  virtual void
  test_erase () override
  {
    object o;

    value *v[3]= {
      new Boolean (),
      new Boolean (),
      new Boolean ()
    };

    v[0]->setKey (L"key_1", 5);
    v[1]->setKey (L"key_2", 5);
    v[2]->setKey (L"key_3", 5);

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
  }

  void test_strValue_2 ()
  {
    /* JSON j = L"{\
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
    }"; */
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
    /* 9. */ s->addTest (new CppUnit::TestCaller<json_object_test> ("test_strLength", &json_object_test::test_strLength));
    /* 10. */ s->addTest (new CppUnit::TestCaller<json_object_test> ("test_strvalue", &json_object_test::test_strValue));

     return s;
  }
};
}
#endif // JSON_OBJECT_TEST_H
