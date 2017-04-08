#ifndef JSON_STRING_TEST_H
#define JSON_STRING_TEST_H

#include "json_leaf_test.h"

namespace format
{
  /**
   * 4.
   * @brief The json_string_test class
   */
  class json_string_test : public json_leaf_test
  {
  public:

    virtual void
    test_ctor_dtor () override
    {
      json *p[] = { 0, new json () };

      for (size_t pidx = 0; pidx < 2; pidx++)
        {
          string a[] = {
            string (),
            string (L"x"),
            string (p[pidx], 1),
          };
        }

      delete p[1];

      string src = L"xxx";
      string copy = src;

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("string::type ()", json::string_t , src.type ());
      CPPUNIT_ASSERT_MESSAGE ("string", & copy != & src);
      CPPUNIT_ASSERT_EQUAL_MESSAGE ("src._string_value.empty ()", true, src._string_value[0].empty () );
      CPPUNIT_ASSERT_MESSAGE ("copy.value ()", wcscmp (L"xxx", copy.get ()) == 0);
    }

    virtual void
    test_parse_1 () override
    {
      test_parse_parent ();
      test_parse_no_parent ();
    }

    void
    test_parse_parent ()
    {
      struct assert
      {
        const wchar_t *startp;
        const wchar_t *str_value;
        size_t charc;
        wchar_t endc;
        int assert_status;
      };

      std::vector<struct assert > test = {
          { L"\"\"", L"\"\"", 0 + 2, (wchar_t) 0, PASS },
          { L"\"xxx\"", L"\"xxx\"", 3 + 2, (wchar_t) 0, PASS },
          { L"\" xxx \"", L"\" xxx \"", 5 + 2, (wchar_t) 0, PASS },
          { L"\" xxx \" ", L"\" xxx \"", 5 + 2, L' ', PASS },
      };

      TEST_IT_START

        json p;

        const wchar_t *startp = (*it).startp;

        string *s = new string (& p, (*it).charc);

        CPPUNIT_ASSERT_EQUAL_MESSAGE ("s->get ()", (size_t) 0, wcslen (s->get ()));

        const wchar_t *readp = s->_parse (startp);

        ASSERT_EQUAL_IDX ("string.readp", readp, (*it).startp + (*it).charc);
        ASSERT_EQUAL_IDX ("*(string.readp)", (wchar_t) *readp, (*it).endc);
        ASSERT_EQUAL_IDX ("s->strLength ()", (*it).charc, s->str_length ());
        CPPUNIT_ASSERT_MESSAGE ("s->strValue ()", wcscmp ((*it).str_value, s->_to_str ()) == 0);

        delete s;

       TEST_IT_END;
    }

    void
    test_parse_no_parent ()
    {
      struct assert
      {
        const wchar_t *startp;
        const wchar_t *str_value;
        size_t charc;
        wchar_t endc;
        int assert_status;
      };

      std::vector<struct assert > test = {
          { L"", L"", 0, (wchar_t) 0, PASS },
          { L"xxx", L"\"xxx\"", 3 + 2, (wchar_t) 0, PASS },

          { L"\"xxx", 0, 0, (wchar_t) 0, FAIL },
          { L"xxx\"", 0, 0, (wchar_t) 0, FAIL },
          { L"\"xxx\"", 0, 0, (wchar_t) 0, FAIL },
          { L"\u001Fx", 0, 0, (wchar_t) 0, FAIL },
          { L"x\u001F", 0, 0, (wchar_t) 0, FAIL }
      };

      string *s = 0;

      TEST_IT_START

            s = new string ((*it).startp);

            ASSERT_EQUAL_IDX ("s->strLength ()", (*it).charc, s->str_length ());
            CPPUNIT_ASSERT_MESSAGE ("s->strValue ()", wcscmp ((*it).str_value, s->_to_str ()) == 0);

            delete s;
          }
        catch (format::json_error & e)
          {
            this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl;
            // delete s; // Can't delete ???
          }
        }

      (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]); \
      CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
    }

    virtual void
    test_assign_all_values () override
    {
      object_accessor object_parent;

      std::array<json *, 2> parents = {
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

       string s (L"xxx");

       std::vector<struct assert > test = {
        { & s, value::string_t, L"0",  0, 1,  { PASS, PASS } },
        { __VALUE[value::number_t], value::number_t, L"1",  0, 2, { PASS, FAIL } },
       };

       string *old_value = 0;

       for (size_t pidx = 0; pidx < parents.size () ; pidx++)
          {
            this->_idx[0] = 0;

            for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++)
              {
                try
                  {
                    if ((*it).assert_status[pidx] == SKIP) { continue; }\
                    if ((*it).assert_status[pidx] > PASS) { this->_errorc[EXPECTED]++; }

                    /** old_value: value from Value[key] */
                    old_value = new string (parents[pidx], 0);

                    old_value->_set_key ((*it).key, wcslen ((*it).key));

                    if ((*it).new_value->type () == value::string_t)
                      *old_value = *(dynamic_cast<string *>((*it).new_value));
                    else
                      *(dynamic_cast<value *>(old_value)) = *(*it).new_value;

                    json *parent = parents[pidx];   //  old_value->_parent;

                    if (parent)
                      {
                        ASSERT_EQUAL_IDX ("parent->count ()",
                                          (*it).count,
                                          parent->length ());

                        ASSERT_EQUAL_IDX ("(*parent)[(*it).key].type ()",
                                          (*parent)[(*it).key].type (),
                                          (*it).type);
                      }
                    else if ((*it).new_value->type () == value::string_t)
                      {
                        CPPUNIT_ASSERT_MESSAGE ("old_value->get ()",
                                                wcscmp (L"xxx",
                                                old_value->get ()) == 0);
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
      test_str_length () override
      {
       // Tested in test_parse_parent () and test_parse_no_parent ()
      }

      virtual void
      test_str_value () override
      {
        // Tested in test_parse_parent () and test_parse_no_parent ()
      }

      void
      test__string ()
      {
        wchar_t endc = 0;

        struct assert
        {
            const wchar_t *input;
            long charc;
            int assert_status;
        };

        std::vector<struct assert > test = {
            { L"", 0, PASS },
            { L"x", 1, PASS },

            { L"x\"", -1, PASS },
            { L"x\u001F\"", -1, PASS }
        };

        TEST_IT_START

          string s;

          s._readp = (*it).input;

          long charc = s.__string (endc);

          ASSERT_EQUAL_IDX ("charc", (*it).charc, charc);

        TEST_IT_END;
      }

      virtual void test__clear () override {}

      /**
       * 4.
       * @brief suite
       * @return
       */
      static CppUnit::Test*
      suite ()
      {
        CppUnit::TestSuite *s = new CppUnit::TestSuite ("json string test");

        /* 0. */  s->addTest (new CppUnit::TestCaller<json_string_test> ("test_ctor_dtor", &json_string_test::test_ctor_dtor));
        /* 1. */  s->addTest (new CppUnit::TestCaller<json_string_test> ("test_parse_1", &json_string_test::test_parse_1));
        /* 2. */  s->addTest (new CppUnit::TestCaller<json_string_test> ("test_assign_all_values", &json_string_test::test_assign_all_values));
        /* 3. */  s->addTest (new CppUnit::TestCaller<json_string_test> ("test__string", &json_string_test::test__string));

        /* 4.   s->addTest (new CppUnit::TestCaller<json_string_test> ("test__clear", &json_string_test::test__clear)); */

        return s;
      }
  };
} // Namespace format
#endif // JSON_STRING_TEST_H
