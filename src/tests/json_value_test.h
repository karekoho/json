#ifndef JSON_INTERFACE_TEST_H
#define JSON_INTERFACE_TEST_H

#include "json_value_test_interface.h"
#include "json_mock_value.h"

namespace format
{
  /**
   * 0.
   * @brief The json_value_test class
   */
  class json_value_test : public json_value_test_interface
  {
  public:

      void
      test__lookahead ()
      {
        struct assert {
            const wchar_t *startp;
            wchar_t readp;
            int assert_status;
        };

        std::vector<struct assert > test = {
            { L"", 0, PASS},
            { L"   ", 0, PASS },
            { L"x", 'x', PASS },
            { L" \
                a", 'a', PASS },
            { L"   \"b", '"', PASS },
            { L"   \n\r\tc ", 'c', PASS },
            { L"   5", '5', PASS }
        };

        TEST_IT_START

          const wchar_t *startp = (*it).startp;

          format::json_mock_value *m  = new format::json_mock_value ();

          m->_readp = startp;

          m->_look_ahead ();

          ASSERT_EQUAL_IDX ("value.readp", (*it).readp , *(m->_readp));

          delete m;

        TEST_IT_END
      }

      void
      test__string () // Moved to json_test
      {
        wchar_t endc;

        struct assert {
            const wchar_t *startp;
            long charc;
            int assert_status;
        };

        std::vector<struct assert > test = {
            { L" ", 0, PASS},
            { L"\"", -1, PASS },
            { L"\"x\"", 3, PASS },
            { L"\" x\"", 4, PASS },
            { L"\" xx", -4, PASS },

            { L"\"\u001F\"", -1, PASS },
            { L"\"xx\u001F\"", -3, PASS }
        };

        TEST_IT_START

            const wchar_t *startp = (*it).startp;
            long charc = static_cast<long> (wcslen (startp));

            json_mock_value *m  = new json_mock_value ();

            m->_readp = startp;

            m->_look_ahead ();

            charc = m->_string (endc);

            ASSERT_EQUAL_IDX ("charc", (*it).charc , charc);

            delete m;

        TEST_IT_END
      }

      void
      test__is_literal ()
      {
        struct assert {
            const wchar_t *startp;
            value::_literal value_type;
            int assert_status;
        };

        std::vector<struct assert> test = {
          { L"", value::_literal::no_literal, PASS },
          { L"   ", value::_literal::no_literal, PASS },
          { L"xxx   ", value::_literal::no_literal, PASS },
          { L"xxxxxx   ", value::_literal::no_literal, PASS },
          { L"true    ", value::_literal::true_value, PASS },
          { L"false    ", value::_literal::false_value, PASS },
          { L"null   ", value::_literal::null_value, PASS }
        };

        TEST_IT_START

            const wchar_t *startp = (*it).startp;

            json_mock_value *m  = new json_mock_value ();

            m->_readp = startp;

            value::_literal ltr = m->_is_literal ();

            ASSERT_EQUAL_IDX ("literal value", (*it).value_type , ltr);

            delete m;

        TEST_IT_END
      }

      void
      test__str_append ()
      {
        wchar_t *dst = new wchar_t[8 + 1]();
        wchar_t *startp = dst;

        struct assert {
            const wchar_t *src;
            size_t charc[2];
            int assert_status;
        };

        std::vector<struct assert> test = {
          { L"",  { 0, 0 }, PASS },
          { L"a",  { 1, 1 }, PASS },
          { L"bb",  { 2, 3 }, PASS },
          { L"\"ccc\"",  { 5, 8 }, PASS },
        };

        TEST_IT_START

            dst = value::_str_append (dst, (*it).src, (*it).charc[0]);

            ASSERT_EQUAL_IDX ("dst", startp + (*it).charc[1], dst);

        TEST_IT_END

        CPPUNIT_ASSERT_MESSAGE ("starp", wcscmp (L"abb\"ccc\"", startp) == 0);

        delete[] startp;
      }

