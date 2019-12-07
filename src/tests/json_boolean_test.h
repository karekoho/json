#ifndef JSON_BOOLEAN_TEST
#define JSON_BOOLEAN_TEST

#include "json_leaf_test.h"

namespace format
{
  /**
   * 6.
   *
   * @brief The json_boolean_test class
   */
  class json_boolean_test : public json_leaf_test
  {
  public:

    virtual void
    test_ctor_dtor () override
    {
      json *parent = new json ();

      boolean b[] = {
        boolean (),
        boolean (true),
        boolean (parent)
      };

      delete parent;
    }

    virtual void
    test_assign_all_values () override
    {
      object_accessor object_parent;

      json *parents[] = {
        & object_parent,
        nullptr
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

      boolean *old_value = nullptr;

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
                                        parent->count ());

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

    virtual void
    test__parse () override
    {
      struct assert
      {
        const wchar_t *input;
        bool value;
        size_t charc;
        int assert_status;
      };

      std::vector<struct assert > test = {
        { L"false ", false, 5, PASS },
        { L"true ", true, 4, PASS }
      };

      TEST_IT_START
          boolean b ((*it).value);
          ASSERT_EQUAL_IDX ("readp",
                            (*it).input + (*it).charc,
                            b._parse ((*it).input));
      TEST_IT_END;
    }

    virtual void
    test_str_length () override
    {
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("boolean::str_length ()",
                                    (size_t) 5,
                                    boolean (false)._str_length ());

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("boolean::str_length ()",
                                    (size_t) 4,
                                    boolean (true)._str_length ());
    }

    virtual void
    test__to_string () override
    {
      CPPUNIT_ASSERT_MESSAGE ("boolean::_to_string ()",
                              boolean (false)._to_string () == std::wstring (L"false"));

      CPPUNIT_ASSERT_MESSAGE ("boolean::_to_string ()",
                              boolean (true)._to_string () == std::wstring (L"true"));
    }

    virtual void
    test__clear () override
    { CPPUNIT_ASSERT_ASSERTION_PASS ("boolean::_clear is nop"); }

    virtual void
    test_type () override
    {
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("value::type ()",
                                    value::boolean_t,
                                    boolean ().type ());
    }

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

    void
    test_operator_assign_bool ()
    {
      json parent;

      boolean *b = new boolean (false);
      *b = true;

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("boolean::get ()",
                                    true,
                                    b->get ());

      parent[L"0"] = b; // b._parent == parent
      parent[L"0"] = false;

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("boolean::get ()",
                                    false,
                                    b->get ());
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
      /* 3. */ s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test__parse", &json_boolean_test::test__parse));
      /* 4. */ s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test_str_length", &json_boolean_test::test_str_length));
      /* 5. */ s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test__to_string", &json_boolean_test::test__to_string));
      /* 6. */ s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test__clear", &json_boolean_test::test__clear));
      /* 7. */ s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test_type", &json_boolean_test::test_type));
      /* 8. */ s->addTest (new CppUnit::TestCaller<json_boolean_test> ("test_operator_assign_bool", &json_boolean_test::test_operator_assign_bool));

      return s;
    }
  };
}
#endif // JSON_BOOLEAN_TEST

