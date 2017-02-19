#ifndef JSON_ARRAY_ITERATOR_TEST
#define JSON_ARRAY_ITERATOR_TEST

#include "unit_test.h"
namespace Format {
/**
 * 10.
 *
 * @brief The json_array_iterator_test class
 */
class json_array_iterator_test : public unit_test
{
public:

  void
  test_hasNext ()
  {
    std::vector<Value *> vector;

    struct assert {
      std::vector<Value *> *vector;
      size_t vecc;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { new std::vector<Value *>({new number (1), new number (2), new number (3)}), 3, PASS },
      { new std::vector<Value *>(), 0, PASS }
    };

    TEST_IT_START

        vector = *(*it).vector;

        JSON_Iterator *vit = new Array_Iterator (vector);

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
  }

  void
  test_construct_assign_destruct ()
  {
    Array::element_list list = { new Boolean };

    Array::Iterator *it[] = {
      new Array::Iterator,
      new Array::Iterator (list.begin ()),
    };

    Array::Iterator copy = Array::Iterator (*it[1]);

    CPPUNIT_ASSERT_MESSAGE ("& copy != it[1]", & copy != it[1]);

    delete it[0];
    delete it[1];

    (void) element_list_clear (list);
  }

  void
  test_dereference ()
  {
    Array::element_list list = { new Boolean };

    Array::Iterator it (list.begin ());
    Array::Iterator copy = Array::Iterator (it);

    struct assert {
      Array::Iterator *itp;
      Value::object_type type;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { & it, Value::boolean_t, PASS },
      { & copy, Value::boolean_t, PASS }
    };

    TEST_IT_START

        Value & v = **(*it).itp;

        ASSERT_EQUAL_IDX ("v.type ()", Value::object_type::boolean_t, v.type ());

    TEST_IT_END;

    (void) element_list_clear (list);
  }

  void
  test_pre_increment ()
  {
    Array::element_list list = { new Boolean, new Boolean };

    Array::Iterator begin (list.begin ());
    Array::Iterator end (list.end ());

    size_t count = 0;

    for (auto it = begin; it != end; ++it)
      count++;

    CPPUNIT_ASSERT_EQUAL_MESSAGE ("count", (size_t) 2, count);

    (void) element_list_clear (list);
  }

  void
  test_post_increment ()
  {
    Array::element_list list = { new Boolean };

    Array::Iterator begin (list.begin ());
    Array::Iterator current = begin;

    CPPUNIT_ASSERT_MESSAGE ("current++ == begin", current++ == begin);
    CPPUNIT_ASSERT_MESSAGE ("current != begin", current != begin);

    (void) element_list_clear (list);
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

     s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_hasNext", &json_array_iterator_test::test_hasNext));

     s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_construct_assign_destruct", &json_array_iterator_test::test_construct_assign_destruct));
     s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_dereference", &json_array_iterator_test::test_dereference));
     s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_pre_increment", &json_array_iterator_test::test_pre_increment));
     s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_post_increment", &json_array_iterator_test::test_post_increment));

    return s;
  }
};
}
#endif // JSON_ARRAY_ITERATOR_TEST

