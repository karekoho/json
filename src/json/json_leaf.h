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
    { _startp = json; }

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
     * @brief Leaf
     * @param ov
     * @param nv
     */
    leaf (const value *ov, const leaf &nv)
      : value (ov, nv)
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
    type () const noexcept = 0;

    /**
     * @brief size
     * @return
     */
    virtual size_t
    count () const noexcept final override
    { return 0; }

    /**
     * @brief assign
     * @return
     */
    virtual value &
    _assign (value *, value *) final override
    { return *this; }

    /**
     * @brief isLeaf
     * @return
     */
    virtual bool
    is_leaf () const noexcept final override
    { return true; }

    /**
     * @brief iterator
     * @return
     */
    virtual json_iterator *
    __iterator__ () const final override;

    /**
     * @brief erase
     * @return
     */
    virtual value &
    erase (const value &) noexcept final override
    { return *this; }

    /**
     * @brief The Iterator class
     */
    class iterator : public std::iterator<
        std::input_iterator_tag,
        value *,        // Type
        value *,        // Distance
        value *,
        value &
        >
    {
    public:

      /**
       * @brief Iterator
       * @param value
       */
      iterator (leaf *value = 0)
        : _value (value)
      {}

      /**
       * @brief Iterator
       * @param other
       */
      iterator (const iterator &other) = default;

      /**
        * @brief ~Iterator
        */
      ~iterator () = default;

      /**
       * @brief operator ++
       * @return
       */
      iterator &
      operator ++()
      {
        _value++;
        return *this;
      }

      /**
       * @brief operator ++
       * @return
       */
      iterator
      operator ++(int)
      {
        iterator it (*this);
        ++(*this);
        return it;
      }

      /**
       * @brief operator ==
       * @param rhs
       * @return
       */
      inline bool
      operator ==(const iterator &rhs)
      { return _value == rhs._value; }

      /**
       * @brief operator !=
       * @param rhs
       * @return
       */
      inline bool
      operator !=(const iterator &rhs)
      { return ! operator ==(rhs); }

      /**
       * @brief operator *
       * @return
       */
      reference
      operator *()
      {
        if (_value == 0)
          throw json_out_of_range ("Iterator not derefenceable");

        return *_value;
      }

    protected:

      /**
       * @brief _value
       */
      leaf *_value;

    }; // Iterator

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
     * @brief _clear
     */
    virtual void
    _clear () = 0;

    /**
     * @brief _clone
     * @return
     */
    virtual value *
    _clone (const value &) = 0;
  };
}
#endif // LEAF_H
