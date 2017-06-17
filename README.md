# JSON support for C++

## Introduction
JSON support for C++ is a library to parse JSON unicode input, 

create and modify JSON objects and stringify them back to characters.

It's goal is to be simple and self-explanatory, so getting started is easy and no in-depth guides are needed.


## Installation
Checkout out the repository.

Go to the directory you want the compilation output to be placed.

For example, if you are at the top of the repository, then run: 
```
cmake . 
make
make install
```
The single dot after `cmake` refers to the location of the `CMakeLists.txt` 

Thus if you are two directories below the root of the repo,

then the cmake command will be `cmake ../..`

If no problems occur,

a shared library called `libjson` will be created in `/usr/local/lib`

Headers will be copied to `/usr/local/include/format`

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
