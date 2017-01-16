#include "json_shared_undefined.h"

Shared_Undefined * Shared_Undefined::__instance = 0;

Shared_Undefined &
Shared_Undefined::instance ()
  {
    if (__instance == 0)
      __instance = new Shared_Undefined ();

    return *__instance;
  }

 Shared_Undefined::Shared_Undefined ()
  : Undefined ()
 {
 }
