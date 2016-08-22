#ifndef JSON_VALUE_TEST_H
#define JSON_VALUE_TEST_H

#include <unit_test.h>

class json_value_test_interface : public CppUnit::TestFixture
{
public:

    void test_lookahead ();
    void test_lexeme ();
    void test_is_literal ();

    virtual void test_smoke () = 0;
    virtual void test_parse_1 () = 0;
    virtual void test_size_1 () = 0;
    virtual void test_get_1 () = 0;
    virtual void test_value_1 () = 0;
    virtual void test_debug_1 () = 0;

protected:

    static const char *_input[];
};

#endif // JSON_VALUE_TEST_H
