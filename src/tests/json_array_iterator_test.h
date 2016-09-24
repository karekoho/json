#ifndef JSON_ARRAY_ITERATOR_TEST
#define JSON_ARRAY_ITERATOR_TEST

#include "unit_test.h"

// Test number 10
class json_array_iterator_test : public unit_test
{
public:

  void
  test_1 ()
  {
    std::vector<Value *> x;

    struct assert {
      std::vector<Value *> *vector;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { new std::vector<Value *>({new Null, new Boolean (true), new Number (100)}), PASS },
      { new std::vector<Value *>(), PASS }
    };

    TEST_IT_START

        x = *(*it).vector;

        std::cout << x.size () << std::endl;

        delete (*it).vector;

    TEST_IT_END;
  }

  static CppUnit::Test *
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json array iterator test");

     s->addTest (new CppUnit::TestCaller<json_array_iterator_test> ("test_1", &json_array_iterator_test::test_1));

    return s;
  }
};

#endif // JSON_ARRAY_ITERATOR_TEST

