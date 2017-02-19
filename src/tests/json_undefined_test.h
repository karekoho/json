#ifndef JSON_UNDEFINED_TEST
#define JSON_UNDEFINED_TEST

#include "json_leaf_test.h"

namespace format {

/**
 * 8.
 * @brief The json_undefined_test class
 */
class json_undefined_test : public json_leaf_test
{
public:

  virtual void test_ctor_dtor ()
  {
    json *p[] = { 0, new json };

    for (size_t pidx = 0; pidx < 2; pidx++)
      {
        format::undefined *u[] = {
          new format::undefined,
          new format::undefined (p[pidx]),
        };

        delete u[0];
        delete u[1];
      }

    delete p[1];

    format::undefined src;
    format::undefined copy = src;

    CPPUNIT_ASSERT_MESSAGE ("undefined", & copy != & src);
  }


  virtual void
  test_assign_all_values ()
  {
    object obj_parent;
    array arr_parent;

    json *parents[] = {
      & obj_parent,
      & arr_parent,
      0
    };

    struct assert {
      value *new_value;
      value::value_t type;
      const wchar_t *key;
      size_t index;
      size_t count;
      int assert_status[3];
    };

    std::vector<struct assert > test = {
      { new array (L"[true,false]"), value::array_t, L"key_1",  0, 1,  { PASS, PASS, FAIL } },
      { new object (L"{\"k1\":true,\"k2\":false}"), value::object_t, L"key_2",  0, 2, { PASS, PASS, FAIL } },
      { new string (L"\"xxx\""), value::string_t, L"key_3",  0, 3,  { PASS, PASS, FAIL } },
      { new number (10), value::number_t, L"key_4",  0, 4, { PASS, PASS, FAIL } },
      { new boolean (true), value::boolean_t, L"key_6",  0, 5, { PASS, PASS, FAIL } },
      { new null, value::null_t, L"key_7",  0, 6, { PASS, PASS, FAIL } }
    };

    for (size_t pidx = 0; pidx < 3; pidx++)
      {
          obj_parent._member_list.clear ();
          arr_parent._element_list.clear ();

          for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++) {\
            try {\
                if ((*it).assert_status[pidx] == SKIP) { continue; }\
                if ((*it).assert_status[pidx] > PASS) { this->_errorc[EXPECTED]++; }

          /// old_value: value from Value[key], any value

          format::undefined *old_value = new format::undefined;
          old_value->_parent = parents[pidx];

          arr_parent._element_list.push_back (new format::undefined);
          old_value->setKey ((*it).key, wcslen ((*it).key));

          (*it).index  = arr_parent._element_list.size () - 1;
          old_value->setIndex ((*it).index);

          // old_value->_assign (*(*it).new_value);   // Can't do. old_value will be free'd by new_value
          *old_value = *(*it).new_value;

          json *parent = old_value->_parent;

          if (parent)
            {
              ASSERT_EQUAL_IDX ("old_value.parent.count ()", (*it).count, parent->count ());
              // ASSERT_EQUAL_IDX ("(*it).new_value->_old->type ()", Value::object_type::undefined, (*it).new_value->_old->type ());

              if (parent->type () == value::object_t)
                {
                  value *ov =  obj_parent._member_list.at ((*it).key);

                  ASSERT_EQUAL_IDX ("obj_parent[key].type", ov->type (), (*it).type);
                  // ASSERT_EQUAL_IDX ("obj_parent[key].value", ov, new_value);
                }
              else
                {
                  value *av =  arr_parent._element_list.at ((*it).index);

                  ASSERT_EQUAL_IDX ("arr_parent[key].type", av->type (), (*it).type);
                  // ASSERT_EQUAL_IDX ("arr_parent[key].value", av, new_value);
                }
            }

          TEST_IT_END;
        }

        for (auto it = test.begin (); it != test.end (); ++it)
          delete (*it).new_value;
  }

  virtual void test_parse_1 () {}
  //virtual void test_stringify () override {}
  virtual void test_strLength () override {}
  virtual void test_strValue () override  {}
  virtual void test__clear() {}
  virtual void test_operator_assign () {}
  virtual void test_operator_at () {}
  virtual void test_erase () override {}

  void
  test_shared_undefined ()
  {
    shared_undefined & u = shared_undefined::instance ();
    shared_undefined *pu = & u;

    delete pu;

    CPPUNIT_ASSERT_MESSAGE ("instance () > 0", (& shared_undefined::instance ()) > 0 );
    CPPUNIT_ASSERT_EQUAL_MESSAGE ("instance () == instance ()",  & shared_undefined::instance (), & shared_undefined::instance ());
  }

  /**
   * 8.
   * @brief suite
   * @return
   */
  static CppUnit::Test *
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json undefined test");

    /* 0. */  s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_ctor_dtor", &json_undefined_test::test_ctor_dtor));
    /* 1. */  s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_assign_all_values", &json_undefined_test::test_assign_all_values));
    /* 2. */  s->addTest (new CppUnit::TestCaller<json_undefined_test> ("test_shared_undefined", &json_undefined_test::test_shared_undefined));

    return s;
  }
};
  }

#endif // JSON_UNDEFINED_TEST

