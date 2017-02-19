#include "json_shared_undefined.h"

using namespace Format;

Shared_Undefined * Shared_Undefined::__instance = 0;

Shared_Undefined &
Shared_Undefined::instance ()
  {
    if (__instance == 0)
      __instance = new Shared_Undefined ();

    return *__instance;
  }

No_Value * No_Value::__instance = 0;

Value *
No_Value::instance (json *parent)
{
  if (__instance == 0)
    __instance = new No_Value (parent);

  return __instance;
}
