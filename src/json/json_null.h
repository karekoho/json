#ifndef NULL_H
#define NULL_H

#include "json_leaf.h"
#include "json_json.h"

namespace format
{
  #ifdef UNIT_TEST
   class json_null_test;
  #endif

  /**
   * @brief The Null class
   */
  class null : public leaf
  {
    #ifdef UNIT_TEST
      friend class json_null_test;
    #endif

    public:

    /**
     * @brief Null
     */
    null ()
      : leaf ()
    {}

    /**
     * @brief Null
     * @param endp
     * @param parent
     * @param charc
     */
    null (json *parent)
      : leaf (parent)
    {}

    /**
     * @brief Null
     * @param other
     */
    null (const null &other) = default;

    /**
     * @brief Null
     * @param ov
     * @param nv
     */
    null (const value *ov, const null &nv)
      : leaf (ov, nv)
    {}

    /**
     * @brief ~null
     */
    virtual ~null () override = default;

    /**
     * @brief clone
     * @param other
     * @return
     */
    virtual value *
    clone () const
    { return new null (*this); }

    /**
     * @brief clone
     * @param ov
     * @return
     */
    virtual value *
    _clone (const value *ov) const override
    { return new null (ov, *this); }

    /**
     * @brief parse
     * @param json
     * @return
     */
    virtual inline const wchar_t *
    _parse (const wchar_t *json) override
    { return json + 4; }

    /**
     * @brief type
     * @return
     */
    virtual inline value::value_t
    type () const noexcept override
    { return value::value_t::null_t; }

    /**
     * TODO: return nullptr
     * @brief Value
     * @return
     */
    inline std::nullptr_t
    get () const noexcept
    { return nullptr; }

    /**
     * @brief operator =
     * @param n
     * @return
     */
    inline value &
    operator =(const null & n)
    { return _assign (n); }

    /**
     * @brief operator =
     * @param v
     * @return
     */
//    inline value &
//    operator =(const value & v)
//    { return value::_assign (v); }

    /**
     * @brief strValue
     * @return
     */
    virtual const wchar_t *
    str_value (wchar_t *) const noexcept override
    { return L"null"; }

    /**
     * @brief strLength
     * @return
     */
    virtual size_t
    str_length () const noexcept override
    { return 4; }

  protected:

    /**
     * @brief assign
     * @param nv
     * @return
     */
    value &
    _assign (const null &)
    { return _parent ? _parent->_assign (this, new null (this, *this)) : *this; }

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
    _clone (const value &) override
    { return this; }

    /**
     * @brief _sizeof
     * @return
     *
    virtual size_t
    _sizeof () const noexcept
    { return sizeof (null); }*/
  };
} // Namespace format

#endif // NULL_H
