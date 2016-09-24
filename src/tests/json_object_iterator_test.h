#ifndef JSON_OBJECT_ITERATOR_TEST
#define JSON_OBJECT_ITERATOR_TEST

#include "unit_test.h"

class json_object_iterator_test : public unit_test
{
public:

  void
  test_1 ()
  {
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

