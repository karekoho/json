#ifndef OBJECT_H
#define OBJECT_H

#include "json_json.h"
#include "json_undefined.h"

namespace Format
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

    typedef std::unordered_map<std::wstring, Value *> member_list;

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
    object (std::initializer_list<std::pair<std::wstring, Value *>> il);

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
    object (const Value *ov, const object &nv);

    /**
     * @brief clone
     * @param other
     * @return
     */
    virtual Value *
    clone () const
    { return new object (*this); }

    /**
     * @brief clone
     * @param ov
     * @return
     */
    virtual Value *
    clone (const Value *ov) const override
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
    parse (const wchar_t *json);

    /**
     * @brief type
     * @return
     */
    virtual inline object_type
    type () const
    { return Value::object_type::object_t; }

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
    inline Value &
    operator =(const object & o)
    { return _assign (o);  }

    /**
     * @brief operator =
     * @param v
     * @return
     */
    inline Value &
    operator =(const Value & v)
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
    { return strValue (); }

    /**
     * @brief strLength
     * @return
     */
    virtual size_t
    strLength () const noexcept override;

    /**
     * @brief strValue
     * @return
     */
    virtual const wchar_t *
    strValue (wchar_t *offset = 0) const;

    /**
     * @brief erase
     * @param v
     * @return
     */
    virtual Value &
    erase (const Value &v) noexcept override;

    /**
     * @brief The Iterator class
     */
    class Iterator : public std::iterator<
          std::input_iterator_tag,
          std::pair<std::string, Value *>,  // Type
          std::pair<std::string, Value *>,  // Distance
          Value *,
          Value &>
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
    Value &
    _assign (const object & nv);

    /**
     * @brief _at
     * @param key
     * @return
     */
    virtual Value &
    _at (const wchar_t *key);

    /**
     * @brief _at
     * @return
     */
    virtual Value & _at (size_t)
    { return Shared_Undefined::instance (); }

    /**
     * @brief _assign
     * @param nv
     * @return
     */
    virtual Value &
    _assign (const Value & nv)
    { return Value::_assign (nv); }

    /**
     * @brief assign
     * @param ov
     * @param nv
     */
    virtual Value &
    _assign (Value *ov, Value *nv);

    /**
     * @brief _clear
     */
    virtual void
    _clear ();

    /**
     * @brief _clone
     * @return
     */
    virtual Value *
    clone (const Value &other);
  };
} // Namespace format

#endif // OBJECT_H

