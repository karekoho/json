#ifndef JSON_STRING_TEST_H
#define JSON_STRING_TEST_H

#include "json_leaf_test.h"

namespace format
{
  namespace json
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
      json parent;

      string src[] = {
        string (),
        string (L"x"),
        string (& parent, 1),
      };

      // TODO: To be clearer, first test every constructor and copies, then one as<> () test is enough
      // TODO: what is the correct place for these?
      json j = new object { { L"0", new string () },
                            { L"1", new string (L"x") },
                            { L"2", new string (& parent, 1) }, // stringify () --> Segmentation fault: 11
                            { L"3", new string (src[1]) } // copy
                          };

      CPPUNIT_ASSERT_MESSAGE ("as string",
                                wcscmp ( L"", j[L"0"].as<const wchar_t *> () ) == 0);

      CPPUNIT_ASSERT_MESSAGE ("as string",
                                wcscmp ( L"x", j[L"1"].as<const wchar_t *> () ) == 0);

      CPPUNIT_ASSERT_MESSAGE ("as string",
                                wcscmp ( L"", j[L"2"].as<const wchar_t *> () ) == 0);

      CPPUNIT_ASSERT_MESSAGE ("copy as string",
                                wcscmp ( L"x", j[L"3"].as<const wchar_t *> () ) == 0);

    }

    virtual void
    test__parse () override
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
        size_t charc[2];
        size_t length;
        wchar_t endc;
        int assert_status;
      };

      std::vector<struct assert > test = {
//          { L"\"\"", L"\"\"", 0 + 2, 0, (wchar_t) 0, PASS },
//          { L"\"xxx\"", L"\"xxx\"", 3 + 2, 3, (wchar_t) 0, PASS },
//          { L"\" xxx \"", L"\" xxx \"", 5 + 2, 5, (wchar_t) 0, PASS },
//          { L"\" xxx \" ", L"\" xxx \"", 5 + 2, 5, L' ', PASS },

            { L"", L"", { 0 + 0, 0 + 2 }, 0, (wchar_t) 0, PASS_T }, // Actually never possible
            { L"\"\"", L"", { 0 + 2, 0 + 2 }, 0, (wchar_t) 0, PASS_T },
            { L"\"xxx\"", L"xxx", { 3 + 2, 3 + 2  }, 3, (wchar_t) 0, PASS_T },
            { L"\" xxx \"", L" xxx ", { 5 + 2, 5 + 2 }, 5, (wchar_t) 0, PASS_T },
            { L"\" xxx \" ", L" xxx ", { 5 + 2, 5 + 2 }, 5, L' ', PASS_T },
      };

      TEST_IT_START

        json p;

        const wchar_t *startp = (*it).startp;

        wchar_t endc = 0;
        string r;
        r._readp = startp;
        long _make_value_charc = r._string (endc); // This is how _make_value gets string length

        // Verify that assertions are correct
        CPPUNIT_ASSERT_EQUAL_MESSAGE ("_make_value charc", (size_t) _make_value_charc, (*it).charc[0]);

        string *s = new string (& p, (*it).charc[0]);

        CPPUNIT_ASSERT_EQUAL_MESSAGE ("s->get ()", (size_t) 0, wcslen (s->get ()));

        const wchar_t *readp = s->_parse (startp);

        ASSERT_EQUAL_IDX ("string.readp", readp, (*it).startp + (*it).charc[0]);
        ASSERT_EQUAL_IDX ("*(string.readp)", (wchar_t) *readp, (*it).endc);
        ASSERT_EQUAL_IDX ("s->_str_length ()", (*it).charc[1], s->_str_length ());
        ASSERT_EQUAL_IDX ("s->length ()", (*it).length, s->length ());

        CPPUNIT_ASSERT_MESSAGE ("s->_to_string ()", wcscmp ((*it).str_value, s->_to_string ()) == 0);

        delete s;

       TEST_IT_END
    }

    void
    test_parse_no_parent ()
    {
      struct assert
      {
        const wchar_t *startp;
        const wchar_t *str_value;
        size_t charc;
        size_t length;
        wchar_t endc;
        int assert_status;
      };

      std::vector<struct assert > test = {
          { L"", L"", 0  + 2, 0, (wchar_t) 0, PASS_T },

          { L" ", L" ", 1 + 2, 1, (wchar_t) 0, PASS_T },
          { L"x", L"x", 1 + 2, 1, (wchar_t) 0, PASS_T },
          { L"xxx", L"xxx", 3 + 2, 3, (wchar_t) 0, PASS_T },

          { L"\u005C", L"\\", 1 + 2, 1, (wchar_t) 0, PASS_T }, // https://datatracker.ietf.org/doc/html/rfc8259#section-7
          //{ L"a\u005Cb", L"a\\b", 3 + 2, 3, (wchar_t) 0, PASS }, // https://datatracker.ietf.org/doc/html/rfc8259#section-8.3

          // Inner quotes
          { L"\"xxx\"", L"\"xxx\"", 5 + 2, 5, (wchar_t) 0, PASS_T },

          // Control characters
          { L"\u0000", L"", 2, 0, (wchar_t) 0, PASS_T },
          { L"\u001F", nullptr, 0, 0, (wchar_t) 0, FAIL_T },
      };

      string *s = nullptr;

      TEST_IT_START

            s = new string ((*it).startp);

            ASSERT_EQUAL_IDX ("s->_str_length ()", (*it).charc, s->_str_length ());
            ASSERT_EQUAL_IDX ("s->length ()", (*it).length, s->length ());

            CPPUNIT_ASSERT_MESSAGE ("s->_to_string ()", wcscmp ((*it).str_value, s->_to_string ()) == 0);

            delete s;
          }
        catch (format::json::json_error & e)
          {
            this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl;
            // delete s; // Can't delete ???
          }
        }

      (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]); \
      CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);

      {
        string s;
        CPPUNIT_ASSERT_EQUAL_MESSAGE ("string _str_length", (size_t) 2, s._str_length ());
        CPPUNIT_ASSERT_EQUAL_MESSAGE ("string length", (size_t) 0, s.length ());
        CPPUNIT_ASSERT_MESSAGE ("string equal", wcscmp (L"", s._to_string ()) == 0);
      }
    }

    virtual void
    test_assign_all_values () override
    {
      object_accessor object_parent;

      std::array<json *, 2> parents = {
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

       string s (L"xxx");

       std::vector<struct assert > test = {
        /// @note operator =(const wchar_t * const s) removed
        // { & s, value::string_t, L"0",  0, 1,  { PASS, PASS } },
        // { __VALUE[value::number_t], value::number_t, L"1",  0, 2, { PASS, FAIL } },
       };

       string *old_value = nullptr;

       for (size_t pidx = 0; pidx < parents.size () ; pidx++)
          {
            this->_idx[0] = 0;

            for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++)
              {
                try
                  {
                    if ((*it).assert_status[pidx] == SKIP_T) { continue; }\
                    if ((*it).assert_status[pidx] > PASS_T) { this->_errorc[EXPECTED]++; }

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
                                          parent->size ());

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
                 catch (format::json::json_error & e)
                  {
                    this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl;
                    delete old_value;
                  }
              }
            (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]);
            CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
        }
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
            { L"", 0, PASS_T },
            { L"x", 1, PASS_T },

            { L"x\"", -1, PASS_T },
            { L"x\u001F\"", -1, PASS_T }
        };

        TEST_IT_START

          string s;
          s._readp = (*it).input;
          //long charc = s.__string (endc);
          //ASSERT_EQUAL_IDX ("charc", (*it).charc, charc);

        TEST_IT_END
      }

      /**
       * @brief test_operator_assign_const_wchar_t_ptr
       */
      void
      test_operator_assign_const_wchar_t_ptr ()
      {
        json parent;

        string *s = new string (L"xx");
        *s = L"x";

        CPPUNIT_ASSERT_MESSAGE ("s.get () == \"x\"",
                                s->get () == std::wstring (L"x"));

        {
          // Testing assignment via copy, find out a direct way... propably ok
          json j = new object { { L"0", new string (*s) } };

          CPPUNIT_ASSERT_MESSAGE ("s.get () == \"x\"",
                                  j[L"0"].as<const wchar_t *> () == std::wstring (L"x"));
        }

        parent[L"0"] = s;   // s->_parent == parent
        parent[L"0"] = L"xxx";

        CPPUNIT_ASSERT_MESSAGE ("(parent[L\"0\"] == \"xxx\"",
                                s->get () == std::wstring (L"xxx"));

        {
          // Testing assignment via copy, find out a direct way... propably ok
          json j = new object { { L"0", new string (*s) } };

          CPPUNIT_ASSERT_MESSAGE ("s.get () == \"xxx\"",
                                  j[L"0"].as<const wchar_t *> () == std::wstring (L"xxx"));
        }
      }

      virtual void
      test__clone_const_value_ref () override
      {
        string src = L"xxx";
        string copy (src);
        // string copy;
        // (void) copy._clone (src); // will not work for test as string

        // const wchar_t * startp = copy._string_value.c_str ();
        const wchar_t * startp = copy._value.string;

        //CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy._startp is set", true, copy._startp == startp);
        CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy._charc", src._charc, copy._charc);
        CPPUNIT_ASSERT_MESSAGE ("copy.get ()", wcscmp (L"xxx", copy.get ()) == 0);
        CPPUNIT_ASSERT_MESSAGE ("copy._to_string ()", wcscmp (L"xxx", copy._to_string ()) == 0);

        {
          string src[] = {
            string (),
            string (L""),
          };

          string copy[] = {
            src[0],
            src[1]
          };

//          CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy._startp is set",
//                                        true, copy[0]._startp != src[0]._startp
//                                              && copy[1]._startp != src[1]._startp);

          CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy._charc", src[0]._charc, copy[0]._charc);
          CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy._charc", src[1]._charc, copy[1]._charc);

          CPPUNIT_ASSERT_MESSAGE ("copy.get ()",
                                  wcscmp (L"", copy[0].get ()) == 0
                                  && wcscmp (L"", copy[1].get ()) == 0);

          CPPUNIT_ASSERT_MESSAGE ("copy._to_string ()",
                                  wcscmp (L"", copy[0]._to_string ()) == 0
                                  && wcscmp (L"", copy[1]._to_string ()) == 0);
        }

        // Test copy as<> ()
        json j = new object { { L"0", new string (copy) } }; // copy of copy

        CPPUNIT_ASSERT_MESSAGE ("copy copy as string == \"xxx\"",
                                j[L"0"].as<const wchar_t *> () == std::wstring (L"xxx"));
      }

      virtual void
      test_type () override
      {
        CPPUNIT_ASSERT_EQUAL_MESSAGE ("value::type ()",
                                      value::string_t,
                                      string ().type ());
      }

      virtual void
      test__clear () override
      { CPPUNIT_ASSERT_ASSERTION_PASS ("Calls std::string.clear ()"); }

      virtual void
      test_str_length () override
      { CPPUNIT_ASSERT_ASSERTION_PASS ("Asserted in test_parse_parent (), test_parse_no_parent ()"); }

      virtual void
      test__to_string () override
      { CPPUNIT_ASSERT_ASSERTION_PASS ("Asserted in test_parse_parent (), test_parse_no_parent ()"); }

      // TODO: rename value_test_interface::test_lenght --> test_count
      void
      test_length ()
      { CPPUNIT_ASSERT_ASSERTION_PASS ("Asserted in test_parse_parent (), test_parse_no_parent ()"); }

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
        /* 1. */  s->addTest (new CppUnit::TestCaller<json_string_test> ("test__parse", &json_string_test::test__parse));
        /* 2. */  s->addTest (new CppUnit::TestCaller<json_string_test> ("test_assign_all_values", &json_string_test::test_assign_all_values));
        /* 3. */  // s->addTest (new CppUnit::TestCaller<json_string_test> ("test__string", &json_string_test::test__string));
        /* 4. */  s->addTest (new CppUnit::TestCaller<json_string_test> ("test__clone_const_value_ref", &json_string_test::test__clone_const_value_ref));
        /* 5. */  s->addTest (new CppUnit::TestCaller<json_string_test> ("test__clear", &json_string_test::test__clear));
        /* 6. */  s->addTest (new CppUnit::TestCaller<json_string_test> ("test_type", &json_string_test::test_type));
        /* 7. */  s->addTest (new CppUnit::TestCaller<json_string_test> ("test_str_length", &json_string_test::test_str_length));
        /* 8. */  s->addTest (new CppUnit::TestCaller<json_string_test> ("test__to_string", &json_string_test::test__to_string));
        /** @note operator =(const wchar_t * const s) removed */
        /* 9. */  // s->addTest (new CppUnit::TestCaller<json_string_test> ("test_operator_assign_const_wchar_t_ptr", &json_string_test::test_operator_assign_const_wchar_t_ptr));
        /* 10. */ s->addTest (new CppUnit::TestCaller<json_string_test> ("test_length", &json_string_test::test_length));

        return s;
      }
  };
} // Namespace json
} // Namespace format
#endif // JSON_STRING_TEST_H
