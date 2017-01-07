#include <iostream>
#include <json/json.h>

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

int
main ()
{

  JSON j = L"{\
    \"Image\": {\
        \"Width\":  800,\
        \"Height\": 600,\
        \"Title\":  \"View from 15th Floor\",\
        \"Thumbnail\": {\
            \"Url\":    \"http://www.example.com/image/481989943\",\
            \"Height\": 125,\
            \"Width\":  100\
        },\
        \"Animated\" : false,\
        \"IDs\": [116, 943, 234, 38793]\
      }\
  }";

  // std::wcout << j.value () << std::endl;

  std::wcout << j[L"Image"].value () << std::endl;

  Number & n = static_cast<Number &> (j[L"Image"][L"Width"]);
  std::cout << n.value () << std::endl;

  // std::wcout << j[L"Image"][L"Thumbnail"][L"Url"].value () << std::endl;

  std::wcout << j[L"Image"][L"IDs"].value () << std::endl;

  return 0;
}

