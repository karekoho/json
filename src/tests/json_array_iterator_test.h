#ifndef JSON_ARRAY_ITERATOR_TEST
#define JSON_ARRAY_ITERATOR_TEST

#include "unit_test.h"

// Test number 10
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
      { new std::vector<Value *>({new Number (1), new Number (2), new Number (3)}), 3, PASS },
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
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json array iterator test");

     s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_hasNext", &json_array_iterator_test::test_hasNext));

     s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("", &json_array_iterator_test::test_construct_assign_destruct));
     s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("", &json_array_iterator_test::test_dereference));
     s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("", &json_array_iterator_test::test_pre_increment));
     s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("", &json_array_iterator_test::test_post_increment));

    return s;
  }
};

#endif // JSON_ARRAY_ITERATOR_TEST