      void
      test_operator_assign_undefined ()
      {
        boolean b;

        array a = { new boolean () }; //L"[true]";

        struct assert
        {
          value *val;
          size_t size;    // Array::_element_list.size ()
          int assert_status;
        };

        std::vector<struct assert> test = {
          { & b, 1, PASS }, // No parent
          { & (a[(size_t) 0]), 0, PASS }  // Has parent
        };

        TEST_IT_START
            *(*it).val = format::undefined ();
            ASSERT_EQUAL_IDX ("array::count ()",
                              (*it).size,
                              a.count ());
        TEST_IT_END

        json j = new object {
                  { L"Image",
                    new object {
                      { L"Width", new number ((long) 800) },
                      { L"Height", new number ((long) 600) },
                      { L"Title", new string (L"View from 15th Floor") },
                      { L"Thumbnail", new object {
                          { L"Url", new string (L"http://www.example.com/image/481989943") },
                          { L"Height", new number ((long) 125) },
                          { L"Width", new number ((long) 100) },
                        }
                      },
                      { L"Animated", new boolean (false) },
                      { L"IDs", new array { new number ((long) 116), new number ((long) 943), new number ((long) 234), new number ((long) 38793) } }
                    }
                  }
                };

//        j[L"Image"][L"Thumbnail"][L"Url"] = undefined ();
//        j[L"Image"][L"Thumbnail"][L"Height"] = undefined ();
//        j[L"Image"][L"Thumbnail"][L"Width"] = undefined ();
//        j[L"Image"][L"Thumbnail"] = undefined ();

//        j[L"Image"][L"Width"] = undefined ();
//        j[L"Image"][L"Height"] = undefined ();
//        j[L"Image"][L"Title"] = undefined ();

//        j[L"Image"][L"Animated"] = undefined ();
//        j[L"Image"][L"IDs"][(size_t) 3] = undefined ();
//        j[L"Image"][L"IDs"] = undefined ();

//        CPPUNIT_ASSERT_EQUAL_MESSAGE ("j[L\"Image\"].count ()", // PASS
//                                      (size_t) 0,
//                                      j[L"Image"].count ());
      }

      void
      test_assign_copy ()
      {
        json j[] = {
          L"{}",
          L"[]"
        };

        struct assert
        {
          value *val;
          value::value_t type;  // old, current
          int assert_status;
        };

        std::vector<struct assert> test = {
          { __VALUE[value::object_t], value::object_t, PASS },
          { __VALUE[value::array_t], value::array_t, PASS },
          { __VALUE[value::string_t], value::string_t, PASS },
          { __VALUE[value::number_t], value::number_t, PASS },
          { __VALUE[value::boolean_t], value::boolean_t, PASS },
          { __VALUE[value::null_t], value::null_t, PASS },
          { __VALUE[value::undefined_t], value::undefined_t, PASS }
        };

        for (size_t hdx = 0; hdx < 2; hdx++)
          {
            _idx[0] = 0;

            TEST_IT_START

                for (size_t jdx = 0; jdx < 2; jdx++)
                  {
                    j[hdx][L"0"] = *(*it).val;   // Undefined <-- Object, Object <-- Array, ...

                    ASSERT_EQUAL_IDX ("value::type ()",
                                      (*it).type,
                                      j[hdx][L"0"].type ());
                  }
            TEST_IT_END
          }
      }

      void
      test_assign_value_ptr ()
      {
        json j[] = {
          L"{}",
          L"[]"
        };

        struct assert
        {
          value *val;
          value::value_t type;  // old, current
          int assert_status;
        };

        for (size_t hdx = 0; hdx < 2; hdx++)
          {
            std::vector<struct assert> test = {
              { new object (), value::object_t, PASS },
              { new array (), value::array_t, PASS },
              { new string (), value::string_t, PASS },
              { new number (), value::number_t, PASS },
              { new boolean (), value::boolean_t, PASS },
              { new null (), value::null_t, PASS },
              { new format::unique_undefined (), value::undefined_t, PASS }
            };

            _idx[0] = 0;

            TEST_IT_START
                j[hdx][L"0"] = (*it).val;   // Undefined <-- Object, Object <-- Array, ...

                ASSERT_EQUAL_IDX ("value::type ()",
                                  (*it).type,
                                  j[hdx][L"0"].type ());
            TEST_IT_END
          }
      }

      void
      test_operator_equal_value_t ()
      {
        CPPUNIT_ASSERT_MESSAGE ("value == value_t",
                                boolean () == value::boolean_t);
      }

      void
      test_operator_equal_value ()
      {
        CPPUNIT_ASSERT_MESSAGE ("value == value",
                                boolean () == boolean ());
      }

      void
      test_operator_assign_wchar_t_ptr ()
      {
        json j = L"{}";

        CPPUNIT_ASSERT_EQUAL_MESSAGE ("j[\"0\"].type ()",
                                      value::array_t,
                                      (j[L"0"] = L"[]")[L"0"].type ()
                                      // (json (L"{}")[L"0"] = L"[]")[L"0"].type () // Compiles and passes
            );
      }

      void
      test_operator_assign_long ()
      {
        json j = L"{}";

        CPPUNIT_ASSERT_EQUAL_MESSAGE ("j[\"0\"].type ()",
                                      value::number_t,
                                      (j[L"0"] = (long) 100)[L"0"].type ());
      }

      void
      test_operator_assign_double ()
      {
        json j = L"{}";

        CPPUNIT_ASSERT_EQUAL_MESSAGE ("j[\"0\"].type ()",
                                      value::number_t,
                                      (j[L"0"] = 100.0)[L"0"].type ());
      }

