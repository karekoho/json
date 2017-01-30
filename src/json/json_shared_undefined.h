#ifndef SHARED_UNDEFINED_H
#define SHARED_UNDEFINED_H

#include "json_undefined.h"

/**
 * @brief The Shared_Undefined class
 */
class Shared_Undefined : public Undefined
{
public:

  /**
   * @brief ~Shared_Undefined
   */
  virtual ~Shared_Undefined () = default;

  /**
   * @brief operator delete
   */
  void operator delete (void *) noexcept {}

  /**
   * @brief instance
   * @return
   */
  static Shared_Undefined &
  instance ();

protected:

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

  /**
   * @brief Shared_Undefined
   * @param parent
   */
  Shared_Undefined (JSON *parent)
    :  Undefined (parent)
  {
  }
};

/**
 * @brief The No_Value class
 */
class No_Value : public Shared_Undefined
{
public:

  /**
   * @brief type
   * @return
   */
  virtual object_type
  type () const
  { return Value::object_type::novalue; }

  /**
   * @brief instance
   * @param parent
   * @return
   */
  static Value *
  instance (JSON *parent);

private:

  /**
   * @brief No_Value
   */
  No_Value (JSON *parent)
    : Shared_Undefined (parent)
  {}
};

#endif // SHARED_UNDEFINED_H
