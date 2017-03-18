#ifndef ARRAY
#define ARRAY

#include "json_json.h"

namespace format
{
  #ifdef UNIT_TEST
    class json_array_test;
  #endif

 /**
  * @brief The array class
  */
  class array : public json
  {
  #ifdef UNIT_TEST
    friend class json_array_test;
  #endif

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
    clone () const override
    { return new array (*this); }

   /**
    * @brief clone
    * @param ov
    * @return
    */
    virtual value *
    _clone (const value *ov) const override
    { return new array (ov, *this); }

   /**
    * @brief ~Array
    */
    virtual
    ~array () override;

   /**
    * @brief type
    * @return
    */
    virtual value_t
    type () const noexcept override
    { return value::value_t::array_t; }

   /**
    * @brief size
    * @return
    */
    virtual size_t
    count () const noexcept override
    { return _element_list.size (); }

   /**
    * @brief operator =
    * @param a
    * @return
    */
    inline value &
    operator =(const array & a)
    { return _parent ? _parent->_assign (this, new array (a)) : *(_clone (a)); }

   /**
    * @brief iterator
    * @return
    */
    virtual json_iterator *
    __iterator__ () const override;

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
    str_value (wchar_t *offset = 0) const override;

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
    class iterator : public std::iterator<
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
      iterator ()
      {}

     /**
      * @brief Iterator
      * @param it
      */
      iterator (element_list::iterator it)
        : _it (it)
      {}

     /**
      * @brief Iterator
      * @param other
      */
      iterator (const iterator & other)
        : _it (other._it)
      {}

     /**
      * @brief ~Iterator
      */
      virtual ~iterator () = default;

     /**
      * @brief operator ++
      * @return
      */
      iterator &
      operator ++()
      {
        ++_it;
        return *this;
      }

     /**
      * @brief operator ++
      * @return
      */
      iterator
      operator ++(int)
      {
        iterator it (*this);
        ++(*this);
        return it;
      }

     /**
      * @brief operator ==
      * @param rhs
      * @return
      */
      inline bool
      operator ==(const iterator &rhs)
      { return _it == rhs._it; }

     /**
      * @brief operator !=
      * @param rhs
      * @return
      */
      inline bool
      operator !=(const iterator &rhs)
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

    /**
     * @brief begin
     * @return
     */
    iterator
    begin ()
    { return iterator (_element_list.begin ()); }

    /**
     * @brief end
     * @return
     */
    iterator
    end ()
    { return iterator (_element_list.end ()); }

  protected:

   /**
    * @brief _element_list
    */
    element_list _element_list;

   /**
    * @brief parse
    * @param json
    * @return
    */
    virtual const wchar_t *
    _parse ( const wchar_t *json) override;

   /**
    * @brief _at
    * @return
    */
    virtual value &
    _at (const wchar_t *key) override
    {
      wchar_t *end = 0;
      return _at (std::wcstoll (key, & end, 10));
    }

    /**
    * @brief _assign
    * @param nv
    * @return
    */
//    value &
//    _assign (const array & nv);

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
    _clone (const value &other) override;

    /**
     * @brief _sizeof
     * @return
     */
    virtual size_t
    _sizeof () const noexcept override
    { return sizeof (array); }
  };
} // Namespace format

#endif // ARRAY

