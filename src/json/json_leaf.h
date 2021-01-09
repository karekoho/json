#ifndef LEAF_H
#define LEAF_H

#include "json_value.h"
#include "json_exception.h"

namespace format
{
  #ifdef UNIT_TEST
    class json_leaf_test;
  #endif

  /**
   * @brief The leaf class
   */
  class leaf : public value
  {
  #ifdef UNIT_TEST
    friend class json_leaf_test;
  #endif
  public:
    /**
     * @brief Leaf
     */
    leaf () : value ()
    {}

    /**
     * @brief Leaf
     * @param json
     */
    leaf (const wchar_t *json) : value (json)
    {}

    /**
     * @brief Leaf
     * @param parent
     */
    leaf (json *parent) : value (parent)
    {}

    /**
     * @brief Leaf
     * @param other
     */
    leaf (const leaf &other) = default;

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
    virtual size_t
    count () const noexcept final override
    { return 0; }

    /**
     * @brief The iterator class
     */
    class iterator : public value::iterator<value *,
        std::input_iterator_tag,
        value *,        // Type
        value *,        // Distance
        value *,
        value &>
    {
    public:
      /**
       * @brief iterator
       * @param value
       */
      iterator (leaf *value = nullptr)
        : value::iterator<format::value *,
          std::input_iterator_tag,
          format::value *,
          format::value *,
          format::value *,
          format::value &>::iterator (value)
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
       * @brief operator *
       * @return
       */
      reference
      operator *()
      {
        if (_it == nullptr)
          throw json_out_of_range ("Iterator not derefenceable");

        return *_it;
      }
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
    _at (const wchar_t *) final override
    { return *this; }

    /**
     * @brief _at
     * @return
     */
    virtual value &
    _at (size_t) final override
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
    _clear () override = 0;

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
}
#endif // LEAF_H
