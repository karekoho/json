#ifndef SHARED_UNDEFINED_H
#define SHARED_UNDEFINED_H

#include "json_undefined.h"

class Shared_Undefined : public Undefined
{
public:

  /**
   * @brief ~Shared_Undefined
   */
  virtual ~Shared_Undefined () = default;

  /**
   * @brief instance
   * @return
   */
  static Shared_Undefined &
  instance ()
  {
    if (__instance == 0)
      __instance = new Shared_Undefined ();

    return *__instance;
  }

private:

  /**
   * @brief __instance
   */
  static Shared_Undefined *__instance;

  /**
   * @brief Shared_Undefined
   */
  Shared_Undefined ()
    : Undefined ()
  {
  }
};

Shared_Undefined * Shared_Undefined::__instance = 0;

#endif // SHARED_UNDEFINED_H
