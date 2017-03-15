#include "json_undefined.h"

void * format::undefined::__instance = 0;

format::no_value * format::no_value::__instance = 0;

format::no_value *
format::no_value::instance (json *parent)
{
  if (__instance == 0)
    __instance = new no_value (parent);

  return __instance;
}
