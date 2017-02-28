#ifndef LEAF_H
#define LEAF_H

#include "json_value.h"

namespace format
{
#ifdef UNIT_TEST
  class json_leaf_test;
#endif
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
  virtual ~leaf () = default;

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
  type () const = 0;

  /**
   * @brief size
   * @return
   */
  virtual size_t
  count () const final override
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
  iterator () const final override;

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
  class Iterator : public std::iterator<
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
    Iterator (leaf *value = 0)
      : _value (value)
    {}

    /**
     * @brief Iterator
     * @param other
     */
    Iterator (const Iterator &other) = default;

    /**
      * @brief ~Iterator
      */
    ~Iterator () = default;

    /**
     * @brief operator ++
     * @return
     */
    Iterator &
    operator ++()
    {
      _value++;
      return *this;
    }

    /**
     * @brief operator ++
     * @return
     */
    Iterator
    operator ++(int)
    {
      Iterator it (*this);
      ++(*this);
      return it;
    }

    /**
     * @brief operator ==
     * @param rhs
     * @return
     */
    inline bool
    operator ==(const Iterator &rhs)
    { return _value == rhs._value; }

    /**
     * @brief operator !=
     * @param rhs
     * @return
     */
    inline bool
    operator !=(const Iterator &rhs)
    { return ! operator ==(rhs); }

    /**
     * @brief operator *
     * @return
     */
    reference
    operator *()
    {
      if (_value == 0)
        throw "iterator not derefenceable";   // TODO: throw out_of_range

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
  Iterator
  begin ()
  { return Iterator (this); }

  /**
   * @brief end
   * @return
   */
  Iterator
  end ()
  { return Iterator (this + 1); }

protected:

  /**
   * @brief _at
   * @return
   */
  virtual value &
  _at (const wchar_t *) final override;

  /**
   * @brief _at
   * @return
   */
  virtual value &
  _at (size_t) final override;

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
  clone (const value &) = 0;
};
}
#endif // LEAF_H
