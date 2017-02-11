#ifndef JSON_EXCEPTION
#define JSON_EXCEPTION

#include <exception>
#include <string>
#include <cstdlib>

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
    char str[4];

    std::snprintf (str, 4, "'%c'", (char) token);   /// TODO: unit test

    _what.append (str, 3);
  }

  /**
   * @brief Syntax_Error
   * @param what
   * @param token
   */
  JSON_Syntax_Error (const char * const what, const wchar_t *token)
    : JSON_Error (what)
  {
    _what.append ((char *) token);
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

