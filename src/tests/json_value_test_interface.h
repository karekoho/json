#ifndef JSON_VALUE_TEST_H
#define JSON_VALUE_TEST_H

#include <unit_test.h>

class json_value_test_interface : public unit_test
{
public:

    void test_lookahead ();
    void test_lexeme ();
    void test_is_literal ();

    virtual void test_ctor_dtor () = 0;
    virtual void test_parse_1 () = 0;
    virtual void test_size_1 () = 0;
    virtual void test_at () = 0;
    virtual void test_assign_all_values () = 0;
    virtual void test__at () {}

    /// TODO: test_assign
    virtual void test_value_1 () = 0; /// TODO: remove
    virtual void test_debug_1 () = 0;

protected:

    static const char *_input[];
};

#endif // JSON_VALUE_TEST_H
