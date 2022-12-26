#include "unit_test.h"
#include "json_value_test.h"
#include "json_test.h"
#include "json_object_test.h"
#include "json_array_test.h"
#include "json_string_test.h"
#include "json_number_test.h"
#include "json_boolean_test.h"
//#include "json_null_test.h"
//#include "json_undefined_test.h"
//#include "json_leaf_test.h"
//#include "json_object_iterator_test.h"
//#include "json_array_iterator_test.h"
//#include "json_leaf_iterator_test.h"
//#include "test_selector_test.h"
//#include "json_exception_test.h"

//#include <cstdlib>

int
main (int argc, char *argv[])
{
  ::testing::InitGoogleTest (& argc, argv);
  // testing::GTEST_FLAG (filter) = "-json_pointer_test.point";
  return RUN_ALL_TESTS ();
}

