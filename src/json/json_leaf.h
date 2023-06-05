#ifndef LEAF_H
#define LEAF_H

#include "json_value.h"
#include "json_exception.h"

namespace format
{
  namespace json
  {
    /**
     * @brief The leaf class
     */
    class leaf : public value
    {
    public:
      /**
       * @brief Leaf
       */
      leaf () : value ()
      {}

      /**
       * @brief leaf
       * @param b
       */
      leaf (bool b) : value (b)
      {}

      /**
       * @brief leaf
       * @param ld
       */
      leaf (long double ld, long double) : value (ld)
      {}

      /**
       * @brief Leaf
       * @param json
       */
      leaf (const wchar_t * const json_text) : value (json_text)
      {}

      /**
       * @brief Leaf
       * @param parent
       */
      leaf (json *parent) : value (parent)
      {}

      /**
       * @brief Leaf
       * @param parent
       */
      leaf (json *parent, long double ld) : value (parent, ld)
      {}

      /**
       * @brief leaf
       * @param parent
       * @param charc
       */
      leaf (json *parent, size_t charc) : value (parent, charc)
      {}

      /**
       * @brief leaf
       * @param parent
       * @param b
       */
      leaf (json *parent, bool b) : value (parent, b)
      {}

      /**
       * @brief Leaf
       * @param other
       */
      leaf (const leaf &other) : value (other)
      {}

      leaf (leaf&& other) : value (other)
      {}

      /**
       * @brief ~Leaf
       */
      virtual ~leaf () override = default;

      /**
       * @brief _clone
       * @return
       */
      virtual value *
      clone  () const override = 0;

      /**
       * @brief type
       * @return
       */
      virtual value_t
      type () const noexcept override = 0;

      /**
       * @brief size
       * @return
       */
      virtual inline size_t
      size () const noexcept final override
      { return 0; }

      virtual inline const wchar_t *
      stringify () const final override
      {
        try
          {
            size_t length = _str_length ();
            return wcsncpy (new wchar_t[length + 1] (), _to_string (), length);
          } catch (const std::exception & e) {
            throw json_error (e.what ());
          }
      }

      /**
       * @brief The iterator class
       */
      class iterator : public value::iterator<value *,
          std::input_iterator_tag,
          value,        // Type
          value,        // Distance
          value *,
          value &>
      {
      public:
        /**
         * @brief iterator
         * @param value
         */
        iterator (leaf *value = nullptr)
          : value::iterator<format::json::value *,
            std::input_iterator_tag,
            format::json::value,
            format::json::value,
            format::json::value *,
            format::json::value &>::iterator (value)
        {}

        /**
         * @brief iterator
         * @param other
         */
        iterator (const iterator &other) = default;

        /**
         * @brief ~iterator
         */
        virtual ~iterator () = default;

        /**
         * @brief Get reference to the value pointed by iterator
         * @return
         */
        reference
        operator *() const
        {
          if (_it == nullptr)
            throw json_out_of_range ("Iterator not derefenceable");

          return *_it;
        }

        /**
         * @brief Get pointer to the value pointed by iterator
         * @return
         */
        pointer
        operator ->() const noexcept
        { return _it; }

      }; // Class iterator

      /**
       * @brief begin
       * @return
       */
      iterator
      begin ()
      { return iterator (this); }

      /**
       * @brief end
       * @return
       */
      iterator
      end ()
      { return iterator (this + 1); }

    protected:

      /**
       * @brief _at
       * @return
       */
      virtual value &
      _at (const wchar_t * const) final override
      { return *this; }

      /**
       * @brief _at
       * @return
       */
      virtual const value &
      _at (const wchar_t * const) const final override
      { return *this; }

      /**
       * @brief _at
       * @return
       */
      virtual value &
      _at (size_t) final override
      { return *this; }

      /**
       * @brief _at
       * @return
       */
      virtual const value &
      _at (size_t) const final override
      { return *this; }

      /**
       * @brief assign
       * @return
       */
      virtual value &
      _assign (value *, value *) final override
      { return *this; }

      /**
       * @brief _clear
       */
      virtual void
      _clear () final override
      { /* nop */ }

      /**
       * @brief _erase
       * @return
       */
      virtual value &
      _erase (const value &) noexcept final override
      { return *this; }

      /**
       * @brief _clone
       * @return
       */
      virtual value *
      _clone (const value &) override = 0;
    };
  } // Namespace json
} // Namespace format
#endif // LEAF_H
