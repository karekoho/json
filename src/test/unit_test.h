#ifndef UNIT_TEST
#define UNIT_TEST

#include <cstdio>
#include <ctype.h>
#include <vector>
#include <cstring>
#include <array>
#include <wchar.h>
#include <clocale>
#include <algorithm>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../json/json.h"

using ::testing::Eq;
using ::testing::Ne;
using ::testing::Lt;
using ::testing::Gt;
using ::testing::StrEq;
using ::testing::IsTrue;
using ::testing::IsFalse;
using ::testing::FloatEq;
using ::testing::DoubleEq;
using ::testing::Address;
using ::testing::FieldsAre;

#define PASS_T  0
#define FAIL_T  1
#define SKIP_T -1
#define MEM_DEBUG 0

#define EXPECTED 0
#define ACTUAL 1

#ifndef FN
  #define FN __FUNCTION__
#endif

#ifndef ERR_IDX_MSG
  #define  ERR_IDX_MSG "Error at index: "
#endif

#ifndef TEST_IT_START
  #define TEST_IT_START\
  \
  for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++) {\
    try {\
        if ((*it).assert_status == SKIP_T) { continue; }\
        if ((*it).assert_status > PASS_T) { this->_errorc[EXPECTED]++; }
#endif

#ifndef TEST_IT_END
  #define TEST_IT_END\
  \
} catch (format::json::json_syntax_error & e) { this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl; }\
  catch (format::json::json_out_of_range & e) { this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl; }\
  catch (format::json::json_error & e) { this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl; }\
  catch (std::exception & e) { this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl; }\
  catch (const char *error) { this->_errorc[ACTUAL]++; std::cerr << error << std::endl; }\
  catch (const wchar_t *error) { this->_errorc[ACTUAL]++; std::cerr << error << std::endl; }\
  catch (...) { this->_errorc[ACTUAL]++; std::cerr << "unknown exception" << std::endl; } }\
EXPECT_EQ (this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
#endif

/**
 * @brief The unit_test class
 */
class unit_test : public ::testing::Test
{

public:
  unit_test ()
    : _errorc { 0, 0 },
      _idx { 0, 0, 0, 0, 0 }
  {}

  virtual void
  setUp ()
  {
    // std::setlocale(LC_ALL, "en_US.UTF-8");
    std::setlocale (LC_CTYPE, "");
    _errorc[0] = _errorc[1] = 0;
    _idx[0] = _idx[1] = _idx[2] = _idx[3] = _idx[4] =  0;
  }

  virtual void
  tearDown ()
  { _errorc[0] =_errorc[1] = 0;
    _idx[0] = _idx[1] = _idx[2] = _idx[3] = _idx[4] =  0;
  }

  std::unordered_map<std::wstring, format::json::value *> &
  member_list_clear (std::unordered_map<std::wstring, format::json::value *> & m)
  {
    for (auto it = m.begin (); it != m.end (); it = m.erase (it))
      delete static_cast <std::pair<std::wstring, format::json::value *>>(*it).second;

    return m;
  }

  std::vector<format::json::value *> &
  element_list_clear (std::vector<format::json::value *> & v)
  {
    for (auto it = v.begin (); it != v.end (); it = v.erase (it))
      delete *it;

    return v;
  }

protected:

  size_t _errorc[2];
  size_t _idx[5];

  static format::json::json   *__JSON;
  static format::json::value  *__VALUE[];
}; // Class unit_test

/**
 * @brief The value_accessor class
 */
class value_accessor : public format::json::value
{
public:
  /**
   * @brief set_parent
   * @param parent
   */
  void set_parent (format::json::json *parent)
  { _set_parent (parent); }
};





/**
 * @brief The string_accessor class
 */
class string_accessor : public format::json::string
{
public:
  /**
   * @brief string_accessor
   * @param parent
   * @param charc
   */
  string_accessor (format::json::json *parent, size_t charc)
    : string (parent,charc){}
};

/**
 * @brief The number_accessor class
 */
class number_accessor : public format::json::number
{
public:
  /**
   * @brief number_accessor
   * @param parent
   */
  number_accessor (format::json::json *parent) : number (parent){}
};

/**
 * @brief The null_accessor class
 */
class null_accessor: public format::json::null
{
public:
  /**
   * @brief null_accessor
   * @param parent
   */
  null_accessor (format::json::json *parent): null (parent){}
};

/**
 * @brief The boolean_accessor class
 */
class boolean_accessor: public format::json::boolean
{
public:
  /**
   * @brief boolean_accessor
   * @param parent
   * @param b
   */
  boolean_accessor (format::json::json *parent, bool b): boolean (parent, b)
  {}
};

format::json::json * unit_test::__JSON = new format::json::json ();

format::json::value * unit_test::__VALUE[] = {
      format::json::no_value::instance (unit_test::__JSON),
      new format::json::unique_undefined (),
      new format::json::object (),
      new format::json::array (),
      new format::json::string (),
      new format::json::number (),
      new format::json::boolean (),
      new format::json::null ()
};

#endif // UNIT_TEST

