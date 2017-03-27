#ifndef UNIT_TEST
#define UNIT_TEST

#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Exception.h>
#include <cstdio>
#include <ctype.h>
#include <vector>
#include <cstring>
#include <array>
#include <wchar.h>

#include "../json/json.h"

#define PASS  0
#define FAIL  1
#define SKIP -1

#define EXPECTED 0
#define ACTUAL 1

#ifndef FN
  #define FN __FUNCTION__
#endif

#ifndef CATCH_ERROR_PCHAR
#define CATCH_ERROR_PCHAR\
  catch (const char *error) { errorc++; std::cerr << error << std::endl; }
#endif

#ifndef PRT_IDX
  #define PRT_IDX (void) sprintf (_sz_idx, "%s: index: %u", FN, idx)
#endif

#ifndef PRT_2IDX
  #define PRT_2IDX (void) sprintf (_sz_idx, "%s: 1. index: %u, 2. index: %u", FN, idx, jdx)
#endif

#ifndef ASSERT_IDX
  #define ASSERT_IDX(cond)\
    PRT_IDX;\
    CPPUNIT_ASSERT_MESSAGE (_sz_idx, (cond))
#endif

#ifndef ASSERT_2IDX
  #define ASSERT_2IDX(cond)\
    PRT_2IDX;\
    CPPUNIT_ASSERT_MESSAGE (_sz_idx, (cond))
#endif

#ifndef ASSERT_NO_ERROR
  #define ASSERT_NO_ERROR\
    (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, errorc);\
    CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, 0, errorc)
#endif

#ifndef ASSERT_ERRORC
  #define ASSERT_ERRORC(__errorc)\
  (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, errorc);\
  CPPUNIT_ASSERT_MESSAGE (_sz_idx, errorc == __errorc)
#endif

#ifndef ASSERT_EQUAL_IDX
  #define ASSERT_EQUAL_IDX(message, expected, actual)\
  (void) sprintf (_sz_idx, "%s: idx[0] = %lu: %s", FN, this->_idx[0], message);\
  CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, expected, actual)
#endif

#ifndef TEST_IT_START
  #define TEST_IT_START\
  \
  for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++) {\
    try {\
        if ((*it).assert_status == SKIP) { continue; }\
        if ((*it).assert_status > PASS) { this->_errorc[EXPECTED]++; }
#endif

#ifndef TEST_IT_END
  #define TEST_IT_END\
  \
} catch (format::json_syntax_error & se) { this->_errorc[ACTUAL]++; std::cerr << se.what () << std::endl; }\
  catch (format::json_out_of_range & oor) { this->_errorc[ACTUAL]++; std::cerr << oor.what () << std::endl; }\
  catch (format::json_error & e) { this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl; }\
  catch (const char *error) { this->_errorc[ACTUAL]++; std::cerr << error << std::endl; } \
  catch (const wchar_t *error) { this->_errorc[ACTUAL]++; std::cerr << error << std::endl; } }\
(void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]); \
CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
#endif

class test_selector;
/**
 * @brief The unit_test class
 */
class unit_test : public CppUnit::TestFixture
{
  friend class test_selector;

public:
  unit_test ()
    : CppUnit::TestFixture(),
      _errorc { 0, 0 },
      _idx { 0, 0, 0, 0, 0 }
  {}

  // virtual ~unit_test (){ std::cerr << "delete" << std::endl; }

  void
  setUp ()
  { _errorc[0] = _errorc[1] = _idx[0] = _idx[1] = _idx[2] = _idx[3] = _idx[4] =  0; }

  void
  tearDown ()
  { _errorc[0] =_errorc[1] = _idx[0] = _idx[1] = _idx[2] = _idx[3] = _idx[4] =  0; }

  std::unordered_map<std::wstring, format::value *> &
  member_list_clear (std::unordered_map<std::wstring, format::value *> & m)
  {
    for (auto it = m.begin (); it != m.end (); it = m.erase (it))
      delete static_cast <std::pair<std::wstring, format::value *>>(*it).second;

    return m;
  }

  std::vector<format::value *> &
  element_list_clear (std::vector<format::value *> & v)
  {
    for (auto it = v.begin (); it != v.end (); it = v.erase (it))
      delete *it;

    return v;
  }

protected:

  size_t _errorc[2];
  size_t _idx[5];

  char _sz_idx[300];

  static format::json   *__JSON;
  static format::value  *__VALUE[];
}; // Class unit_test

/**
 * @brief The value_accessor class
 */
class value_accessor : public format::value
{
public:
  /**
   * @brief set_parent
   * @param parent
   */
  void set_parent (format::json *parent)
  { _set_parent (parent); }
};

/**
 * @brief The object_accessor class
 */
class object_accessor : public format::object
{
public:
  /**
   * @brief object_accessor
   */
  object_accessor () : object () {}

  /**
   * @brief object_accessor
   * @param input
   */
  object_accessor (const wchar_t *input) : object (input) {}

  /**
   * @brief object_accessor
   * @param parent
   */
  object_accessor (json *parent) : object (parent){}

  /**
   * @brief begin
   * @return
   */
  std::unordered_map<std::wstring, value *>::iterator
  begin ()
  { return _member_list.begin (); }

  /**
   * @brief end
   * @return
   */
  std::unordered_map<std::wstring, value *>::iterator
  end ()
  { return _member_list.end (); }

  /**
   * @brief clear
   */
  void
  clear ()
  { _clear (); }

  /**
   * @brief _clear
   */
  void
  _clear ()
  { _member_list.clear (); }

  /**
   * @brief assign
   * @param ov
   * @param nv
   * @return
   */
  value & assign (value *ov, value *nv)
  { return _assign (ov, nv); }

};  // Class object_accessor

/**
 * @brief The array_accessor class
 */
class array_accessor : public format::array
{
  public:

  /**
   * @brief array_accessor
   */
  array_accessor () : array () {}

  /**
   * @brief array_accessor
   * @param input
   */
  array_accessor (const wchar_t *input) : array (input) {}

  /**
   * @brief push
   * @param v
   */
  size_t push (format::value *v)
  {
    _element_list.push_back (v);
    return _element_list.size () - 1;
  }

  /**
   * @brief assign
   * @param ov
   * @param nv
   * @return
   */
  value & assign (value *ov, value *nv)
  { return _assign (ov, nv); }

  /**
   * @brief clear
   */
  void
  clear ()
  { _clear (); }

  /**
   * @brief _clear
   */
  void
  _clear ()
  { _element_list.clear (); }

  /**
   * @brief begin
   * @return
   */
  std::vector<value *>::iterator
  begin ()
  { return _element_list.begin (); }

  /**
   * @brief end
   * @return
   */
  std::vector<value *>::iterator
  end ()
  { return _element_list.end (); }
};  // Class array_accessor

/**
 * @brief The string_accessor class
 */
class string_accessor : public format::string
{
public:
  /**
   * @brief string_accessor
   * @param parent
   * @param charc
   */
  string_accessor (format::json *parent, size_t charc)
    : string (parent,charc){}
};

format::json * unit_test::__JSON = new format::json ();

format::value * unit_test::__VALUE[] = {
     format::no_value::instance (unit_test::__JSON),
      new format::unique_undefined (),
      new format::object (),
      new format::array (),
      new format::string (),
      new format::number (),
      new format::boolean (),
      new format::null (),
};

#endif // UNIT_TEST

