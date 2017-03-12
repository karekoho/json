#ifndef JSON_INTERFACE_TEST_H
#define JSON_INTERFACE_TEST_H

#include <json_value_test_interface.h>
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

          m->_startp = m->_readp = startp;

          m->_look_ahead ();

          ASSERT_EQUAL_IDX ("value.readp", (*it).readp , *(m->_readp));

          delete m;

        TEST_IT_END;
      }

      // void test_lexeme ();

      void
      test__string () // Moved to json_test
      {
        wchar_t endc;

        struct assert {
            const wchar_t *startp;
            long int charc;
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
            long int charc = wcslen (startp);

            json_mock_value *m  = new json_mock_value ();

            m->_startp = m->_readp = startp;

            m->_look_ahead ();

            charc = m->_string (endc);

            ASSERT_EQUAL_IDX ("charc", (*it).charc , charc);

            delete m;

        TEST_IT_END;
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

            m->_startp = m->_readp = startp;

            value::_literal ltr = m->_is_literal ();

            ASSERT_EQUAL_IDX ("literal value", (*it).value_type , ltr);

            delete m;

        TEST_IT_END;
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

        TEST_IT_END;

        CPPUNIT_ASSERT_MESSAGE ("starp", wcscmp (L"abb\"ccc\"", startp) == 0);

        delete[] startp;
        // delete dst;
      }

      void
      test_operator_assign_undefined ()
      {
        boolean b;

        array a = L"[true]";

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
                              a.count ()
                              );
        TEST_IT_END;
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

//        std::vector<struct assert> test = {
//          { new object (), value::object_t, PASS },
//          { new array (), value::array_t, PASS },
//          { new string (), value::string_t, PASS },
//          { new number (), value::number_t, PASS },
//          { new boolean (), value::boolean_t, PASS },
//          { new null (), value::null_t, PASS },
//          { new unique_undefined (), value::undefined_t, PASS }
//        };

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
                                      j[hdx][L"0"].type ()
                                     );
                  }
            TEST_IT_END;
          }

//        for (auto it = test.begin (); it != test.end (); ++it)
//          delete (*it).val;
      }

      void
      test_assign_ptr ()
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
                                  j[hdx][L"0"].type ()
                                 );
            TEST_IT_END;
          }
      }

      virtual void
      test_operator_at_index () override
      {
      }

      virtual void
      test_count () override
      {
      }

      void
      test_operator_equal_value_t ()
      {
        CPPUNIT_ASSERT_MESSAGE ("value == value_t", boolean () == value::boolean_t);
      }

      void
      test_operator_equal_value ()
      {
        CPPUNIT_ASSERT_MESSAGE ("value == value", boolean () == boolean ());
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
      test_operator_assign_double ()
      {
        json j = L"{}";

        CPPUNIT_ASSERT_EQUAL_MESSAGE ("j[\"0\"].type ()",
                                      value::number_t,
                                      (j[L"0"] = (double) 100)[L"0"].type ()
            );
      }

      void
      test_operator_assign_bool ()
      {
        json j = L"{}";

        CPPUNIT_ASSERT_EQUAL_MESSAGE ("j[\"0\"].type ()",
                                      value::boolean_t,
                                      (j[L"0"] = true)[L"0"].type ()
            );
      }

      void
      test_operator_assign_nullptr ()
      {
        json j = L"{}";

        CPPUNIT_ASSERT_EQUAL_MESSAGE ("j[\"0\"].type ()",
                                      value::null_t,
                                      (j[L"0"] = nullptr)[L"0"].type ()
            );
      }

      virtual void test_str_length () override {}
      virtual void test_str_value () override {}
      virtual void test_assign_all_values () override {}
      virtual void test__clear () override {}
      virtual void test_erase () override {}
      virtual void test_ctor_dtor () override {}
      virtual void test_parse_1 () override {}
      virtual void test_operator_at_key () override {}
      virtual void test_type () override {}

      void
      test___sizeof ()
      {
        json parent;

        struct assert
        {
          value *val;
          size_t size;
          int assert_status;
        };

        std::vector<struct assert> test = {
          { new json (), sizeof (json), PASS },
          { new object (), sizeof (object), PASS },
          { new array (), sizeof (array), PASS },
          { new string (), sizeof (string), PASS },
          { new number (), sizeof (number), PASS },
          { new boolean (), sizeof (boolean), PASS },
          { new null (), sizeof (null), PASS },
          { new undefined (), sizeof (undefined), PASS },
          { new format::undefined (), sizeof (format::undefined), PASS },
          { no_value::instance (& parent), sizeof (no_value), PASS }
        };

        TEST_IT_START
            // std::cout << (*it).size << std::endl;
            ASSERT_EQUAL_IDX ("value::__sizeof ()", (*it).size, (*it).val->__sizeof ());
        TEST_IT_END;

        for (auto it = test.begin (); it != test.end () - 2; ++it)
          delete (*it).val;
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
        /* 8. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_size", &json_value_test::test___sizeof));

        /* 9. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("", &json_value_test::test_operator_assign_wchar_t_ptr));
        /* 10. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("", &json_value_test::test_operator_assign_double));
        /* 11. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("", &json_value_test::test_operator_assign_bool));
        /* 12. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("", &json_value_test::test_operator_assign_nullptr));

        /* 13. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_assign_ptr", &json_value_test::test_assign_ptr));

        return s;
      }
  };
}
#endif // JSON_INTERFACE_TEST_H
