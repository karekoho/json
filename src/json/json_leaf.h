#ifndef LEAF_H
#define LEAF_H

#include "json_value.h"
namespace Format {
class Leaf : public Value
{
public:

  /**
   * @brief Leaf
   */
  Leaf () : Value ()
  {}

  /**
   * @brief Leaf
   * @param json
   */
  Leaf (const wchar_t *json) : Value (json)
  { _startp = json; }

  /**
   * @brief Leaf
   * @param parent
   */
  Leaf (JSON *parent) : Value (parent)
  {}

  /**
   * @brief Leaf
   * @param other
   */
  Leaf (const Leaf &other) = default;

  /**
   * @brief Leaf
   * @param ov
   * @param nv
   */
  Leaf (const Value *ov, const Leaf &nv)
    : Value (ov, nv)
  {}

  /**
   * @brief ~Leaf
   */
  virtual ~Leaf () = default;

  /**
   * @brief _clone
   * @return
   */
  virtual Value *
  clone  () const override = 0;

  /**
   * @brief parse
   * @param json
   * @return
   */
  virtual const wchar_t *
  parse (const wchar_t *json) = 0;

  /**
   * @brief at
   * @return
   */
  //virtual  Value &
  //at (const wchar_t *) const final override;

  /**
   * @brief at
   * @return
   */
  //virtual Value &
  //at (size_t) const final override;

  /**
   * @brief type
   * @return
   */
  virtual object_type
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
  virtual Value &
  _assign (Value *, Value *) final override
  { return *this; }

  /**
   * @brief isLeaf
   * @return
   */
  virtual bool
  isLeaf () const noexcept final override
  { return true; }

  /**
   * @brief iterator
   * @return
   */
  virtual JSON_Iterator *
  iterator () const final override;

  /**
   * @brief stringify
   * @return
   */
  virtual const wchar_t *
  stringify () noexcept final override
  { return strValue (); }

  /**
   * @brief erase
   * @return
   */
  virtual Value &
  erase (const Value &) noexcept final override
  { return *this; }

  /**
   * @brief The Iterator class
   */
  class Iterator : public std::iterator<
      std::input_iterator_tag,
      Value *,        // Type
      Value *,        // Distance
      Value *,
      Value &
      >
  {
  public:

    /**
     * @brief Iterator
     * @param value
     */
    Iterator (Leaf *value = 0)
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
    Leaf *_value;

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
  virtual Value &
  _at (const wchar_t *) final override;

  /**
   * @brief _at
   * @return
   */
  virtual Value &
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
  virtual Value *
  clone (const Value &) = 0;
};
}
#endif // LEAF_H
