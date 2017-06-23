# JSON for C++

## Introduction
JSON for C++ is a library to parse JSON Unicode text input,

create and modify JSON objects and stringify them back to text.

It's goal is to be simple and self-explanatory, so getting started is easy and no in-depth guides are needed.

## Installation
Get the source code:
```
git clone https://github.com/karekoho/json.git
```
or download and extract the zip archive.

Go to the root of the repository, make sure that you are on branch `master`

and run commands:
```
cmake . 
make 
make install
```
If you want the cmake and compilation output to go to a different directory, 

such as `/path/to/repo_root/build`

then run `cmake ..` in `build`

The double dot after `cmake` refers to the location of `CMakeLists.txt`

A shared library called `libjson` will be created in `/usr/local/lib`

The development headers will be found in `/usr/local/include/format`

Include 
```c++
<format/json.h> 
```
in your source code to use JSON support.


# Usage
## Parsing and reading JSON text input
```c++
#include <format/json.h>

using namespace format;

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
```
## Filtering and transforming parsing results
```c++
#include <format/json.h>

using namespace format;

value *
fn_reviver (const wchar_t *key, value *val)
{
  if (wcscmp (key, L"Thumbnail") == 0) // "Thumbnail" object is removed
    return new undefined ();

  return val;
}

value *v = json::parse ( L"{\
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
  }", fn_reviver);

std::wcout << v->stringify () << std::endl;
// output: {"Image":{"Animated":true,"Title":"View from 15th Floor",
// "Height":600,"IDs":[116,943,234,38793],"Width":800}}
```
## Contructing and modifying a JSON-like object
```c++
#include <format/json.h>

using namespace format;

// Construct a format::json object
json j = new object { // Assign a pointer to format::object
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
              { L"IDs", new array { new number ((long) 116), new number ((long) 943),
                new number ((long) 234), new number ((long) 38793) } }
            }
          }
        };

array & ids = static_cast<array &> (j[L"Image"][L"IDs"]);

// Modify value
ids[(size_t) 1] = (long) 100;

// Assigning format::undefined removes the value
ids[(size_t) 3] = undefined ();
```
