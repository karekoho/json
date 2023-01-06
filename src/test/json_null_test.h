#ifndef JSON_NULL_TEST
#define JSON_NULL_TEST

#include "unit_test.h"
#include "json_mock_value.h"

namespace format
{
  namespace json
  {
    namespace test
    {
      //s->addTest (new CppUnit::TestCaller<json_null_test> ("test_ctor_dtor", &json_null_test::test_ctor_dtor));
      //s->addTest (new CppUnit::TestCaller<json_null_test> ("test_assign_all_values", &json_null_test::test_assign_all_values));
      //s->addTest (new CppUnit::TestCaller<json_null_test> ("test__clone_const_value_ref", &json_null_test::test__clone_const_value_ref));
      //s->addTest (new CppUnit::TestCaller<json_null_test> ("test__parse", &json_null_test::test__parse));
      //s->addTest (new CppUnit::TestCaller<json_null_test> ("test_str_length", &json_null_test::test_str_length));
      //s->addTest (new CppUnit::TestCaller<json_null_test> ("test__to_string", &json_null_test::test__to_string));
      //s->addTest (new CppUnit::TestCaller<json_null_test> ("test__clear", &json_null_test::test__clear));
      //s->addTest (new CppUnit::TestCaller<json_null_test> ("test_type", &json_null_test::test_type));

      class null_test : public unit_test {};

      TEST_F (null_test, ctor_dtor)
      {
        json parent;

        mock_null n[] = {
          mock_null (),
          mock_null (& parent)
        };
      }

      TEST_F (null_test, _clone_const_value_ref)
      {
        /// TODO: IF ov.parent: success
        /// TODO: ELSE: fail

        mock_object object_parent;

        json *parents[] = {
          & object_parent,
          nullptr
        };

        struct assert
        {
          value *new_value;
          value::value_t type;
          const wchar_t *key;
          size_t count;
          int assert_status[3];
        };

        mock_null n;

        std::vector<struct assert > test = {
          /// operator =(const null & n), operator =(std::nullptr_t) removed
          //{ __VALUE[value::boolean_t], value::boolean_t, L"0",  1, { PASS, FAIL } },
          //{ & n, value::null_t, L"1", 2, { PASS, PASS } }
        };

        mock_null *old_value = nullptr;

        for (size_t pidx = 0; pidx < 2; pidx++)
          {
            this->_idx[0] = 0;
            for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++)
              {\
                try
                  {\
                    if ((*it).assert_status[pidx] == SKIP_T) { continue; }\
                    if ((*it).assert_status[pidx] > PASS_T) { this->_errorc[EXPECTED]++; }

                    /** old_value: value from value[key] */
                    old_value = new mock_null (parents[pidx]);

                    old_value->_set_key ((*it).key, wcslen ((*it).key));

                    if ((*it).new_value->type () == value::null_t)
                      *old_value = *(dynamic_cast<mock_null *>((*it).new_value));
                    else
                      *(dynamic_cast<value *>(old_value)) = *(*it).new_value;

                    json *parent = parents[pidx];

                    if (parent)
                      {
                        // Original assertion:
                        ///ASSERT_EQUAL_IDX ("parent->count ()", (*it).count, parent->size ());
                        ///
                        ASSERT_THAT (parent->size (), Eq ((*it).count))
                            << ERR_IDX_MSG << _idx[0];

                        // Original assertion:
                        ///ASSERT_EQUAL_IDX ("(*parent)[(*it).key].type ()", (*parent)[(*it).key].type (), (*it).type);
                        ///
                        ASSERT_THAT ((*parent)[(*it).key].type (), Eq ((*it).type))
                            << ERR_IDX_MSG << _idx[0];
                      }
                    else
                      delete old_value;
                  }
                 catch (format::json::json_error & e)
                  {
                    this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl;
                    delete old_value;
                  }
              }
            //(void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]);

            // Original assertion:
            ///CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
            ///
            ASSERT_THAT (this->_errorc[ACTUAL], Eq (this->_errorc[EXPECTED]));
          }
      }

      TEST_F (null_test, _parse)
      {
        mock_null n;
        const wchar_t *input = L"null ";

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("endp", input + 4, n._parse (input));
        ///
        ASSERT_THAT (n._parse (input), Eq (input + 4));
      }

      TEST_F (null_test, str_length)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_ASSERTION_PASS ("null::str_length () return value is fixed");
      }

