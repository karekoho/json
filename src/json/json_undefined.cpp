#include "json_undefined.h"

void * format::json::undefined::__instance = nullptr;

format::json::no_value * format::json::no_value::__instance = nullptr;

format::json::no_value *
format::json::no_value::instance (json *parent)
{
  if (__instance == nullptr)
    __instance = new no_value (parent);

  return __instance;
}