      void
      test_operator_assign_bool ()
      {
        json j = L"{}";

        CPPUNIT_ASSERT_EQUAL_MESSAGE ("j[\"0\"].type ()",
                                      value::boolean_t,
                                      (j[L"0"] = true)[L"0"].type ());
      }

      void
      test_operator_assign_nullptr ()
      {
        json j = L"{}";

        CPPUNIT_ASSERT_EQUAL_MESSAGE ("j[\"0\"].type ()",
                                      value::null_t,
                                      (j[L"0"] = nullptr)[L"0"].type ());
      }

      virtual void
      test_operator_at_index () override
      { CPPUNIT_ASSERT_ASSERTION_PASS (); }

      virtual void
      test_count () override
      { CPPUNIT_ASSERT_ASSERTION_PASS (); }

      virtual void
      test_str_length () override
      { CPPUNIT_ASSERT_ASSERTION_PASS (); }

      virtual void
      test__to_string () override
      { CPPUNIT_ASSERT_ASSERTION_PASS (); }

      virtual void
      test_assign_all_values () override
      { CPPUNIT_ASSERT_ASSERTION_PASS (); }

      virtual void
      test__clear () override
      { CPPUNIT_ASSERT_ASSERTION_PASS (); }

      virtual void
      test__erase () override
      { CPPUNIT_ASSERT_ASSERTION_PASS (); }

      virtual void
      test_ctor_dtor () override
      { CPPUNIT_ASSERT_ASSERTION_PASS (); }

      virtual void
      test__parse () override
      { CPPUNIT_ASSERT_ASSERTION_PASS (); }

      virtual void
      test_operator_at_key () override
      { CPPUNIT_ASSERT_ASSERTION_PASS (); }

      virtual void
      test_type () override
      { CPPUNIT_ASSERT_ASSERTION_PASS ();}

      virtual void
      test__assign_value_ptr_value_ptr () override
      { CPPUNIT_ASSERT_ASSERTION_PASS (); }

      virtual void test__clone_const_value_ref () override
      { CPPUNIT_ASSERT_ASSERTION_PASS (); }

      void
      test_sizeof ()
      {
        struct assert
        {
          const char *name;
          size_t size;
          int assert_status;
        };

        std::vector<struct assert> test = {
          { "json", sizeof (json), PASS },
          { "object", sizeof (object), PASS },
          { "array", sizeof (array), PASS },
          { "string", sizeof (string), PASS },
          { "number", sizeof (number), PASS },
          { "boolean", sizeof (boolean), PASS },
          { "null", sizeof (null), PASS },
          { "undefined", sizeof (undefined), PASS },
        };

        TEST_IT_START
            std::cout << (*it).name << ": " << (*it).size << std::endl;
        TEST_IT_END
      }

      void
      test_decode ()
      {
        struct assert
        {
          const wchar_t *endoced;
          const wchar_t *dedoced;
          int assert_status;
        };

        std::vector<struct assert > test = {
          { L"012", L"012", PASS },
          { L"~0", L"~", PASS },
          { L"~1", L"/", PASS },
          { L"~01", L"~1", PASS },
          { L"~012", L"~12", PASS },
          { L"~", L"~", FAIL }, // NOTE: throwing exception leak 8 bytes
          { L"~2", L"~2", FAIL }  // NOTE: throwing exception leak 12 bytes
        };

        TEST_IT_START

          const wchar_t *encoded = (*it).endoced;

          wchar_t *key_cursor = new wchar_t[wcslen (encoded) + 1] ();
          const wchar_t * const key_begin = key_cursor;

          while (*encoded != 0)
            key_cursor = value::reference_token::decode (key_cursor, & encoded);

          ASSERT_EQUAL_IDX ("key decoded", 0, wcscmp (key_begin, (*it).dedoced));

          delete [] key_begin;

        TEST_IT_END
      }

      void
      test_path_next ()
      {
        struct assert
        {
          const wchar_t *ref_token;
          std::vector<const wchar_t *> key_vec;
          int assert_status;
        };

        std::vector<struct assert > test = {
          { L"", { L"" } , PASS },
          { L"/foo", { L"foo" } , PASS },
          { L"/foo/0", { L"foo", L"0" } , PASS },
          { L"/1/0123/foo", { L"1", L"0123", L"foo" } , PASS },
        };

        TEST_IT_START

            value::reference_token rt ((*it).ref_token);

            for (auto exp_it = (*it).key_vec.begin (); exp_it != (*it).key_vec.end (); ++exp_it)
              {
                const wchar_t *act_key = rt.path_next ();
                const wchar_t *exp_key = (*exp_it);

                ASSERT_EQUAL_IDX ("path next", 0, wcscmp (act_key, exp_key));
              }

        TEST_IT_END
      }

