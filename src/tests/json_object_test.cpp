#include "json_object_test.h"




void
json_object_test::test_smoke ()
{
}

void
json_object_test::test_parse_1 ()
{
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

    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_smoke", &json_object_test::test_smoke));
    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_parse_1", &json_object_test::test_parse_1));
    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_size_1", &json_object_test::test_size_1));
    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_get_1", &json_object_test::test_get_1));
    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_value_1", &json_object_test::test_value_1));
    s->addTest (new CppUnit::TestCaller<json_object_test> ("test_debug_1", &json_object_test::test_debug_1));

    return s;
}
