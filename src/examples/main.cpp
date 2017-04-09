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
#include <format/json.h>

using namespace format;

int
main ()
{
  json j = L"{\
    \"Image\": {\
        \"Width\":  800,\
        \"Height\": 600,\
        \"Title\":  \"View from 15th Floor\",\
        \"Thumbnail\": {\
            \"Url\":    \"http://www.example.com/image/481989943\",\
            \"Height\": 125,\
            \"Width\":  100\
        },\
        \"Animated\" : true,\
        \"IDs\": [116, 943, 234, 38793]\
      }\
  }";

  // Get the whole structure  as wchar_t *
  std::wcout << j.get () << std::endl;

  // Cast to object
  object & image = static_cast<object &> (j[L"Image"]);

  // Get the object as wchar_t *
  std::wcout << image[L"Thumbnail"].get () << std::endl;

  // Cast to boolean
  boolean & animated = static_cast<boolean &> (image[L"Animated"]);

  // Get value as bool
  std::wcout << animated.get () << std::endl;

  // Cast to array
  array & ids = static_cast<array &> (image[L"IDs"]);

  // Iterate the array
  for (auto it = ids.begin (); it != ids.end (); ++it)
    {
      // Cast to number and get the value as double
      number & id = static_cast<number &> (*it);
      double d = id.get ();
      std::wcout << d << std::endl;
    }

  return 0;
}

