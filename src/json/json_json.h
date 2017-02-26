#ifndef JSON_JSON_H
#define JSON_JSON_H

#include "json_value.h"
#include "json_leaf.h"
#include "json_exception.h"
#include "json_shared_undefined.h"

#include <unordered_map>
#include <vector>
#include <initializer_list>

namespace format
{
  #ifdef UNIT_TEST
    class json_test;
    class json_leaf_test;
  #endif

  #define OFFSET  0
  #define BEGIN  1

  typedef value * (* reviver)(const wchar_t *, value *);

  /**
   * @brief The json class
   */
  class object;
  class array;
  class json : public value
  {
  #ifdef UNIT_TEST
    friend class json_test;
    friend class json_leaf_test;
  #endif

    friend const wchar_t * leaf::stringify ();
    friend class object;  // For stringify { _parent->_str_value }
    friend class array;   // For stringify { _parent->_str_value }

  public:

    /**
     * @brief JSON
     */
    json ();

    /**
     * @brief json
     * @param json
     */
    json (const wchar_t *json, const bool _call_parse = true);

    /**
     * @brief json
     * @param endp
     * @param charc
     */
    json (json *parent);

    /**
     * @brief clone
     * @param other
     * @return
     */
    virtual value *
    clone () const
    { return new json (*this);  }

    /**
     * @brief JSON
     * @param other
     */
    json (const json &other);

    /**
     * @brief JSON
     * @param ov
     * @param nv
     */
    json (const value *ov, const json &nv);

    /**
     * @brief ~JSON
     */
    virtual ~json ();

    /**
     * @brief parse
     * @param json
     * @param reviver
     * @return
     * @see http://stackoverflow.com/questions/1174169/function-passed-as-template-argument
     */
    static inline value *
    parse (const wchar_t *text, reviver r = 0)
    { return new json (text, r); }

    /**
     * @brief type
     * @return
     */
    virtual inline value::value_t
    type () const
    { return __hasRoot () ?  __root->type () : value::value_t::undefined_t; }

    /**
     * @brief size
     * @return
     */
    virtual inline size_t
    count () const
    { return __hasRoot () ? __root->count () : 0; }

    /**
     * @brief _assign
     * @param j
     * @return
     */
    virtual value
    & _assign (const json & j);

    /**
     * @brief operator =
     * @param j
     * @return
     */
    inline value &
    operator =(const json & j)
    { return _assign (j); }

    /**
     * @brief _assign
     * @param nv
     * @return
     */
    virtual value &
    _assign (const value & v) override;

    /**
     * @brief operator =
     * @param v
     * @return
     */
    inline value &
    operator =(const value & v)
    { return _assign (v); }

    /**
     * @brief assign
     * @param ov Old value
     * @param nv New value
     * @return
     */
    virtual value &
    _assign (value *, value *) override
    { return *this; }

    /**
     * @brief iterator
     * @return
     */
    virtual json_iterator *
    iterator () const override
    { return __root ? __root->iterator () : 0; /* TODO: new Leaf_Iterator (new Undefined);  // FIXME: leak */ }

    /**
     * @brief stringify
     * @return
     */
    virtual const wchar_t *
    stringify () noexcept override
    { return strValue (); }

    /**
     * @brief strLength
     * @return
     */
    virtual size_t
    strLength () const noexcept override
    { return __hasRoot () ? __root->strLength () : 0; }

    /**
     * @brief strValue
     * @return
     */
    virtual const wchar_t *
    strValue (wchar_t *offset = 0) const
    { return __hasRoot () ? __root->strValue (offset) : L""; }

    /**
     * @brief erase
     * @param v
     * @return
     */
    virtual value &
    erase (const value &v) noexcept override
    { return __hasRoot() ? __root->erase (v) : *this; }

    /**
     * @brief clone
     * @param old
     * @return
     */
    virtual value *
    clone (const value *) const override
    { return new json (*this); }

  protected:

    /**
     * @brief parse
     * @param readp
     * @return
     */
    virtual const wchar_t *
    _parse (const wchar_t *readp) override;

    /**
     * @brief _at
     * @param key
     * @return
     */
    virtual value &
    _at (const wchar_t *key) override
    { return __hasRoot() ? (*__root)[key] : format::shared_undefined::instance (); }

    /**
     * @brief _at
     * @param index
     * @return
     */
    virtual value &
    _at (size_t index) override
    { return __hasRoot() ? (*__root)[index] : format::shared_undefined::instance (); }

    /**
     * @brief _make_value
     * @return
     */
    value *
    _make_value ();

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
    clone (const value &) override
    { return this; }

    /**
     * @brief _call_reviver
     * @param v
     * @param key
     * @param index
     * @return
     */
    value *
    _call_reviver (value *v, const wchar_t *key, size_t index = 0) const;

    /**
     * @brief _str_value
     */
    mutable wchar_t *_str_value[2];

  private:

    /**
     * @brief __value
     */
    value *__root;

    /**
     * @brief _reviver
     */
    reviver __reviver;

    /**
     * @brief JSON
     * @param json
     * @param r
     */
    json (const wchar_t *json, reviver r);

    /**
     * @brief __hasRoot
     * @return
     */
    inline bool
    __hasRoot () const noexcept
    { return ! __root == 0; }
  };
} // Namespace format

#endif // JSON_JSON_H
