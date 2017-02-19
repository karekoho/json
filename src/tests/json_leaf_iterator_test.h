#ifndef JSON_LEAF_ITERATOR_TEST
#define JSON_LEAF_ITERATOR_TEST

#include "unit_test.h"
namespace Format {
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
    Null n;

    JSON_Iterator *iit = new Leaf_Iterator (&n);

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
    Leaf *l = & b;

    Leaf::Iterator *it[] = {
      new Leaf::Iterator,
      new Leaf::Iterator (l),
    };

    Leaf::Iterator copy = Leaf::Iterator (*it[1]);

    CPPUNIT_ASSERT_MESSAGE ("l.type ()", & copy != it[1]);

    delete it[0];
    delete it[1];
  }

  void
  test_dereference ()
  {
    Boolean b;
    Leaf *l = & b;

    Leaf::Iterator it[] = {
      Leaf::Iterator (),
      Leaf::Iterator (l)
    };

    Leaf::Iterator copy = Leaf::Iterator (it[1]);

    struct assert {
      Leaf::Iterator *itp;
      Value::object_type type;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { & it[0], Value::undefined, FAIL },
      { & it[1], Value::boolean, PASS },
      { & copy, Value::boolean, PASS }
    };

    TEST_IT_START

        Value & v = **(*it).itp;

        ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());

    TEST_IT_END;
  }

  void
  test_pre_increment ()
  {
    Boolean b;
    Leaf *l = & b;

    Leaf::Iterator begin (l);
    Leaf::Iterator end (l + 1);

    size_t count = 0;

    for (auto it = begin; it != end; ++it)
      count++;

    CPPUNIT_ASSERT_EQUAL_MESSAGE ("count", (size_t) 1, count);
  }

  void
  test_post_increment ()
  {
    Boolean b;
    Leaf *l = & b;

    Leaf::Iterator begin (l);
    Leaf::Iterator current = begin;

    CPPUNIT_ASSERT_MESSAGE ("current++ == begin", current++ == begin);
    CPPUNIT_ASSERT_MESSAGE ("current != begin", current != begin);
  }

  void
  test_begin_end ()
  {
    Boolean b;
    Leaf *l = & b;

    Leaf::Iterator begin (l);
    Leaf::Iterator end (l + 1);

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

