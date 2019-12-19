#ifndef JSON_EXCEPTION
#define JSON_EXCEPTION

#include <exception>
#include <cstdlib>
#include <alloca.h>
#include <string>

namespace format
{
  /**
   * @brief The JSON_Error class
   */
  class json_error : public std::exception
  {
    public:
    /**
     * @brief JSON_Error
     * @param what
     */
    json_error (const char * const what)
      : exception (),
        _what (what)
    {
    }

    /**
     * @brief what
     * @return
     */
    virtual const char *
    what () const noexcept
    { return _what.c_str (); }

  protected:

    /**
     * @brief _what
     */
    std::string _what;
  };

  /**
   * @brief The JSON_Syntax_Error class
   */
  class json_syntax_error : public json_error
  {
  public:
    /**
     * @brief Syntax_Error
     * @param what
     */
    json_syntax_error (const char * const what)
      : json_error (what)
    {}

    /**
     * @brief Syntax_Error
     * @param what
     * @param token
     */
    json_syntax_error (const char * const what, wchar_t token)
      : json_error (what)
    {
      _add_token (& token, 1);
    }

    /**
     * @see http://www.cplusplus.com/reference/cstdlib/wcstombs/
     * @brief Syntax_Error
     * @param what
     * @param token
     */
    json_syntax_error (const char * const what, const wchar_t *token, size_t charc = 0)
      : json_error (what)
    {
      _add_token (token, charc);
    }

  protected:

    size_t
    _add_token (const wchar_t *token, size_t charc = 0)
    {
      size_t bytec = 0;
      size_t token_len = charc == 0 ? wcslen (token) : charc;

      char *src_buf = static_cast<char *> (alloca (token_len + 1));

      if ((bytec = wcstombs (static_cast<char *> (memset (src_buf, 0, token_len + 1)), token, token_len)) < token_len)
        return bytec;

      char *dst_buf = static_cast<char *> (alloca (token_len + 3)); // ' + token + ' + 0

      if ((bytec = static_cast<size_t> (std::snprintf (dst_buf, token_len + 3, "'%s'", src_buf))) < token_len + 2)
        return bytec;

      _what.append (dst_buf);

      return bytec;
    }
  };

  /**
   * @brief The JSON_Out_Of_Range class
   */
  class json_out_of_range : public json_error
  {
  public:
    /**
     * @brief Syntax_Error
     * @param what
     */
    json_out_of_range (const char * const what)
      : json_error (what)
    {}
  };

  /**
   * @brief The json_pointer_error class
   */
  class json_pointer_error : public json_syntax_error
  {
  public:
    json_pointer_error (const char * const what)
     : json_syntax_error (what)
    {}

    json_pointer_error (const char * const what, const wchar_t *token, size_t charc = 0)
     : json_syntax_error (what, token, charc)
    {}
  };
} // Namespace format

#endif // JSON_EXCEPTION

