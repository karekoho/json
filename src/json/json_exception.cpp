#include <string.h>

#include "json_exception.h"

size_t
format::json_syntax_error::_add_token (const wchar_t *token, size_t offset)
{
  if (*token == 0)
    return 0;

  std::mbstate_t state = std::mbstate_t ();

  size_t mbytec = 0;
  size_t token_len = std::wcsrtombs (nullptr, & token, 0, & state);

  if (offset > 0)
    {
      const wchar_t * token_offset = token + offset;
      token_len = token_len - std::wcsrtombs (nullptr, & token_offset, 0, & state);
    }

  // Allocate for ' + token + ' + 0
  char *dst_buf = static_cast<char *> (memset (static_cast<char *> (alloca (token_len  + 3)), 0, token_len  + 3));
  const char * const begin_dst_buf = dst_buf;

  if ((mbytec = std::wcsrtombs (dst_buf + 1, & token, token_len + 1, & state)) == 0)
    {
      _what.append ("'wide character conversion error'");
      return mbytec;
    }

  *dst_buf = 39;
  *(dst_buf + (token_len + 1)) = 39;

  _what.append (begin_dst_buf);

  return  mbytec;
}
