#ifndef JSON_INTERFACE_TEST_H
#define JSON_INTERFACE_TEST_H

#include <json_value_test_interface.h>
#include "json_value_parse_mock.h"

/**
 * 0.
 * @brief The json_value_test class
 */
class json_value_test : public json_value_test_interface
{
public:
    virtual void test_ctor_dtor() {}
    virtual void test_parse_1(){}
    virtual void test_size_1(){}
    virtual void test_at(){}
    virtual void test_value_1(){}
    virtual void test_debug_1(){}

    void test_lookahead ()
    {
      struct assert {
          const wchar_t *startp;
          wchar_t readp;
          int assert_status;
      };

      std::vector<struct assert > test = {
          { L"", 0, PASS},
          { L"   ", 0, PASS },
          { L"x", 'x', PASS },
          { L" \
              a", 'a', PASS },
          { L"   \"b", '"', PASS },
          { L"   \n\r\tc ", 'c', PASS },
          { L"   5", '5', PASS }
      };

      TEST_IT_START

        const wchar_t *startp = (*it).startp;

        json_value_mock *m  = new json_value_mock;

        m->_startp = m->_readp = startp;

        m->_look_ahead ();

        ASSERT_EQUAL_IDX ("value.readp", (*it).readp , *(m->_readp));

        delete m;

      TEST_IT_END;
    }

    void test_lexeme ();

    void test_string () // Moved to json_test
    {
      wchar_t endc;

      struct assert {
          const wchar_t *startp;
          long int charc;
          int assert_status;
      };

      std::vector<struct assert > test = {
          { L" ", 0, PASS},
          { L"\"", -1, PASS },
          { L"\"x\"", 3, PASS },
          { L"\" x\"", 4, PASS },
          { L"\" xx", -4, PASS },

          { L"\"\u001F\"", -1, PASS },
          { L"\"xx\u001F\"", -3, PASS }
      };

      TEST_IT_START

          const wchar_t *startp = (*it).startp;
          long int charc = wcslen (startp);

          json_value_mock *m  = new json_value_mock;

          m->_startp = m->_readp = startp;

          m->_look_ahead ();

          charc = m->_string (endc);

          ASSERT_EQUAL_IDX ("charc", (*it).charc , charc);

          delete m;

      TEST_IT_END;
    }

    void test_is_literal ()
    {
      struct assert {
          const wchar_t *startp;
          Value::_literal value_type;
          int assert_status;
      };

      std::vector<struct assert> test = {
        { L"", Value::_literal::no_value, PASS },
        { L"   ", Value::_literal::no_value, PASS },
        { L"xxx   ", Value::_literal::no_value, PASS },
        { L"xxxxxx   ", Value::_literal::no_value, PASS },
        { L"true    ", Value::_literal::true_value, PASS },
        { L"false    ", Value::_literal::false_value, PASS },
        { L"null   ", Value::_literal::null_value, PASS }
      };

      TEST_IT_START

          const wchar_t *startp = (*it).startp;

          json_value_mock *m  = new json_value_mock;

          m->_startp = m->_readp = startp;

          Value::_literal ltr = m->_is_literal ();

          ASSERT_EQUAL_IDX ("literal value", (*it).value_type , ltr);

          delete m;

      TEST_IT_END;
    }

    void
    test__str_append ()
    {
      wchar_t *dst = new wchar_t[8 + 1]();
      wchar_t *startp = dst;

      struct assert {
          const wchar_t *src;
          size_t charc[2];
          int assert_status;
      };

      std::vector<struct assert> test = {
        { L"",  { 0, 0 }, PASS },
        { L"a",  { 1, 1 }, PASS },
        { L"bb",  { 2, 3 }, PASS },
        { L"\"ccc\"",  { 5, 8 }, PASS },
      };

      TEST_IT_START

          dst = Value::_str_append (dst, (*it).src, (*it).charc[0]);

          ASSERT_EQUAL_IDX ("dst", startp + (*it).charc[1], dst);

      TEST_IT_END;

      CPPUNIT_ASSERT_MESSAGE ("starp", wcscmp (L"abb\"ccc\"", startp) == 0);

      delete[] startp;
    }

    void
    test_assign_undefined ()
    {
      Boolean b;

      Array a = L"[true]";

      struct assert
      {
        Value *value;
        size_t size;    // Array::_element_list.size ()
        int assert_status;
      };

      size_t index = 0;

      std::vector<struct assert> test = {
        { & b, 1, PASS }, // No parent
        { & (a.at (index)), 0, PASS }  // Has parent
      };

      TEST_IT_START

          (*it).value->_assign (Undefined ());

          ASSERT_EQUAL_IDX ("a.count ()", (*it).size, a.count ());

      TEST_IT_END;
    }

    void
    test_assign_copy ()
    {
      JSON json[] = {
        L"{}",
        L"[]"
      };

      struct assert
      {
        Value *value;
        Value::object_type type;  // old, current
        int assert_status;
      };

      std::vector<struct assert> test = {
        { new Object, Value::object, PASS },
        { new Array, Value::array, PASS },
        { new String, Value::string, PASS },
        { new Number, Value::number, PASS },
        { new Boolean, Value::boolean, PASS },
        { new Null, Value::null, PASS },
        { new Undefined, Value::undefined, PASS }
      };

      for (size_t hdx = 0; hdx < 2; hdx++)
        {
          _idx[0] = 0;

      TEST_IT_START

          for (size_t jdx = 0; jdx < 2; jdx++)
            {
              json[hdx][L"0"] = *(*it).value;   // Undefined <-- Object, Object <-- Array, ...

              Value & v = json[hdx][L"0"];

              ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());
            }

      TEST_IT_END;
        }

      for (auto it = test.begin (); it != test.end (); ++it)
        delete (*it).value;
    }


    virtual void test_stringify () override {}
    virtual void test_strLength () override {}
    virtual void test_strValue () override {}

    virtual void test_operator_assign () {}
    virtual void test_operator_at () {}
    virtual void test_assign_all_values (){}
    virtual void test__clear () {}

    virtual void test_erase () override {}

    /**
     * 0.
     * @brief suite
     * @return
     */
    static CppUnit::Test *
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json value test");

      s->addTest (new CppUnit::TestCaller<json_value_test> ("test_assign_copy", &json_value_test::test_assign_copy));
      s->addTest (new CppUnit::TestCaller<json_value_test> ("test_assign_undefined", &json_value_test::test_assign_undefined));

      s->addTest (new CppUnit::TestCaller<json_value_test> ("test_lookahead", &json_value_test::test_lookahead));
      s->addTest (new CppUnit::TestCaller<json_value_test> ("test_is_literal", &json_value_test::test_is_literal));
      s->addTest (new CppUnit::TestCaller<json_value_test> ("test_is_quoted", &json_value_test::test_string));

      s->addTest (new CppUnit::TestCaller<json_value_test> ("test__str_append", &json_value_test::test__str_append));

      return s;
    }
};

#endif // JSON_INTERFACE_TEST_H
