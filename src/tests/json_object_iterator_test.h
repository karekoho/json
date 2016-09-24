#ifndef JSON_OBJECT_ITERATOR_TEST
#define JSON_OBJECT_ITERATOR_TEST

#include "unit_test.h"

// Test number 9
class json_object_iterator_test : public unit_test
{
public:

  void
  test_1 ()
  {
    std::unordered_map<std::string, Value *> x;

    struct assert {
      std::unordered_map<std::string, Value *> *map;
      int assert_status;
    };

    std::vector<struct assert> test = {
    { new std::unordered_map<std::string, Value *>({{"key_1", new Null },{"key_2", new Boolean (true)},{"key_3", new Number (100)}}), PASS },
      { new std::unordered_map<std::string, Value *>(), PASS }
    };

    TEST_IT_START

        x = *(*it).map;

        std::cout << x.size () << std::endl;

        delete (*it).map;

    TEST_IT_END;
  }

  static CppUnit::Test *
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json object iterator test");

     s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_1", &json_object_iterator_test::test_1));

    return s;
  }
};
#endif // JSON_OBJECT_ITERATOR_TEST

