#ifndef JSON_ARRAY_TEST
#define JSON_ARRAY_TEST

#include "json_value_test_interface.h"

namespace Format {

/**
 * 3.
 * @brief The json_array_test class
 */
class json_array_test : public json_value_test_interface
{
public:

  virtual void
  test_ctor_dtor ()
  {
    json *p[] = { 0, new json };

    for (size_t pidx = 0; pidx < 2; pidx++)
      {
        array a[] = {
          array (),
          array (L"[]"),
          array (p[pidx]),
          array {new number (1)},
        };
      }

    delete p[1];

    array src = L"[true]";
    array copy = src;

    CPPUNIT_ASSERT_MESSAGE ("array", & copy != & src);
    CPPUNIT_ASSERT_MESSAGE ("array", & copy._element_list.at (0) != & src._element_list.at (0));
    CPPUNIT_ASSERT_EQUAL_MESSAGE ("array._element_list.size ()", (size_t) 1, copy._element_list.size ());
  }

  virtual void
  test_parse_1 ()
  {
    struct assert {
      const wchar_t *startp;
      size_t size;
      Value::object_type type; 
      int moveback;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { L"[]", 0, Value::object_type::array_t, 0, PASS },
      { L"[ ] ", 0, Value::object_type::array_t, 1, PASS },
      { L"[\t] ", 0, Value::object_type::array_t, 1, PASS },
      { L"[\r] ", 0, Value::object_type::array_t, 1, PASS },
      { L"[\n] ", 0, Value::object_type::array_t, 1, PASS },
      { L"[\"x\"]", 1, Value::object_type::array_t, 0, PASS },
      { L"[\"x\",\"x\"] ", 2, Value::object_type::array_t, 1, PASS },
      { L"[\"x\",\"x\",[\"x\"]] ", 3,  Value::object_type::array_t, 1, PASS },

      // errors
      { L"[", 0, Value::object_type::undefined_t, 0, FAIL },
      { L"[ ", 0, Value::object_type::undefined_t, 0, FAIL },
      { L"]", 0, Value::object_type::undefined_t, 0, FAIL },
      { L"[, ", 0, Value::object_type::undefined_t, 0, FAIL },
      { L"[ x ", 0, Value::object_type::undefined_t, 0, FAIL },
      { L"", 0, Value::object_type::undefined_t, 0, FAIL },
      { L" ", 0, Value::object_type::undefined_t, 0, FAIL },
      { L"x", 0, Value::object_type::undefined_t, 0, FAIL },
    };

    json *p[] = { 0, new json () };

    TEST_IT_START
      for (size_t pidx = 0; pidx < 2; pidx++)
        {
          const wchar_t *startp = (*it).startp;
          size_t charc = wcslen (startp);
          array *a = new array (p[pidx]);

          const wchar_t *readp = a->parse (startp);

          ASSERT_EQUAL_IDX ("array.readp", (startp + charc) - (*it).moveback, readp);
          ASSERT_EQUAL_IDX ("*(array.readp - 1)", L']', *(readp - 1));
          ASSERT_EQUAL_IDX ("array.size", (*it).size, a->count ());

          delete a;
        }
    TEST_IT_END;
  }

  void
  test_index ()
  {
    struct assert {
      const wchar_t *startp;
      int assert_status;
    };

    std::vector<struct assert > test = {
      { L"[]", PASS },
      { L"[ ] ", PASS },
      { L"[\"a\",\"b\",\"c\"]", PASS },
    };

    TEST_IT_START;
      const wchar_t *startp = (*it).startp;
      array *a = new array ();

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
    object obj_parent;
    array arr_parent;

    json *parents[] = {
      & obj_parent,
      & arr_parent,
      0
    };

    // Array old_value;

    struct assert {
      Value *new_value;
      Value::object_type type;
      const wchar_t *key;
      size_t index;
      size_t count;
      int assert_status[3];
    };

    std::vector<struct assert > test = {
      { new array (L"[true,false]"), Value::array_t, L"key_2",  0, 1,  { PASS, PASS, PASS } },
      { new object (L"{\"k1\":true,\"k2\":false}"), Value::object_t, L"key_1",  0, 2,  { PASS, PASS, FAIL } },
      { new string (L"\"x\""), Value::string_t, L"key_3",  0, 3,  { PASS, PASS, FAIL } },
      { new number (), Value::number_t, L"key_4",  0, 4, { PASS, PASS, FAIL } },
      { new Boolean (true), Value::boolean_t, L"key_5",  0, 5, { PASS, PASS, FAIL } },
      { new null (), Value::null_t, L"key_6",  0, 6, { PASS, PASS, FAIL } }
    };
      arr_parent._element_list.reserve (6);

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

          array *old_value = new array;
          old_value->_parent = parents[pidx];

          old_value->_element_list.clear ();
          arr_parent._element_list.push_back (new Format::undefined);
          old_value->setKey ((*it).key, wcslen ((*it).key) /* (*it).keylen */);

          (*it).index  = arr_parent._element_list.size () - 1;
          old_value->setIndex ((*it).index);

          // Value *new_value = 0;

          if ((*it).new_value->type () == Value::array_t)
            {
              array *new_a_value = static_cast<array *>((*it).new_value);

              // old_value->_assign (*new_a_value);
              *old_value = *new_a_value;

              // new_value = new_a_value;
            }
          else
            {
              // old_value->_assign (*(*it).new_value);
              *old_value = *(*it).new_value;

              // new_value = (*it).new_value;
            }

          json *parent = parents[pidx]; // old_value->_parent;

          if (parent)
            {
              ASSERT_EQUAL_IDX ("old_value.parent.count ()", (*it).count, parent->count ());

              if (parent->type () == Value::object_t)
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
              ASSERT_EQUAL_IDX ("old_value.size ()", (size_t) 2, old_value->count ());
            }

          TEST_IT_END;
        }

