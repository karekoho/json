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
    json parent;

    boolean b[] = {
      boolean (),
      boolean (true),
      boolean (& parent)
    };
  }

  virtual void
  test_assign_all_values ()
  {
    object_accessor object_parent;

    json *parents[] = {
      & object_parent,
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

    boolean b (true);

    std::vector<struct assert > test = {
      { & b, value::boolean_t, L"0",  0, 1, { PASS, PASS } },
      { __VALUE[value::null_t], value::null_t, L"1",  0, 2, { PASS, FAIL } }
    };

    boolean *old_value = 0;

    for (size_t pidx = 0; pidx < 2; pidx++)
      {
        this->_idx[0] = 0;
        for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++)
          {
            try
              {
                if ((*it).assert_status[pidx] == SKIP) { continue; }\
                if ((*it).assert_status[pidx] > PASS) { this->_errorc[EXPECTED]++; }

                /** old_value: value from value[key] */
                old_value = new boolean (parents[pidx], false);

                old_value->_set_key ((*it).key, wcslen ((*it).key));

                if ((*it).new_value->type () == value::boolean_t)
                  *old_value = *(static_cast<boolean *>((*it).new_value));
                else
                  *(static_cast<value *>(old_value)) = *(*it).new_value;

                json *parent = parents[pidx];

                if (parent)
                  {
                    ASSERT_EQUAL_IDX ("parent->count ()",
                                      (*it).count,
                                      parent->length ());

                    ASSERT_EQUAL_IDX ("(*parent)[(*it).key].type ()",
                                      (*parent)[(*it).key].type (),
                                      (*it).type);
                  }
                else if ((*it).new_value->type () == value::boolean_t)
                  {
                    ASSERT_EQUAL_IDX ("old_value.value ()", (bool) true, old_value->get ());
                    delete old_value;
                  }
               }
             catch (format::json_error & e)
              {
                this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl;
                delete old_value;
              }
           }
          (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]);
          CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
        }
  }

  virtual void test__parse_1 () override {}
  virtual void test_str_length () override {}
  virtual void test__to_string () override {}
  virtual void test__clear () override {}

  virtual void
  test__clone_const_value_ref () override
  {
    boolean src = true;
    boolean copy;

    (void) copy._clone (src);

    CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy.get ()",
                                  true,
                                  copy.get ());
  }


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
    /* 2.*/ s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test__clone_const_value_ref", &json_boolean_test::test__clone_const_value_ref));
    /* 3. */ //s->addTest (new CppUnit::TestCaller<json_boolean_test> ("", &json_boolean_test::test_parse_1));
    /* 4. */ //s->addTest (new CppUnit::TestCaller<json_boolean_test> ("", &json_boolean_test::test_str_length));
    /* 5. */ //s->addTest (new CppUnit::TestCaller<json_boolean_test> ("", &json_boolean_test::test_str_value));
    /* 6. */ //s->addTest (new CppUnit::TestCaller<json_boolean_test> ("", &json_boolean_test::test__clear));

    return s;
  }
};
}
#endif // JSON_BOOLEAN_TEST

