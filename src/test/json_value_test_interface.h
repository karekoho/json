#ifndef JSON_VALUE_TEST_H
#define JSON_VALUE_TEST_H

#include "unit_test.h"

/**
 * @brief The json_value_test_interface class
 * Test virtual methods of format::value
 */
class json_value_test_interface : public unit_test
{
public:
    /**  public abstract value interface */
    /**
     * @brief test_ctor_dtor
     */
    virtual void test_ctor_dtor () = 0;

    /**
     * @brief test_operator_at_key
     *
     * value & operator[] (const wchar_t *key)
     * virtual value & _at (const wchar_t *key) = 0
     */
    virtual void test_operator_at_key () = 0;

    /**
     * @brief test_const_operator_at_key
     */
    virtual void test_const_operator_at_key () = 0;

    /**
     * @brief test_operator_at_index
     *
     * value & operator[] (size_t index)
     * virtual value & _at (size_t index) = 0
     */
    virtual void test_operator_at_index () = 0;

    virtual void test_const_operator_at_index () = 0;

    /**
     * @brief test_assign_all_values
     *
     * value & operator= (value *v)
     * value & _assign (value *nv)
     */
    virtual void test_assign_all_values () = 0;

    /**
    * @brief test_length
    *
    * virtual size_t length () const noexcept = 0
    */
    virtual void test_count() = 0;

    /**
     * @brief test_str_length
     *
     * virtual size_t 	str_length () const noexcept = 0
     */
    virtual void test_str_length () = 0;

    /**
     * Asserted in test_ctor_dtor
     *
     * @brief test_type
     */
    virtual void test_type () = 0;

   /** protected */
   /**
    * @brief test_parse
    *
    * virtual const wchar_t * _parse (const wchar_t *json) = 0
    */
    virtual void test__parse () = 0;

    /**
     * @brief test_erase
     */
    virtual void test__erase () = 0;

    /**
     * @brief test__clear
     */
    virtual void test__clear () = 0;

    /**
     * @brief test__to_string
     */
    virtual void test__to_string () = 0;

    /**
     * @brief void_test__assign_value_ptr_value_ptr
     *
     * virtual value & _assign (value *, value *) = 0
     */
    virtual void test__assign_value_ptr_value_ptr () = 0;

    /**
     * @brief void_test__clone_const_value_ref
     *
     * virtual value * _clone (const value &other) = 0
     */
    virtual void test__clone_const_value_ref () = 0;
};

#endif // JSON_VALUE_TEST_H
