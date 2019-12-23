#ifndef JSON_LEAF_TEST
#define JSON_LEAF_TEST

#include "json_value_test_interface.h"

namespace format
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
      // stringify calls strValue which always returns string value
      // TODO: move to test_strValue

      object op;

      json *parent[2] = {
        nullptr, & op,
      };

      struct assert
      {
        leaf *value;
        size_t output_len[2];
        const wchar_t *output[2];
        int assert_status;
      };

      std::vector<struct assert > test = {
        { new string (L"x"), { 3, 4 }, { L"\"x\"", L"x\"x\"" }, PASS },
        //{ new number ((long) 100), { 10, 11 }, { L"100.000000", L"x100.000000" }, PASS },
        { new number (static_cast<long> (100)), { 3, 4 }, { L"100", L"x100" }, PASS },
        { new boolean (), { 5, 6 }, { L"false", L"xfalse" }, PASS },
        { new null (), { 4, 5 }, { L"null", L"xnull" }, PASS },
      };

      for (size_t pidx = 0; pidx < 1; pidx++)
        {
          this->_idx[0] = 0;
          TEST_IT_START
            if (parent[pidx] == nullptr)   // No parent
              {
                const wchar_t *output = (*it).value->stringify ();

                ASSERT_EQUAL_IDX ("wcslen (output)",
                                  (*it).output_len[0],
                                  wcslen (output));

                CPPUNIT_ASSERT_MESSAGE ("output",
                                        wcscmp ((*it).output[0],
                                        output) == 0);
              }
              /* else
                  {
                    p->_str_value[0] = new wchar_t[20 + 1]();
                    p->_str_value[1] = p->_str_value[0];

                    *(p->_str_value[0]++) =  L'x';
                    (*it).value->_parent = p;

                    (void) (*it).value->stringify ();

                    ASSERT_EQUAL_IDX ("output length", (*it).output_len[1], wcslen (p->_str_value[1]));
                    CPPUNIT_ASSERT_MESSAGE ("output", wcscmp ((*it).output[1], p->_str_value[1]) == 0);

                    delete[]  p->_str_value[1];
              } */
            TEST_IT_END
        }

      for (auto it = test.begin (); it != test.end (); it = test.erase (it))
        delete (*it).value;
    }

    virtual void
    test_operator_at_key () final override
    {
      CPPUNIT_ASSERT_MESSAGE("leaf [const wchar_t *]",
                             number ()[L""].type () == value::number_t);
    }

    virtual void
    test_operator_at_index () final override
    {
      CPPUNIT_ASSERT_MESSAGE("leaf [size_t]",
                             number ()[static_cast<size_t> (0)].type () == value::number_t);
    }

    void
    test_point ()
    {
      CPPUNIT_ASSERT_MESSAGE("leaf point",
                             number ().point (L"/").type () == value::number_t);
    }

    virtual void
    test_count () final override
    {
      json j;
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("leaf::count ()", static_cast<size_t> (0), no_value::instance (& j)->count ());
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

      /* 0. */  s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_assign_all_values", &json_leaf_test::test__to_string));
      /* 1. */  s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_count", &json_leaf_test::test_count));
      /* 2. */  s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_erase", &json_leaf_test::test__erase));
      /* 3. */  s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test__assign_value_ptr_value_ptr", &json_leaf_test::test__assign_value_ptr_value_ptr));
      /* 4. */  s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test__clone_const_value_ref", &json_leaf_test::test__clone_const_value_ref));
      /* 5. */  s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_operator_at_key", &json_leaf_test::test_operator_at_key));
      /* 6. */  s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_operator_at_index", &json_leaf_test::test_operator_at_index));
      /* 7. */  s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_point", &json_leaf_test::test_point));

      return s;
    }
  };
}
#endif // JSON_LEAF_TEST

