#ifndef STRING
#define STRING

#include "json_leaf.h"

#ifdef UNIT_TEST
  class json_string_test;
#endif

namespace format
{
  /**
   * @brief The string class
   */
  class string : public leaf
  {
  #ifdef UNIT_TEST
    friend class json_string_test;
  #endif

    public:

    /**
     * @brief String
     */
    string ();

    /**
     * @brief String
     * @param json
     */
    string (const wchar_t *json);

    /**
     * @brief String
     * @param parent
     * @param charc
     */
    string (json *parent, size_t charc);

    /**
     * @brief String
     * @param other
     */
    string (const string & other);

    /**
     * @brief String
     * @param ov
     * @param nv
     */
    string (const value *ov, const string & nv);

    /**
     * @brief clone
     * @param other
     * @return
     */
    virtual value *
    clone () const
    { return new string (*this); }

    /**
     * @brief clone
     * @param ov
     * @return
     */
    virtual value *
    clone (const value *ov) const override
    { return new string (ov, *this);}

    /**
     * @brief parse
     * @param json
     * @return
     */
    virtual const wchar_t *
    parse (const wchar_t *json);

    /**
     * @brief type
     * @return
     */
    virtual inline value_t
    type () const
    { return value::value_t::string_t; }

    /**
     * @brief operator =
     * @param s
     * @return
     */
    inline value &
    operator =(const string & s)
    { return _assign (s); }

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
    _assign (const string & nv);

    /**
     * @brief value
     * @return
     */
    const wchar_t *
    get() const;

    /**
     * @brief strLength
     * @return
     */
    virtual size_t
    strLength () const noexcept override
    { return _charc; }

    /**
     * @brief strValue
     * @return
     */
    virtual const wchar_t *
    strValue (wchar_t * = 0) const;

  protected:

    /**
     * @brief _charc
     */
    size_t _charc;

    /**
     * @brief _value
     */
    mutable std::wstring _string_value[2];

    /**
     * @brief _copy
     * @param nv
     * void _copy (const String &nv);
     */

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
    clone (const value &nv) override;
  };
}
#endif // STRING

