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
    friend array * __call_array (json *parent);

  #ifdef UNIT_TEST
    friend class json_array_test;
  #endif

  public:
   /**
    * @brief element_list
    */
   typedef std::vector<value *> element_list;

    /**
     * @brief array
     */
    array ();

    /**
     * @brief array
     * @param json
     */
    array (const wchar_t *json);

    /**
     * @brief array
     * @param il
     */
    array (std::initializer_list<value *> il);

    /**
     * @brief array
     * @param other
     */
    array (const array &other);

    /**
     * @brief clone
     * @return
     */
    virtual value *
    clone () const override
    { return new array (*this); }

    /**
     * @brief ~array
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
     * @brief count
     * @return
     */
    virtual size_t
    length () const noexcept override
    { return _element_list.size (); }

   /**
    * @brief operator =
    * @param a
    * @return
    */
    inline value &
    operator =(const array & a)
    //{ return _parent ? _parent->_assign (this, new array (a)) : *(_clone (a)); }
    { return _parent ? __call__assign (_parent, this, new array (a)) : *(_clone (a)); }

   /**
    * @brief str_length
    * @return
    */
    virtual size_t
    str_length () const noexcept override;

   /**
    * @brief The iterator class
    */
    class iterator : public value::iterator<element_list::iterator,
        std::input_iterator_tag,
        value *,  // Type
        value *,  // Distance
        value *,
        value &>
    {
    public:
     /**
      * @brief iterator
      */
      iterator ()
        : value::iterator<element_list::iterator,
          std::input_iterator_tag,
          value *,
          value *,
          value *,
          value &>::iterator ()
      {}

     /**
      * @brief iterator
      * @param it
      */
      iterator (element_list::iterator it)
        : value::iterator<element_list::iterator,
          std::input_iterator_tag,
          value *,
          value *,
          value *,
          value &>::iterator (it)
      {}

     /**
      * @brief iterator
      * @param other
      */
      iterator (const iterator & other)
        : value::iterator<element_list::iterator,
          std::input_iterator_tag,
          value *,
          value *,
          value *,
          value &>::iterator (other)
      {}

     /**
      * @brief ~Iterator
      */
      virtual ~iterator () = default;

     /**
      * @brief operator *
      * @return
      */
      reference
      operator *()
      { return **_it; }
    }; // Class iterator

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
     * @brief array
     * @param parent
     */
    array (json *parent);

    /**
     * @brief _parse
     * @param json
     * @return
     */
    virtual const wchar_t *
    _parse ( const wchar_t *json) override;

    /**
     * @brief _at
     * @param key
     * @return
     */
    virtual value &
    _at (const wchar_t *key) override
    {
      wchar_t *end = 0;
      return _at (std::wcstoll (key, & end, 10));
    }

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
     * @brief _erase
     * @param v
     * @return
     */
     virtual value &
     _erase (const value &v) noexcept override;

   /**
    * @brief _clone
    * @param other
    * @return
    */
    virtual value *
    _clone (const value &other) override;

    /**
     * @brief str_value
     * @return
     */
     virtual const wchar_t *
     _to_string (wchar_t *offset = 0) const override;

  }; // Class array

  inline array *
  __call_array (json *parent)
  { return new array (parent); }
} // Namespace format

#endif // ARRAY