      void
      test__point ()
      {
        format::json j (  L"{ \"foo\": [\"bar\", \"baz\"],\
                          \"\": 0,\
                          \"a/b\": 1,\
                          \"c%d\": 2,\
                          \"e^f\": 3,\
                          \"g|h\": 4,\
                          \"i\\j\": 5,\
                          \" \": 7,\
                          \"m~n\": 8 }" );

        // FIXME: \"k\"l\": 6 parse error

        struct assert
        {
          const wchar_t *ref_token;
          value::value_t type;
          long num_val;
          int assert_status;
        };

        std::vector<struct assert > test = {
          { L"", value::value_t::object_t, 0, PASS },
          { L"/foo", value::value_t::array_t, 0, PASS },
          { L"/foo/1", value::value_t::string_t, 0, PASS },
          { L"/", value::value_t::number_t, 0, PASS },
          { L"a~1b", value::value_t::number_t, 1, PASS },
          { L"c%d", value::value_t::number_t, 2, PASS },
          { L"g|h", value::value_t::number_t, 4, PASS },
          { L"i\\j", value::value_t::number_t, 5, PASS },
          { L"/ ", value::value_t::number_t, 7, PASS },
          { L"m~0n", value::value_t::number_t, 8, PASS },
          { L"/not", value::value_t::undefined_t, 0, PASS },
          { L"/not/found", value::value_t::undefined_t, 0, FAIL },
          { L"/foo/foo", value::value_t::string_t, 0, FAIL },
        };

        TEST_IT_START

            value::reference_token rt = value::reference_token ((*it).ref_token);
            format::value & v = j._point (& rt, static_cast<value &> (j));

            ASSERT_EQUAL_IDX ("point type", (*it).type, v.type ());

            if (v.type () == value::number_t)
              {
                format::number & n = static_cast<format::number &> (v);
                ASSERT_EQUAL_IDX ("point numeric value", (*it).num_val, static_cast<long> (n.get ()));
              }

        TEST_IT_END
      }

      void
      test_is_index ()
      {
        struct assert
        {
          const wchar_t *key;
          bool is_index;
          int assert_status;
        };

        std::vector<struct assert > test = {
          { L"-", true, PASS },
          { L"0", true, PASS },
          { L"1", true, PASS },
          { L"123", true, PASS },
          { L"", false, PASS },
          { L"01", false, PASS },
          { L"a", false, PASS },
          { L"1a", false, PASS },
        };

        TEST_IT_START

          bool is_index = value::reference_token::is_index ((*it).key);
          ASSERT_EQUAL_IDX ("is_index", (*it).is_index, is_index);

        TEST_IT_END
      }

      /**
       * 0.
       * @brief suite
       * @return
       */
      static CppUnit::Test *
      suite ()
      {
        CppUnit::TestSuite *s = new CppUnit::TestSuite ("json value test");

        /* 0. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_assign_copy", &json_value_test::test_assign_copy));
        /* 1. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_assign_undefined", &json_value_test::test_operator_assign_undefined));
        /* 2. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_lookahead", &json_value_test::test__lookahead));
        /* 3. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_is_literal", &json_value_test::test__is_literal));
        /* 4. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_is_quoted", &json_value_test::test__string));
        /* 5. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test__str_append", &json_value_test::test__str_append));
        /* 6. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_operator_equal_value_t", &json_value_test::test_operator_equal_value_t));
        /* 7. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_operator_equal_value", &json_value_test::test_operator_equal_value));
        /* 8. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_operator_assign_wchar_t_ptr", &json_value_test::test_operator_assign_wchar_t_ptr));
        /* 9. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_operator_assign_double", &json_value_test::test_operator_assign_double));
        /* 10. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_operator_assign_bool", &json_value_test::test_operator_assign_bool));
        /* 11. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_operator_assign_nullptr", &json_value_test::test_operator_assign_nullptr));
        /* 12. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_assign_ptr", &json_value_test::test_assign_value_ptr));
        /* 13. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test__assign_value_ptr_value_ptr", &json_value_test::test__assign_value_ptr_value_ptr));
        /* 14. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test__clone_const_value_ref", &json_value_test::test__clone_const_value_ref));
        /* 15. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_operator_assign_long", &json_value_test::test_operator_assign_long));
        /* 16. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_decode", &json_value_test::test_decode));
        /* 17. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_path_next", &json_value_test::test_path_next));
        /* 18. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_is_index", &json_value_test::test_is_index));
        /* 19. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test__point", &json_value_test::test__point));

        return s;
      }
  };
}
#endif // JSON_INTERFACE_TEST_H
