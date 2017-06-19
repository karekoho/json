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

  json j = L"{\
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
  value & val = j[L"Image"];

  // format::value is the interface for all JSON values.
  // format::value.get () returns value the object is holding, but in the JSON text format.
  std::wcout << val[L"Title"].get () << std::endl;
  // output: "View from 15th Floor"

  std::wcout << val[L"Width"].get () << std::endl;
  // output: 800

  std::wcout << val[L"Animated"].get () << std::endl;
  // output: true

  std::wcout << val[L"Description"].get () << std::endl;
  // output: null

  // To get the value as the actual C++ data type, format::value must be cast to the concrete type.
  string & title = static_cast<string &> (val[L"Title"]);         // Holds const wchar_t *
  number & width = static_cast<number &> (val[L"Width"]);         // Holds long or double
  boolean & animated = static_cast<boolean &> (val[L"Animated"]); // Holds bool
  null & description = static_cast<null &> (val[L"Description"]); // Holds nullptr_t

  std::wcout << animated.get () << std::endl;
  // output: 1

  // However, format::object and format::array return their value as JSON text.
  object & image = static_cast<object &> (val);
  array & ids = static_cast<array &> (val[L"IDs"]);

  std::wcout << ids.get () << std::endl;
  // output: [116,943,234,38793]

  // All values can be iterated.
  // Iterate the array.
  std::for_each (ids.begin (),
                 ids.end (),
                 [] (value & v)
  {
    std::wcout << v.get () << L" ";
  });
  // output: 116 943 234 38793
}
#endif // PARSE_H
