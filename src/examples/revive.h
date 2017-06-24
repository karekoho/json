#ifndef REVIVE_H
#define REVIVE_H

#include <cstring>
#include <iostream>
#include <format/json.h>

using namespace format;

value *
fn_reviver (const wchar_t *key, value *val)
{
  if (wcscmp (key, L"Thumbnail") == 0) // Remove the Thumbnail object
    return new undefined ();

  if (wcscmp (key, L"Description") == 0
      && val->type () == value::null_t)
    // val = new string (L"n/a");
    return new string (L"n/a");

  return val;
}

void
revive ()
{
  std::wcout << std::endl << "Revive:" << std::endl;

  value *v = json::parse ( L"{\
      \"Image\": {\
          \"Width\":  800,\
          \"Height\": 600,\
          \"Title\":  \"View from 15th Floor\",\
          \"Description\": null,\
          \"Thumbnail\": {\
              \"Url\":    \"http://www.example.com/image/481989943\",\
              \"Height\": 125,\
              \"Width\":  100\
          },\
          \"Animated\" : true,\
          \"IDs\": [116, 943, 234, 38793]\
        }\
    }", fn_reviver);

  std::wcout << v->stringify () << std::endl;
  // output: {"Image":{"Animated":true,"Title":"View from 15th Floor",
  // "Height":600,"IDs":[116,943,234,38793],"Width":800}}
}

#endif // REVIVE_H
