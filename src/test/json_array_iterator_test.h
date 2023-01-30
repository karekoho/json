#ifndef JSON_ARRAY_ITERATOR_TEST
#define JSON_ARRAY_ITERATOR_TEST

#include "unit_test.h"
#include "json_mock_value.h"

namespace format
{
  namespace json
  {
    namespace test
    {
      //s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_construct_assign_destruct", &json_array_iterator_test::test_construct_assign_destruct));
      //s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_dereference", &json_array_iterator_test::test_dereference));
      //s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_pre_increment", &json_array_iterator_test::test_pre_increment));
      //s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_post_increment", &json_array_iterator_test::test_post_increment));
      //s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_begin_end", &json_array_iterator_test::test_begin_end));
      //s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_debug", &json_array_iterator_test::test_debug));

      class array_iterator_test : public unit_test
      {
        public:
        static void
        test_debug ()
        {
          array a = L"[\
               { \"op\": \"test\", \"path\": \"/a/b/c\", \"value\": \"foo\" },\
               { \"op\": \"remove\", \"path\": \"/a/b/c\" },\
               { \"op\": \"add\", \"path\": \"/a/b/c\", \"value\": [ \"foo\", \"bar\" ] },\
               { \"op\": \"replace\", \"path\": \"/a/b/c\", \"value\": 42 },\
               { \"op\": \"move\", \"from\": \"/a/b/c\", \"path\": \"/a/b/d\" },\
               { \"op\": \"copy\", \"from\": \"/a/b/d\", \"path\": \"/a/b/e\" }\
               { \"pop\": \"copy\", \"from\": \"/a/b/d\", \"path\": \"/a/b/e\" }\
             ]";

          std::for_each ( a.begin (),
                          a.end (),
                          [] (const value & v)
            {
              try
                {
                  const json::value & op = v[L"op"];
                  const wchar_t *str_op = op.as<const wchar_t *> ();
                  std::wcout << op.type () << ": " << str_op << std::endl;

                } catch (const json_error & e) {
                  std::cerr << e.what () << std::endl;
                }
            });
        }
      };

      TEST_F (array_iterator_test, construct_assign_destruct)
      {
        array::element_list list = { new boolean };

        array::const_iterator *it[] = {
                new array::const_iterator (),
                new array::const_iterator (list.begin ()),
        };

        array::const_iterator copy = array::const_iterator (*it[1]);

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("& copy != it[1]", & copy != it[1]);
        ///
        ASSERT_THAT (& copy, Ne (it[1]));

        delete it[0];
        delete it[1];

        (void) element_list_clear (list);
      }

      TEST_F (array_iterator_test, dereference)
      {
        array a = { new boolean };

        array::const_iterator it = a.begin ();
        array::const_iterator copy = array::const_iterator (it);

        struct assert {
          array::const_iterator *itp;
          value::value_t type;
          int assert_status;
        };

        std::vector<struct assert> test = {
          { & it, value::boolean_t, PASS_T },
          { & copy, value::boolean_t, PASS_T }
        };

        TEST_IT_START

            value & v = **(*it).itp;

            // Original assertion:
            ///ASSERT_EQUAL_IDX ("v.type ()", value::value_t::boolean_t, v.type ());
            ///
            ASSERT_THAT (v.type (), Eq (value::value_t::boolean_t))
                << ERR_IDX_MSG << _idx[0];

        TEST_IT_END;
      }

      TEST_F (array_iterator_test, pre_increment)
      {
        array a = { new boolean, new boolean };

        array::const_iterator begin = a.begin ();
        array::const_iterator end = a.end ();

        size_t count = 0;

        for (auto it = begin; it != end; ++it)
          count++;

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("count", (size_t) 2, count);
        ///
        ASSERT_THAT (count, Eq (2));
      }

      TEST_F (array_iterator_test, post_increment)
      {
        array a = { new boolean };
        array::const_iterator begin = a.begin ();
        array::const_iterator current = begin;

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("current++ == begin", current++ == begin);
        ///
        ASSERT_THAT (current++, Eq (begin));

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("current != begin", current != begin);
        ///
        ASSERT_THAT (current, Ne (begin));
      }

      TEST_F (array_iterator_test, begin_end) {
        mock_array a = L"[0,1]";

        array::const_iterator begin (a.begin ());
        array::const_iterator end (a.end ());

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("array::begin ()", begin == a.begin ());
        ///
        ASSERT_THAT (begin, Eq (a.begin ()));

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("array::end ()", end == a.end ());
        ///
        ASSERT_THAT (end, Eq (a.end ()));
      }

      TEST_F (array_iterator_test, debug)
      {
        // test::array_iterator_test::test_debug ()
      }
    }
  } // Namespace json
} // Namespace format
#endif // JSON_ARRAY_ITERATOR_TEST