        for (auto it = test.begin (); it != test.end (); ++it)
          delete (*it).new_value;
  }

  virtual void
  test_operator_at_key ()
  {
    array a;

    a._element_list.push_back (new Boolean (true));

    struct assert
    {
      const wchar_t *key;
      Value::object_type type;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { L"0", Value::object_type::boolean_t, PASS },
      { L"1", Value::object_type::undefined_t, PASS },
      { L"x", Value::object_type::boolean_t, PASS }   // Converted to 0
    };

    TEST_IT_START

        const Value & v = a[((*it).key)]; // Array::_at("key") tries to convert "key" to size_t

        ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());

    TEST_IT_END;
  }

  virtual void
  test_operator_at_index ()
  {
    array a;

    a._element_list.push_back (new Boolean (true));

    struct assert
    {
      size_t index;
      Value::object_type type;
      int assert_status;
    };

    std::vector<struct assert> test = {


      { 0, Value::object_type::boolean_t, PASS },
      { 1, Value::object_type::undefined_t, PASS }

    };

    TEST_IT_START

      const Value & v = a [(*it).index];

      ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());

    TEST_IT_END;
  }

  virtual void
  test__clear ()
  {
    array a = L"[true, false]";
    a._clear ();

    CPPUNIT_ASSERT_EQUAL_MESSAGE ("array._element_list.size ()", (size_t) 0, a._element_list.size ());
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
      const wchar_t *input;
      size_t length;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { L"[]", 2, PASS },
      { L"[null]", 6, PASS },
      { L"[null,null]", 11, PASS },
      { L"[null,[]]", 9, PASS },
    };

    TEST_IT_START

        array a = (*it).input;

        ASSERT_EQUAL_IDX ("a.strLength ()", (*it).length, a.strLength ());

    TEST_IT_END;
  }

  virtual void
  test_strValue () override
  {
    array p;

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
      { L"[]",
        { L"[]",  // Without parent
          L"[\"x\",[]" }, PASS },  // <-- last closing ] intentionally missing
      { L"[false,[true]]",
        { L"[false,[true]]",  // Without parent
          L"[\"x\",[false,[true]]" }, PASS },  // <-- last closing ] intentionally missing
    };

    TEST_IT_START

        for (size_t pidx = 0; pidx < 2; pidx++)
          {
            wchar_t *str_value = 0;

            size_t len = wcslen ((*it).output[pidx]);

            array a;

            a._parent = parent[pidx];

            if (a._parent)
              {
                str_value = new wchar_t[len +1 ] ();
                str_value = wcsncpy (str_value,  L"[\"x\",", 5);

                p._str_value[BEGIN]   = str_value;
                p._str_value[OFFSET]  = str_value + 5;
              }

            (void) a.parse ((*it).input);

            const wchar_t *output = a.strValue (a._parent ? p._str_value[OFFSET] : 0);

            if (a._parent == 0)
              {
                ASSERT_EQUAL_IDX ("strlen (output)", len, wcslen (output));
                CPPUNIT_ASSERT_MESSAGE ("strcmp (output, (*it).output[0])", wcscmp (output, (*it).output[0]) == 0);
              }
            else
              {
                ASSERT_EQUAL_IDX ("strlen (p._str_value[BEGIN])", len, wcslen (p._str_value[BEGIN]));
                CPPUNIT_ASSERT_MESSAGE ("strcmp (output, (*it).output[1])", wcscmp (p._str_value[BEGIN], (*it).output[1]) == 0);
              }

            //if (a._parent == 0) delete[] str_value;
          }

    TEST_IT_END;

  }

  virtual void
  test_erase () override
  {
    array a;

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

  virtual void test__at () override {}
  // virtual void test_size_1 () {}

  /**
   * 3.
   * @brief suite
   * @return
   */
  static CppUnit::Test *
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json array test");

    /* 0. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_strValue", &json_array_test::test_strValue));
    /* 1. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_strValue", &json_array_test::test_strLength));
    /* 2. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_ctor_dtor", &json_array_test::test_ctor_dtor));
    /* 3. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_parse_1", &json_array_test::test_parse_1));
    /* 4. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_index", &json_array_test::test_index));
    /* 5. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_operator_at_key", &json_array_test::test_operator_at_key));
    /* 6. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_operator_at_index", &json_array_test::test_operator_at_index));
    /* 7. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_assign_all_values", &json_array_test::test_assign_all_values));
    /* 8. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test__clear", &json_array_test::test__clear));
    /* 9. */  s->addTest (new CppUnit::TestCaller<json_array_test> ("test_erase", &json_array_test::test_erase));

    return s;
  }
};
}
#endif // JSON_ARRAY_TEST

