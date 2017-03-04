#ifndef JSON_VALUE_TEST_H
#define JSON_VALUE_TEST_H

#include <unit_test.h>

class json_value_test_interface : public unit_test
{
public:

    /**  public abstract value interface */

    /**
     * @brief test_ctor_dtor
     */
    virtual void test_ctor_dtor () = 0;

    /**
     * @brief test_parse_1
     */
    virtual void test_parse_1 () = 0;

    /**
     * @brief test_at
     */
    virtual void test_operator_at_key () = 0;

    /**
     * @brief test_operator_at_index
     */
    virtual void test_operator_at_index () = 0;

    /**
     * @brief test_assign_all_values
     */
    virtual void test_assign_all_values () = 0;

    /**
     * @brief test_strLength
     */
    virtual void test_str_length () = 0;

    /**
     * @brief test_strValue
     */
    virtual void test_str_value () = 0;

    /** protected */

    /**
     *
     * @brief test_erase
     */
    virtual void test_erase () = 0;

    /**
     * @brief test__clear
     */
    virtual void test__clear () = 0;

    /**
     * @brief test_count
     */
    // TODO: virtual void test_count () = 0;

    /**
     * @brief test_type
     */
    // virtual void test_type () = 0;
};

#endif // JSON_VALUE_TEST_H
