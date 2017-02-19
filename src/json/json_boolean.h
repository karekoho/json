#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "json_leaf.h"
#include "json_json.h"

#ifdef UNIT_TEST
  class json_boolean_test;
#endif

namespace Format
{
  /**
    * @brief The boolean class
    */
    class Boolean : public Leaf
    {
    #ifdef UNIT_TEST
      friend class json_boolean_test;
    #endif

    public:

     /**
      * @brief Boolean
      */
      Boolean ()
        : Leaf (), _boolean_value (false)
      {}

     /**
      * @brief Boolean
      * @param value
      */
      Boolean (const bool value)
        : Leaf (), _boolean_value (value)
      {}

     /**
      * @brief Boolean
      * @param parent
      * @param value
      */
      Boolean (JSON *parent, const bool value)
        : Leaf (parent), _boolean_value (value)
      {}

     /**
      * @brief Boolean
      * @param other
      */
      Boolean (const Boolean &other) = default;

     /**
      * @brief Boolean
      * @param ov
      * @param nv
      */
      Boolean (const Value *ov, const Boolean &nv)
        : Leaf (ov, nv), _boolean_value (nv._boolean_value)
      {}

     /**
      * @brief ~Boolean
      */
      virtual ~Boolean () = default;

     /**
      * @brief clone
      * @param other
      * @return
      */
      virtual Value *
      clone () const
      { return new Boolean (*this); }

     /**
      * @brief clone
      * @param ov
      * @return
      */
      virtual Value *
      clone (const Value *ov) const override
      { return new Boolean (ov, *this); }

      /**
   * @brief strLength
   * @return
   */
      virtual size_t
      strLength () const noexcept override
      { return _boolean_value == true ? 4 : 5; }

      /**
   * @brief strValue
   * @return
   */
      virtual const wchar_t *
      strValue (wchar_t * = 0) const override
      { return _boolean_value == true ? L"true" : L"false"; }

    public:

      /**
   * @brief parse
   * @param json
   * @return
   */
      virtual const wchar_t *
      parse (const wchar_t *json)
      { return json + (_boolean_value == true ? 4 : 5); }

      /**
   * @brief type
   * @return
   */
      virtual inline object_type
      type () const
      { return Value::object_type::boolean_t; }

      /**
   * @brief operator =
   * @param b
   * @return
   */
      inline Value &
      operator =(Boolean & b)
      { return _assign (b); }

      /**
   * @brief operator =
   * @param v
   * @return
   */
      inline Value &
      operator =(const Value & v)
      { return Value::_assign (v); }

      /**
   * @brief assign
   * @param nv
   * @return
   */
      Value &
      _assign (const Boolean & nv)
      { return _parent ? _parent->_assign (this, new Boolean (nv)) : *(clone (nv)); }

      /**
   * @brief value
   * @return
   */
      inline bool value () const
      { return _boolean_value; }

      /**
   * @brief setValue
   * @param value
   */
      void setValue (bool value)
      { _boolean_value = value; }

    protected:

      /**
   * @brief _boolean_value
   */
      bool _boolean_value;

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
      virtual Value *
      clone (const Value &other) override
      {
        _boolean_value = dynamic_cast<const Boolean &>(other)._boolean_value;
        return this;
      }
    };
  } // Namespace Format

#endif // BOOLEAN_H
