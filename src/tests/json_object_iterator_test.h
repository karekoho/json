#ifndef JSON_OBJECT_ITERATOR_TEST
#define JSON_OBJECT_ITERATOR_TEST

#include "unit_test.h"

// Test number 9
class json_object_iterator_test : public unit_test
{
public:

  void
  test_hasNext ()
  {
    std::unordered_map<std::string, Value *> map;

    struct assert {
      std::unordered_map<std::string, Value *> *map;
      size_t mapc;
      int assert_status;
    };

    std::vector<struct assert> test = {
      { new std::unordered_map<std::string, Value *>({{"key_1", new Number(1) },{"key_2", new Number (2)},{"key_3", new Number (3)}}), 3, PASS },
      { new std::unordered_map<std::string, Value *>(), 0, PASS }
    };

    TEST_IT_START

        map = *(*it).map;

        JSON_Iterator *oit = new Object_Iterator (map);
        size_t mapc = 0;

        while (oit->hasNext ())
          {
            (void) oit->next ();
            mapc++;
          }

        ASSERT_EQUAL_IDX ("mapc", (*it).mapc, mapc);

        (void) member_list_clear (map);

        delete (*it).map;
        delete oit;

    TEST_IT_END;
  }

  void
  test_construct_assign_destruct ()
  {
  }

  void
  test_dereference ()
  {
    Object::member_list list = { { "key_1", new Number } };
    Object::Iterator it (list.begin ());

    Value & v = *it;

    CPPUNIT_ASSERT_EQUAL_MESSAGE ("v.type ()", Value::object_type::number, v.type ());
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
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json object iterator test");

     s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("test_hasNext", &json_object_iterator_test::test_hasNext));

     s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("", &json_object_iterator_test::test_construct_assign_destruct));
     s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("", &json_object_iterator_test::test_dereference));
     s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("", &json_object_iterator_test::test_pre_increment));
     s->addTest (new CppUnit::TestCaller<json_object_iterator_test> ("", &json_object_iterator_test::test_post_increment));

    return s;
  }
};
#endif // JSON_OBJECT_ITERATOR_TEST

