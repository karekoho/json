#ifndef PARSE_H
#define PARSE_H

// OBJECT:
//  {
//          "Image": {
//              "Width":  800,
//              "Height": 600,
//              "Title":  "View from 15th Floor",
//              "Thumbnail": {
//                  "Url":    "http://www.example.com/image/481989943",
//                  "Height": 125,
//                  "Width":  100
//              },
//              "Animated" : false,
//              "IDs": [116, 943, 234, 38793]
//            }
//        }
// ARRAY:
//[
//        {
//           "precision": "zip",
//           "Latitude":  37.7668,
//           "Longitude": -122.3959,
//           "Address":   "",
//           "City":      "SAN FRANCISCO",
//           "State":     "CA",
//           "Zip":       "94107",
//           "Country":   "US"
//        },
//        {
//           "precision": "zip",
//           "Latitude":  37.371991,
//           "Longitude": -122.026020,
//           "Address":   "",
//           "City":      "SUNNYVALE",
//           "State":     "CA",
//           "Zip":       "94085",
//           "Country":   "US"
//        }
//      ]

#include <iostream>
#include <algorithm>
#include <format/json.h>

using namespace format;

void
parse ()
{
  std::wcout << std::endl << "Parse and read:" << std::endl;

  // Construct a JSON object with a wide character string
  json::json j = L"{\
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
  }";

  // Get the image object.
  json::value & val = j[L"Image"];

  {
    // Get the primitive value using value::as<T> ()
    // Possible values are: const wchar_t *, long, bool
    const wchar_t * title = val[L"Title"].as<const wchar_t *> ();

    long width = val[L"Title"].as<long> ();

    bool animated = val[L"Animated"].as<bool> ();

    // "Description" is empty string, because it's defined as null
    const wchar_t * description = val[L"Description"].as<const wchar_t *> ();
  }

  {
    // To get the internal JSON object, use static_cast<T>
    json::object & image = static_cast<json::object &> (val);
    json::array & ids = static_cast<json::array &> (val[L"IDs"]);
    json::string & title = static_cast<json::string &> (val[L"Title"]);
    json::number & width = static_cast<json::number &> (val[L"Width"]);
    json::boolean & animated = static_cast<json::boolean &> (val[L"Animated"]);
    json::null & description = static_cast<json::null &> (val[L"Description"]);

    {
      // Get the primitive value of an object
      bool value = animated.get ();
    }

    // Object and array values are represented as a string
    std::wcout << ids.get () << std::endl;
    // output: [116,943,234,38793]

    // All values can be iterated.
    // Iterate the array.
    std::for_each (ids.begin (),
                   ids.end (),
                   [] (json::value & v)
    {
      std::wcout << v.get () << L" ";
    });
    // output: 116 943 234 38793
  }
}
#endif // PARSE_H
