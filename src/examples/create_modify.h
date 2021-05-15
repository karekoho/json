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
  // Assign a pointer to an object
  // Objects and arrays are constructed using initializer lists
  json::json j = new json::object {
            { L"Image",
              new json::object {
                { L"Width",new json::number (800.0) },
                { L"Height",new json::number (600.0) },
                { L"Title", new json::string (L"View from 15th Floor") },
                { L"Thumbnail", new json::object {
                    { L"Url",new json::string (L"http://www.example.com/image/481989943") },
                    { L"Height",new json::number (static_cast<long long>(125) ) },
                    { L"Width", new json::number (static_cast<long long> (100)) },
                  }
                },
                { L"Animated", new json::boolean (false) },
                { L"IDs", new json::array { new json::number (static_cast<long long> (116)), new json::number (static_cast<long long> (943)),
                  new json::number (static_cast<long long> (234)), new json::number (static_cast<long long> (38793)) } }
              }
            }
          };

  json::array & ids = static_cast<json::array &> (j[L"Image"][L"IDs"]);

  // Modify value
  ids[static_cast<size_t> (1)] = static_cast<long long> (100);

  // Assigning format::undefined removes the value
  ids[static_cast<size_t> (3)] = json::undefined ();

  std::wcout << ids.stringify () << std::endl;
  // output: [116,100,234]

  // Iterate the array
  std::for_each (ids.begin (),
                 ids.end (),
                 [] (json::value & v)
  {
    json::number & id = static_cast<json::number &> (v);
    long l = static_cast<long> (id.get ());
    std::wcout << l << L" ";
  });
  // output: 116 100 234
}
#endif // CREATE_MODIFY_H
