#ifndef SHARED_UNDEFINED_H
#define SHARED_UNDEFINED_H

#include "json_undefined.h"

namespace format
{
  /**
   * @brief The Shared_Undefined class
   */
  class shared_undefined : public unique_undefined
  {
  public:

    /**
     * @brief ~Shared_Undefined
     */
    virtual ~shared_undefined () = default;

    /**
     * @brief operator delete
     */
    void operator delete (void *) noexcept {}

    /**
     * @brief instance
     * @return
     */
    static shared_undefined &
    instance ();

  protected:

    /**
     * @brief Shared_Undefined
     */
    shared_undefined ()
      : unique_undefined ()
    {
    }

    /**
     * @brief Shared_Undefined
     * @param parent
     */
    shared_undefined (json *parent)
      :  unique_undefined (parent)
    {
    }

  private:

    /**
     * @brief __instance
     */
    static shared_undefined *__instance;
  };

  /**
   * @brief The No_Value class
   */
  class no_value : public shared_undefined
  {
  public:

    /**
     * @brief ~no_value
     */
    virtual ~no_value () = default;

    /**
     * @brief type
     * @return
     */
    virtual value_t
    type () const noexcept override
    { return value::value_t::no_value_t; }

    /**
     * @brief instance
     * @param parent
     * @return
     */
    static value *
    instance (json *parent);

  protected:

    /**
     * @brief No_Value
     */
    no_value (json *parent)
      : shared_undefined (parent)
    {}

  private:

    /**
     * @brief __instance
     */
    static no_value *__instance;
  };
} // Namespace format

#endif // SHARED_UNDEFINED_H
