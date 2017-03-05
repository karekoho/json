#ifndef JSON_BOOLEAN_TEST
#define JSON_BOOLEAN_TEST

#include "json_leaf_test.h"

namespace format {

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
          boolean *b[] = {
          new boolean,
          new boolean (true),
          new boolean (p[pidx]),
        };

        delete b[0];
        delete b[1];
        delete b[2];
      }

    delete p[1];

    boolean src = true;
    boolean copy = src;

    CPPUNIT_ASSERT_EQUAL_MESSAGE ("boolean::type ()", json::boolean_t, src.type ());
    CPPUNIT_ASSERT_MESSAGE ("src != copy", & src != & copy);
    CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.value ()", true, copy.get ());
  }

  virtual void
  test_assign_all_values ()
  {
    object_accessor object_parent;
    array_accessor array_parent;

    json *parents[] = {
      & object_parent,
      & array_parent,
      0
    };

    struct assert
    {
      value *new_value;
      value::value_t type;
      const wchar_t *key;
      size_t index;
      size_t count;
      int assert_status[3];
    };

    std::vector<struct assert > test = {
      { new array (L"[true,false]"), value::array_t, L"key_2",  0, 1, { PASS, PASS, FAIL }  },
      { new object (L"{\"k1\":true,\"k2\":false}"), value::object_t, L"key_1",  0, 2, { PASS, PASS, FAIL } },
      { new string (L"x"), value::string_t, L"key_3",  0, 3, { PASS, PASS, FAIL } },
      { new number (10), value::number_t, L"key_4",  0, 4, { PASS, PASS, FAIL } },
      { new boolean (true), value::boolean_t, L"key_5",  0, 5, { PASS, PASS, PASS } },
      { new null, value::null_t, L"key_6",  0, 6, { PASS, PASS, FAIL } }
    };

      for (size_t pidx = 0; pidx < 3; pidx++)
        {
          object_parent.clear ();
          array_parent.clear ();

          this->_idx[0] = 0;

          for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++)
            {\
              try
                {\
                  if ((*it).assert_status[pidx] == SKIP) { continue; }\
                  if ((*it).assert_status[pidx] > PASS) { this->_errorc[EXPECTED]++; }

                  /** old_value: value from value[key] */
                  boolean *old_value = new boolean (false);
                  old_value->_parent = parents[pidx];

                  (*it).index  = array_parent.push (new format::undefined ());
                  old_value->_set_index ((*it).index);
                  old_value->_set_key ((*it).key, wcslen ((*it).key));

                  if ((*it).new_value->type () == value::boolean_t)
                    *old_value = *(static_cast<boolean *>((*it).new_value));
                  else
                    // *old_value = *(*it).new_value;
                    *(static_cast<value *>(old_value)) = *(*it).new_value;

                  json *parent = old_value->_parent;

                  if (parent)
                    {
                      ASSERT_EQUAL_IDX ("old_value.parent.count ()", (*it).count, parent->count ());

                      if (parent->type () == value::object_t)
                        {
                          value & ov =  object_parent[(*it).key];
                          ASSERT_EQUAL_IDX ("obj_parent[key].type", ov.type (), (*it).type);
                        }
                      else
                        {
                          value & av =  array_parent[(*it).index];
                          ASSERT_EQUAL_IDX ("arr_parent[key].type", av.type (), (*it).type);
                        }
                    }
                  else if ((*it).new_value->type () == value::boolean_t)
                    {
                      ASSERT_EQUAL_IDX ("old_value.value ()", (bool) true, old_value->get ());
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

  /**
   * 6.
   * @brief suite
   * @return
   */
  static CppUnit::Test *
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json boolean test");

    /* 0.*/ s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test_ctor_dtor", &json_boolean_test::test_ctor_dtor));
    /* 1.*/ s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test_assign_all_values", &json_boolean_test::test_assign_all_values));

    /* 2. s->addTest (new CppUnit::TestCaller<json_boolean_test> ("", &json_boolean_test::test_parse_1));
       3. s->addTest (new CppUnit::TestCaller<json_boolean_test> ("", &json_boolean_test::test_str_length));
       4. s->addTest (new CppUnit::TestCaller<json_boolean_test> ("", &json_boolean_test::test_str_value));
       5. s->addTest (new CppUnit::TestCaller<json_boolean_test> ("", &json_boolean_test::test__clear)); */

    return s;
  }
};
}
#endif // JSON_BOOLEAN_TEST

