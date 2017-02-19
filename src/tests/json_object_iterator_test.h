#ifndef JSON_OBJECT_ITERATOR_TEST
#define JSON_OBJECT_ITERATOR_TEST

#include "unit_test.h"
namespace format {
/**
 * 9.
 * @brief The json_object_iterator_test class
 */
class json_object_iterator_test : public unit_test
{
public:

  void
  test_hasNext ()
  {
    object::member_list list;

    struct assert {
      object::member_list *list;
      size_t listc;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { new object::member_list ({ { L"1", new number(1) }, { L"2", new number (2) }, { L"3", new number (3) } }), 3, PASS },
      { new object::member_list (), 0, PASS }
    };

    TEST_IT_START

        list = *(*it).list;

        json_iterator *oit = new object_iterator (list);
        size_t listc = 0;

        while (oit->hasNext ())
          {
            (void) oit->next ();
            listc++;
          }

        ASSERT_EQUAL_IDX ("mapc", (*it).listc, listc);

        (void) member_list_clear (list);

        delete (*it).list;
        delete oit;

    TEST_IT_END;
  }

  void
  test_construct_assign_destruct ()
  {
    object::member_list list = { { L"1", new boolean } };

    object::Iterator *it[] = {
      new object::Iterator,
      new object::Iterator (list.begin ()),
    };

    object::Iterator copy = object::Iterator (*it[1]);

    CPPUNIT_ASSERT_MESSAGE ("v.type ()", & copy != it[1]);

    delete it[0];
    delete it[1];

    (void) member_list_clear (list);
  }

  void
  test_dereference ()
  {
    object::member_list list = { { L"1", new boolean } };

    object::Iterator it (list.begin ());
    object::Iterator copy = object::Iterator (it);

    struct assert {
      object::Iterator *itp;
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

    (void) member_list_clear (list);
  }

  void
  test_pre_increment ()
  {
    object::member_list list = { { L"1", new boolean }, { L"2", new boolean } };

    object::Iterator begin (list.begin ());
    object::Iterator end (list.end ());

    size_t count = 0;

    for (auto it = begin; it != end; ++it)
      count++;

    CPPUNIT_ASSERT_EQUAL_MESSAGE ("count", (size_t) 2, count);

    (void) member_list_clear (list);
  }

  void
  test_post_increment ()
  {
    object::member_list list = { { L"1", new boolean } };

    object::Iterator begin (list.begin ());
    object::Iterator current = begin;

    CPPUNIT_ASSERT_MESSAGE ("current++ == begin", current++ == begin);
    CPPUNIT_ASSERT_MESSAGE ("current != begin", current != begin);

    (void) member_list_clear (list);
  }

  void
  test_begin_end ()
  {
    object o = L"{\"1\":true,\"2\":false}";

    object::Iterator begin (o._member_list.begin ());
    object::Iterator end (o._member_list.end ());

    CPPUNIT_ASSERT_MESSAGE ("Object::begin ()", begin == o.begin ());
    CPPUNIT_ASSERT_MESSAGE ("Object::end ()", end == o.end ());
  }

  /**
   * 9.
   * @brief suite
   * @return
   */
  static CppUnit::Test *
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json object iterator test");

     s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_hasNext", &json_object_iterator_test::test_hasNext));

     s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_construct_assign_destruct", &json_object_iterator_test::test_construct_assign_destruct));
     s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_dereference", &json_object_iterator_test::test_dereference));
     s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_pre_increment", &json_object_iterator_test::test_pre_increment));
     s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_post_increment", &json_object_iterator_test::test_post_increment));
     s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_begin_end", &json_object_iterator_test::test_begin_end));

    return s;
  }
};
}
#endif // JSON_OBJECT_ITERATOR_TEST

