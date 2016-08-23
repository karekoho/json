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

#include "../json/json.h"

#ifndef FN
  #define FN __FUNCTION__
#endif

#ifndef CATCH_ERROR_PCHAR
#define CATCH_ERROR_PCHAR \
  catch (const char *error) { errorc++; std::cerr << error << std::endl; }
#endif

#ifndef PRT_IDX
  #define PRT_IDX (void) sprintf (_sz_idx, "%s: index: %u", FN, idx)
#endif

#ifndef PRT_2IDX
  #define PRT_2IDX (void) sprintf (_sz_idx, "%s: 1. index: %u, 2. index: %u", FN, idx, jdx)
#endif

#ifndef ASSERT_IDX
  #define ASSERT_IDX(cond) \
    PRT_IDX; \
    CPPUNIT_ASSERT_MESSAGE (_sz_idx, (cond))
#endif

#ifndef ASSERT_2IDX
  #define ASSERT_2IDX(cond) \
    PRT_2IDX; \
    CPPUNIT_ASSERT_MESSAGE (_sz_idx, (cond))
#endif

#ifndef ASSERT_NO_ERROR
  #define ASSERT_NO_ERROR \
    (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, errorc); \
    CPPUNIT_ASSERT_MESSAGE (_sz_idx, errorc == 0)
#endif

#ifndef ASSERT_ERRORC
  #define ASSERT_ERRORC(__errorc) \
  (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, errorc); \
  CPPUNIT_ASSERT_MESSAGE (_sz_idx, errorc == __errorc)
#endif


#endif // UNIT_TEST

