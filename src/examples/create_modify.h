#ifndef CREATE_MODIFY_H
#define CREATE_MODIFY_H

#include <iostream>
#include <algorithm>
#include <format/json.h>

using namespace format;

void
create_modify ()
{
  std::wcout << std::endl << "Create and modify:" << std::endl;

  // Construct a JSON object
  // Objects and arrays are constructed using initializer lists
  const json::json j ( new json::object {
            { L"Image",
              new json::object {
                { L"Width", new json::number (800.0) },
                { L"Height", new json::number (600.0) },
                { L"Title", new json::string (L"View from 15th Floor") },
                { L"Thumbnail", new json::object { { L"Url", new json::string (L"http://www.example.com/image/481989943") },
                                                   { L"Height", new json::number (static_cast<long long>(125) ) },
                                                   { L"Width", new json::number (static_cast<long long> (100)) } }
                },
                { L"Animated", new json::boolean (false) },
                { L"IDs", new json::array { new json::number (static_cast<long long> (116)),
                                            new json::number (static_cast<long long> (943)),
                                            new json::number (static_cast<long long> (234)),
                                            new json::number (static_cast<long long> (38793)) }
                }
              }
            }
          } );

  // Get the array
  const json::array & ids = static_cast<const json::array &> (j[L"Image"][L"IDs"]);

  // Make a copy via copy constructor
  json::array *copy_ids = new json::array (ids);

  // Modify existing value
  (*copy_ids)[1] = static_cast<long long> (100);

  // Add a new value. If index is greater than array.size - 1,
  // new value goes at the end, i.e. array[array.size]
  (*copy_ids)[4] = static_cast<long long> (101);

  // Remove value by assigning undefined to it
  (*copy_ids)[3] = json::undefined ();

  std::wcout << copy_ids->stringify () << std::endl;
  // output: [116,100,234,101]

  delete copy_ids;

  // Iterate the original values
  std::for_each (ids.begin (),
                 ids.end (),
                 [] (const json::value & v)
  {
      try
        {
          std::wcout << v.as<unsigned int> () << L" ";
        }
      catch (const json::json_conversion_error & e)
        {
          std::cerr << e.what () << std::endl;
        }
  });
  // output: 116 943 234 38793
}
#endif // CREATE_MODIFY_H
