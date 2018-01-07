# JSON for C++

## Introduction
JSON for C++ is a library for encoding and decoding JSON in C++ applications.

The result of decoding JSON encoded text input is a format::json object, an associative container such as std::map or an EcmaScript object.
The elements of format::json object are accessed and assigned via the "[]" operator.

Encoding a format::json object is done by the format::json::stringify() method.

JSON for C++ also supports transforming the computed value using the "reviver" callback function
for format::json::parse(text [,reviver]), as with JSON.parse() in EcmaScript.
## Requirements
C++ compiler supporting the C++11 standard,
such as GCC >= 4.5 or Clang >= 3.3
## Installation
Get the source code:
```
git clone https://github.com/karekoho/json.git
```
or download and extract the zip archive.

In the root of the repository run the following commands:
```
cmake . 
make 
make install
```
A shared library called `libjson` will be created in `/usr/local/lib`

The development headers will be found in `/usr/local/include/format`

Include 
```c++
<format/json.h> 
```
in your source code to use JSON for C++.


# Usage
## Decoding JSON
```c++
#include <format/json.h>

using namespace format;

json j (L"{\    // Construct a format::json object with a wide character string
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
})";

// Access an element, the "Image" object
value & val = j[L"Image"];

// format::value is the interface for all JSON values.
// format::value.get() returns value the object is holding
std::wcout << val[L"Title"].get () << std::endl;
// output: "View from 15th Floor"

std::wcout << val[L"Width"].get () << std::endl;
// output: 800

std::wcout << val[L"Animated"].get () << std::endl;
// output: true

std::wcout << val[L"Description"].get () << std::endl;
// output: null

// format::value.get() returns the value as const wchar_t *
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
## Encoding JSON
```c++
#include <format/json.h>

using namespace format;

json j (new object {    // Construct a format::json object with a format::object object
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
        });

array & ids = static_cast<array &> (j[L"Image"][L"IDs"]);

// Modify value
ids[(size_t) 1] = (long) 100;

// Assigning format::undefined removes the value
ids[(size_t) 3] = undefined ();

std::wcout << ids.stringify () << std::endl;
// output: [116,100,234]
```
## Transforming computed values
```c++
#include <format/json.h>

using namespace format;

value *
fn_reviver (const wchar_t *key, value *val)
{
  if (wcscmp (key, L"Thumbnail") == 0)  // "Thumbnail" object is removed
    return new undefined ();

  if (wcscmp (key, L"Description") == 0
      && val->type () == value::null_t)  // Value of type format::null is replaced
    return new string (L"n/a");

  return val;
}

value *v = json::parse ( L"{\
    \"Image\": {\
        \"Width\":  800,\
        \"Height\": 600,\
        \"Title\":  \"View from 15th Floor\",\
        \"Description\":null,\
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
// output: {"Image":{"IDs":[116,943,234,38793],"Description":"n/a",
// "Height":600,"Animated":true,"Title":"View from 15th Floor","Width":800}}
```
