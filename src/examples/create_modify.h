#ifndef CREATE_MODIFY_H
#define CREATE_MODIFY_H

#include <iostream>
#include <algorithm>
#include <format/json.h>

using namespace format;

void
create_modify ()
{
  std::wcout << std::endl << "Create and modify" << std::endl;

  // Construct a json object
  json j = new object {
            { L"Image",
              new object {
                { L"Width",new number (800.0) },
                { L"Height",new number (600.0) },
                { L"Title", new string (L"View from 15th Floor") },
                { L"Thumbnail", new object {
                    { L"Url",new string (L"http://www.example.com/image/481989943") },
                    { L"Height",new number ((long) 125) },
                    { L"Width", new number ((long) 100) },
                  }
                },
                { L"Animated", new boolean (false) },
                { L"IDs", new array { new number ((long) 116), new number ((long) 943), new number ((long) 234), new number ((long) 38793) } }
              }
            }
          };

  array & ids = static_cast<array &> (j[L"Image"][L"IDs"]);

  // Modify value
  ids[L"1"] = (long) 100;

  // Remove value
  //ids[(size_t) 3] = undefined (); // FIXME: crash, ok when object is parse
  //value & v = ids[(size_t) 3];
  //v = undefined (); // FIXME: crash

  // Iterate the array
  std::for_each (ids.begin (),
                 ids.end (),
                 [] (value & v)
  {
    number & id = static_cast<number &> (v);
    long l = id.get ();
    std::wcout << l << L" ";
  });
  // output: 116 100 234 38793
}
#endif // CREATE_MODIFY_H
