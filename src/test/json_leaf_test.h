#ifndef JSON_LEAF_TEST
#define JSON_LEAF_TEST

#include "unit_test.h"

namespace format
{
  namespace json
  {
    namespace test
    {
      // All commented out, no tests run
      //s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test__to_string", &json_leaf_test::test__to_string));
      //s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_count", &json_leaf_test::test_count));
      //s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_erase", &json_leaf_test::test__erase));
      //s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test__assign_value_ptr_value_ptr", &json_leaf_test::test__assign_value_ptr_value_ptr));
      //s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test__clone_const_value_ref", &json_leaf_test::test__clone_const_value_ref));
      //s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_operator_at_key", &json_leaf_test::test_operator_at_key));
      //s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_const_operator_at_key", &json_leaf_test::test_const_operator_at_key));
      //s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_operator_at_index", &json_leaf_test::test_operator_at_index));
      //s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_const_operator_at_index", &json_leaf_test::test_const_operator_at_index));

      class leaf_test : public unit_test {};

      TEST_F (leaf_test, _to_string)
      {
        struct assert
        {
          leaf *value;
          size_t output_len;
          const wchar_t *output;
          int assert_status;
        };

        std::vector<struct assert > test = {
          { new string (),  0, L"", PASS_T },
          { new string (L""), 0, L"", PASS_T },
          { new string (L"x"), 1, L"x", PASS_T },
          { new number (), 1, L"0", PASS_T },
          { new number ((float) 100.0), 3, L"100", PASS_T },
          { new number (static_cast<long long> (100)), 3, L"100", PASS_T },
          { new boolean (), 5, L"false", PASS_T },
          { new boolean (true), 4, L"true", PASS_T },
          { new null (), 4, L"null", PASS_T },
          { new undefined (), 0, L"", PASS_T },
        };

        TEST_IT_START

          const wchar_t *output = (*it).value->stringify ();

          // Original assertion:
          ///ASSERT_EQUAL_IDX ("wcslen (output)", (*it).output_len, wcslen (output));
          ///
          ASSERT_THAT (wcslen (output), Eq ((*it).output_len))
              << ERR_IDX_MSG << _idx[0];

          // Original assertion:
          ///CPPUNIT_ASSERT_MESSAGE ("output", wcscmp ((*it).output, output) == 0);
          ///
          ASSERT_THAT (output, StrEq ((*it).output))
              << ERR_IDX_MSG << _idx[0];

          delete (*it).value;
          delete [] output;

        TEST_IT_END

        //for (auto it = test.begin (); it != test.end (); it = test.erase (it))
          //delete (*it).value;
      }

      TEST_F (leaf_test, count)
      {
        json j;
        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("leaf::count ()", static_cast<size_t> (0), no_value::instance (& j)->size ());
        ///
        ASSERT_THAT (no_value::instance (& j)->size (), Eq (0));
      }

      TEST_F (leaf_test, _erase)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_ASSERTION_PASS ();
      }

      TEST_F (leaf_test, _assign_value_ptr_value_ptr)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_ASSERTION_PASS ();
      }

