# JSON support for C++

## Introduction
JSON support for C++ is a library to parse JSON unicode input, 

create and modify JSON objects and stringify them back to characters.

It's goal is to be simple and self-explanatory, so getting started is easy and no in-depth guides are needed.


## Installation
Get the source code:
```
git clone https://github.com/karekoho/json.git
```
or download and extract the zip archive.

Go to the root of the repository and run: 
```
cmake . 
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
```c++
#include <format/json.h>
#include <iostream>
#include <algorithm>

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

  // Get the whole structure as wchar_t *
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
  std::for_each (ids.begin (),
                 ids.end (),
                 [] (value & v)
  {
    // Cast to number and get the value as double
    number & id = static_cast<number &> (v);
    double d = id.get ();
    std::wcout << d << std::endl;
  });

  return 0;
}
```
