#include "json_test.h"

json_test::json_test ()
{
}

void
json_test::test_smoke ()
{
}

void
json_test::test_parse_1 ()
{
}

void
json_test::test_size_1 ()
{
}

void
json_test::test_get_1 ()
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

    s->addTest (new CppUnit::TestCaller<json_test> ("test_smoke", &json_test::test_smoke));
    s->addTest (new CppUnit::TestCaller<json_test> ("test_parse_1", &json_test::test_parse_1));
    s->addTest (new CppUnit::TestCaller<json_test> ("test_size_1", &json_test::test_size_1));
    s->addTest (new CppUnit::TestCaller<json_test> ("test_get_1", &json_test::test_get_1));
    s->addTest (new CppUnit::TestCaller<json_test> ("test_value_1", &json_test::test_value_1));
    s->addTest (new CppUnit::TestCaller<json_test> ("test_debug_1", &json_test::test_debug_1));

    return s;
}
