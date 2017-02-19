#include "json_shared_undefined.h"

using namespace format;

shared_undefined * shared_undefined::__instance = 0;

shared_undefined &
shared_undefined::instance ()
  {
    if (__instance == 0)
      __instance = new shared_undefined ();

    return *__instance;
  }

no_value * no_value::__instance = 0;

value *
no_value::instance (json *parent)
{
  if (__instance == 0)
    __instance = new no_value (parent);

  return __instance;
}
