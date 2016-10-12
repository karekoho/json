#ifndef JSON_LEAF_ITERATOR_TEST
#define JSON_LEAF_ITERATOR_TEST

#include "unit_test.h"

// Test number 11
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
  }

  void
  test_dereference ()
  {
  }

  void
  test_pre_increment ()
  {
  }

  void
  test_post_increment ()
  {
  }

  static CppUnit::Test *
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json leaf iterator test");

     s->addTest (new CppUnit::TestCaller<json_leaf_iterator_test> ("test_hasNext", &json_leaf_iterator_test::test_hasNext));

     s->addTest (new CppUnit::TestCaller<json_leaf_iterator_test> ("", &json_leaf_iterator_test::test_construct_assign_destruct));
     s->addTest (new CppUnit::TestCaller<json_leaf_iterator_test> ("", &json_leaf_iterator_test::test_dereference));
     s->addTest (new CppUnit::TestCaller<json_leaf_iterator_test> ("", &json_leaf_iterator_test::test_pre_increment));
     s->addTest (new CppUnit::TestCaller<json_leaf_iterator_test> ("", &json_leaf_iterator_test::test_post_increment));

    return s;
  }
};

#endif // JSON_LEAF_ITERATOR_TEST

