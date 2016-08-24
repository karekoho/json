#include "json_object_test.h"




void
json_object_test::test_smoke ()
{
}

void
json_object_test::test_parse_1 ()
{
    size_t charc = 0;
    size_t errorc = 0;
    size_t idx = 0;

    json::object *j;

    // size_t idx = 0;

    const char *startp = 0;
    const char *readp = 0;

    struct assert {
        const char *input;
        size_t memberc;
        char endch;
        // value::otype type;
    };

    std::vector<struct assert > test = {
        { "{ \"foo\" : \"bar\" } ", 1, '}' },
        // { " { \"bar\" : null } ", 1, '}' },
        // { "[ true ] ", 7, ']',  value::otype::array },
        // { " [ false ] ", 8, ']',  value::otype::array }
    };

    for (auto it = test.begin (); it != test.end (); it++, idx++) {
        try {
            startp = (*it).input;
            charc = strlen (startp);

            j = new json::object (startp + charc, 0);

            readp = j->parse (startp);

            // CPPUNIT_ASSERT_EQUAL_MESSAGE ("readp", (*it).endch, *readp);
            // CPPUNIT_ASSERT_EQUAL_MESSAGE ("object type", (*it).type, j->type ());

            delete j;


        } CATCH_ERROR_PCHAR;
    }
}

void
json_object_test::test_size_1 ()
{
}

void
json_object_test::test_get_1 ()
{
}

void
json_object_test::test_value_1 ()
{
}

void json_object_test::test_debug_1 ()
{
}

CppUnit::Test *
json_object_test::suite ()
{
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json object test");

//    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_smoke", &json_object_test::test_smoke));
      s->addTest (new CppUnit::TestCaller<json_object_test> ("test_parse_1", &json_object_test::test_parse_1));
//    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_size_1", &json_object_test::test_size_1));
//    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_get_1", &json_object_test::test_get_1));
//    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_value_1", &json_object_test::test_value_1));
//    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_debug_1", &json_object_test::test_debug_1));

    return s;
}
