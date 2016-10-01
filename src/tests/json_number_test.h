#ifndef JSON_NUMBER_TEST
#define JSON_NUMBER_TEST

#include "json_value_test_interface.h"

/// Test number 5
class json_number_test : public json_value_test_interface {

  // json_value_test_interface interface
public:

  virtual void
  test_ctor_dtor ()
  {
    JSON *p[] = { 0, new JSON };

    for (size_t pidx = 0; pidx < 2; pidx++)
      {
        Number *n[] = {
          new Number,
          new Number (10),
          new Number ("10"),
          new Number (p[pidx]),
        };

        delete n[0];
        delete n[1];
        delete n[2];
        delete n[3];
      }

    delete p[1];

    Number src[] = {
      Number (10),
      Number ("100")
    };

    Number copy[] = {
        Number (src[0]),
        Number (src[1])
    };

    // double d[] = { copy[0].value (), copy[1].value () };

    CPPUNIT_ASSERT_MESSAGE ("number", & copy[0] != & src[0]);

    CPPUNIT_ASSERT_EQUAL_MESSAGE ("src[1]._double_value", (double) 0, src[1]._double_value);

    CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy[0].value ()", (double) 10, copy[0].value ());
    CPPUNIT_ASSERT_EQUAL_MESSAGE ("copy[1].value ()", (double) 100, copy[1].value ());

  }

  virtual void
  test_parse_1 ()
  {
    Number n;

    struct assert
    {
      const char *starp;
      size_t move;
      double dval;
      int assert_status;
    };

    std::vector<struct assert > test = {
        { "0", 1, 0, PASS },
        { "1 ", 1, 1, PASS },
        { "-2]", 2, -2, PASS },
        { "3.3 }", 3, 3.3, PASS },
        { "0.4, ", 3, 0.4, PASS },
        { "-0.5 ,", 4, -0.5, PASS },
        { "6e2", 3, 600, PASS },
        { "7E2}", 3, 700, PASS },
        { "8E+2 ] ", 4, 800, PASS },
        { "9E-2, ", 4, 0.09, PASS },

        { "x", 1, 0, FAIL },
        { "00", 1, 0, FAIL },
        { "05", 2, 0, FAIL },
        { "+5", 2, 0, FAIL },
        { "2e", 2, 0, FAIL },
        { "2eX", 2, 0, FAIL },
    };

    TEST_IT_START
      const char *startp = (*it).starp;
      const char *readp = n.parse (startp);

      n._double_valuep = 0;

      ASSERT_EQUAL_IDX ("n._readp", startp + (*it).move, readp);
      ASSERT_EQUAL_IDX ("n.value ()", (*it).dval, n.value ());

    TEST_IT_END;
  }

  virtual void test_size_1() {}

  virtual void test_at() {}

  virtual void test_value_1() {}

  virtual void test_debug_1() {}

  void
  test_digits ()
  {
    Number n;

    struct assert
    {
      const char *starp;
      size_t move;
      int peek;
      int assert_status;
    };

    std::vector<struct assert > test = {
        { "123", 3, 0, PASS },
        { "123x", 3, 'x', PASS },
        { "0.", 1, '.', PASS },
        { "123 ", 3, ' ', PASS },

        { "", 0, -1, PASS },
        { "x", 0, -1, PASS },
    };

    TEST_IT_START

        const char *startp = (*it).starp;

        n._readp = startp;
        // n._endp = startp + strlen (startp);

        int peek  = n._digits ();

        ASSERT_EQUAL_IDX ("readp", startp + (*it).move, n._readp);
        ASSERT_EQUAL_IDX ("peek", (*it).peek, peek);

    TEST_IT_END;
  }

  void
  test_frag ()
  {
    Number n;

    struct assert
    {
      const char *starp;
      size_t move;
      int peek;
      int assert_status;
    };

    std::vector<struct assert > test = {

        { "5.123 ", 5, ' ', PASS },
        { "5.123}", 5, '}', PASS },
        // { "5.123e", 5, 'e', PASS },
        // { "5.123E", 5, 'E', PASS },

        { "5.", 2, 0, FAIL },
        { "5.E", 2, 'E', FAIL },
    };

    TEST_IT_START

        const char *startp = (*it).starp;
        const char *endp = startp + (*it).move;

        n._readp = startp + 1;
        // n._endp = startp + strlen (startp);

        n._frag ();

        ASSERT_EQUAL_IDX ("readp", endp, n._readp);
        ASSERT_EQUAL_IDX ("peek", (*it).peek, (int)*(n._readp));
        ASSERT_EQUAL_IDX ("digitp[0][1]", endp, n._digitp[0][1]);

    TEST_IT_END;
  }

