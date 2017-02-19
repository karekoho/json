#ifndef ARRAY
#define ARRAY

#include "json_json.h"

#ifdef UNIT_TEST
class json_test;
class json_array_test;
class json_object_test;
class json_string_test;
class json_number_test;
class json_boolean_test;
class json_null_test;
class json_undefined_test;
#endif

namespace format
{
 /**
  * @brief The array class
  */
  class array : public json
  {
  #ifdef UNIT_TEST
    friend class json_test;
    friend class json_array_test;
    friend class json_object_test;
    friend class json_string_test;
    friend class json_number_test;
    friend class json_boolean_test;
    friend class json_null_test;
    friend class json_undefined_test;
  #endif

  // TODO: friend void Value::setKey (const char *key);
  // TODO: friend void Value::setIndex (const size_t &index);
  // TODO: friend Value & Value::_root__at (const char *key, JSON *root);

  public:

   typedef std::vector<value *> element_list;

   /**
    * @brief Array
    */
    array ();

   /**
    * @brief Array
    * @param json
    */
    array (const wchar_t *json);

   /**
    * @brief Array
    * @param l elements
    */
    array (std::initializer_list<value *> il);

   /**
    * @brief Array
    * @param endp
    * @param parent
    * @param charc
    */
    array (json *parent);

   /**
    * @brief Array
    * @param other
    */
    array (const array &other);

   /**
    * @brief Array
    * @param ov
    * @param nv
    */
    array (const value *ov, const array &nv);

   /**
    * @brief clone
    * @param other
    * @return
    */
    virtual value *
    clone () const
    { return new array (*this); }

   /**
    * @brief clone
    * @param ov
    * @return
    */
    virtual value *
    clone (const value *ov) const override
    { return new array (ov, *this); }

   /**
    * @brief ~Array
    */
    virtual ~array ();

   /**
    * @brief parse
    * @param json
    * @return
    */
    virtual const wchar_t *
    parse ( const wchar_t *json);

   /**
    * @brief type
    * @return
    */
    virtual value_t
    type () const
    { return value::value_t::array_t; }

   /**
    * @brief size
    * @return
    */
    virtual size_t
    count () const
    { return _element_list.size (); }

   /**
    * @brief operator =
    * @param a
    * @return
    */
    inline value &
    operator =(const array & a)
    { return _assign (a); }

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
    * @brief stringify
    * @return
    */
    virtual const wchar_t *
    stringify () noexcept
    { return strValue (); }

   /**
    * @brief erase
    * @param v
    * @return
    */
    virtual value &
    erase (const value &v) noexcept  override;

   /**
    * @brief The Iterator class
    */
    class Iterator : public std::iterator<
        std::input_iterator_tag,
        value *,  // Type
        value *,  // Distance
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
      Iterator (element_list::iterator it)
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
      { return **_it; }

    protected:

      /**
       * @brief _it
       */
      element_list::iterator _it;
    }; // Iterator

  protected:

   /**
    * @brief _element_list
    */
    element_list _element_list;

   /**
    * @brief _at
    * @return
    */
    virtual value &
    _at (const wchar_t *key)
    {
      wchar_t *end = 0;
      return _at (std::wcstoll (key, & end, 10));
    }

    /**
    * @brief _assign
    * @param nv
    * @return
    */
    value &
    _assign (const array & nv);

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
    _assign (value *ov, value *nv) override;

    /**
     * @brief _at
    * @param index
    * @return
    */
    virtual value &
    _at (size_t index) override;

   /**
    * @brief _clear
    */
    virtual void
    _clear ();

   /**
    * @brief _clone
    * @param other
    * @return
    */
    virtual value *
    clone (const value &other) override;
  };
} // Namespace format

#endif // ARRAY

