#ifndef LEAF_H
#define LEAF_H

#include "json_value.h"

class Leaf : public Value
{
public:

  /**
   * @brief Leaf
   */
  Leaf () : Value () {}

  /**
   * @brief Leaf
   * @param json
   */
  Leaf (const char *json): Value (json) {}

  /**
   * @brief Leaf
   * @param parent
   */
  Leaf (JSON *parent) : Value (parent) {}

  /**
   * @brief Leaf
   * @param other
   */
  Leaf (const Leaf &other) = default;

  /**
   * @brief _clone
   * @return
   */
  virtual Value * _clone  () override = 0;

  /**
   * @brief parse
   * @param json
   * @return
   */
  virtual const char * parse (const char *json) = 0;

  /**
   * @brief at
   * @return
   */
  virtual  Value & at (const char *) const final override;

  /**
   * @brief at
   * @return
   */
  virtual Value & at (size_t) const final override;

  /**
   * @brief type
   * @return
   */
  virtual object_type type () const = 0;

  /**
   * @brief size
   * @return
   */
  virtual size_t count () const final override { return 0; }

  /**
   * @brief assign
   * @return
   */
  virtual Value & assign (Value *, Value *) final override { return *this; }

  /**
   * @brief isLeaf
   * @return
   */
  virtual bool isLeaf () const noexcept final override  { return true; }

protected:

  /**
   * @brief _at
   * @return
   */
  virtual Value &_at (const char *) final override;

  /**
   * @brief _clear
   */
  virtual void _clear () = 0;

  /**
   * @brief _clone
   * @return
   */
  virtual Value *_clone (const Value &) = 0;
};

#endif // LEAF_H
