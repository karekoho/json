#ifndef UNDEFINED_H
#define UNDEFINED_H

#include "json_leaf.h"

namespace format
{
  #ifdef UNIT_TEST
    class json_undefined_test;
  #endif

  /**
   * @brief The undefined class
   */
  class undefined : public leaf
  {
  #ifdef UNIT_TEST
    friend class json_undefined_test;
  #endif

    public:

    undefined ()
      : leaf ()
    {}

    /**
     * @brief Undefined
     * @param parent
     */
    undefined (json *parent)
      : leaf (parent)
    {}

    /**
     * @brief Undefined
     * @param other
     */
    undefined (const undefined &other) = default;

    /**
     * @brief Undefined
     * @param ov
     * @param nv
     */
    undefined (const value *ov, const undefined &nv)
      : leaf (ov, nv)
    {}

    /**
     * @brief ~undefined
     */
    virtual ~undefined () override = default;

    /**
     * @brief operator new
     * @param size
     * @return
     */
    static void *
    operator new (std::size_t size)
    {
      if (__instance == 0)
        __instance = ::operator new (size);

      return __instance;
    }

    /**
     * @brief operator new[]
     * @param size
     * @return
     */
    static void *
    operator new[] (std::size_t size)
    {
      if (__instance == 0)
        __instance = ::operator new[] (size);

      return __instance;
    }

    /**
     * @brief operator delete
     */
    void operator
    delete (void *)
    {/* nop */}

    /**
     * @brief operator delete[]
     */
    void operator
    delete[] (void *)
    {/* nop */}

    /**
     * @brief clone
     * @param other
     * @return
     */
    virtual value *
    clone () const
    { return new undefined (*this); }

    /**
     * @brief clone
     * @param ov
     * @return
     */
    virtual value *
    _clone (const value *ov) const override
    { return new undefined (ov, *this); }

    /**
     * TODO: return nullptr
     * @brief value
     * @return
     */
    inline std::nullptr_t
    get () const noexcept
    { return nullptr; }

    /**
     * @brief parse
     * @param json
     * @return
     */
    virtual const wchar_t *
    _parse (const wchar_t *json) override
    { return json; }

    /**
     * @brief type
     * @return
     */
    virtual inline value_t
    type () const noexcept override
    { return value::value_t::undefined_t; }

    /**
     * @brief strLength
     * @return
     */
    virtual size_t
    str_length () const noexcept override
    { return 0; }

    /**
     * @brief strValue
     * @return
     */
    virtual const wchar_t *
    str_value (wchar_t * = 0) const override
    { return L""; }

  protected:

    /**
     * @brief _clear
     */
    virtual void
    _clear ()
    {}

    /**
     * @brief _clone
     * @return
     */
    virtual value *
    _clone (const value &) override
    { return new undefined (*this); }

    /**
     * @brief _sizeof
     * @return
     */
    virtual size_t
    _sizeof () const noexcept
    { return sizeof (undefined); }

  private:
    /**
     * @brief __instance
     */
    static  void * __instance;
  }; // Class undefined

  class unique_undefined : public undefined
  {
  public:
    /**
     * @brief unique_undefined
     */
    unique_undefined ()
     : undefined ()
    {}

    /**
     * @brief unique_undefined
     * @param parent
     */
    unique_undefined (json *parent)
     : undefined (parent)
    {}

    /**
     * @brief Undefined
     * @param other
     */
    unique_undefined (const unique_undefined &other) = default;

    /**
     * @brief Undefined
     * @param ov
     * @param nv
     */
    unique_undefined (const value *ov, const unique_undefined &nv)
      : undefined (ov, nv)
    {}

    /**
     * @brief clone
     * @return
     */
    virtual value *
    clone () const
    { return new unique_undefined (*this); }

    /**
     * @brief operator new
     * @param size
     * @return
     */
    static void *
    operator new (std::size_t size)
    { return ::operator new (size); }

    /**
     * @brief operator new[]
     * @param size
     * @return
     */
    static void *
    operator new[] (std::size_t size)
    { return ::operator new[] (size); }

    /**
     * @brief operator delete
     */
    void operator
    delete (void *ptr)
    { ::operator delete (ptr); }

    /**
     * @brief operator delete[]
     */
    void operator
    delete[] (void *ptr)
    { ::operator delete (ptr); }

    protected:
    /**
     * @brief clone
     * @param ov
     * @return
     */
    virtual value *
    _clone (const value *ov) const override
    { return new unique_undefined (ov, *this); }
  };
} // Namespace format
#endif // UNDEFINED_H
