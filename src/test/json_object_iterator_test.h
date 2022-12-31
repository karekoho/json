#ifndef JSON_OBJECT_ITERATOR_TEST
#define JSON_OBJECT_ITERATOR_TEST

#include "unit_test.h"
namespace format
{
  namespace json
  {
    namespace test
    {
      //s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_construct_assign_destruct", &json_object_iterator_test::test_construct_assign_destruct));
      //s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_dereference", &json_object_iterator_test::test_dereference));
      //s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_pre_increment", &json_object_iterator_test::test_pre_increment));
      //s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_post_increment", &json_object_iterator_test::test_post_increment));
      //s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_begin_end", &json_object_iterator_test::test_begin_end));

      class object_iterator_test : public unit_test {};

      TEST_F (object_iterator_test, construct_assign_destruct)
      {
        object::member_list list = { { L"1", new boolean } };

        object::const_iterator *it[] = {
          new object::const_iterator (),
          new object::const_iterator (list.begin ()),
        };

        object::const_iterator copy = object::const_iterator (*it[1]);

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("v.type ()", & copy != it[1]);
        ///
        ASSERT_THAT (& copy, Ne (it[1]));

        delete it[0];
        delete it[1];

        (void) member_list_clear (list);
      }

      TEST_F (object_iterator_test, dereference)
      {
        object o = { { L"1", new boolean } };

        object::const_iterator it = o.begin ();
        object::const_iterator copy = object::const_iterator (it);

        struct assert {
          object::const_iterator *itp;
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

      TEST_F (object_iterator_test, pre_increment)
      {
        object o = { { L"1", new boolean }, { L"2", new boolean } };

        object::const_iterator begin = o.begin ();
        object::const_iterator end = o.end ();

        size_t count = 0;

        for (auto it = begin; it != end; ++it)
          count++;

        // Original assertion:
        ///CPPUNIT_ASSERT_EQUAL_MESSAGE ("count", (size_t) 2, count);
        ///
        ASSERT_THAT (count, Eq (2));
      }

      TEST_F (object_iterator_test, post_increment)
      {
        object o = { { L"1", new boolean } };

        object::const_iterator begin = o.begin ();
        object::const_iterator current = begin;

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("current++ == begin", current++ == begin);
        ///
        ASSERT_THAT (current++, Eq (begin));

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("current != begin", current != begin);
        ///
        ASSERT_THAT (current, Ne (begin));
      }

      TEST_F (object_iterator_test, begin_end)
      {
        object o = L"{\"1\":true,\"2\":false}";

        object::const_iterator begin (o.begin ());
        object::const_iterator end (o.end ());

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("Object::begin ()", begin == o.begin ());
        ///
        ASSERT_THAT (begin, Eq (o.begin ()));

        // Original assertion:
        ///CPPUNIT_ASSERT_MESSAGE ("Object::end ()", end == o.end ());
        ///
        ASSERT_THAT (end, Eq (o.end ()));
      }
    }
    /**
     * 9.
     * @brief The json_object_iterator_test class
     */
    class json_object_iterator_test : public unit_test
    {
    public:
      void
      test_construct_assign_destruct ()
      {
//        object::member_list list = { { L"1", new boolean } };

//        object::const_iterator *it[] = {
//          new object::const_iterator (),
//          new object::const_iterator (list.begin ()),
//        };

//        object::const_iterator copy = object::const_iterator (*it[1]);

//        CPPUNIT_ASSERT_MESSAGE ("v.type ()", & copy != it[1]);

//        delete it[0];
//        delete it[1];

//        (void) member_list_clear (list);
      }

      void
      test_dereference ()
      {
//        object o = { { L"1", new boolean } };

//        object::const_iterator it = o.begin ();
//        object::const_iterator copy = object::const_iterator (it);

//        struct assert {
//          object::const_iterator *itp;
//          value::value_t type;
//          int assert_status;
//        };

//        std::vector<struct assert> test = {
//          { & it, value::boolean_t, PASS_T },
//          { & copy, value::boolean_t, PASS_T }
//        };

//        TEST_IT_START

//            value & v = **(*it).itp;

//            ASSERT_EQUAL_IDX ("v.type ()", value::value_t::boolean_t, v.type ());

//        TEST_IT_END;
      }

      void
      test_pre_increment ()
      {
//        object o = { { L"1", new boolean }, { L"2", new boolean } };

//        object::const_iterator begin = o.begin ();
//        object::const_iterator end = o.end ();

//        size_t count = 0;

//        for (auto it = begin; it != end; ++it)
//          count++;

//        CPPUNIT_ASSERT_EQUAL_MESSAGE ("count", (size_t) 2, count);
      }

      void
      test_post_increment ()
      {
//        object o = { { L"1", new boolean } };

//        object::const_iterator begin = o.begin ();
//        object::const_iterator current = begin;

//        CPPUNIT_ASSERT_MESSAGE ("current++ == begin", current++ == begin);
//        CPPUNIT_ASSERT_MESSAGE ("current != begin", current != begin);
      }

      void
      test_begin_end ()
      {
//        object o = L"{\"1\":true,\"2\":false}";

//        object::const_iterator begin (o.begin ());
//        object::const_iterator end (o.end ());

//        CPPUNIT_ASSERT_MESSAGE ("Object::begin ()", begin == o.begin ());
//        CPPUNIT_ASSERT_MESSAGE ("Object::end ()", end == o.end ());
      }

      /**
       * 9.
       * @brief suite
       * @return
       *
      static CppUnit::Test *
      suite ()
      {
        CppUnit::TestSuite *s = new CppUnit::TestSuite ("json object iterator test");
         s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_construct_assign_destruct", &json_object_iterator_test::test_construct_assign_destruct));
         s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_dereference", &json_object_iterator_test::test_dereference));
         s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_pre_increment", &json_object_iterator_test::test_pre_increment));
         s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_post_increment", &json_object_iterator_test::test_post_increment));
         s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_begin_end", &json_object_iterator_test::test_begin_end));
        return s;
      }*/
    };
  } // Namespace json
} // Namespace format
#endif // JSON_OBJECT_ITERATOR_TEST

