#ifndef UNDEFINED_H
#define UNDEFINED_H

#include "json_leaf.h"

namespace format
{
  namespace json
  {
    #ifdef UNIT_TEST
      namespace test
      {
        class undefined_test_ctor_dtor_Test;
        class undefined_test_assign_all_values_Test;
        class undefined_test__parse_Test;
        class undefined_test_str_length_Test;
        class undefined_test__to_string_Test;
      }
    #endif

    /**
     * @brief The undefined class
     */
    class undefined : public leaf
    {
    #ifdef UNIT_TEST
//      friend class test::undefined_test_ctor_dtor_Test;
//      friend class test::undefined_test_assign_all_values_Test;
//      friend class test::undefined_test__parse_Test;
//      friend class test::undefined_test_str_length_Test;
//      friend class test::undefined_test__to_string_Test;
    #endif

      public:
      /**
       * @brief undefined
       */
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
       * @brief ~undefined
       */
      virtual ~undefined () override = default;

      /**
       * @brief operator new
       * @param size
       * @return
       */
      static inline void *
      operator new (std::size_t size)
      {
        if (__instance == nullptr)
          __instance = ::operator new (size);

        return __instance;
      }

      /**
       * @brief operator new[]
       * @param size
       * @return
       */
      static inline void *
      operator new[] (std::size_t size)
      {
        if (__instance == nullptr)
          __instance = ::operator new[] (size);

        return __instance;
      }

      /**
       * @brief operator delete
       */
      void
      operator
      delete (void *)
      {/* nop */}

      /**
       * @brief operator delete[]
       */
      void
      operator
      delete[] (void *)
      {/* nop */}

      /**
       * @brief clone
       * @param other
       * @return
       */
      virtual inline value *
      clone () const override
      { return new undefined (*this); }

      /**
       * @brief get
       * @return
       */
      inline std::nullptr_t
      value () const noexcept
      { return nullptr; }

      /**
       * @deprecated Use value instead
       * @brief get
       * @return
       */
      inline std::nullptr_t
      get () const noexcept
      { return value (); }

      /**
       * @brief parse
       * @param json
       * @return
       */
      virtual inline const wchar_t *
      _parse (const wchar_t * const json) noexcept override
      { return json; }

      /**
       * @brief type
       * @return
       */
      virtual inline value_t
      type () const noexcept override
      { return value::value_t::undefined_t; }

    protected:
      /**
       * @brief _clone
       * @return
       */
      virtual inline class value *
      _clone (const class value &) override
      { return new undefined (*this); }

      /**
       * @brief strValue
       * @return
       */
      virtual inline const wchar_t *
      _to_string (wchar_t * = nullptr) const override
      { return L""; }

      /**
       * @brief str_length
       * @return
       */
      virtual inline size_t
      _str_length () const noexcept override
      { return 0; }

    private:
      /**
       * @brief __instance
       */
      static  void * __instance;
    }; // Class undefined

    /**
     * @brief The unique_undefined class
     */
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
       * @brief unique_undefined
       * @param other
       */
      unique_undefined (const unique_undefined &other) = default;

      /**
       * @brief ~unique_undefined
       */
      virtual ~unique_undefined () override = default;

      /**
       * @brief clone
       * @return
       */
      virtual inline class value *
      clone () const override
      { return new unique_undefined (*this); }

      /**
       * @brief operator new
       * @param size
       * @return
       */
      static inline void *
      operator new (std::size_t size)
      { return ::operator new (size); }

      /**
       * @brief operator new[]
       * @param size
       * @return
       */
      static inline void *
      operator new[] (std::size_t size)
      { return ::operator new[] (size); }

      /**
       * @brief operator delete
       */
      inline void
      operator delete (void *ptr)
      { ::operator delete (ptr); }

      /**
       * @brief operator delete[]
       */
      inline void
      operator delete[] (void *ptr)
      { ::operator delete (ptr); }
    };

    /**
     * @brief The no_value class
     */
    class no_value : public unique_undefined
    {
    public:
      /**
       * @brief operator delete
       */
      void operator delete (void *) {}

      /**
       * @brief operator delete[]
       */
      void operator delete[](void *) {}

      /**
       * @brief ~no_value
       */
      virtual ~no_value () override = default;

      /**
       * @brief type
       * @return
       */
      virtual inline value_t
      type () const noexcept override
      { return value::value_t::no_value_t; }

      /**
       * @brief instance
       * @param parent
       * @return
       */
      static no_value *
      instance (json *parent);

    protected:

      /**
       * @brief No_Value
       */
      no_value (json *parent)
        : unique_undefined (parent)
      {}

    private:
      /**
       * @brief __instance
       */
      static no_value *__instance;
    }; // Class no_value
  } // Namespace json
} // Namespace format
#endif // UNDEFINED_H
