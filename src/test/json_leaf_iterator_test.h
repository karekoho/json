#ifndef JSON_LEAF_ITERATOR_TEST
#define JSON_LEAF_ITERATOR_TEST

#include "unit_test.h"

namespace format
{
  namespace json
  {
/**
 * 11.
 * @brief The json_leaf_iterator_test class
 */
class json_leaf_iterator_test : public unit_test
{
public:

  /*void
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
  }*/

  void
  test_construct_assign_destruct ()
  {
    boolean b;
    leaf *l = & b;

    leaf::iterator *it[] = {
      new leaf::iterator,
      new leaf::iterator (l),
    };

    leaf::iterator copy = leaf::iterator (*it[1]);

    CPPUNIT_ASSERT_MESSAGE ("l.type ()", & copy != it[1]);

    delete it[0];
    delete it[1];
  }

  void
  test_dereference ()
  {
    boolean b = true;
    leaf *l = & b;

    leaf::iterator it[] = {
      leaf::iterator (),
      leaf::iterator (l)
    };

    leaf::iterator copy = leaf::iterator (it[1]);

    struct assert {
      leaf::iterator *itp;
      value::value_t type;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { & it[0], value::undefined_t, FAIL },
      { & it[1], value::boolean_t, PASS },
      { & copy, value::boolean_t, PASS }
    };

    TEST_IT_START

        const value & v = **(*it).itp;  // reference
        auto const vp = *(*it).itp; // pointer

        ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());
        ASSERT_EQUAL_IDX ("v.type ()", (*it).type, vp->type ());
        ASSERT_EQUAL_IDX("v.type ()", true, static_cast<const boolean &> (v).get ());

    TEST_IT_END
  }

  void
  test_pre_increment ()
  {
    boolean b;
    leaf *l = & b;

    leaf::iterator begin (l);
    leaf::iterator end (l + 1);

    size_t count = 0;

    for (auto it = begin; it != end; ++it)
      count++;

    CPPUNIT_ASSERT_EQUAL_MESSAGE ("count", (size_t) 1, count);
  }

  void
  test_post_increment ()
  {
    boolean b;
    leaf *l = & b;

    leaf::iterator begin (l);
    leaf::iterator current = begin;

    CPPUNIT_ASSERT_MESSAGE ("current++ == begin", current++ == begin);
    CPPUNIT_ASSERT_MESSAGE ("current != begin", current != begin);
  }

  void
  test_begin_end ()
  {
    boolean b;
    leaf *l = & b;

    leaf::iterator begin (l);
    leaf::iterator end (l + 1);

    CPPUNIT_ASSERT_MESSAGE ("Object::begin ()", begin == b.begin ());
    CPPUNIT_ASSERT_MESSAGE ("Object::end ()", end == b.end ());
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

     //s->addTest (new CppUnit::TestCaller<json_leaf_iterator_test> ("test_hasNext", &json_leaf_iterator_test::test_hasNext));
     s->addTest (new CppUnit::TestCaller<json_leaf_iterator_test> ("test_construct_assign_destruct", &json_leaf_iterator_test::test_construct_assign_destruct));
     s->addTest (new CppUnit::TestCaller<json_leaf_iterator_test> ("test_dereference", &json_leaf_iterator_test::test_dereference));
     s->addTest (new CppUnit::TestCaller<json_leaf_iterator_test> ("test_pre_increment", &json_leaf_iterator_test::test_pre_increment));
     s->addTest (new CppUnit::TestCaller<json_leaf_iterator_test> ("test_post_increment", &json_leaf_iterator_test::test_post_increment));
     s->addTest (new CppUnit::TestCaller<json_leaf_iterator_test> ("test_begin_end", &json_leaf_iterator_test::test_begin_end));

    return s;
  }
};
}
}
#endif // JSON_LEAF_ITERATOR_TEST

