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

namespace Format {

 /**
  * @brief The array class
  */
  class Array : public json
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

    typedef std::vector<Value *> element_list;

    /**
   * @brief Array
   */
    Array ();

    /**
   * @brief Array
   * @param json
   */
    Array (const wchar_t *json);

    /**
   * @brief Array
   * @param l elements
   */
    Array (std::initializer_list<Value *> il);

    /**
   * @brief Array
   * @param endp
   * @param parent
   * @param charc
   */
    Array (json *parent);

    /**
   * @brief Array
   * @param other
   */
    Array (const Array &other);

    /**
   * @brief Array
   * @param ov
   * @param nv
   */
    Array (const Value *ov, const Array &nv);

    /**
   * @brief clone
   * @param other
   * @return
   */
    virtual Value *
    clone () const
    { return new Array (*this); }

    /**
   * @brief clone
   * @param ov
   * @return
   */
    virtual Value *
    clone (const Value *ov) const override
    { return new Array (ov, *this); }

    /**
   * @brief ~Array
   */
    virtual ~Array ();

    /**
   * @brief parse
   * @param json
   * @return
   */
    virtual const wchar_t *
    parse ( const wchar_t *json);

    /**
   * @brief at
   * @param key
   * @return
   *
    virtual Value &
    at (const wchar_t *key) const
    {
      wchar_t *end = 0;
      return at (std::wcstoll (key, & end, 10));
    } */

    /**
   * @brief at
   * @param index
   * @return
   */
    Value &
    at (size_t index) const;

    /**
   * @brief assign
   * @param ov
   * @param nv
   */
    //virtual Value &
    //assign (Value *ov, Value *nv);

  //virtual const wchar_t *
  //parse (const wchar_t *json);

    /**
   * @brief type
   * @return
   */
    virtual object_type
    type () const
    { return Value::object_type::array_t; }

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
    inline Value &
    operator =(const Array & a)
    { return _assign (a); }

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
    virtual JSON_Iterator *
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
    virtual Value &
    erase (const Value &v) noexcept  override;

    /**
   * @brief The Iterator class
   */
    class Iterator : public std::iterator<
        std::input_iterator_tag,
        Value *,  // Type
        Value *,  // Distance
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

    virtual Value &
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
    Value &
    _assign (const Array & nv);

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
  _assign (Value *ov, Value *nv) override;

  /**
   * @brief _at
   * @param index
   * @return
   */
  virtual Value &
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
    virtual Value *
    clone (const Value &other) override;
  };
} // Namespace Format

#endif // ARRAY

