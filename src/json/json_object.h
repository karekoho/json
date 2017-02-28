#ifndef OBJECT_H
#define OBJECT_H

#include "json_json.h"
#include "json_undefined.h"

namespace format
{
  /**
   * @brief The object class
   */
  class object : public json
  {
  #ifdef UNIT_TEST
    friend class json_test;
    friend class json_object_test;
    friend class json_object_iterator_test;
    friend class json_array_test;
    friend class json_string_test;
    friend class json_number_test;
    friend class json_boolean_test;
    friend class json_null_test;
    friend class json_undefined_test;
  #endif

  public:

    typedef std::unordered_map<std::wstring, value *> member_list;

    /**
     * @brief Object
     */
    object ();

    /**
     * @brief Object
     * @param JSON
     */
    object (const wchar_t *json);

    /**
     * @brief Object
     * @param il
     */
    object (std::initializer_list<std::pair<std::wstring, value *>> il);

  /**
     * @brief Object
     * @param endp
     * @param parent
     * @param charc
     */
    object (json *parent);

    /**
     * @brief Object
     * @param other
     */
    object (const object &other);

    /**
     * @brief Object
     * @param ov
     * @param nv
     */
    object (const value *ov, const object &nv);

    /**
     * @brief clone
     * @param other
     * @return
     */
    virtual value *
    clone () const
    { return new object (*this); }

    /**
     * @brief clone
     * @param ov
     * @return
     */
    virtual value *
    clone (const value *ov) const override
    { return new object (ov, *this); }

    /**
     * @brief ~Object
     */
    virtual ~object ();

    /**
     * @brief parse
     * @param JSON
     * @return
     */
    virtual const wchar_t *
    _parse (const wchar_t *json);

    /**
     * @brief type
     * @return
     */
    virtual inline value_t
    type () const
    { return value::value_t::object_t; }

    /**
     * @brief size
     * @return
     */
    virtual inline size_t
    count () const
    { return _member_list.size (); }

    /**
     * @brief operator =
     * @param o
     * @return
     */
    inline value &
    operator =(const object & o)
    { return _assign (o);  }

    /**
     * @brief operator =
     * @param v
     * @return
     */
    inline value &
    operator =(const value & v)
    { return _assign (v); }

    /**
     * @brief iterator
     * @return
     */
    virtual json_iterator *
    iterator () const override;

    /**
     * @brief stringify
     * @return
     */
    virtual const wchar_t *
    stringify () noexcept override
    { return str_value (); }

    /**
     * @brief strLength
     * @return
     */
    virtual size_t
    str_length () const noexcept override;

    /**
     * @brief strValue
     * @return
     */
    virtual const wchar_t *
    str_value (wchar_t *offset = 0) const;

    /**
     * @brief erase
     * @param v
     * @return
     */
    virtual value &
    erase (const value &v) noexcept override;

    /**
     * @brief The Iterator class
     */
    class Iterator : public std::iterator<
          std::input_iterator_tag,
          std::pair<std::string, value *>,  // Type
          std::pair<std::string, value *>,  // Distance
          value *,
          value &>
    {
    public:

      /**
       * @brief Iterator
       */
      Iterator () {}

      /**
       * @brief Iterator
       * @param it
       */
      Iterator (member_list::iterator it)
       : _it (it)
      {}

      /**
       * @brief Iterator
       * @param other
       */
      Iterator (const Iterator & other)
        : _it (other._it)
      {}

      /**
       * @brief ~Iterator
       */
      virtual ~Iterator () = default;

      /**
       * @brief operator ++
       * @return
       */
      Iterator &
      operator ++()
      {
        ++_it;
        return *this;
      }

      /**
       * @brief operator ++
       * @return
       */
      Iterator
      operator ++(int)
      {
        Iterator it (*this);
        ++(*this);
        return it;
      }

      /**
       * @brief operator ==
       * @param rhs
       * @return
       */
      inline bool
      operator ==(const Iterator &rhs)
      { return _it == rhs._it; }

      /**
       * @brief operator !=
       * @param rhs
       * @return
       */
      inline bool
      operator !=(const Iterator &rhs)
      { return ! operator ==(rhs); }

      /**
       * @brief operator *
       * @return
       */
      reference
      operator *()
      { return *(*_it).second; }

    protected:

        /**
         * @brief _it
         */
        member_list::iterator _it;

    }; // Iterator

    /**
     * @brief begin
     * @return
     */
    Iterator
    begin ()
    { return Iterator (_member_list.begin ()); }

    /**
     * @brief end
     * @return
     */
    Iterator
    end ()
    { return Iterator (_member_list.end ()); }

  protected:

    /**
     * @brief _member_list
     */
    mutable member_list _member_list;

    /**
     * @brief _pair
     * @return
     */
    bool
    _pair ();

    /**
     * @brief _assign
     * @param nv
     * @return
     */
    value &
    _assign (const object & nv);

    /**
     * @brief _at
     * @param key
     * @return
     */
    virtual value &
    _at (const wchar_t *key);

    /**
     * @brief _at
     * @return
     */
    virtual value & _at (size_t)
    { return shared_undefined::instance (); }

    /**
     * @brief _assign
     * @param nv
     * @return
     */
    virtual value &
    _assign (const value & nv)
    { return value::_assign (nv); }

    /**
     * @brief assign
     * @param ov
     * @param nv
     */
    virtual value &
    _assign (value *ov, value *nv);

    /**
     * @brief _clear
     */
    virtual void
    _clear ();

    /**
     * @brief _clone
     * @return
     */
    virtual value *
    clone (const value &other);
  };
} // Namespace format

#endif // OBJECT_H

