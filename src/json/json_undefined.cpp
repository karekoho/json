#include "json_undefined.h"

void * format::undefined::__instance = nullptr;

format::no_value * format::no_value::__instance = nullptr;

format::no_value *
format::no_value::instance (json *parent)
{
  if (__instance == nullptr)
    __instance = new no_value (parent);

  return __instance;
}