      TEST_F (null_test, _to_string)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_ASSERTION_PASS ("null::_to_string () return value is fixed");
      }

      TEST_F (null_test, _clear)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_ASSERTION_PASS ("null::_clear () is nop");
      }

      TEST_F (null_test, type)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("value::type ()", value::null_t, null ().type ());
        ///
        ASSERT_THAT (null ().type (), Eq (value::null_t));
      }
    } // Namespace test

  class json_null_test
  {
  public:

    virtual void
    test_ctor_dtor ()
    {
//      json parent;

//      null n[] = {
//        null (),
//        null (& parent)
//      };
    }

    virtual void
    test_assign_all_values ()
    {
//      /// TODO: IF ov.parent: success
//      /// TODO: ELSE: fail

//      object_accessor object_parent;

//      json *parents[] = {
//        & object_parent,
//        nullptr
//      };

//      struct assert
//      {
//        value *new_value;
//        value::value_t type;
//        const wchar_t *key;
//        size_t count;
//        int assert_status[3];
//      };

//      null n;
//      std::vector<struct assert > test = {
//        /// operator =(const null & n), operator =(std::nullptr_t) removed
//        //{ __VALUE[value::boolean_t], value::boolean_t, L"0",  1, { PASS, FAIL } },
//        //{ & n, value::null_t, L"1", 2, { PASS, PASS } }
//      };

//      null *old_value = nullptr;

//      for (size_t pidx = 0; pidx < 2; pidx++)
//        {
//          this->_idx[0] = 0;
//          for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++)
//            {\
//              try
//                {\
//                  if ((*it).assert_status[pidx] == SKIP_T) { continue; }\
//                  if ((*it).assert_status[pidx] > PASS_T) { this->_errorc[EXPECTED]++; }

//                  /** old_value: value from value[key] */
//                  old_value = new null (parents[pidx]);

//                  old_value->_set_key ((*it).key, wcslen ((*it).key));

//                  if ((*it).new_value->type () == value::null_t)
//                    *old_value = *(dynamic_cast<null *>((*it).new_value));
//                  else
//                    *(dynamic_cast<value *>(old_value)) = *(*it).new_value;

//                  json *parent = parents[pidx];

//                  if (parent)
//                    {
//                      ASSERT_EQUAL_IDX ("parent->count ()",
//                                        (*it).count,
//                                        parent->size ());

//                      ASSERT_EQUAL_IDX ("(*parent)[(*it).key].type ()",
//                                        (*parent)[(*it).key].type (),
//                                        (*it).type);
//                    }
//                  else
//                    delete old_value;
//                }
//               catch (format::json::json_error & e)
//                {
//                  this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl;
//                  delete old_value;
//                }
//            }
//          (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]);
//          CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
//        }
    }

    virtual void
    test__parse ()
    {
//      null n;
//      const wchar_t *input = L"null ";
//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("endp", input + 4, n._parse (input));
    }

    virtual void
    test_str_length ()
    { /*CPPUNIT_ASSERT_ASSERTION_PASS ("null::str_length () return value is fixed"); */}

    virtual void
    test__to_string ()
    { /*CPPUNIT_ASSERT_ASSERTION_PASS ("null::_to_string () return value is fixed");*/ }

    virtual void
    test__clear ()
    { /*CPPUNIT_ASSERT_ASSERTION_PASS ("null::_clear () is nop");*/ }

    virtual void
    test_type ()
    {
//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("value::type ()",
//                                    value::null_t,
//                                    null ().type ());
    }

    virtual void
    test__clone_const_value_ref ()
    { /*CPPUNIT_ASSERT_ASSERTION_PASS ("null::_clone (const value &) return value is fixed (this)");*/ }

    /**
     * 7.
     * @brief suite
     * @return
     *
    static CppUnit::Test *
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json null test");

      s->addTest (new CppUnit::TestCaller<json_null_test> ("test_ctor_dtor", &json_null_test::test_ctor_dtor));
      s->addTest (new CppUnit::TestCaller<json_null_test> ("test_assign_all_values", &json_null_test::test_assign_all_values));
      s->addTest (new CppUnit::TestCaller<json_null_test> ("test__clone_const_value_ref", &json_null_test::test__clone_const_value_ref));
      s->addTest (new CppUnit::TestCaller<json_null_test> ("test__parse", &json_null_test::test__parse));
      s->addTest (new CppUnit::TestCaller<json_null_test> ("test_str_length", &json_null_test::test_str_length));
      s->addTest (new CppUnit::TestCaller<json_null_test> ("test__to_string", &json_null_test::test__to_string));
      s->addTest (new CppUnit::TestCaller<json_null_test> ("test__clear", &json_null_test::test__clear));
      s->addTest (new CppUnit::TestCaller<json_null_test> ("test_type", &json_null_test::test_type));

      return s;
    }*/
  };
}
}
#endif // JSON_NULL_TEST

