#ifndef JSON_OBJECT_TEST_H
#define JSON_OBJECT_TEST_H

#include <json_value_test_interface.h>

/**
 * Test number 2
 * @brief The json_object_test class
 */
class json_object_test : public json_value_test_interface
{
public:

    virtual void test_smoke () {}
    virtual void test_parse_1();
    virtual void test_size_1() {}
    virtual void test_at_1() {}
    virtual void test_value_1() {}
    virtual void test_debug_1() {}

    void test__pair ();
    void test__value ();

    static CppUnit::Test* suite ();

};

#endif // JSON_OBJECT_TEST_H
