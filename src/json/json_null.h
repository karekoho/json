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
   * @brief The null class
   */
  class null : public leaf
  {
    friend null * __call_null (json *);

    #ifdef UNIT_TEST
      friend class json_null_test;
    #endif

    public:
    /**
     * @brief null
     */
    null ()
      : leaf ()
    {}

    /**
     * @brief Null
     * @param other
     */
    null (const null &other) = default;

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
     * @brief _parse
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
     * @return
     */
    inline value &
    operator =(std::nullptr_t)
    { return *this; }

    /**
     * @brief strLength
     * @return
     */
    virtual size_t
    str_length () const noexcept override
    { return 4; }

  protected:
    /**
     * @brief null
     * @param parent
     */
    null (json *parent)
      : leaf (parent)
    {}

    /**
     * @brief assign
     * @param nv
     * @return
     */
    value &
    _assign (const null &)
    { return _parent ? __call__assign (_parent, this, new null (*this)) : *this; }

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
     * @brief strValue
     * @return
     */
    virtual const wchar_t *
    _to_string (wchar_t *) const noexcept override
    { return L"null"; }
  };  // Class null

  inline
  null * __call_null (json *parent)
  { return new null (parent); }
} // Namespace format

#endif // NULL_H
