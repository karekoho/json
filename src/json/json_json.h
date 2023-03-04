#ifndef JSON_JSON_H
#define JSON_JSON_H

#include "json_leaf.h"
#include "json_exception.h"
#include "json_undefined.h"

#include <unordered_map>
#include <vector>
#include <initializer_list>

namespace format
{
  namespace json
  {
    #define OFFSET  0
    #define BEGIN  1

    typedef value * (* reviver)(const wchar_t * const, value *);

    class array;
    class object;
    /**
     * @brief The json class
     */
    class json : public value
    {
    public:
      /**
       * @brief json
       */
      json ();

      /**
       * @brief json
       * @param json
       */
      json (const wchar_t * const json);

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
       * @brief json
       * @param other
       */
      json (const json &other);

      /**
       * @brief ~json
       */
      virtual
      ~json () override;

      /**
       * @brief clone
       * @return
       */
      virtual inline value *
      clone () const override
      { return new json (*this); }

      /**
       * @brief parse
       * @param json
       * @param reviver
       * @return
       * @see http://stackoverflow.com/questions/1174169/function-passed-as-template-argument
       */
      static inline json *
      parse (const wchar_t * const json_text, reviver r = nullptr)
      { return new json (json_text, r); }

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
      size () const noexcept override
      { return __hasRoot () ? __root->size () : 0; }

      /**
       * @brief operator =
       * @param json
       * @return
       */
      value &
      operator =(const wchar_t * const json_text);

      /**
       * @brief operator =
       * @param j
       * @return
       */
      inline value &
      operator =(const json & j)
      { return _assign (j); }

      /**
       * @brief operator =
       * @param o
       * @return
       */
      value &
      operator =(object *o);

      /**
       * @brief operator =
       * @param a
       * @return
       */
      value &
      operator =(array *a);

#ifdef UNIT_TEST
      inline value *
      root ()
      { return __root; }
#endif

    protected:

      /**
       * @brief json
       * @param parent
       */
      json (json *parent);

      /**
       * @brief json
       * @param json
       * @param _call_parse
       */
      json (const wchar_t * const json, const bool _call_parse);

      /**
       * @brief parse
       * @param readp
       * @return
       */
      virtual const wchar_t *
      _parse (const wchar_t * const readp) override;

      /**
       * @brief _at
       * @param key
       * @return
       */
      virtual value &
      _at (const wchar_t * const key) override;

      /**
       * @brief _at
       * @param key
       * @return
       */
      virtual const value &
      _at (const wchar_t * const key) const override;

      /**
       * @brief _at
       * @param index
       * @return
       */
      virtual value &
      _at (size_t index) override;

      /**
       * @brief _at
       * @param index
       * @return
       */
      virtual const value &
      _at (size_t index) const override;

      /**
       * @brief _assign
       * @param j
       * @return
       */
      value
      & _assign (const json & j);

      /**
       * @brief assign
       * @param ov Old value
       * @param nv New value
       * @return
       **/
      virtual inline value &
      _assign (value *, value *) override
      { return *this; }

      /**
       * @todo move to value::_make_value to get rid of friend wrappers
       * @brief _make_value
       * @return
       */
      value *
      _make_value ();

      /**
       * @brief _clear
       */
      virtual inline void
      _clear () override
      { /* nop */ }

      /**
       * @brief _clone
       * @return
       */
      virtual inline value *
      _clone (const value &) override
      { return this; }

      /**
       * @brief _to_string
       * @return
       */
      virtual inline const wchar_t *
      _to_string (wchar_t *offset = nullptr) const override
      { return __hasRoot () ? value::_to_string (__root, offset) : L""; }

      /**
       * @brief _str_length
       * @return
       */
      virtual inline size_t
      _str_length () const noexcept override
      { return __hasRoot () ? value::_str_length (__root) : 0; }

      /**
       * @brief erase
       * @param v
       * @return
       */
      virtual inline value &
      _erase (const value &v) noexcept override
      { return __hasRoot () ? value::_erase (__root, v) : *this; }

      /**
       * @brief _call_reviver
       * @param v
       * @param key
       * @param index
       * @return
       */
      value *
      _call_reviver (value *v, const wchar_t * const key, size_t index = 0) const;

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
      json (const wchar_t * const json, reviver r);

      /**
       * @brief __hasRoot
       * @return
       */
      inline bool
      __hasRoot () const noexcept
      { return ! (__root == nullptr); }
    };
  }  // Namespace json
} // Namespace format

#endif // JSON_JSON_H
