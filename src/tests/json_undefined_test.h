#ifndef JSON_UNDEFINED_TEST
#define JSON_UNDEFINED_TEST

#include "json_leaf_test.h"

namespace format
{
  /**
   * 8.
   * @brief The json_undefined_test class
   */
  class json_undefined_test : public json_leaf_test
  {
  public:

    virtual void
    test_ctor_dtor () override
    {
      json parent;

      format::unique_undefined uu[] = {
        format::unique_undefined (),
        format::unique_undefined (& parent),
      };

      format::undefined *u[] = {
        new format::undefined (),
        new format::undefined (),
        no_value::instance (& parent)
      };

      delete u[0];
      u[0] = new format::undefined ();

      delete no_value::instance (& parent);

      CPPUNIT_ASSERT_MESSAGE ("new () == new ()",
                              u[0] == u[1]);

      CPPUNIT_ASSERT_MESSAGE ("new () == new ()",
                              no_value::instance (& parent) == no_value::instance (& parent));
    }

    virtual void
    test_assign_all_values () override
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
        size_t count;
        int assert_status[2];
      };

      std::vector<struct assert > test = {
        { __VALUE[value::null_t], value::null_t, L"key_7", 1, { PASS, FAIL } }
      };

      unique_undefined *old_value = 0;

      for (size_t pidx = 0; pidx < 2; pidx++)
        {
          this->_idx[0] = 0;
          for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++)
            {\
              try
                {\
                  if ((*it).assert_status[pidx] == SKIP) { continue; }\
                  if ((*it).assert_status[pidx] > PASS) { this->_errorc[EXPECTED]++; }

                  /** old_value: value from value[key] */
                  old_value = new format::unique_undefined (parents[pidx]);
                  old_value->_set_key ((*it).key, wcslen ((*it).key));

                  *(dynamic_cast<value *>(old_value)) = *(*it).new_value;

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
              }
            catch (format::json_error & e)
              {
                this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl;
                delete old_value;
              }
            (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]);
            CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
          }
        }
    }

    virtual void
    test__parse () override
    {
      const wchar_t *s = L"x";
      undefined u;
      CPPUNIT_ASSERT_MESSAGE ("undefined::_parse (L\"x\")", s == u._parse (s));
    }

    virtual void
    test_str_length () override
    {
      undefined u;
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("undefined::str_length ()", (size_t) 0, u._str_length ()) ;
    }

    virtual void
    test__to_string () override
    {
      undefined u;
      CPPUNIT_ASSERT_MESSAGE ("undefined::str_value ()", wcslen (u._to_string ()) == 0);
    }

    virtual void
    test__clear () override
    { CPPUNIT_ASSERT_ASSERTION_PASS ("undefined::_clear () is nop");}

    virtual void
    test_type () override
    {
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("value::type ()",
                                    value::undefined_t,
                                    undefined ().type ());
    }

    virtual void
    test__clone_const_value_ref () override
    { CPPUNIT_ASSERT_ASSERTION_PASS (); }

    /**
     * 8.
     * @brief suite
     * @return
     */
    static CppUnit::Test *
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json undefined test");

      /* 0. */  s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_ctor_dtor", &json_undefined_test::test_ctor_dtor));
      /* 1. */  s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_assign_all_values", &json_undefined_test::test_assign_all_values));
      /* 2. */  s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_parse_1", &json_undefined_test::test__parse));
      /* 3. */  s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_str_length", &json_undefined_test::test_str_length));
      /* 4. */  s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_str_value", &json_undefined_test::test__to_string));
      /* 5. */  s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test__clear", &json_undefined_test::test__clear));
      /* 6. */  s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_type", &json_undefined_test::test_type));
      /* 7. */  s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test__clone_const_value_ref", &json_undefined_test::test__clone_const_value_ref));

      return s;
    }
  }; // Namespace format
}

#endif // JSON_UNDEFINED_TEST

