#ifndef ARRAY
#define ARRAY

#include "json_json.h"

namespace format
{
  namespace json
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
      count () const noexcept override
      { return _element_list.size (); }

      /**
       * @brief operator =
       * @param json_text
       * @return
       */
      inline value &
      operator =(const wchar_t *json_text) override
      {
        if (! _element_list.empty ())
          _clear ();
        (void) _parse (json_text);
        return *this;
      }

      /**
       * @brief operator =
       * @param il
       * @return
       */
      inline value &
      operator =(std::initializer_list<value *> il)
      {
        if (! _element_list.empty ())
          _clear ();
        _set_initializer_list (il);
        return *this;
      }

     /**
      * @brief operator =
      * @param a
      * @return
      */
      value &
      operator =(const array & a);

     /**
      * @brief Read-only, forward iterator. Can be incremented one step forward.
      */
      class const_iterator : public value::iterator<element_list::const_iterator,
          std::input_iterator_tag,
          value,  // Type
          value,  // Distance
          value *,
          value &>
      {
      public:
       /**
        * @brief Default constructor
        */
        const_iterator ()
          : value::iterator<element_list::const_iterator,
            std::input_iterator_tag,
            value,
            value,
            value *,
            value &>::iterator ()
        {}

       /**
        * @brief Point constructor
        * @param it
        */
        const_iterator (element_list::const_iterator it)
          : value::iterator<element_list::const_iterator,
            std::input_iterator_tag,
            value,
            value,
            value *,
            value &>::iterator (it)
        {}

       /**
        * @brief Copy constructor
        * @param other
        */
        const_iterator (const iterator & other)
          : value::iterator<element_list::const_iterator,
            std::input_iterator_tag,
            value,
            value,
            value *,
            value &>::iterator (other)
        {}

       /**
        * @brief Destructor
        */
        virtual ~const_iterator () = default;

       /**
        * @brief Get reference to the element pointer by iterator
        * @return
        */
        reference
        operator *() const noexcept
        { return **_it; }
      }; // Class iterator

      /**
       * @brief Get iterator to begin
       * @return
       */
      const_iterator
      begin () const noexcept
      { return const_iterator (_element_list.cbegin ()); }

      /**
       * @brief Get iterator to end
       * @return
       */
      const_iterator
      end () const noexcept
      { return const_iterator (_element_list.cend ()); }

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
      { return _at (__to_index (key)); }

      /**
       * @brief _at
       * @param key
       * @return
       */
      virtual const value &
      _at (const wchar_t *key) const override
      { return _at (__to_index (key)); }

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
       * @brief _at
       * @param index
       * @return
       */
      virtual const value &
      _at (size_t index) const override;

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
       _to_string (wchar_t *offset = nullptr) const override;

      /**
       * @brief str_length
       * @return
       */
       virtual size_t
       _str_length () const noexcept override;

      /**
       * @brief _set_initializer_list
       * @param il
       */
      void
      _set_initializer_list (std::initializer_list<value *> il);

    private:
      /**
       * @brief __to_index
       * @param key
       * @return
       */
      static inline size_t
      __to_index (const wchar_t * const key)
      {
        wchar_t *end = nullptr;
        return static_cast<size_t>(std::wcstoll (key, & end, 10));
      }
    }; // Class array

    inline array *
    __call_array (json *parent)
    { return new array (parent); }
  } // Namespace json
} // Namespace format

#endif // ARRAY

