#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "json_leaf.h"
#include "json_json.h"

#ifdef UNIT_TEST
  class json_boolean_test;
#endif

namespace format
{
  /**
    * @brief The boolean class
    */
    class boolean : public leaf
    {
    #ifdef UNIT_TEST
      friend class json_boolean_test;
    #endif

    public:

     /**
      * @brief Boolean
      */
      boolean ()
        : leaf (), _boolean_value (false)
      {}

     /**
      * @brief Boolean
      * @param value
      */
      boolean (const bool value)
        : leaf (), _boolean_value (value)
      {}

     /**
      * @brief Boolean
      * @param parent
      * @param value
      */
      boolean (json *parent, const bool value)
        : leaf (parent), _boolean_value (value)
      {}

     /**
      * @brief Boolean
      * @param other
      */
      boolean (const boolean &other) = default;

     /**
      * @brief Boolean
      * @param ov
      * @param nv
      */
      boolean (const value *ov, const boolean &nv)
        : leaf (ov, nv), _boolean_value (nv._boolean_value)
      {}

     /**
      * @brief ~Boolean
      */
      virtual ~boolean () = default;

     /**
      * @brief clone
      * @param other
      * @return
      */
      virtual value *
      clone () const
      { return new boolean (*this); }

     /**
      * @brief clone
      * @param ov
      * @return
      */
      virtual value *
      clone (const value *ov) const override
      { return new boolean (ov, *this); }

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
      _parse (const wchar_t *json)
      { return json + (_boolean_value == true ? 4 : 5); }

      /**
   * @brief type
   * @return
   */
      virtual inline value_t
      type () const
      { return value::value_t::boolean_t; }

      /**
   * @brief operator =
   * @param b
   * @return
   */
      inline value &
      operator =(boolean & b)
      { return _assign (b); }

      /**
   * @brief operator =
   * @param v
   * @return
   */
      inline value &
      operator =(const value & v)
      { return value::_assign (v); }

      /**
   * @brief assign
   * @param nv
   * @return
   */
      value &
      _assign (const boolean & nv)
      { return _parent ? _parent->_assign (this, new boolean (nv)) : *(clone (nv)); }

      /**
   * @brief value
   * @return
   */
      inline bool get () const
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
      virtual value *
      clone (const value &other) override
      {
        _boolean_value = dynamic_cast<const boolean &>(other)._boolean_value;
        return this;
      }
    };
  } // Namespace Format

#endif // BOOLEAN_H
