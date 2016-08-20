#ifndef JSON_TEST_H
#define JSON_TEST_H

#include <json_value_test_interface.h>

class json_test : public json_value_test_interface
{
public:

    virtual void test_smoke ();
    virtual void test_parse_1 ();
    virtual void test_size_1 ();
    virtual void test_get_1 ();
    virtual void test_value_1 ();
    virtual void test_debug_1 ();

    static CppUnit::Test* suite ();
};

#endif // JSON_TEST_H
