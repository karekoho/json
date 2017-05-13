#ifndef OBJECT_H
#define OBJECT_H

#include "json_json.h"
#include "json_undefined.h"

namespace format
{
  #ifdef UNIT_TEST
    class json_object_test;
  #endif
  /**
   * @brief The object class
   */
  class object : public json
  {
    friend object * __call_object (json *parent);

    #ifdef UNIT_TEST
      friend class json_object_test;
    #endif

  public:
    /**
     * @brief member_list
     */
    typedef std::unordered_map<std::wstring, value *> member_list;

    /**
     * @brief object
     */
    object ();

    /**
     * @brief object
     * @param json
     */
    object (const wchar_t *json_text);

    /**
     * @brief object
     * @param il
     */
    object (std::initializer_list<std::pair<std::wstring, value *>> il);

    /**
     * @brief object
     * @param other
     */
    object (const object &other);

    /**
     * @brief clone
     * @return
     */
    virtual value *
    clone () const override
    { return new object (*this); }

    /**
     * @brief ~object
     */
    virtual
    ~object () override;

    /**
     * @brief type
     * @return
     */
    virtual inline value_t
    type () const noexcept override
    { return value::value_t::object_t; }

    /**
     * @brief count
     * @return
     */
    virtual inline size_t
    length () const noexcept override
    { return _member_list.size (); }

    /**
     * @brief operator =
     * @param o
     * @return
     */
    inline value &
    operator =(const object & o)
    { return _parent ? __call__assign (_parent, this, new object (o)) : *(_clone (o)); }

    /**
     * @brief operator =
     * @param json_text
     * @return
     */
    virtual inline value &
    operator =(const wchar_t *json_text) override
    {
      if (! _member_list.empty ())
        _clear ();
      (void) _parse (json_text);
      return *this;
    }

    /**
     * @brief str_length
     * @return
     */
    virtual size_t
    str_length () const noexcept override;

    /**
     * @brief The iterator class
     */
    class iterator : public value::iterator<member_list::iterator,
        std::input_iterator_tag,
        std::pair<std::string, value *>,  // Type
        std::pair<std::string, value *>,  // Distance
        value *,
        value &>
    {
    public:
      /**
       * @brief iterator
       */
      iterator ()
        : value::iterator<member_list::iterator,
          std::input_iterator_tag,
          std::pair<std::string, value *>,
          std::pair<std::string, value *>,
          value *,
          value &>::iterator ()
      {}

      /**
       * @brief iterator
       * @param it
       */
      iterator (member_list::iterator it)
        : value::iterator<member_list::iterator,
          std::input_iterator_tag,
          std::pair<std::string, value *>,
          std::pair<std::string, value *>,
          value *,
          value &>::iterator (it)
      {}

      /**
       * @brief iterator
       * @param other
       */
      iterator (const iterator & other)
        : value::iterator<member_list::iterator,
          std::input_iterator_tag,
          std::pair<std::string, value *>,
          std::pair<std::string, value *>,
          value *,
          value &>::iterator (other)
      {}

      /**
       * @brief ~iterator
       */
      virtual ~iterator () = default;

      /**
       * @brief operator *
       * @return
       */
      reference
      operator *()
      { return *(*_it).second; }
    }; // Class iterator

    /**
     * @brief begin
     * @return
     */
    iterator
    begin ()
    { return iterator (_member_list.begin ()); }

    /**
     * @brief end
     * @return
     */
    iterator
    end ()
    { return iterator (_member_list.end ()); }

  protected:

    /**
     * @brief _member_list
     */
    mutable member_list _member_list;

    /**
     * @brief object
     * @param parent
     */
    object (json *parent);

    /**
     * @brief _clone
     * @return
     */
    virtual value *
    _clone (const value &other) override;

    /**
     * @brief parse
     * @param json
     * @return
     */
    virtual const wchar_t *
    _parse (const wchar_t *json_text) override;

    /**
     * @brief _pair
     * @return
     */
    bool
    _pair ();

    /**
     * @brief _at
     * @param key
     * @return
     */
    virtual value &
    _at (const wchar_t *key) override;

    /**
     * @brief _at
     * @return
     */
    virtual value & _at (size_t) override
    { return *(new format::undefined ()); }

    /**
     * @brief assign
     * @param ov
     * @param nv
     */
    virtual value &
    _assign (value *ov, value *nv) override;

    /**
     * @brief _clear
     */
    virtual void
    _clear () override;

    /**
     * @brief _erase
     * @param v
     * @return
     */
    virtual value &
    _erase (const value &v) noexcept override;

    /**
     * @brief _to_str
     * @param offset
     * @return
     */
    virtual const wchar_t *
    _to_string (wchar_t *offset = 0) const override;
  }; // Class object

  inline
  object * __call_object (json *parent)
  { return new object (parent); }
} // Namespace format

#endif // OBJECT_H

