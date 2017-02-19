#ifndef SHARED_UNDEFINED_H
#define SHARED_UNDEFINED_H

#include "json_undefined.h"
namespace Format {
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

private:

  /**
   * @brief __instance
   */
  static Shared_Undefined *__instance;
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
  { return Value::object_type::no_value_t; }

  /**
   * @brief instance
   * @param parent
   * @return
   */
  static Value *
  instance (JSON *parent);

protected:

  /**
   * @brief No_Value
   */
  No_Value (JSON *parent)
    : Shared_Undefined (parent)
  {}

private:

  /**
   * @brief __instance
   */
  static No_Value *__instance;
};
}
#endif // SHARED_UNDEFINED_H
