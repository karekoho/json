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
    test_str_value () override
    {
      // stringify calls strValue which always returns string value
      // TODO: move to test_strValue

      object op;

      json *parent[2] = {
        0, & op,
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
        { new number (100), { 10, 11 }, { L"100.000000", L"x100.000000" }, PASS },
        { new boolean (), { 5, 6 }, { L"false", L"xfalse" }, PASS },
        { new null (), { 4, 5 }, { L"null", L"xnull" }, PASS },
      };

      for (size_t pidx = 0; pidx < 1; pidx++)
        {
          this->_idx[0] = 0;
          TEST_IT_START
            if (parent[pidx] == 0)   // No parent
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
            TEST_IT_END;
        }
      for (auto it = test.begin (); it != test.end (); it = test.erase (it))
        delete (*it).value;
    }

    virtual void
    test_operator_at_key () final override
    {
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("leaf[key]",
                                    value::undefined_t,
                                    undefined ()[L"0"].type ());
    }

    virtual void
    test_operator_at_index () final override
    {
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("leaf[index]",
                                    value::undefined_t,
                                    undefined ()[(size_t) 0].type ());
    }

    virtual void
    test_count () final override
    {
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("leaf::count ()",
                                    (size_t) 0,
                                    undefined ().count ());
    }

    virtual void
    test_erase () final override
    {
      CPPUNIT_ASSERT_MESSAGE ("leaf::erase ()",
                              undefined ().erase (undefined ()).type () == value::undefined_t);
    }

    virtual void test_type () override {}
    virtual void test_ctor_dtor () override {}
    virtual void test_parse_1 () override {}
    virtual void test_assign_all_values () override {}
    virtual void test__clear () override {}
    virtual void test_str_length () override {}

    /**
     * 12.
     * @brief suite
     * @return
     */
    static CppUnit::Test *
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json leaf test");

      /* 0. */ s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_assign_all_values", &json_leaf_test::test_str_value));
      /* 1. */ s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_count", &json_leaf_test::test_count));
      /* 2. */ s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_operator_at_key", &json_leaf_test::test_operator_at_key));
      /* 3. */ s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_operator_at_index", &json_leaf_test::test_operator_at_index));
      /* 4. */ s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_count", &json_leaf_test::test_count));
      /* 5. */ s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_erase", &json_leaf_test::test_erase));

      return s;
    }
  };
}
#endif // JSON_LEAF_TEST

