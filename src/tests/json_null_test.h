#ifndef JSON_NULL_TEST
#define JSON_NULL_TEST

#include "json_leaf_test.h"

namespace format {

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
    json *p[] = { 0, new json () };

    for (size_t pidx = 0; pidx < 2; pidx++)
      {
          null *n[] = {
          new null,
          new null (p[pidx]),
        };

        delete n[0];
        delete n[1];
      }

    delete p[1];

    null src;
    null copy = src;

    CPPUNIT_ASSERT_MESSAGE ("null", & copy != & src);
  }

  virtual void
  test_assign_all_values ()
  {
    /// TODO: IF ov.parent: success
    /// TODO: ELSE: fail

    object obj_parent;
    array arr_parent;

    json *parents[] = {
      & obj_parent,
      & arr_parent,
      0
    };

    // Null old_value;

    struct assert {
      value *new_value;
      value::value_t type;
      const wchar_t *key;
      size_t index;
      size_t count;
      int assert_status[3];
    };

    std::vector<struct assert > test = {
      { new array (L"[true,false]"), value::array_t, L"key_1",  0, 1,  { PASS, PASS, FAIL }  },
      { new object (L"{\"k1\":true,\"k2\":false}"), value::object_t, L"key_2",  0, 2,  { PASS, PASS, FAIL }},
      { new string (L"xxx"), value::string_t, L"key_3",  0, 3,  { PASS, PASS, FAIL }  },
      { new number (10), value::number_t, L"key_4",  0, 4, { PASS, PASS, FAIL } },
      { new boolean (true), value::boolean_t, L"key_6",  0, 5, { PASS, PASS, FAIL } },
      { new null, value::null_t, L"key_7",  0, 6, { PASS, PASS, PASS } }
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

          null *old_value = new null;
          old_value->_parent = parents[pidx];

          arr_parent._element_list.push_back (new format::undefined);
          old_value->set_key ((*it).key, wcslen ((*it).key));

          (*it).index  = arr_parent._element_list.size () - 1;
          old_value->set_index ((*it).index);

          if ((*it).new_value->type () == value::null_t)
            {
              null *new_null_value = dynamic_cast<null *>((*it).new_value);

              //old_value->_assign (*new_null_value);
              *old_value = *new_null_value;
            }
          else
            {
              //old_value->_assign (*(*it).new_value);
              *old_value = *(*it).new_value;
            }

          json *parent = old_value->_parent;

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

          TEST_IT_END;
        }

        for (auto it = test.begin (); it != test.end (); ++it)
          delete (*it).new_value;
  }

  virtual void test_parse_1 () override {}
  virtual void test_str_length () override {}
  virtual void test_str_value () override {}
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
}
#endif // JSON_NULL_TEST

