# JSON for C++
## Introduction
JSON for C++ is a library for encoding and decoding JSON in C++ applications.
Since JSON has a context-free and unambiguous grammar, the implementation is a non-backtracking, recursive-descent LL(1) parser.

The result of decoding JSON encoded text input is a *format::json* object, an associative container such as *std::map* or an EcmaScript object.
The elements of *format::json* object are accessed and assigned with the *[]* and *=* operators.

Encoding a *format::json* object is done by the *format::json::stringify()* method.

JSON for C++ also supports transforming the computed value using the *reviver* callback function 
for *format::json::parse(text [,reviver])*, as with *JSON.parse()* in EcmaScript.
## Requirements
- C++ compiler supporting the C++11 standard, such as GCC >= 4.5 or Clang >= 3.3
## Installation
Get the source code:
```
git clone https://github.com/karekoho/json.git
```
In the _root of the repository_ run the following commands:
```
cmake . 
make & make install
```
A shared library called `libjson` will be created in `/usr/local/lib`. The development headers will be found in `/usr/local/include/format`.
#### Include 
```c++
<format/json.h> 
```
in your source code to use JSON for C++.
# Usage
## Decoding JSON
```c++
#include <format/json.h>

using namespace format;

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

  unsigned int width = val[L"Width"].as<unsigned int> ();

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
```
## Encoding JSON
```c++
#include <format/json.h>

using namespace format;

// Construct a JSON object
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
```
## Transforming computed values
```c++
#include <format/json.h>

using namespace format;

/**
 * This function modifies the parsed JSON object
 * by returning modified value
 * @param key The key in JSON object
 * @param val The value to modify
 * @return modified or original value
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

// Create json object and pass the reviver function
json::json *j = json::json::parse ( L"{\
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

std::wcout << j->stringify () << std::endl;
// output: {"Image":{"IDs":[116,943,234,38793],"Description":"n/a",
// "Height":600,"Animated":true,"Title":"View from 15th Floor","Width":800}}
```
