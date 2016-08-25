#include "json_object_test.h"

void
json_object_test::test_parse_1 ()
{
    size_t charc = 0;
    size_t errorc = 0;
    size_t idx = 0;

    json::object *o;
    json::object *p;

    // size_t idx = 0;

    const char *startp = 0;
    const char *readp = 0;

    char _sz_idx[300];

    struct assert {
        const char *input;
        size_t size;
        value::otype type;
    };

    std::vector<struct assert > test = {
        { "{ \"k\" : \"v\" } ", 1, value::string },
        { "{ \"k\" : \"v\", \"q\" : \"p\" } ", 2, value::string },
        { "{ \"k\": \"v\", \"q\" : \"p\",\"K\":\"v\" } ", 3, value::string },
        { "{ \"k\": \"p\" ,\"q\" : \"p\", \"K\" :\"v\",\"Q\":\"p\" } ", 4, value::string },
        { "{}", 0, value::undefined },
        { "{ \"k\" : { } }", 1, value::object },
        { "{ \"k\" : {\"kk\" : \"v\"}}", 1, value::object },
        { "{ \"k\" : {\"kk\" : {\"kkk\" : \"v\"}}", 1, value::object },

        // errors
        { "{ , }", 0, value::undefined }, // syntax error exception
    };

    for (auto it = test.begin (); it != test.end (); it++, idx++) {
        try {
            startp = (*it).input;
            charc = strlen (startp);

            o = new json::object (startp + charc, p);

            readp = o->parse (startp);

            CPPUNIT_ASSERT_EQUAL_MESSAGE ("value.size", (*it).size, o->size ());
            CPPUNIT_ASSERT_EQUAL_MESSAGE ("value.type", (*it).type, o->at ("k").type ());

            delete o;

        } catch (json::syntax_error & se) {
            errorc++;
            std::cerr << se.what () << std::endl;

        } CATCH_ERROR_PCHAR;
    }
    ASSERT_ERRORC (1);
}

void
json_object_test::test__pair ()
{
    size_t charc = 0;
    size_t errorc = 0;
    size_t idx = 0;

    json::object *o;

    char _sz_idx[300];
    // size_t idx = 0;

    const char *startp = 0;
    // const char *readp = 0;

    struct assert {
        const char *input;
        bool status;
    };

    std::vector<struct assert > test = {
        { " \"foo\" : \"bar\"  ", true },
        { " }" , false },

        // errors
        { " ", false },         // syntax error exception
        { " \"foo  ", false },  // syntax error exception
        { " \"foo\" ", false },  // syntax error exception
    };

    for (auto it = test.begin (); it != test.end (); it++, idx++) {
        try {
            startp = (*it).input;
            charc = strlen (startp);

            o = new json::object (startp + charc, 0);
            o->_readp = startp;
            bool status = o->_pair ();
            // readp = o->parse (startp);

             CPPUNIT_ASSERT_EQUAL_MESSAGE ("status", (*it).status, status);

            delete o;


        } catch (json::syntax_error & se) {
            errorc++;
            std::cerr << se.what () << std::endl;

        } CATCH_ERROR_PCHAR
    }

    ASSERT_ERRORC (3);
}

void
json_object_test::test__value ()
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

     s->addTest (new CppUnit::TestCaller<json_object_test> ("test_pair_1", &json_object_test::test__pair));
 //     s->addTest (new CppUnit::TestCaller<json_object_test> ("test_pair_1", &json_object_test::test__value));

    return s;
}
