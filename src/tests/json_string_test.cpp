#include "json_string_test.h"


void
json_string_test::test_parse_1 ()
{
    size_t charc = 0;
    size_t errorc = 0;
    size_t idx = 0;

    json::string *s = 0;

    // size_t idx = 0;

    const char *startp = 0;
    const char *readp = 0;

    struct assert {
        const char *input;
        size_t charc;
    };

    std::vector<struct assert > test = {
        { "\"\"", 0 },
        { "\"xxx\"", 3 },
        { "\" xxx \"", 5 },
    };

    for (auto it = test.begin (); it != test.end (); it++, idx++) {
        try {
            startp = (*it).input;
            charc = strlen (startp);

            s = new json::string (startp + charc, 0, charc);

            std::string ss = s->value ();

            CPPUNIT_ASSERT_MESSAGE ("empty", ss.empty () );

            readp = s->parse (startp);
            ss = s->value ();

            // std::cout << readp << "" << ss.length () << " " << ss << std::endl;

            CPPUNIT_ASSERT_EQUAL_MESSAGE ("readp", *readp, (char) 0);
            CPPUNIT_ASSERT_EQUAL_MESSAGE ("length", (*it).charc, ss.length () );

            delete s;


        } CATCH_ERROR_PCHAR;
    }
}

CppUnit::Test *
json_string_test::suite ()
{
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json string test");

     s->addTest (new CppUnit::TestCaller<json_string_test> ("test_parse_1", &json_string_test::test_parse_1));

    return s;
}