  void
  test_exp ()
  {
    Number n;

    struct assert {
        const char *starp;
        size_t move[2];
        int peek;
        long long atoll;
        int assert_status;
    };

    std::vector<struct assert > test = {

        { "2e2 ", { 2, 3 }, ' ', 2, PASS },
        { "2E3}", { 2, 3 }, '}', 3, PASS },
        { "2e+4]", { 2, 4 }, ']', 4, PASS },
        { "2e-5", { 2, 4 }, 0, -5, PASS },
        { "2e-00005", { 2, 8 }, 0, -5, PASS },

        { "2e", { 0, 0 }, 0, 0, FAIL },
        { "2e ", { 0, 0 }, 0, 0, FAIL },
        { "2e.", { 0, 0 }, 0, 0, FAIL },
        { "2e+", { 0, 0 }, 0, 0, FAIL },
    };

    TEST_IT_START

        const char *startp = (*it).starp;
        const char *endp = startp + (*it).move[1];

        n._readp = startp + 1;
        // n._endp = startp + strlen (startp);

        n._exp ();

        ASSERT_EQUAL_IDX ("n._readp", endp, n._readp);
        ASSERT_EQUAL_IDX ("*(n._readp)", (int) *endp, (*it).peek);
        ASSERT_EQUAL_IDX ("n._digitp[1][0]", startp + (*it).move[0], n._digitp[1][0]);
        ASSERT_EQUAL_IDX ("n._digitp[1][1]", startp + (*it).move[1], n._digitp[1][1]);

        std::string s (n._digitp[1][0], n._digitp[1][1]);

        ASSERT_EQUAL_IDX ("n._llexp", (*it).atoll, atoll (s.c_str ()));

    TEST_IT_END;
  }

  void
  test_calculate ()
  {
    Number n;

    struct assert {
        const char *starp[2];
        size_t move[2];
        double dval;
        int assert_status;
    };

    std::vector<struct assert > test = {
      { { 0, 0 }, { 0, 0 }, 0, PASS },
      { { "", "" }, { 0, 0 }, 0, PASS },
      { { "5", "" }, { 1, 1 }, 5, PASS },
      { { "5", "0" }, { 1, 1 }, 5, PASS },
      { { "2", "1" }, { 1, 1 }, 20, PASS },
      { { "2", "2" }, { 1, 1 }, 200, PASS },
      { { "2", "-2" }, { 1, 2 }, 0.02, PASS },
    };

    TEST_IT_START

      const char *digitp[2][2] = {
        { (*it).starp[0], (*it).starp[0] + (*it).move[0] },
        { (*it).starp[1], (*it).starp[1] + (*it).move[1] }
      };

      double d = n._calculate (digitp);
      // std::cerr << d << " " << *(n._double_valuep) << std::endl;

      ASSERT_EQUAL_IDX ("n._calculate ()", (*it).dval, d);
      ASSERT_EQUAL_IDX ("n._double_valuep", d, *(n._double_valuep));

    TEST_IT_END;
  }

  void
  test_atof ()
  {
    Number n;

    struct assert {
        const char *starp;
        double dval;
        int assert_status;
    };

    std::vector<struct assert > test = {
        { "5.5", 5.5, PASS },
        { "55.55", 55.55, PASS },
    };


    TEST_IT_START

      const char *digitp[] = { (*it).starp, (*it).starp + strlen ((*it).starp) };

      double d = n._atof (digitp);

      ASSERT_EQUAL_IDX ("n._atof ()", (*it).dval, d);

    TEST_IT_END;
  }

  void
  test_atoll ()
  {
    Number n;

    struct assert {
        const char *starp;
        long long llval;
        int assert_status;
    };

    std::vector<struct assert > test = {
        { "55", 55, PASS },
        { "5555", 5555, PASS },
    };

    TEST_IT_START

      const char *digitp[] = { (*it).starp, (*it).starp + strlen ((*it).starp) };

      long long ll = n._atoll (digitp);

      ASSERT_EQUAL_IDX ("n._atoll ()", (*it).llval, ll);

    TEST_IT_END;
  }