      TEST_F (leaf_test, _clone_const_value_ref)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_ASSERTION_PASS ();
      }

      TEST_F (leaf_test, operator_at_key)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE("leaf [const wchar_t *]", number ()[L""].type () == value::number_t);
        ///
        ASSERT_THAT (number ()[L""].type (), Eq (value::number_t));
      }

      TEST_F (leaf_test, const_operator_at_key)
      {
        const number n;
        const value & v = n[L""];

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE("leaf [const wchar_t *]", v.type () == value::number_t);
        ///
        ASSERT_THAT (v.type (), Eq (value::number_t));
      }

      TEST_F (leaf_test, operator_at_index)
      {
        ///CPPUNIT_ASSERT_MESSAGE("leaf [size_t]", number ()[static_cast<size_t> (0)].type () == value::number_t);
        ///
        ASSERT_THAT (number ()[static_cast<size_t> (0)].type (), Eq (value::number_t));
      }

      TEST_F (leaf_test, const_operator_at_index)
      {
        const number n;
        const value & v = n[static_cast<size_t> (0)];

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE("leaf [size_t]", v.type () == value::number_t);
        ///
        ASSERT_THAT (v.type (), Eq (value::number_t));
      }
    }


  /**
   * 12.
   * @brief The json_leaf_test class
   */
  class json_leaf_test // public json_value_test_interface
  {
  public:

    virtual void
    test__to_string ()
    {
//      struct assert
//      {
//        leaf *value;
//        size_t output_len;
//        const wchar_t *output;
//        int assert_status;
//      };

//      std::vector<struct assert > test = {
//        { new string (),  0, L"", PASS_T },
//        { new string (L""), 0, L"", PASS_T },
//        { new string (L"x"), 1, L"x", PASS_T },
//        { new number (), 1, L"0", PASS_T },
//        { new number ((float) 100.0), 3, L"100", PASS_T },
//        { new number (static_cast<long long> (100)), 3, L"100", PASS_T },
//        { new boolean (), 5, L"false", PASS_T },
//        { new boolean (true), 4, L"true", PASS_T },
//        { new null (), 4, L"null", PASS_T },
//        { new undefined (), 0, L"", PASS_T },
//      };

//      TEST_IT_START

//        const wchar_t *output = (*it).value->stringify ();

//        ASSERT_EQUAL_IDX ("wcslen (output)",
//                          (*it).output_len,
//                          wcslen (output));

//        CPPUNIT_ASSERT_MESSAGE ("output",
//                                wcscmp ((*it).output,
//                                output) == 0);

//        delete (*it).value;
//        delete [] output;

//      TEST_IT_END

//      //for (auto it = test.begin (); it != test.end (); it = test.erase (it))
//        //delete (*it).value;
    }

    virtual void
    test_operator_at_key ()
    {
//      CPPUNIT_ASSERT_MESSAGE("leaf [const wchar_t *]",
//                             number ()[L""].type () == value::number_t);
    }

    virtual void
    test_const_operator_at_key ()
    {
//      const number n;
//      const value & v = n[L""];

//      CPPUNIT_ASSERT_MESSAGE("leaf [const wchar_t *]",
//                              v.type () == value::number_t);
    }

    virtual void
    test_operator_at_index ()
    {
//      CPPUNIT_ASSERT_MESSAGE("leaf [size_t]",
//                             number ()[static_cast<size_t> (0)].type () == value::number_t);
    }

    virtual void
    test_const_operator_at_index ()
    {
//      const number n;
//      const value & v = n[static_cast<size_t> (0)];

//      CPPUNIT_ASSERT_MESSAGE("leaf [size_t]",
//                              v.type () == value::number_t);
    }

    virtual void
    test_count ()
    {
//      json j;
//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("leaf::count ()", static_cast<size_t> (0), no_value::instance (& j)->size ());
    }

//    virtual void test_ctor_dtor () override { CPPUNIT_ASSERT_ASSERTION_PASS (); }
//    virtual void test__parse () override { CPPUNIT_ASSERT_ASSERTION_PASS (); }
//    virtual void test_assign_all_values () override { CPPUNIT_ASSERT_ASSERTION_PASS (); }
//    virtual void test__clear () override { CPPUNIT_ASSERT_ASSERTION_PASS (); }
//    virtual void test_str_length () override { CPPUNIT_ASSERT_ASSERTION_PASS (); }
//    virtual void test__erase () final override { CPPUNIT_ASSERT_ASSERTION_PASS (); }
//    virtual void test_type () override { CPPUNIT_ASSERT_ASSERTION_PASS (); }
//    virtual void test__assign_value_ptr_value_ptr () final override { CPPUNIT_ASSERT_ASSERTION_PASS (); }
//    virtual void test__clone_const_value_ref () override { CPPUNIT_ASSERT_ASSERTION_PASS (); }
  };
}
}
#endif // JSON_LEAF_TEST

