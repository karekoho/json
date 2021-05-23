#ifndef JSON_ARRAY_ITERATOR_TEST
#define JSON_ARRAY_ITERATOR_TEST

#include "unit_test.h"

namespace format
{
  namespace json
  {
  /**
   * 10.
   *
   * @brief The json_array_iterator_test class
   */
  class json_array_iterator_test : public unit_test
  {
  public:

    /*void
    test_hasNext ()
    {
      std::vector<value *> vector;

      struct assert {
        std::vector<value *> *vector;
        size_t vecc;
        int assert_status;
      };

      std::vector<struct assert> test = {
        { new std::vector<value *>({new number (1), new number (2), new number (3)}), 3, PASS },
        { new std::vector<value *>(), 0, PASS }
      };

      TEST_IT_START

          vector = *(*it).vector;

          json_iterator *vit = new array_iterator (vector);

          size_t vecc = 0;

          while (vit->hasNext ())
            {
              (void) vit->next ();
              vecc++;
            }

          ASSERT_EQUAL_IDX ("vecc", (*it).vecc, vecc);

          (void) element_list_clear (vector);

          delete (*it).vector;
          delete vit;

      TEST_IT_END;
    }*/

    void
    test_construct_assign_destruct ()
    {
      array::element_list list = { new boolean };

      array::const_iterator *it[] = {
        new array::const_iterator (),
        new array::const_iterator (list.begin ()),
      };

      array::const_iterator copy = array::const_iterator (*it[1]);

      CPPUNIT_ASSERT_MESSAGE ("& copy != it[1]", & copy != it[1]);

      delete it[0];
      delete it[1];

      (void) element_list_clear (list);
    }

    void
    test_dereference ()
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
        { & it, value::boolean_t, PASS },
        { & copy, value::boolean_t, PASS }
      };

      TEST_IT_START

          value & v = **(*it).itp;

          ASSERT_EQUAL_IDX ("v.type ()", value::value_t::boolean_t, v.type ());

      TEST_IT_END;
    }

    void
    test_pre_increment ()
    {
      array a = { new boolean, new boolean };

      array::const_iterator begin = a.begin ();
      array::const_iterator end = a.end ();

      size_t count = 0;

      for (auto it = begin; it != end; ++it)
        count++;

      CPPUNIT_ASSERT_EQUAL_MESSAGE ("count", (size_t) 2, count);
    }

    void
    test_post_increment ()
    {
      array a = { new boolean };
      array::const_iterator begin = a.begin ();
      array::const_iterator current = begin;

      CPPUNIT_ASSERT_MESSAGE ("current++ == begin", current++ == begin);
      CPPUNIT_ASSERT_MESSAGE ("current != begin", current != begin);
    }

    void
    test_begin_end ()
    {
      array_accessor a = L"[0,1]";

      array::const_iterator begin (a.begin ());
      array::const_iterator end (a.end ());

      CPPUNIT_ASSERT_MESSAGE ("array::begin ()", begin == a.begin ());
      CPPUNIT_ASSERT_MESSAGE ("array::end ()", end == a.end ());
    }

    void
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

    /**
     * 10.
     *
     * @brief suite
     * @return
     */
    static CppUnit::Test *
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json array iterator test");

      //s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_hasNext", &json_array_iterator_test::test_hasNext));

      /* 0. */  s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_construct_assign_destruct", &json_array_iterator_test::test_construct_assign_destruct));
      /* 1. */  s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_dereference", &json_array_iterator_test::test_dereference));
      /* 2. */  s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_pre_increment", &json_array_iterator_test::test_pre_increment));
      /* 3. */  s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_post_increment", &json_array_iterator_test::test_post_increment));
      /* 4. */  s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_begin_end", &json_array_iterator_test::test_begin_end));

      /* 5. */  //s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_debug", &json_array_iterator_test::test_debug));

      return s;
    }
  };
} // Namespace json
} // Namespace format
#endif // JSON_ARRAY_ITERATOR_TEST

