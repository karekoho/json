#ifndef OBJECT_H
#define OBJECT_H

#include "json_json.h"
#include "json_undefined.h"

namespace format
{
  namespace json
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
      object (const wchar_t * const json_text);

      /**
       * @brief object
       * @param il
       */
      object (std::initializer_list<std::pair<std::wstring, value *> > il);

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
      size () const noexcept override
      { return _member_list.size (); }

      /**
       * @brief operator =
       * @param o
       * @return
       */
      value &
      operator =(const object & o);

      /**
       * @brief operator =
       * @param il
       * @return
       */
      inline value &
      operator =(std::initializer_list<std::pair<std::wstring, value *>> il)
      {
        if (! _member_list.empty ())
          _clear ();

        _set_initializer_list (il);
        return *this;
      }

      /**
       * @note Removed
       * @brief operator =
       * @param json_text
       * @return
       *
      virtual inline value &
      operator =(const wchar_t *json_text) override
      {
        if (! _member_list.empty ())
          _clear ();
        (void) _parse (json_text);
        return *this;
      } */

      /**
       * @brief Read-only, forward iterator. Can be incremented one step forward.
       */
      class const_iterator : public value::iterator<member_list::const_iterator,
          std::input_iterator_tag,
          std::pair<std::string, value *>,  // Type
          std::pair<std::string, value *>,  // Distance
          value *,
          value &>
      {
      public:
        /**
         * @brief Default constructor
         */
        const_iterator ()
          : value::iterator<member_list::const_iterator,
            std::input_iterator_tag,
            std::pair<std::string, value *>,
            std::pair<std::string, value *>,
            value *,
            value &>::iterator ()
        {}

        /**
         * @brief Point constructor
         * @param it
         */
        const_iterator (member_list::const_iterator it)
          : value::iterator<member_list::const_iterator,
            std::input_iterator_tag,
            std::pair<std::string, value *>,
            std::pair<std::string, value *>,
            value *,
            value &>::iterator (it)
        {}

        /**
         * @brief Copy constructor
         * @param other
         */
        const_iterator (const iterator & other)
          : value::iterator<member_list::const_iterator,
            std::input_iterator_tag,
            std::pair<std::string, value *>,
            std::pair<std::string, value *>,
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
        reference inline
        operator *() const noexcept
        { return *(*_it).second; }
      }; // Class iterator

      /**
       * @brief Get iterator to begin
       * @return
       */
      const_iterator inline
      begin () const noexcept
      { return const_iterator (_member_list.cbegin ()); }

      /**
       * @brief Get iterator to end
       * @return
       */
      const_iterator inline
      end () const  noexcept
      { return const_iterator (_member_list.cend ()); }

    protected:

      /**
       * @brief _member_list
       */
      member_list _member_list;

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
       * @return
       */
      virtual inline value & _at (size_t) override
      { return *(new format::json::undefined ()); }

      /**
       * @brief _at
       * @return
       */
      virtual inline const value & _at (size_t) const override
      { throw json_out_of_range ("Key not found"); }

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
      _to_string (wchar_t *offset = nullptr) const override;

      /**
       * @brief str_length
       * @return
       */
      virtual size_t
      _str_length () const noexcept override;

      /**
       * @brief _initializer_list
       * @param il
       */
      void
      _set_initializer_list (const std::initializer_list<std::pair<std::wstring, value *>> & il);
    }; // Class object

    inline
    object * __call_object (json *parent)
    { return new object (parent); }
  } // Namespace json
} // Namespace format

#endif // OBJECT_H

