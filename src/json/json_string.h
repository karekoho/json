#ifndef STRING
#define STRING

#include "json_leaf.h"

namespace format
{
#ifdef UNIT_TEST
  class json_string_test;
#endif
  /**
   * @brief The string class
   */
  class string : public leaf
  {
    friend string * __call_string (json *parent, size_t charc);

  #ifdef UNIT_TEST
    friend class json_string_test;
  #endif

    public:
    /**
     * @brief String
     */
    string ();

    /**
     * @brief string
     * @param json
     */
    string (const wchar_t *json);

    /**
     * @brief String
     * @param other
     */
    string (const string & other);

    /**
     * @brief ~string
     */
    virtual ~string () override = default;

    /**
     * @brief clone
     * @param other
     * @return
     */
    virtual value *
    clone () const override
    { return new string (*this); }

    /**
     * @brief type
     * @return
     */
    virtual inline value_t
    type () const noexcept override
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
     * @param s
     * @return
     */
    virtual value &
    operator =(const wchar_t *s) override
    {
      json *p = _parent;
      _parent = nullptr;

      _clear ();

      (void) _parse (s);

      _parent = p;

      return *this;
    }

    /**
     * @brief value
     * @return
     */
    const wchar_t *
    get () const;

    /**
     * @brief length
     * @return
     */
    inline size_t
    length () const noexcept
    {
      size_t length = _str_length ();
      return length > 1 ? length - 2 : length;
    }

  protected:
    /**
     * @brief _startp
     */
    const wchar_t *_startp;

    /**
     * @brief _charc
     */
    size_t _charc;

    /**
     * @brief _value
     */
    mutable std::wstring _string_value[2];

    /**
     * @brief string
     * @param parent
     * @param charc
     */
    string (json *parent, size_t charc);

    /**
     * @brief parse
     * @param json
     * @return
     */
    virtual const wchar_t *
    _parse (const wchar_t *json) override;

    /**
     * @brief _clear
     */
    virtual void
    _clear () override
    {
      _string_value[0].clear ();
      _string_value[1].clear ();
    }

    /**
     * @brief _clone
     * @return
     */
    virtual value *
    _clone (const value &nv) override;

    /**
     * @brief assign
     * @param nv
     * @return
     */
    value &
    _assign (const string & nv);

    /**
     * @brief strValue
     * @return
     */
    virtual const wchar_t *
    _to_string (wchar_t * = nullptr) const override;

    /**
     * @brief str_length
     * @return
     */
    virtual size_t
    _str_length () const noexcept override
    { return _charc == 0 || *_startp == _sc::double_quote ? _charc : _charc + 2; }

  private:
    /**
     * @brief __string Read characters until character is < 32 or \".
     * If last charater is \0, return string length,
     * otherwise return string as negative value.
     * @return Number of characters read
     */
    long
    __string (wchar_t & endc) const noexcept;
  }; // Class string

  /**
   * @brief call_string
   * @param parent
   * @param charc
   * @return
   */
  inline string *
  __call_string (json *parent, size_t charc)
  { return new string (parent, charc); }
} // Namespace format
#endif // STRING

