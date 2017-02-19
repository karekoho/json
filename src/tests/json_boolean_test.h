#ifndef JSON_BOOLEAN_TEST
#define JSON_BOOLEAN_TEST

#include "json_leaf_test.h"

namespace Format {

/**
 * 6.
 *
 * @brief The json_boolean_test class
 */
class json_boolean_test : public json_leaf_test
{
public:

  virtual void
  test_ctor_dtor ()
  {
    json *p[] = { 0, new json () };

    for (size_t pidx = 0; pidx < 2; pidx++)
      {
          Boolean *b[] = {
          new Boolean,
          new Boolean (true),
          new Boolean (p[pidx]),
        };

        delete b[0];
        delete b[1];
        delete b[2];
      }

    delete p[1];

    Boolean src = true;
    Boolean copy = src;

    CPPUNIT_ASSERT_MESSAGE ("boolean", & src != & copy);
    CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.value ()", true, copy.value ());
  }

  virtual void
  test_assign_all_values ()
  {
    Object obj_parent;
    array arr_parent;

    json *parents[] = {
      & obj_parent,
      & arr_parent,
      0
    };

    // Boolean old_value;

    struct assert {
      Value *new_value;
      Value::object_type type;
      const wchar_t *key;
      size_t index;
      size_t count;
      int assert_status[3];
    };

    std::vector<struct assert > test = {
      { new array (L"[true,false]"), Value::array_t, L"key_2",  0, 1, { PASS, PASS, FAIL }  },
      { new Object (L"{\"k1\":true,\"k2\":false}"), Value::object_t, L"key_1",  0, 2, { PASS, PASS, FAIL } },
      { new string (L"\"x\""), Value::string_t, L"key_3",  0, 3, { PASS, PASS, FAIL } },
      { new number (10), Value::number_t, L"key_4",  0, 4, { PASS, PASS, FAIL } },
      { new Boolean (true), Value::boolean_t, L"key_5",  0, 5, { PASS, PASS, PASS } },
      { new null, Value::null_t, L"key_6",  0, 6, { PASS, PASS, FAIL } }
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

          Boolean *old_value = new Boolean;

          old_value->_parent = parents[pidx];

          arr_parent._element_list.push_back (new Format::undefined);

          old_value->_boolean_value = false;
          old_value->setKey ((*it).key, wcslen ((*it).key));

          (*it).index  = arr_parent._element_list.size () - 1;
          old_value->setIndex ((*it).index);

          Value *new_value = 0;

          if ((*it).new_value->type () == Value::boolean_t)
            {
              Boolean *new_boolean_value = static_cast<Boolean *>((*it).new_value);

              // old_value->_assign (*new_boolean_value);
              *old_value = *new_boolean_value;

              new_value = new_boolean_value;
            }
          else
            {
              // old_value->_assign (*(*it).new_value);
              *old_value = *(*it).new_value;

              new_value = (*it).new_value;
            }

          json *parent = old_value->_parent;

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

                  ASSERT_EQUAL_IDX ("arr_parent[key].type", av->type (), (*it).type);
                  // ASSERT_EQUAL_IDX ("arr_parent[key].value", av, new_value);
                }
            }
          else
            {
              if (new_value->type () == Value::boolean_t)
                {
                  ASSERT_EQUAL_IDX ("old_value.value ()", (bool) true, old_value->value ());
                }
            }
          TEST_IT_END;
        }

    for (auto it = test.begin (); it != test.end (); ++it)
      delete (*it).new_value;
  }

  virtual void test_parse_1 () override {}

  virtual void test_strLength () override {}
  virtual void test_strValue () override {}
  virtual void test__clear () override {}

  virtual void test_erase () override {}

  /**
   * 6.
   * @brief suite
   * @return
   */
  static CppUnit::Test *
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json boolean test");

//<<<<<<< HEAD
//    /* 0. */  s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test_ctor_dtor", &json_boolean_test::test_ctor_dtor));
//    /* 1. */  s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test_assign_all_values", &json_boolean_test::test_assign_all_values));
//=======
    /* 0.*/ s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test_ctor_dtor", &json_boolean_test::test_ctor_dtor));
    /* 1.*/ s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test_assign_all_values", &json_boolean_test::test_assign_all_values));
//>>>>>>> f058e8b1150497ae319ee0ca0a6d4851cbc80ddf

    return s;
  }
};
}
#endif // JSON_BOOLEAN_TEST

