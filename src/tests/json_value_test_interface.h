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

    /**
     * @brief test_assign_all_values
     */
    virtual void test_assign_all_values () = 0;

    /**
     * Test with "this" and Value (2 assertions).
     * Node 2 pass
     * Leaf 1 pass, 1 fail
     * @brief test_operator_assign
     */
    virtual void test_operator_assign () = 0;   // =
    virtual void test__clear () = 0;

    /**
     * Test with existing and missing node value (2 assertions).
     * @brief test_operator_at
     */
    virtual void test_operator_at () = 0;       // []

    virtual void test__at () {}

    virtual void test_strLength () = 0;
    virtual void test_strValue () = 0;
    virtual void test_stringify ()  = 0;

    /// TODO: test_assign
    virtual void test_value_1 () = 0; /// TODO: remove
    virtual void test_debug_1 () = 0;

protected:

    static const char *_input[];
};

#endif // JSON_VALUE_TEST_H
