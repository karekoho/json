#ifndef JSON_LEAF_TEST
#define JSON_LEAF_TEST

#include "json_value_test_interface.h"

namespace format
{
  namespace json
  {
  /**
   * 12.
   * @brief The json_leaf_test class
   */
  class json_leaf_test : public json_value_test_interface
  {
  public:

    virtual void
    test__to_string () override
    {
      struct assert
      {
        leaf *value;
        size_t output_len;
        const wchar_t *output;
        int assert_status;
      };

      std::vector<struct assert > test = {
        { new string (),  0, L"", PASS },
        { new string (L""), 0, L"", PASS },
        { new string (L"x"), 1, L"x", PASS },
        { new number (), 1, L"0", PASS },
        { new number ((float) 100.0), 10, L"100.000000", PASS },
        { new number (static_cast<long long> (100)), 3, L"100", PASS },
        { new boolean (), 5, L"false", PASS },
        { new boolean (true), 4, L"true", PASS },
        { new null (), 4, L"null", PASS },
        { new undefined (), 0, L"", PASS },
      };

      TEST_IT_START

        const wchar_t *output = (*it).value->stringify ();

        ASSERT_EQUAL_IDX ("wcslen (output)",
                          (*it).output_len,
                          wcslen (output));

        CPPUNIT_ASSERT_MESSAGE ("output",
                                wcscmp ((*it).output,
                                output) == 0);

        delete (*it).value;
        delete [] output;

      TEST_IT_END

      //for (auto it = test.begin (); it != test.end (); it = test.erase (it))
        //delete (*it).value;
    }

    virtual void
    test_operator_at_key () final override
    {
      CPPUNIT_ASSERT_MESSAGE("leaf [const wchar_t *]",
                             number ()[L""].type () == value::number_t);
    }

    virtual void
    test_const_operator_at_key () final override
    {
      const number n;
      const value & v = n[L""];

      CPPUNIT_ASSERT_MESSAGE("leaf [const wchar_t *]",
                              v.type () == value::number_t);
    }

    virtual void
    test_operator_at_index () final override
    {
      CPPUNIT_ASSERT_MESSAGE("leaf [size_t]",
                             number ()[static_cast<size_t> (0)].type () == value::number_t);
    }

    virtual void
    test_const_operator_at_index () final override
    {
      const number n;
      const value & v = n[static_cast<size_t> (0)];

      CPPUNIT_ASSERT_MESSAGE("leaf [size_t]",
                              v.type () == value::number_t);
    }

    virtual void
    test_count () final override
    {
      json j;
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("leaf::count ()", static_cast<size_t> (0), no_value::instance (& j)->size ());
    }

    virtual void test_ctor_dtor () override { CPPUNIT_ASSERT_ASSERTION_PASS (); }
    virtual void test__parse () override { CPPUNIT_ASSERT_ASSERTION_PASS (); }
    virtual void test_assign_all_values () override { CPPUNIT_ASSERT_ASSERTION_PASS (); }
    virtual void test__clear () override { CPPUNIT_ASSERT_ASSERTION_PASS (); }
    virtual void test_str_length () override { CPPUNIT_ASSERT_ASSERTION_PASS (); }
    virtual void test__erase () final override { CPPUNIT_ASSERT_ASSERTION_PASS (); }
    virtual void test_type () override { CPPUNIT_ASSERT_ASSERTION_PASS (); }
    virtual void test__assign_value_ptr_value_ptr () final override { CPPUNIT_ASSERT_ASSERTION_PASS (); }
    virtual void test__clone_const_value_ref () override { CPPUNIT_ASSERT_ASSERTION_PASS (); }

    /**
     * 12.
     * @brief suite
     * @return
     */
    static CppUnit::Test *
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json leaf test");

      /* 0. */  s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test__to_string", &json_leaf_test::test__to_string));
      /* 1. */  s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_count", &json_leaf_test::test_count));
      /* 2. */  s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_erase", &json_leaf_test::test__erase));
      /* 3. */  s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test__assign_value_ptr_value_ptr", &json_leaf_test::test__assign_value_ptr_value_ptr));
      /* 4. */  s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test__clone_const_value_ref", &json_leaf_test::test__clone_const_value_ref));
      /* 5. */  s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_operator_at_key", &json_leaf_test::test_operator_at_key));
      /* 6. */  s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_const_operator_at_key", &json_leaf_test::test_const_operator_at_key));
      /* 7. */  s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_operator_at_index", &json_leaf_test::test_operator_at_index));
      /* 8. */  s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_const_operator_at_index", &json_leaf_test::test_const_operator_at_index));

      return s;
    }
  };
}
}
#endif // JSON_LEAF_TEST

