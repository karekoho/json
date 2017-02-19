#ifndef JSON_STRING_TEST_H
#define JSON_STRING_TEST_H

#include "json_value_test_interface.h"
namespace Format {
/// Test number 4
class json_string_test : public json_value_test_interface
{
public:
  virtual void
  test_ctor_dtor ()
  {
    JSON *p[] = { 0, new JSON () };

    for (size_t pidx = 0; pidx < 2; pidx++)
      {
        String *a[] = {
          new String (),
          new String (L"\"x\""),
          new String (p[pidx], 1),
        };

        delete a[0];
        delete a[1];
        delete a[2];
      }

    delete p[1];

    String src = L"\"xxx\"";
    String copy = src;

    CPPUNIT_ASSERT_MESSAGE ("string", & copy != & src);
    CPPUNIT_ASSERT_EQUAL_MESSAGE ("src._string_value.empty ()", true, src._string_value[0].empty () );
    CPPUNIT_ASSERT_MESSAGE ("copy.value ()", wcscmp (L"xxx", copy.value ()) == 0);
  }

  virtual void
  test_parse_1 ()
    {
      JSON *p[] = { 0, new JSON () };

      struct assert
      {
        const wchar_t *startp;
        size_t charc;
        wchar_t endc;
        int assert_status;
      };

      std::vector<struct assert > test = {
          { L"\"\"", 0, (wchar_t) 0, PASS },
          { L"\"xxx\"", 3, (wchar_t) 0, PASS },
          { L"\" xxx \"", 5, (wchar_t) 0, PASS },
          { L"\" xxx \" ", 5, L' ', PASS },
      };

      TEST_IT_START
          for (int pidx = 0; pidx < 2; pidx++)
            {
              const wchar_t *startp = (*it).startp;
              size_t move = (*it).charc + 2;

              String *s = new String (p[pidx], move);

              std::wstring ss = s->value ();

              CPPUNIT_ASSERT_MESSAGE ("string.empty ()", ss.empty () );

              const wchar_t *readp = s->parse (startp);
              ss = s->value ();

              // std::cout << readp << "" << ss.length () << " " << ss << std::endl;

              ASSERT_EQUAL_IDX ("string.readp", readp, startp + move);
              ASSERT_EQUAL_IDX ("*(string.readp)", (wchar_t)* readp, (*it).endc);
              ASSERT_EQUAL_IDX ("string.length", (*it).charc, ss.length () );

              delete s;
            }
       TEST_IT_END;

       delete p[1];
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

      struct assert {
        Value *new_value;
        Value::object_type type;
        const wchar_t *key;
        size_t index;
        size_t count;
        int assert_status[3];
      };

      std::vector<struct assert > test = {
        { new Array (L"[true,false]"), Value::array_t, L"key_1",  0, 1,  { PASS, PASS, FAIL } },
        { new Object (L"{\"k1\":true,\"k2\":false}"), Value::object_t, L"key_2",  0, 2,  { PASS, PASS, FAIL } },
        { new String (L"\"xxx\""), Value::string_t, L"key_3",  0, 3,  { PASS, PASS, PASS } },
        { new Number (10), Value::number_t, L"key_4",  0, 4, { PASS, PASS, FAIL } },
        { new Boolean (true), Value::boolean_t, L"key_6",  0, 5, { PASS, PASS, FAIL } },
        { new Null, Value::null_t, L"key_7",  0, 6, { PASS, PASS, FAIL } }
      };

      for (size_t pidx = 0; pidx < 3; pidx++)
        {
            obj_parent._member_list.clear ();
            arr_parent._element_list.clear ();

            for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++) {\
              try {\
                  if ((*it).assert_status[pidx] == SKIP) { continue; }\
                  if ((*it).assert_status[pidx] > PASS) { this->_errorc[EXPECTED]++; }

            /// old_value: value from Value[key], any value

            String *old_value = new String ();
            old_value->_parent = parents[pidx];

            arr_parent._element_list.push_back (new Format::Undefined);
            old_value->setKey ((*it).key, wcslen ((*it).key));

            (*it).index  = arr_parent._element_list.size () - 1;
            old_value->setIndex ((*it).index);

            Value *new_value = 0;

            if ((*it).new_value->type () == Value::string_t)
              {
                String *new_a_value = static_cast<String *>((*it).new_value);

                // old_value->_assign (*new_a_value);
                *old_value = *new_a_value;

                new_value = new_a_value;
              }
            else
              {
                // old_value->_assign (*(*it).new_value);
                *old_value = *(*it).new_value;

                new_value = (*it).new_value;
              }

            JSON *parent = parents[pidx];   //  old_value->_parent;

            if (parent)
              {
                ASSERT_EQUAL_IDX ("old_value.parent.count ()", (*it).count, parent->count ());

                if (parent->type () == Value::object_t)
                  {
                    Value *ov =  obj_parent._member_list.at ((*it).key);

                    ASSERT_EQUAL_IDX ("obj_parent[key].type", ov->type (), (*it).type);
                    //ASSERT_EQUAL_IDX ("obj_parent[key].value", ov, new_value);
                  }
                else
                  {
                    Value *av =  arr_parent._element_list.at ((*it).index);

                    ASSERT_EQUAL_IDX ("arr_parent[key].type", av->type (), (*it).type);
                    //ASSERT_EQUAL_IDX ("arr_parent[key].value", av, new_value);
                  }
              }
            else if (new_value->type () == Value::string_t)
              {
                CPPUNIT_ASSERT_MESSAGE ("old_value.value ()", wcscmp (L"xxx", old_value->value ()) == 0);
              }

            TEST_IT_END;
          }

        for (auto it = test.begin (); it != test.end (); ++it)
          delete (*it).new_value;
    }

    virtual void test_erase () override {}

    virtual void test_stringify () override {}

    virtual void test_strLength () override {}
    virtual void test_strValue () override {}

    virtual void test__clear() {}

    virtual void test_operator_assign () {}
    virtual void test_operator_at () {}

    virtual void test_size_1() {}
    virtual void test_at() {}
    virtual void test_value_1() {}
    virtual void test_debug_1() {}

    /**
     * 4.
     *
     * @brief suite
     * @return
     */
    static CppUnit::Test*
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json string test");

      s->addTest (new CppUnit::TestCaller<json_string_test> ("test_ctor_dtor", &json_string_test::test_ctor_dtor));
      s->addTest (new CppUnit::TestCaller<json_string_test> ("test_parse_1", &json_string_test::test_parse_1));
      s->addTest (new CppUnit::TestCaller<json_string_test> ("test_assign_all_values", &json_string_test::test_assign_all_values));

      return s;
    }
};
}
#endif // JSON_STRING_TEST_H
