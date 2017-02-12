#ifndef JSON_EXCEPTION
#define JSON_EXCEPTION

#include <exception>
#include <cstring>
#include <cstdlib>
#include <wchar.h>
#include <alloca.h>

#ifdef UNIT_TEST
  class json_exception_test;
#endif

  /**
 * @brief The JSON_Error class
 */
class JSON_Error : public std::exception
{
  public:
  /**
   * @brief JSON_Error
   * @param what
   */
  JSON_Error (const char * const what)
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
class JSON_Syntax_Error : public JSON_Error
{
#ifdef UNIT_TEST
  friend class json_exception_test;
#endif

public:
  /**
   * @brief Syntax_Error
   * @param what
   */
  JSON_Syntax_Error (const char * const what)
    : JSON_Error (what)
  {}

  /**
   * @brief Syntax_Error
   * @param what
   * @param token
   */
  JSON_Syntax_Error (const char * const what, wchar_t token)
    : JSON_Error (what)
  {
    // char str[4];
    //if (std::snprintf (str, 4, "'%c'", (char) token) == 3) _what.append (str, 3);

    _add_token (& token, 1);
  }

  /**
   * @see http://www.cplusplus.com/reference/cstdlib/wcstombs/
   * @brief Syntax_Error
   * @param what
   * @param token
   */
  JSON_Syntax_Error (const char * const what, const wchar_t *token, size_t charc = 0)
    : JSON_Error (what)
  {
    _add_token (token, charc);
  }

protected:

  size_t
  _add_token (const wchar_t *token, size_t charc = 0)
  {
    size_t bytec = 0;
    size_t token_len = charc == 0 ? wcslen (token) : charc;

    char *src_buf = (char *) alloca (token_len + 1);

    src_buf = (char *) memset (src_buf, 0, token_len + 1);

    if ((bytec = wcstombs (src_buf, token, token_len)) < token_len)
      return bytec;

    char *dst_buf = (char *) alloca (token_len + 3);

    if ((bytec = std::snprintf (dst_buf, token_len + 3, "'%s'", src_buf)) < token_len + 2)
      return bytec;

    _what.append (dst_buf);

    return bytec;
  }

};

/**
 * @brief The JSON_Out_Of_Range class
 */
class JSON_Out_Of_Range : public JSON_Error
{
public:
  /**
   * @brief Syntax_Error
   * @param what
   */
  JSON_Out_Of_Range (const char * const what)
    : JSON_Error (what)
  {}
};

#endif // JSON_EXCEPTION