  virtual void
  test_assign_all_values ()
  {
    Object obj_parent;
    Array arr_parent;

    JSON *parents[] = {
      &obj_parent,
      &arr_parent,
      0
    };

    Number old_value;

    struct assert {
      Value *new_value;
      Value::object_type type;
      const char *key;
      size_t index;
      size_t count;
      int assert_status[3];
    };

    std::vector<struct assert > test = {
      { new Array ("[true,false]"), Value::array, "key_2",  0, 1,  { PASS, PASS, FAIL }  },
      { new Object ("{\"k1\":true,\"k2\":false}"), Value::object, "key_1",  0, 2,  { PASS, PASS, FAIL }},
      { new String ("\"x\""), Value::string, "key_3",  0, 3,  { PASS, PASS, FAIL }  },
      { new Number (10), Value::number, "key_4",  0, 4, { PASS, PASS, PASS } },
      { new Number ("10"), Value::number, "key_5",  0, 5, { PASS, PASS, PASS } },
      { new Boolean (true), Value::boolean, "key_6",  0, 6, { PASS, PASS, FAIL } },
      { new Null, Value::null, "key_7",  0, 7, { PASS, PASS, FAIL } }
    };
      arr_parent._element_list.reserve (6);

      for (size_t pidx = 0; pidx < 3; pidx++)
        {
          obj_parent._member_list.clear ();
          arr_parent._element_list.clear ();
          old_value._parent = parents[pidx];

          for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++) {\
            try {\
                if ((*it).assert_status[pidx] == SKIP) { continue; }\
                if ((*it).assert_status[pidx] > PASS) { this->_errorc[EXPECTED]++; }

          /// old_value: value from Value[key], any value

          arr_parent._element_list.push_back (new Undefined);
          old_value.setKey ((*it).key, strlen ((*it).key));

          (*it).index  = arr_parent._element_list.size () - 1;
          old_value.setIndex ((*it).index);

          Value *new_value = 0;

          if ((*it).new_value->type () == Value::number)
            {
              Number *new_a_value = static_cast<Number *>((*it).new_value);
              // old_value._assign (*new_a_value);
              old_value = *new_a_value;
              new_value = new_a_value;
            }
          else
            {
              // old_value._assign (*(*it).new_value);
              old_value = *(*it).new_value;
              new_value = (*it).new_value;
            }

          JSON *parent = old_value._parent;

          if (parent)
            {
              ASSERT_EQUAL_IDX ("old_value.parent.count ()", (*it).count, parent->count ());

              if (parent->type () == Value::object)
                {
                  Value *ov =  obj_parent._member_list.at ((*it).key);

                  ASSERT_EQUAL_IDX ("obj_parent[key].type", ov->type (), (*it).type);
                  ASSERT_EQUAL_IDX ("obj_parent[key].value", ov, new_value);
                }
              else
                {
                  Value *av =  arr_parent._element_list.at ((*it).index);

                  ASSERT_EQUAL_IDX ("arr_parent[key].type", av->type (), (*it).type);
                  ASSERT_EQUAL_IDX ("arr_parent[key].value", av, new_value);
                }
            }
          else
            {
              if (new_value->type () == Value::number)
                {
                  ASSERT_EQUAL_IDX ("old_value.value ()", (double) 10, old_value.value ());
                  // ASSERT_EQUAL_IDX ("old_value.value ()", static_cast<Number *>(new_value)->value (), old_value.value ());
                }
            }
          TEST_IT_END;
        }
  }

  virtual void test_stringify() override {}

  virtual void test_strLength () override {}
  virtual void
  test_strValue () override
  {

    struct assert
    {
      double df;
      long li;
      const char *output[2];
      int assert_status;
    };

    std::vector<struct assert > test = {
      { 100, 100, { "100.000000", "100.000000" }, PASS }
    };

    TEST_IT_START

      Number n[2] = {
        Number ((*it).df),
        Number ((*it).li),
      };

      CPPUNIT_ASSERT_MESSAGE ("n[0].strValue ()", strcmp((*it).output[0], n[0].strValue ()) == 0);
      CPPUNIT_ASSERT_MESSAGE ("n[1].strValue ()", strcmp((*it).output[1], n[1].strValue ()) == 0);

      // std::cout << n[0].strValue () << std::endl;
      // std::cout << n[1].strValue () << std::endl;

    TEST_IT_END;
  }

  virtual void test__clear() {}

  virtual void test_operator_assign () {}
  virtual void test_operator_at () {}


  /// Test number 5
  static CppUnit::Test *
  suite ()
  {
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json number test");

     s->addTest (new CppUnit::TestCaller<json_number_test> ("test_strValue", &json_number_test::test_strValue));
     // return s;

    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_ctor_dtor", &json_number_test::test_ctor_dtor));
    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_parse_1", &json_number_test::test_parse_1));
//
//    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_size_1", &json_number_test::test_size_1));
//    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_get_1", &json_number_test::test_get_1));
//    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_value_1", &json_number_test::test_value_1));
//    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_debug_1", &json_object_test::test_debug_1));

    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_digits", &json_number_test::test_digits));
    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_frag", &json_number_test::test_frag));
    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_exp", &json_number_test::test_exp));
    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_atof", &json_number_test::test_atof));
    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_atoll", &json_number_test::test_atoll));

    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_calculate", &json_number_test::test_calculate));
    s->addTest (new CppUnit::TestCaller<json_number_test> ("test_assign_all_values", &json_number_test::test_assign_all_values));

    return s;
  }
};

#endif // json_number_test

