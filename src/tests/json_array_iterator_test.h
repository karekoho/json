#ifndef JSON_ARRAY_ITERATOR_TEST
#define JSON_ARRAY_ITERATOR_TEST

#include "unit_test.h"

class json_array_iterator_test : public unit_test
{
public:

  void
  test_1 ()
  {
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

