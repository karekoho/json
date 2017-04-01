#include <iostream>
#include <sys/time.h>
#include <array>
#include <json/json.h>

using namespace format;

void
parse ()
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
        \"Animated\" : false,\
        \"IDs\": [116, 943, 234, 38793]\
      }\
  }";
}

void
construct ()
{
  json j = new object {
            { L"Image",
              new object {
                { L"Width",new number (800) },
                { L"Height",new number (600) },
                { L"Title", new string (L"View from 15th Floor") },
                { L"Thumbnail", new object {
                    { L"Url",new string (L"http://www.example.com/image/481989943") },
                    { L"Height",new number (125) },
                    { L"Width", new number (100) },
                  }
                },
                { L"Animated", new boolean (false) },
                { L"IDs", new array { new number (116), new number (943), new number (234), new number (38793) } }
              }
            }
          };
}

void
assign ()
{
  json j;
}

void
erase ()
{
  json j = new object {
            { L"Image",
              new object {
                { L"Width",new number (800) },
                { L"Height",new number (600) },
                { L"Title", new string (L"View from 15th Floor") },
                { L"Thumbnail", new object {
                    { L"Url",new string (L"http://www.example.com/image/481989943") },
                    { L"Height",new number (125) },
                    { L"Width", new number (100) },
                  }
                },
                { L"Animated", new boolean (false) },
                { L"IDs", new array { new number (116), new number (943), new number (234), new number (38793) } }
              }
            }
          };

  j[L"Image"][L"Thumbnail"][L"Url"] = undefined ();
  j[L"Image"][L"Thumbnail"][L"Height"] = undefined ();
  j[L"Image"][L"Thumbnail"][L"Width"] = undefined ();

  j[L"Image"][L"Width"] = undefined ();
  j[L"Image"][L"Height"] = undefined ();
  j[L"Image"][L"Title"] = undefined ();

  j[L"Image"][L"Animated"] = undefined ();
  j[L"Image"][L"IDs"] = undefined ();
}

void
get ()
{
  json j = new object {
            { L"Image",
              new object {
                { L"Width",new number (800) },
                { L"Height",new number (600) },
                { L"Title", new string (L"View from 15th Floor") },
                { L"Thumbnail", new object {
                    { L"Url",new string (L"http://www.example.com/image/481989943") },
                    { L"Height",new number (125) },
                    { L"Width", new number (100) },
                  }
                },
                { L"Animated", new boolean (false) },
                { L"IDs", new array { new number (116), new number (943), new number (234), new number (38793) } }
              }
            }
          };

  dynamic_cast<number &> (j[L"Image"][L"Width"]).get ();
  dynamic_cast<number &> (j[L"Image"][L"Height"]).get ();
  dynamic_cast<string &> (j[L"Image"][L"Title"]).get ();
  dynamic_cast<string &> (j[L"Image"][L"Thumbnail"][L"Url"]).get ();
  dynamic_cast<number &> (j[L"Image"][L"Thumbnail"][L"Height"]).get ();
  dynamic_cast<number &> (j[L"Image"][L"Thumbnail"][L"Width"]).get ();
  dynamic_cast<boolean &> (j[L"Image"][L"Animated"]).get ();
  dynamic_cast<number &> (j[L"Image"][L"IDs"][(size_t) 0]).get ();
}

void
iterate ()
{
  json j = new object {
            { L"Image",
              new object {
                { L"Width",new number (800) },
                { L"Height",new number (600) },
                { L"Title", new string (L"View from 15th Floor") },
                { L"Thumbnail", new object {
                    { L"Url",new string (L"http://www.example.com/image/481989943") },
                    { L"Height",new number (125) },
                    { L"Width", new number (100) },
                  }
                },
                { L"Animated", new boolean (false) },
                { L"IDs", new array { new number (116), new number (943), new number (234), new number (38793) } }
              }
            }
          };

  object & o = dynamic_cast<object &> (j[L"Image"]);

  for (auto it = o.begin (); it != o.end (); ++it)
    (*it);
}

void
nop ()
{}

int
main (int argc, char *argv[])
{
  struct timeval tp;

  typedef void  (*Benchmark) ();

  std::array<Benchmark, 7> task = {
    & nop,        // 0
    & parse,      // 1
    & construct,  // 2
    & assign,     // 3
    & erase,      // 4
    & get,        // 5
    & iterate     // 6
  };

  unsigned int n =  argc > 1 ? atoi (argv[1]) : 0;

  n = n < task.size () ? n : 0;

  gettimeofday (& tp, NULL);

  long int  ms_start = tp.tv_sec * 1000 + tp.tv_usec / 1000;
  long int  ms_end = 0;

  for (size_t idx = 0; idx < 1000; idx++)
    {
      task[n] ();
    }

  gettimeofday (& tp, NULL);

  ms_end = tp.tv_sec * 1000 + tp.tv_usec / 1000;

  std::cout << ms_end - ms_start << std::endl;

  return EXIT_SUCCESS;
}

