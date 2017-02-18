#include "json_shared_undefined.h"

Shared_Undefined * Shared_Undefined::__instance = 0;

Shared_Undefined &
Shared_Undefined::instance ()
  {
    if (__instance == 0)
      __instance = new Shared_Undefined ();

    return *__instance;
  }

Value *
No_Value::instance (JSON *parent)
{
  if (__instance == 0)
    __instance = new No_Value (parent);

  return __instance;
}
