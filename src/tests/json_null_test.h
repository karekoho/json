#ifndef JSON_NULL_TEST
#define JSON_NULL_TEST

#include "json_leaf_test.h"

/**
 * 7.
 * @brief The json_null_test class
 */
class json_null_test : public json_leaf_test
{
public:

  virtual void
  test_ctor_dtor ()
  {
    JSON *p[] = { 0, new JSON () };

    for (size_t pidx = 0; pidx < 2; pidx++)
      {
          Null *n[] = {
          new Null,
          new Null (p[pidx]),
        };

        delete n[0];
        delete n[1];
      }

    delete p[1];

    Null src;
    Null copy = src;

    CPPUNIT_ASSERT_MESSAGE ("null", & copy != & src);
  }

  virtual void
  test_assign_all_values ()
  {
    /// TODO: IF ov.parent: success
    /// TODO: ELSE: fail

    Object obj_parent;
    Array arr_parent;

    JSON *parents[] = {
      & obj_parent,
      & arr_parent,
      0
    };

    // Null old_value;

    struct assert {
      Value *new_value;
      Value::object_type type;
      const wchar_t *key;
      size_t index;
      size_t count;
      int assert_status[3];
    };

    std::vector<struct assert > test = {
      { new Array (L"[true,false]"), Value::array, L"key_1",  0, 1,  { PASS, PASS, FAIL }  },
      { new Object (L"{\"k1\":true,\"k2\":false}"), Value::object, L"key_2",  0, 2,  { PASS, PASS, FAIL }},
      { new String (L"\"xxx\""), Value::string, L"key_3",  0, 3,  { PASS, PASS, FAIL }  },
      { new Number (10), Value::number, L"key_4",  0, 4, { PASS, PASS, FAIL } },
      { new Boolean (true), Value::boolean, L"key_6",  0, 5, { PASS, PASS, FAIL } },
      { new Null, Value::null, L"key_7",  0, 6, { PASS, PASS, PASS } }
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

          Null *old_value = new Null;
          old_value->_parent = parents[pidx];

          arr_parent._element_list.push_back (new Undefined);
          old_value->setKey ((*it).key, wcslen ((*it).key));

          (*it).index  = arr_parent._element_list.size () - 1;
          old_value->setIndex ((*it).index);

          if ((*it).new_value->type () == Value::null)
            {
              Null *new_null_value = dynamic_cast<Null *>((*it).new_value);

              //old_value->_assign (*new_null_value);
              *old_value = *new_null_value;
            }
          else
            {
              //old_value->_assign (*(*it).new_value);
              *old_value = *(*it).new_value;
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
   * 7.
   * @brief suite
   * @return
   */
  static CppUnit::Test *
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json null test");

    /* 0. */  s->addTest (new CppUnit::TestCaller<json_null_test> ("test_ctor_dtor", &json_null_test::test_ctor_dtor));
    /* 1. */  s->addTest (new CppUnit::TestCaller<json_null_test> ("test_assign_all_values", &json_null_test::test_assign_all_values));

    return s;
  }
};

#endif // JSON_NULL_TEST

