#include "json_value_test.h"
#include "json_value_parse_mock.h"

void
json_value_test::test_lookahead ()
{
    size_t charc = 0;
    // size_t idx = 0;

    const char *startp = 0;

    struct inout_{
        const char *in;
        char out;
    };

    std::vector<struct inout_ > test = {
        {"   ", 0},
        {" \
            a", 'a'},
        {"   \"b", '"'},
        {"   \n\r\tc ", 'c'},
        {"   5", '5'}
    };


    for (auto it = test.begin (); it != test.end (); it++) {
        startp = (*it).in;
        charc = strlen (startp);

        json_value_parse_mock *m  = new json_value_parse_mock (startp, startp + charc, 0, charc);

        m->_look_ahead ();

        CPPUNIT_ASSERT_EQUAL_MESSAGE ("test_lookahead", (*it).out , *(m->_readp));

        delete m;
    }
}

void
json_value_test::test_lexeme ()
{

}

void
json_value_test::test_is_literal ()
{

}

void
json_value_test::test_is_quoted ()
{

}

void
json_value_test::test_is_number ()
{

}

CppUnit::Test *
json_value_test::suite ()
{
    CppUnit::TestSuite *s = new CppUnit::TestSuite ("json value test");

    s->addTest (new CppUnit::TestCaller<json_value_test> ("test_lookahead", &json_value_test::test_lookahead));
    s->addTest (new CppUnit::TestCaller<json_value_test> ("test_lexeme", &json_value_test::test_lexeme));
    s->addTest (new CppUnit::TestCaller<json_value_test> ("test_is_literal", &json_value_test::test_is_literal));
    s->addTest (new CppUnit::TestCaller<json_value_test> ("test_is_quoted", &json_value_test::test_is_quoted));
    s->addTest (new CppUnit::TestCaller<json_value_test> ("test_is_number", &json_value_test::test_is_number));

    return s;
}
