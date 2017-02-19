#ifndef JSON_INTERFACE_TEST_H
#define JSON_INTERFACE_TEST_H

#include <json_value_test_interface.h>
#include "json_value_parse_mock.h"
namespace format {
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
    virtual void test_operator_at_key(){}
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

        format::json_value_mock *m  = new format::json_value_mock;

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
          value::_literal value_type;
          int assert_status;
      };

      std::vector<struct assert> test = {
        { L"", value::_literal::no_literal, PASS },
        { L"   ", value::_literal::no_literal, PASS },
        { L"xxx   ", value::_literal::no_literal, PASS },
        { L"xxxxxx   ", value::_literal::no_literal, PASS },
        { L"true    ", value::_literal::true_value, PASS },
        { L"false    ", value::_literal::false_value, PASS },
        { L"null   ", value::_literal::null_value, PASS }
      };

      TEST_IT_START

          const wchar_t *startp = (*it).startp;

          json_value_mock *m  = new json_value_mock;

          m->_startp = m->_readp = startp;

          value::_literal ltr = m->_is_literal ();

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

          dst = value::_str_append (dst, (*it).src, (*it).charc[0]);

          ASSERT_EQUAL_IDX ("dst", startp + (*it).charc[1], dst);

      TEST_IT_END;

      CPPUNIT_ASSERT_MESSAGE ("starp", wcscmp (L"abb\"ccc\"", startp) == 0);

      delete[] startp;
    }

    void
    test_assign_undefined ()
    {
      boolean b;

      array a = L"[true]";

      struct assert
      {
        value *val;
        size_t size;    // Array::_element_list.size ()
        int assert_status;
      };

      size_t index = 0;

      std::vector<struct assert> test = {
        { & b, 1, PASS }, // No parent
        { & (a[index]), 0, PASS }  // Has parent
      };

      TEST_IT_START

          (*it).val->_assign (format::undefined ());

          ASSERT_EQUAL_IDX ("a.count ()", (*it).size, a.count ());

      TEST_IT_END;
    }

    void
    test_assign_copy ()
    {
      json json[] = {
        L"{}",
        L"[]"
      };

      struct assert
      {
        value *val;
        value::value_t type;  // old, current
        int assert_status;
      };

      std::vector<struct assert> test = {
        { new object, value::object_t, PASS },
        { new array, value::array_t, PASS },
        { new string, value::string_t, PASS },
        { new number, value::number_t, PASS },
        { new boolean, value::boolean_t, PASS },
        { new null, value::null_t, PASS },
        { new format::undefined, value::undefined_t, PASS }
      };

      for (size_t hdx = 0; hdx < 2; hdx++)
        {
          _idx[0] = 0;

      TEST_IT_START

          for (size_t jdx = 0; jdx < 2; jdx++)
            {
              json[hdx][L"0"] = *(*it).val;   // Undefined <-- Object, Object <-- Array, ...

              value & v = json[hdx][L"0"];

              ASSERT_EQUAL_IDX ("v.type ()", (*it).type, v.type ());
            }

      TEST_IT_END;
        }

      for (auto it = test.begin (); it != test.end (); ++it)
        delete (*it).val;
    }


    //virtual void test_stringify () override {}
    virtual void test_strLength () override {}
    virtual void test_strValue () override {}

    virtual void test_operator_assign () {}
    virtual void test_operator_at () {}
    virtual void test_assign_all_values (){}
    virtual void test__clear () {}

    virtual void test_erase () override {}

    virtual void
    test_operator_at_index ()
    {
    }

    void
    test_operator_equal_value_t ()
    {
      boolean b;
      CPPUNIT_ASSERT_MESSAGE ("value == value_t", b == value::boolean_t);
    }

    void
    test_operator_equal_value ()
    {
      boolean b[2];
      CPPUNIT_ASSERT_MESSAGE ("value == value", b[0] == b[1]);
    }

    /**
     * 0.
     * @brief suite
     * @return
     */
    static CppUnit::Test *
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json value test");

      /* 0. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_assign_copy", &json_value_test::test_assign_copy));
      /* 1. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_assign_undefined", &json_value_test::test_assign_undefined));
      /* 2. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_lookahead", &json_value_test::test_lookahead));
      /* 3. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_is_literal", &json_value_test::test_is_literal));
      /* 4. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_is_quoted", &json_value_test::test_string));
      /* 5. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test__str_append", &json_value_test::test__str_append));
      /* 6. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_operator_equal_value_t", &json_value_test::test_operator_equal_value_t));
      /* 7. */  s->addTest (new CppUnit::TestCaller<json_value_test> ("test_operator_equal_value", &json_value_test::test_operator_equal_value));

      return s;
    }
};
}
#endif // JSON_INTERFACE_TEST_H
