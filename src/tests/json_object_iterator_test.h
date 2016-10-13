#ifndef JSON_OBJECT_ITERATOR_TEST
#define JSON_OBJECT_ITERATOR_TEST

#include "unit_test.h"

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
    Object::member_list list;

    struct assert {
      Object::member_list *list;
      size_t listc;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { new Object::member_list ({ { "1", new Number(1) }, { "2", new Number (2) }, { "3", new Number (3) } }), 3, PASS },
      { new Object::member_list (), 0, PASS }
    };

    TEST_IT_START

        list = *(*it).list;

        JSON_Iterator *oit = new Object_Iterator (list);
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
    Object::member_list list = { { "1", new Boolean } };

    Object::Iterator *it[] = {
      new Object::Iterator,
      new Object::Iterator (list.begin ()),
    };

    Object::Iterator copy = Object::Iterator (*it[1]);

    CPPUNIT_ASSERT_MESSAGE ("v.type ()", & copy != it[1]);

    delete it[0];
    delete it[1];

    (void) member_list_clear (list);
  }

  void
  test_dereference ()
  {
    Object::member_list list = { { "1", new Boolean } };

    Object::Iterator it (list.begin ());
    Object::Iterator copy = Object::Iterator (it);

    struct assert {
      Object::Iterator *itp;
      Value::object_type type;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { & it, Value::boolean, PASS },
      { & copy, Value::boolean, PASS }
    };

    TEST_IT_START

        Value & v = **(*it).itp;

        ASSERT_EQUAL_IDX ("v.type ()", Value::object_type::boolean, v.type ());

    TEST_IT_END;

    (void) member_list_clear (list);
  }

  void
  test_pre_increment ()
  {
    Object::member_list list = { { "1", new Boolean }, { "2", new Boolean } };

    Object::Iterator begin (list.begin ());
    Object::Iterator end (list.end ());

    size_t count = 0;

    for (auto it = begin; it != end; ++it)
      count++;

    CPPUNIT_ASSERT_EQUAL_MESSAGE ("count", (size_t) 2, count);

    (void) member_list_clear (list);
  }

  void
  test_post_increment ()
  {
    Object::member_list list = { { "1", new Boolean } };

    Object::Iterator begin (list.begin ());
    Object::Iterator current = begin;

    CPPUNIT_ASSERT_MESSAGE ("current++ == begin", current++ == begin);
    CPPUNIT_ASSERT_MESSAGE ("current != begin", current != begin);

    (void) member_list_clear (list);
  }

  void
  test_begin_end ()
  {
    Object o = "{\"1\":true,\"2\":false}";

    Object::Iterator begin (o._member_list.begin ());
    Object::Iterator end (o._member_list.end ());

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
#endif // JSON_OBJECT_ITERATOR_TEST

