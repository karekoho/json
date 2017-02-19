#ifndef JSON_LEAF_ITERATOR_TEST
#define JSON_LEAF_ITERATOR_TEST

#include "unit_test.h"

namespace format
{
/**
 * 11.
 * @brief The json_leaf_iterator_test class
 */
class json_leaf_iterator_test : public unit_test
{
public:

  void
  test_hasNext ()
  {
    size_t c = 0;
    null n;

    json_iterator *iit = new leaf_iterator (&n);

    while (iit->hasNext ())
      {
        (void) iit->next ();
        c++;
      }

    CPPUNIT_ASSERT_EQUAL_MESSAGE ("count", (size_t) 1, c);

    delete iit;
  }

  void
  test_construct_assign_destruct ()
  {
    Boolean b;
    leaf *l = & b;

    leaf::Iterator *it[] = {
      new leaf::Iterator,
      new leaf::Iterator (l),
    };

    leaf::Iterator copy = leaf::Iterator (*it[1]);

    CPPUNIT_ASSERT_MESSAGE ("l.type ()", & copy != it[1]);

    delete it[0];
    delete it[1];
  }

  void
  test_dereference ()
  {
    Boolean b;
    leaf *l = & b;

    leaf::Iterator it[] = {
      leaf::Iterator (),
      leaf::Iterator (l)
    };

    leaf::Iterator copy = leaf::Iterator (it[1]);

    struct assert {
      leaf::Iterator *itp;
      value::value_t type;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { & it[0], value::undefined_t, FAIL },
      { & it[1], value::boolean_t, PASS },
      { & copy, value::boolean_t, PASS }
    };

    TEST_IT_START

        value & v = **(*it).itp;

        ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());

    TEST_IT_END;
  }

  void
  test_pre_increment ()
  {
    Boolean b;
    leaf *l = & b;

    leaf::Iterator begin (l);
    leaf::Iterator end (l + 1);

    size_t count = 0;

    for (auto it = begin; it != end; ++it)
      count++;

    CPPUNIT_ASSERT_EQUAL_MESSAGE ("count", (size_t) 1, count);
  }

  void
  test_post_increment ()
  {
    Boolean b;
    leaf *l = & b;

    leaf::Iterator begin (l);
    leaf::Iterator current = begin;

    CPPUNIT_ASSERT_MESSAGE ("current++ == begin", current++ == begin);
    CPPUNIT_ASSERT_MESSAGE ("current != begin", current != begin);
  }

  void
  test_begin_end ()
  {
    Boolean b;
    leaf *l = & b;

    leaf::Iterator begin (l);
    leaf::Iterator end (l + 1);

    CPPUNIT_ASSERT_MESSAGE ("Object::begin ()", begin == b.begin ());
    CPPUNIT_ASSERT_MESSAGE ("Object::end ()", end == b.end ());

    // CPPUNIT_ASSERT_EQUAL_MESSAGE ("(*b.begin ()).type ()", Value::boolean, (*b.begin ()).type ());
  }

  /**
   * 11.
   * @brief suite
   * @return
   */
  static CppUnit::Test *
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json leaf iterator test");

     s->addTest (new CppUnit::TestCaller<json_leaf_iterator_test> ("test_hasNext", &json_leaf_iterator_test::test_hasNext));

     s->addTest (new CppUnit::TestCaller<json_leaf_iterator_test> ("test_construct_assign_destruct", &json_leaf_iterator_test::test_construct_assign_destruct));
     s->addTest (new CppUnit::TestCaller<json_leaf_iterator_test> ("test_dereference", &json_leaf_iterator_test::test_dereference));
     s->addTest (new CppUnit::TestCaller<json_leaf_iterator_test> ("test_pre_increment", &json_leaf_iterator_test::test_pre_increment));
     s->addTest (new CppUnit::TestCaller<json_leaf_iterator_test> ("test_post_increment", &json_leaf_iterator_test::test_post_increment));
     s->addTest (new CppUnit::TestCaller<json_leaf_iterator_test> ("test_begin_end", &json_leaf_iterator_test::test_begin_end));

    return s;
  }
};
}
#endif // JSON_LEAF_ITERATOR_TEST

