#ifndef JSON_STRING_TEST_H
#define JSON_STRING_TEST_H

#include "json_leaf_test.h"

namespace format
{
/**
 * 4.
 * @brief The json_string_test class
 */
class json_string_test : public json_leaf_test
{
public:

  virtual void
  test_ctor_dtor ()
  {
    json *p[] = { 0, new json () };

    for (size_t pidx = 0; pidx < 2; pidx++)
      {
        string *a[] = {
          new string (),
          new string (L"\"x\""),
          new string (p[pidx], 1),
        };

        delete a[0];
        delete a[1];
        delete a[2];
      }

    delete p[1];

    string src = L"\"xxx\"";
    string copy = src;

    CPPUNIT_ASSERT_MESSAGE ("string", & copy != & src);
    CPPUNIT_ASSERT_EQUAL_MESSAGE ("src._string_value.empty ()", true, src._string_value[0].empty () );
    CPPUNIT_ASSERT_MESSAGE ("copy.value ()", wcscmp (L"xxx", copy.get ()) == 0);
  }

  virtual void
  test_parse_1 ()
    {
      json *p[] = { 0, new json () };

      struct assert
      {
        const wchar_t *startp[2];
        size_t charc[2];
        wchar_t endc[2];
        int assert_status;
      };

      std::vector<struct assert > test = {
          { { L"\"\"", L"\"\"" }, { 0, 0 }, { (wchar_t) 0, (wchar_t) 0 }, PASS },
          { { L"xxx", L"\"xxx\"" }, { 3, 3 }, { (wchar_t) 0, (wchar_t) 0 }, PASS },
          { { L" xxx ", L"\" xxx \"" }, { 5, 5 }, { (wchar_t) 0, (wchar_t) 0 }, PASS },
          { { L" xxx ", L"\" xxx \" " }, { 5, 5 }, { (wchar_t) 0, L' ' }, PASS },
      };

      TEST_IT_START
          for (int pidx = 1; pidx < 2; pidx++)
            {
              const wchar_t *startp = (*it).startp[pidx];
              size_t move = (*it).charc[pidx] + 2;

              string *s = 0;

              if (pidx == 1)
                {
                  s = new string (p[pidx], move);

                  std::wstring ss = s->get ();

                  CPPUNIT_ASSERT_MESSAGE ("string.empty ()", ss.empty () );

                  const wchar_t *readp = s->_parse (startp);
                  ss = s->get ();

                  ASSERT_EQUAL_IDX ("string.readp", readp, startp + move);
                  ASSERT_EQUAL_IDX ("*(string.readp)", (wchar_t)* readp, (*it).endc[pidx]);
                  ASSERT_EQUAL_IDX ("string.length", (*it).charc[pidx], ss.length () /* s->strLength() - 2 */ );
                }
              else
                {
                  s = new string (startp);
                  ASSERT_EQUAL_IDX ("string.length", (*it).charc[pidx], s->strLength () );
                }
              // std::cout << readp << "" << ss.length () << " " << ss << std::endl;

              delete s;
            }
       TEST_IT_END;

       delete p[1];
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
        { new object (L"{\"k1\":true,\"k2\":false}"), value::object_t, L"key_2",  0, 2,  { PASS, PASS, FAIL } },
        { new string (L"\"xxx\""), value::string_t, L"key_3",  0, 3,  { PASS, PASS, PASS } },
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

            string *old_value = new string ();
            old_value->_parent = parents[pidx];

            arr_parent._element_list.push_back (new undefined);
            old_value->setKey ((*it).key, wcslen ((*it).key));

            (*it).index  = arr_parent._element_list.size () - 1;
            old_value->setIndex ((*it).index);

            value *new_value = 0;

            if ((*it).new_value->type () == value::string_t)
              {
                string *new_a_value = static_cast<string *>((*it).new_value);

                // old_value->_assign (*new_a_value);
                *old_value = *new_a_value;

                new_value = new_a_value;
              }
            else
              {
                // old_value->_assign (*(*it).new_value);
                *old_value = *(*it).new_value;

                new_value = (*it).new_value;
              }

            json *parent = parents[pidx];   //  old_value->_parent;

            if (parent)
              {
                ASSERT_EQUAL_IDX ("old_value.parent.count ()", (*it).count, parent->count ());

                if (parent->type () == value::object_t)
                  {
                    value *ov =  obj_parent._member_list.at ((*it).key);

                    ASSERT_EQUAL_IDX ("obj_parent[key].type", ov->type (), (*it).type);
                    //ASSERT_EQUAL_IDX ("obj_parent[key].value", ov, new_value);
                  }
                else
                  {
                    value *av =  arr_parent._element_list.at ((*it).index);

                    ASSERT_EQUAL_IDX ("arr_parent[key].type", av->type (), (*it).type);
                    //ASSERT_EQUAL_IDX ("arr_parent[key].value", av, new_value);
                  }
              }
            else if (new_value->type () == value::string_t)
              {
                CPPUNIT_ASSERT_MESSAGE ("old_value.value ()", wcscmp (L"xxx", old_value->get ()) == 0);
              }

            TEST_IT_END;
          }

        for (auto it = test.begin (); it != test.end (); ++it)
          delete (*it).new_value;
    }

    virtual void test_erase () override {}

    // virtual void test_stringify () override {}

    virtual void test_strLength () override {}
    virtual void test_strValue () override {}

    virtual void test__clear () {}

    virtual void test_operator_assign () {}
    virtual void test_operator_at () {}

    void
    test__string ()
    {
      struct assert
      {
          const wchar_t *input;
          long charc;
          int assert_status;
      };

      std::vector<struct assert > test = {
          { L"", 0, PASS },
          { L"x", 1, PASS },

          { L"x\"", -1, PASS },
          { L"x\u001F\"", -1, PASS }
      };


      TEST_IT_START

        string s;

        s._readp = (*it).input;

        long charc = s.__string ();

        ASSERT_EQUAL_IDX ("charc", (*it).charc, charc);

      TEST_IT_END;
    }

    /**
     * 4.
     * @brief suite
     * @return
     */
    static CppUnit::Test*
    suite ()
    {
      CppUnit::TestSuite *s = new CppUnit::TestSuite ("json string test");

      /* 0. */  s->addTest (new CppUnit::TestCaller<json_string_test> ("test_ctor_dtor", &json_string_test::test_ctor_dtor));
      /* 1. */  s->addTest (new CppUnit::TestCaller<json_string_test> ("test_parse_1", &json_string_test::test_parse_1));
      /* 2. */  s->addTest (new CppUnit::TestCaller<json_string_test> ("test_assign_all_values", &json_string_test::test_assign_all_values));
      /* 3. */  s->addTest (new CppUnit::TestCaller<json_string_test> ("test__string", &json_string_test::test__string));

      return s;
    }
};
} // Namespace format
#endif // JSON_STRING_TEST_H
