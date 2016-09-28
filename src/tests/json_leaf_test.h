#ifndef JSON_LEAF_TEST
#define JSON_LEAF_TEST

#include "json_value_test_interface.h"

// Test number 12
class json_leaf_test : public json_value_test_interface
{

public:

  virtual void
  test_stringify () override
  {
    Object op;

    JSON *parent[2] = {
      0, & op,
    };

    JSON *p = 0;

    struct assert
    {
      Leaf *value;
      size_t output_len[2];
      const char *output[2];
      int assert_status;
    };

    std::vector<struct assert > test = {
      { new String ("\"x\""), { 3, 4 }, { "\"x\"", "x\"x\"" }, PASS },
      // { new Number (100), { 3, 4 }, { "\"x\"", "x\"x\"" }, PASS },
      { new Boolean (), { 5, 6 }, { "false", "xfalse" }, PASS },
      { new Null (), { 4, 5 }, { "null", "xnull" }, PASS },
    };

    for (size_t pidx = 0; pidx < 2; pidx++)
      {
          p = parent[pidx];

          TEST_IT_START

              if (p == 0)   // No parent
                {
                  const char *output = (*it).value->stringify ();

                  ASSERT_EQUAL_IDX ("output length", (*it).output_len[0], strlen (output));
                  CPPUNIT_ASSERT_MESSAGE ("output", strcmp ((*it).output[0], output) == 0);
                }
              else
                {
                  p->_str_value[0] = new char[6 + 1]();

                  p->_str_value[1] = p->_str_value[0];

                  *(p->_str_value[0]++) =  'x';

                  (*it).value->_parent = p;

                  (void) (*it).value->stringify ();

                  ASSERT_EQUAL_IDX ("output length", (*it).output_len[1], strlen (p->_str_value[1]));
                  CPPUNIT_ASSERT_MESSAGE ("output", strcmp ((*it).output[1], p->_str_value[1]) == 0);

                  delete[]  p->_str_value[1];
                }

          TEST_IT_END;
      }
  }

  virtual void test_value_1() override {}
  virtual void test_debug_1() override {}
  virtual void test_ctor_dtor() override {}
  virtual void test_parse_1() override {}
  virtual void test_size_1() override {}
  virtual void test_at() override {}
  virtual void test_assign_all_values() override {}
  virtual void test_operator_assign() override {}
  virtual void test__clear() override {}
  virtual void test_operator_at() override {}

  static CppUnit::Test *
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json leaf test");

    s->addTest (new CppUnit::TestCaller<json_leaf_test> ("test_assign_all_values", &json_leaf_test::test_stringify));

    return s;
  }
};

#endif // JSON_LEAF_TEST

