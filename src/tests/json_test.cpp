#include "json_test.h"
#include <stdio.h>
void
json_test::test_smoke ()
{
}

void
json_test::test_parse_1 ()
{
    size_t charc = 0;
    size_t errorc = 0;
    size_t idx = 0;

    json *j;

    // size_t idx = 0;

    const char *startp = 0;
    const char *readp = 0;

    struct assert {
        const char *input;
        size_t move;
        char endch;
        value::otype type;
    };

    std::vector<struct assert > test = {
        { "{ \"foo\" : \"ru\" } ", 17 - 2, '}',   value::otype::object },      // 17 - quotes
        { " { \"bar\" : \"ul\" } ", 17 - 2, '}',  value::otype::object },     // Space skipped in parse
        { "[ \"ru\" ] ", 7, ']',  value::otype::array },
        { " [ \"als\" ] ", 8, ']',  value::otype::array }
    };

    for (auto it = test.begin (); it != test.end (); it++, idx++) {
        try {
            startp = (*it).input;
            charc = strlen (startp);

            j = new json (startp + charc, 0, (*it).move);

            readp = j->parse (startp);
            // std::cout << readp -1 << std::endl;
            CPPUNIT_ASSERT_EQUAL_MESSAGE ("readp", (*it).endch, *(readp - 1));
            CPPUNIT_ASSERT_EQUAL_MESSAGE ("object type", (*it).type, j->type ());

            delete j;


        } CATCH_ERROR_PCHAR;
    }
}

void
json_test::test_size_1 ()
{
}

void
json_test::test_at_1 ()
{
}

void
json_test::test_value_1 ()
{
}

void
json_test::test_debug_1 ()
{
}



CppUnit::Test *
json_test::suite ()
{
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json test");

//    s->addTest (new CppUnit::TestCaller<json_test> ("test_smoke", &json_test::test_smoke));
    s->addTest (new CppUnit::TestCaller<json_test> ("test_parse_1", &json_test::test_parse_1));
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_size_1", &json_test::test_size_1));
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_get_1", &json_test::test_get_1));
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_value_1", &json_test::test_value_1));
//    s->addTest (new CppUnit::TestCaller<json_test> ("test_debug_1", &json_test::test_debug_1));

    return s;
}
