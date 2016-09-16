#ifndef JSON_STRING_TEST_H
#define JSON_STRING_TEST_H

#include "json_value_test_interface.h"

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
          new String ("\"x\""),
          new String (p[pidx], 1),
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
      JSON *p[] = { 0, new JSON () };

      struct assert
      {
        const char *startp;
        size_t charc;
        char endc;
        int assert_status;
      };

      std::vector<struct assert > test = {
          { "\"\"", 0, (char) 0, PASS },
          { "\"xxx\"", 3, (char) 0, PASS },
          { "\" xxx \"", 5, (char) 0, PASS },
          { "\" xxx \" ", 5, ' ', PASS },
      };

      TEST_IT_START
          for (int pidx = 0; pidx < 2; pidx++)
            {
              const char *startp = (*it).startp;
              size_t move = (*it).charc + 2;

              String *s = new String (p[pidx], move);

              std::string ss = s->value ();

              CPPUNIT_ASSERT_MESSAGE ("string.empty ()", ss.empty () );

              const char *readp = s->parse (startp);
              ss = s->value ();

              // std::cout << readp << "" << ss.length () << " " << ss << std::endl;

              ASSERT_EQUAL_IDX ("string.readp", readp, startp + move);
              ASSERT_EQUAL_IDX ("*(string.readp)", (char)* readp, (*it).endc);
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
        &obj_parent,
        &arr_parent,
        0
      };

      String old_value;

      struct assert {
        Value *new_value;
        Value::object_type type;
        const char *key;
        size_t index;
        size_t count;
        int assert_status[3];
      };

      std::vector<struct assert > test = {
        { new Array ("[true,false]"), Value::array, "key_2",  0, 1,  { PASS, PASS, FAIL }  },
        { new Object ("{\"k1\":true,\"k2\":false}"), Value::object, "key_1",  0, 2,  { PASS, PASS, FAIL }},
        { new String ("\"xxx\""), Value::string, "key_3",  0, 3,  { PASS, PASS, PASS }  },
        { new Number (10), Value::number, "key_4",  0, 4, { PASS, PASS, FAIL } },
        { new Boolean (true), Value::boolean, "key_6",  0, 5, { PASS, PASS, FAIL } },
        { new Null, Value::null, "key_7",  0, 6, { PASS, PASS, FAIL } }
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

            arr_parent._element_list.push_back (new Undefined);
            old_value.setKey ((*it).key, strlen ((*it).key));

            (*it).index  = arr_parent._element_list.size () - 1;
            old_value.setIndex ((*it).index);

            Value *new_value = 0;

            if ((*it).new_value->type () == Value::string)
              {
                String *new_a_value = static_cast<String *>((*it).new_value);
                // old_value._assign (*new_a_value);
                old_value = *new_a_value;
                new_value = new_a_value;
              }
            else
              {
                // old_value._assign (*(*it).new_value);
                old_value = *(*it).new_value;
                new_value = (*it).new_value;
              }

            JSON *parent = old_value._parent;

            if (parent)
              {
                ASSERT_EQUAL_IDX ("old_value.parent.count ()", (*it).count, parent->size ());

                if (parent->type () == Value::object)
                  {
                    Value *ov =  obj_parent._member_list.at ((*it).key);

                    ASSERT_EQUAL_IDX ("obj_parent[key].type", ov->type (), (*it).type);
                    ASSERT_EQUAL_IDX ("obj_parent[key].value", ov, new_value);
                  }
                else
                  {
                    Value *av =  arr_parent._element_list.at ((*it).index);

                    ASSERT_EQUAL_IDX ("arr_parent[key].type", av->type (), (*it).type);
                    ASSERT_EQUAL_IDX ("arr_parent[key].value", av, new_value);
                  }
              }
            else
              {
                if (new_value->type () == Value::string)
                  {
                    CPPUNIT_ASSERT_MESSAGE ("old_value.value ()", strcmp ("xxx", old_value.value ()) == 0);
                  }
              }
            TEST_IT_END;
          }
    }

    virtual void test_operator_assign () {}
    virtual void test_operator_at () {}

    virtual void test_size_1() {}
    virtual void test_at() {}
    virtual void test_value_1() {}
    virtual void test_debug_1() {}

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

#endif // JSON_STRING_TEST_H
