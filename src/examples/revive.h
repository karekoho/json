#ifndef REVIVE_H
#define REVIVE_H

#include <cstring>
#include <iostream>
#include <format/json.h>

using namespace format;

/**
 * This function modifies the parsed json object
 * by returning modified value
 * @param key The key in json object
 * @param val The value to modify
 * @return
 */
json::value *
fn_reviver (const wchar_t *key, json::value *val)
{
  json::value::value_t type = val->type ();

  // Replace null value with "n/a"
  if (wcscmp (key, L"Description") == 0
      && type == json::value::null_t)
    return new json::string (L"n/a");

  // Remove the Thumbnail object by returning undefined
  if (wcscmp (key, L"Thumbnail") == 0)
    return new json::undefined ();

  // Otherwise return unchanged value
  return val;
}

void
revive ()
{
  std::wcout << std::endl << "Revive:" << std::endl;

  // Create json object and pass the reviver function
  json::value *v = json::json::parse ( L"{\
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
    }",
    fn_reviver); // The reviver

  std::wcout << v->stringify () << std::endl;
  // output: {"Image":{"IDs":[116,943,234,38793],"Description":"n/a",
  // "Height":600,"Animated":true,"Title":"View from 15th Floor","Width":800}}
}

#endif // REVIVE_H
