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
A shared library called `libformat-json` will be created in `/usr/local/lib`. The development headers will be found in `/usr/local/include/format`.
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
const json::json j = L"{\
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
        \"IDs\": [116, 943, 234, 38793, {}]\
      }\
  }";

// Get the image object.
const json::value & val = j[L"Image"];

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
  const json::object & image = static_cast<const json::object &> (val);
  const json::array & ids = static_cast<const json::array &> (val[L"IDs"]);
  const json::string & title = static_cast<const json::string &> (val[L"Title"]);
  const json::number & width = static_cast<const json::number &> (val[L"Width"]);
  const json::boolean & animated = static_cast<const json::boolean &> (val[L"Animated"]);
  const json::null & description = static_cast<const json::null &> (val[L"Description"]);

  {
    // Get the primitive value of an object
    bool value = animated.value ();
    
    std::cout << value << ',' <<
              // This get the same value
              j[L"Image"][L"Animated"].as<bool> () << std::endl;
    
    // output: 1,1
  }

  // Object and array values are represented as a string
  std::wcout << ids.value () << std::endl;
  // output: [116,943,234,38793,{}]

  // Array and object types are iterable.
  std::for_each (ids.begin (), // Get const_iterator to begin
                 ids.end (),  // Get const_iterator to end
                 [] (const json::value & v)
  {
      try
        {
          std::wcout << v.as<unsigned int> () << L" ";
        }
      catch (const json::json_conversion_error & e)
        {
          // Conversion error is thrown when type casting cannot be done
          std::cerr << e.what () << std::endl;
          // output: Cannot cast object to boolean or numeric type
        }

  });
  // output: 116 943 234 38793
}
```
## Encoding JSON
```c++
#include <format/json.h>

using namespace format;

// Construct a JSON object
// Objects and arrays are constructed using initializer lists
const json::json j ( new json::object {
          { L"Image",
            new json::object {
              { L"Width", new json::number (800.0) },
              { L"Height", new json::number (600.0) },
              { L"Title", new json::string (L"View from 15th Floor") },
              { L"Thumbnail", new json::object { { L"Url", new json::string (L"http://www.example.com/image/481989943") },
                                                 { L"Height", new json::number (125) },
                                                 { L"Width", new json::number (100) } }
              },
              { L"Animated", new json::boolean (false) },
              { L"IDs", new json::array { new json::number (116),
                                          new json::number (943),
                                          new json::number (234),
                                          new json::number (38793) }
              }
            }
          }
        } );

// Get the array
const json::array & ids = static_cast<const json::array &> (j[L"Image"][L"IDs"]);

// Make a copy via copy constructor
json::array *copy_ids = new json::array (ids);

// Modify existing value
(*copy_ids)[1] = 100;

// Add a new value. If index is greater than array.size - 1,
// new value goes at the end, i.e. array[array.size]
(*copy_ids)[4] = 101;

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
