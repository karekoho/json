#ifndef JSON_JSON_H
#define JSON_JSON_H

#include "json_value.h"
#include "json_leaf.h"
#include "json_exception.h"
// #include "json_shared_undefined.h"
#include "json_undefined.h"

#include <unordered_map>
#include <vector>
#include <initializer_list>


namespace format
{
  #ifdef UNIT_TEST
    class json_test;
  #endif

  #define OFFSET  0
  #define BEGIN  1

  typedef value * (* reviver)(const wchar_t *, value *);

  class array;
  class object;
  /**
   * @brief The json class
   */
  class json : public value
  {
    #ifdef UNIT_TEST
      friend class json_test;
    #endif

  public:

    /**
     * @brief json
     */
    json ();

    /**
     * @brief json
     * @param json
     */
    json (const wchar_t *json);

    /**
     * @brief json
     * @param parent
     */
    json (json *parent);

    /**
     * @brief json
     * @param o
     */
    json (object *o);

    /**
     * @brief json
     * @param a
     */
    json (array *a);

    /**
     * @brief clone
     * @return
     */
    virtual value *
    clone () const
    { return new json (*this);  }

    /**
     * @brief json
     * @param other
     */
    json (const json &other);

    /**
     * @brief json
     * @param ov
     * @param nv
     */
    json (const value *ov, const json &nv);

    /**
     * @brief ~json
     */
    virtual
    ~json () override;

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
    type () const noexcept override
    { return __hasRoot () ?  __root->type () : value::value_t::undefined_t; }

    /**
     * @brief size
     * @return
     */
    virtual inline size_t
    count () const noexcept override
    { return __hasRoot () ? __root->count () : 0; }

    /**
     * @brief _assign
     * @param j
     * @return
     */
    value
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
     *
    virtual json_iterator *
    __iterator__ () const override
    { return __root ? __root->__iterator__ () : 0; } */

    /**
     * @brief strLength
     * @return
     */
    virtual size_t
    str_length () const noexcept override
    { return __hasRoot () ? __root->str_length () : 0; }

    /**
     * @brief strValue
     * @return
     */
    virtual const wchar_t *
    str_value (wchar_t *offset = 0) const override
    { return __hasRoot () ? __root->str_value (offset) : L""; }

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
    _clone (const value *) const override
    { return new json (*this); }

  protected:
    /**
     * @brief json
     * @param json
     * @param _call_parse
     */
    json (const wchar_t *json, const bool _call_parse);

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
    _at (const wchar_t *key) override;

    /**
     * @brief _at
     * @param index
     * @return
     */
    virtual value &
    _at (size_t index) override;

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
    _clear () override
    {}

    /**
     * @brief _clone
     * @return
     */
    virtual value *
    _clone (const value &) override
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
