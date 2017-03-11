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
      json *p[] = { 0, new json };

      for (size_t pidx = 0; pidx < 2; pidx++)
        {
          format::unique_undefined *uu[] = {
            new format::unique_undefined (),
            new format::unique_undefined (p[pidx]),
          };
        }

      delete p[1];

      format::undefined src;
      format::undefined copy = src;

      format::undefined *up[] = {
        new format::undefined (),
        new format::undefined ()
      };

      delete up[0];
      up[0] = new format::undefined () ;

      CPPUNIT_ASSERT_MESSAGE ("new () == new ()", up[0] == up[1]);
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("undefined::type ()", json::undefined_t, src.type ());
      CPPUNIT_ASSERT_MESSAGE ("undefined", & copy != & src);
    }

    virtual void
    test_assign_all_values () override
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
        { new array (L"[true,false]"), value::array_t, L"key_1",  0, 1,  { PASS, PASS, FAIL } },
        { new object (L"{\"k1\":true,\"k2\":false}"), value::object_t, L"key_2",  0, 2, { PASS, PASS, FAIL } },
        { new string (L"xxx"), value::string_t, L"key_3",  0, 3,  { PASS, PASS, FAIL } },
        { new number (10), value::number_t, L"key_4",  0, 4, { PASS, PASS, FAIL } },
        { new boolean (true), value::boolean_t, L"key_6",  0, 5, { PASS, PASS, FAIL } },
        { new null, value::null_t, L"key_7",  0, 6, { PASS, PASS, FAIL } }
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
                  format::unique_undefined *old_value = new format::unique_undefined ();
                  old_value->_parent = parents[pidx];

                  (*it).index  = array_parent.push (new format::unique_undefined ());
                  old_value->_set_index ((*it).index);
                  old_value->_set_key ((*it).key, wcslen ((*it).key));

                  *(dynamic_cast<value *>(old_value)) = *(*it).new_value;

                  json *parent = old_value->_parent;

                  if (parent)
                    {
                      ASSERT_EQUAL_IDX ("old_value.parent.count ()", (*it).count, parent->count ());

                      if (parent->type () == value::object_t)
                        {
                          ASSERT_EQUAL_IDX ("obj_parent[key].type", object_parent[(*it).key].type (), (*it).type);
                        }
                      else
                        {
                          ASSERT_EQUAL_IDX ("arr_parent[key].type", array_parent[(*it).index].type (), (*it).type);
                        }
                    }
              TEST_IT_END;
            }

          for (auto it = test.begin (); it != test.end (); ++it)
            delete (*it).new_value;
    }

    void
    test_shared_undefined ()
    {
      shared_undefined & u = shared_undefined::instance ();
      shared_undefined *pu = & u;

      delete pu;

      CPPUNIT_ASSERT_MESSAGE ("instance () > 0", (& shared_undefined::instance ()));
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("instance () == instance ()",  & shared_undefined::instance (), & shared_undefined::instance ());
    }

    virtual void
    test_parse_1 () override
    {
      const wchar_t *s = L"x";
      undefined u;
      CPPUNIT_ASSERT_MESSAGE ("undefined::_parse (L\"x\")", s == u._parse (s));
    }

    virtual void
    test_str_length () override
    {
      undefined u;
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("undefined::str_length ()", (size_t) 0, u.str_length ()) ;
    }

    virtual void
    test_str_value () override
    {
      undefined u;
      CPPUNIT_ASSERT_MESSAGE ("undefined::str_value ()", wcslen (u.str_value ()) == 0);
    }

    virtual void test__clear () override {}
    virtual void test_type () override {}

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
      /* 2. */  s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_shared_undefined", &json_undefined_test::test_shared_undefined));
      /* 3. */  s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_parse_1", &json_undefined_test::test_parse_1));
      /* 4. */  s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_str_length", &json_undefined_test::test_str_length));
      /* 5. */  s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_str_value", &json_undefined_test::test_str_value));
      /* 6. */  s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test__clear", &json_undefined_test::test__clear));

      return s;
    }
  }; // Namespace format
}

#endif // JSON_UNDEFINED_TEST

