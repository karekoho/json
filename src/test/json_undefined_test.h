#ifndef JSON_UNDEFINED_TEST
#define JSON_UNDEFINED_TEST

#include "unit_test.h"
#include "json_mock_value.h"

namespace format
{
  namespace json
  {
    namespace test
    {
      //s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_ctor_dtor", &json_undefined_test::test_ctor_dtor));
      //s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_assign_all_values", &json_undefined_test::test_assign_all_values));
      //s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_parse_1", &json_undefined_test::test__parse));
      //s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_str_length", &json_undefined_test::test_str_length));
      //s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_str_value", &json_undefined_test::test__to_string));
      //s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test__clear", &json_undefined_test::test__clear));
      //s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_type", &json_undefined_test::test_type));
      //s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test__clone_const_value_ref", &json_undefined_test::test__clone_const_value_ref));

      class undefined_test : public unit_test {
      };

      TEST_F (undefined_test, ctor_dtor)
      {
        json parent;

          unique_undefined uu[] = {
          unique_undefined (),
          unique_undefined (& parent),
        };

        undefined *u[] = {
          new undefined (),
          new undefined (),
          no_value::instance (& parent)
        };

        delete u[0];
        u[0] = new undefined ();

        delete no_value::instance (& parent);

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("new () == new ()", u[0] == u[1]);
        ///
        ASSERT_THAT (u[1], Eq (u[0]))
            << ERR_IDX_MSG << _idx[0];

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("new () == new ()", no_value::instance (& parent) == no_value::instance (& parent));
        ///
        ASSERT_THAT ( no_value::instance (& parent), Eq ( no_value::instance (& parent)))
            << ERR_IDX_MSG << _idx[0];
      }

      TEST_F (undefined_test, assign_all_values)
      {
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
          int assert_status[2];
        };

        std::vector<struct assert > test = {
          { __VALUE[value::null_t], value::null_t, L"key_7", 1, { PASS_T, FAIL_T } }
        };

        mock_unique_undefined *old_value = nullptr;

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
                    old_value = new mock_unique_undefined (parents[pidx]);
                    old_value->_set_key ((*it).key, wcslen ((*it).key));

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
                }
              catch (json_error & e)
                {
                  this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl;
                  delete old_value;
                }
              //(void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]);

              // Original assertion:
              ///CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
              ///
              ASSERT_THAT (this->_errorc[ACTUAL], Eq (this->_errorc[EXPECTED]));
            }
        }
      }

      TEST_F (undefined_test, _parse)
      {
        const wchar_t *s = L"x";
        undefined u;

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("undefined::_parse (L\"x\")", s == u._parse (s));
        ///
        ASSERT_THAT (u._parse (s), Eq (s));
      }

      TEST_F (undefined_test, str_length)
      {
        mock_undefined u;

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("undefined::str_length ()", static_cast<size_t> (0), u._str_length ());
        ///
        ASSERT_THAT (u._str_length (), Eq (0));
      }

      TEST_F (undefined_test, _to_string)
      {
        mock_undefined u;

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("undefined::str_value ()", wcslen (u._to_string ()) == 0);
        ///
        ASSERT_THAT (wcslen (u._to_string ()), Eq (0));
      }

      TEST_F (undefined_test, _clear)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_ASSERTION_PASS ("undefined::_clear () is nop");
      }

      TEST_F (undefined_test, type)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("value::type ()", value::undefined_t, undefined ().type ());
        ///
        ASSERT_THAT (undefined ().type (), Eq (value::undefined_t));
      }

      TEST_F (undefined_test, _clone_const_value_ref)
      {
        // Original assertion:
        ///CPPUNIT_ASSERT_ASSERTION_PASS ();
      }

    } // Namespace test
  /**
   * 8.
   * @brief The json_undefined_test class
   */
  class json_undefined_test
  {
  public:

    virtual void
    test_ctor_dtor ()
    {
//      json parent;

//        unique_undefined uu[] = {
//        unique_undefined (),
//        unique_undefined (& parent),
//      };

//      undefined *u[] = {
//        new undefined (),
//        new undefined (),
//        no_value::instance (& parent)
//      };

//      delete u[0];
//      u[0] = new undefined ();

//      delete no_value::instance (& parent);

//      CPPUNIT_ASSERT_MESSAGE ("new () == new ()",
//                              u[0] == u[1]);

//      CPPUNIT_ASSERT_MESSAGE ("new () == new ()",
//                              no_value::instance (& parent) == no_value::instance (& parent));
    }

    virtual void
    test_assign_all_values ()
    {
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
//        int assert_status[2];
//      };

//      std::vector<struct assert > test = {
//        { __VALUE[value::null_t], value::null_t, L"key_7", 1, { PASS_T, FAIL_T } }
//      };

//      unique_undefined *old_value = nullptr;

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
//                  old_value = new unique_undefined (parents[pidx]);
//                  old_value->_set_key ((*it).key, wcslen ((*it).key));

//                  *(dynamic_cast<value *>(old_value)) = *(*it).new_value;

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
//              }
//            catch (json_error & e)
//              {
//                this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl;
//                delete old_value;
//              }
//            (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]);
//            CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
//          }
//        }
    }

    void
    test__parse ()
    {
//      const wchar_t *s = L"x";
//      undefined u;
//      CPPUNIT_ASSERT_MESSAGE ("undefined::_parse (L\"x\")", s == u._parse (s));
    }

    void
    test_str_length ()
    {
//      undefined u;
//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("undefined::str_length ()", static_cast<size_t> (0), u._str_length ()) ;
    }

    void
    test__to_string ()
    {
//      undefined u;
//      CPPUNIT_ASSERT_MESSAGE ("undefined::str_value ()", wcslen (u._to_string ()) == 0);
    }

    void
    test__clear ()
    { /*CPPUNIT_ASSERT_ASSERTION_PASS ("undefined::_clear () is nop");*/ }

    void
    test_type ()
    {
//      CPPUNIT_ASSERT_EQUAL_MESSAGE ("value::type ()",
//                                    value::undefined_t,
//                                    undefined ().type ());
    }

    void
    test__clone_const_value_ref ()
    { /*CPPUNIT_ASSERT_ASSERTION_PASS ();*/ }

    /**
     * 8.
     * @brief suite
     * @return
     *
    static CppUnit::Test *
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json undefined test");

      s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_ctor_dtor", &json_undefined_test::test_ctor_dtor));
      s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_assign_all_values", &json_undefined_test::test_assign_all_values));
      s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_parse_1", &json_undefined_test::test__parse));
      s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_str_length", &json_undefined_test::test_str_length));
      s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_str_value", &json_undefined_test::test__to_string));
      s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test__clear", &json_undefined_test::test__clear));
      s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_type", &json_undefined_test::test_type));
      s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test__clone_const_value_ref", &json_undefined_test::test__clone_const_value_ref));

      return s;
    }*/
  };
} // Namespace json
} // Namespace format

#endif // JSON_UNDEFINED_TEST

