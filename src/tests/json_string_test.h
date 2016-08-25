#ifndef JSON_STRING_TEST_H
#define JSON_STRING_TEST_H

#include "json_value_test_interface.h"

class json_string_test : public json_value_test_interface
{
public:

    // json_value_test_interface interface
public:
    virtual void test_smoke()
    {
    }
    virtual void test_parse_1();

    virtual void test_size_1()
    {
    }
    virtual void test_at_1()
    {
    }
    virtual void test_value_1()
    {
    }
    virtual void test_debug_1()
    {
    }

    static CppUnit::Test* suite ();

};

#endif // JSON_STRING_TEST_H
