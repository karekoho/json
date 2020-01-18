#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "json_leaf.h"
#include "json_json.h"

namespace format
{
#ifdef UNIT_TEST
  class json_boolean_test;
#endif
   /**
    * @brief The boolean class
    */
    class boolean : public leaf
    {
      friend boolean * __call_boolean (json *parent, bool b);
    #ifdef UNIT_TEST
      friend class json_boolean_test;
    #endif

    public:
     /**
      * @brief Boolean
      */
      boolean ()
        : leaf ()
      {
        _primitive.boolean_value = false;
      }

     /**
      * @brief Boolean
      * @param value
      */
      boolean (const bool value)
        : leaf ()
      {
        _primitive.boolean_value = value;
      }

     /**
      * @brief Boolean
      * @param other
      */
      boolean (const boolean & other) = default;

     /**
      * @brief ~Boolean
      */
      virtual ~boolean () override = default;

     /**
      * @brief clone
      * @param other
      * @return
      */
      virtual value *
      clone () const override
      { return new boolean (*this); }

     /**
      * @brief type
      * @return
      */
      virtual inline value_t
      type () const noexcept override
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
       * @param b
       * @return
       */
      virtual inline value &
      operator =(bool b) override
      {
        _primitive.boolean_value = b;
        return *this;
      }

     /**
      * @brief assign
      * @param nv
      * @return
      */
      value &
      _assign (const boolean & nv)
      { return _parent ? __call__assign (_parent, this, new boolean (nv)) : *(_clone (nv)); }

     /**
      * @brief value
      * @return
      */
      inline bool get () const
      { return _primitive.boolean_value; }

    protected:
     /**
      * @brief _boolean_value
      */

      /**
       * @brief boolean
       * @param parent
       * @param value
       */
      boolean (json *parent, const bool value)
        : leaf (parent)
      {
        _primitive.boolean_value = value;
      }

      /**
       * @brief parse
       * @param json
       * @return
       */
      virtual const wchar_t *
      _parse (const wchar_t *json) override
      { return json + (_primitive.boolean_value == true ? 4 : 5); }

     /**
      * @brief _clear
      */
      virtual void
      _clear () override
      {}

     /**
      * @brief _clone
      * @return
      */
      virtual value *
      _clone (const value &other) override
      {
        _primitive.boolean_value = dynamic_cast<const boolean &>(other)._primitive.boolean_value;
        return this;
      }

      /**
       * @brief strValue
       * @return
       */
       virtual const wchar_t *
       _to_string (wchar_t * = nullptr) const override
       { return _primitive.boolean_value == true ? L"true" : L"false"; }

      /**
       * @brief str_length
       * @return
       */
       virtual size_t
       _str_length () const noexcept override
       { return _primitive.boolean_value == true ? 4 : 5; }
    }; // Class boolean

    inline
    boolean * __call_boolean (json *parent, bool b)
    { return new boolean (parent, b); }
  } // Namespace Format

#endif // BOOLEAN_H
