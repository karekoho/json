#include "json_value_test.h"

void
json_value_test::test_lookahead ()
{

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
