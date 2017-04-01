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

  // std::wcout << j.get  () << std::endl;
}

void
assing ()
{
}

void
get ()
{
}

void
iterate ()
{
}

void
nop ()
{}

int
main (int argc, char *argv[])
{
  struct timeval tp;

  typedef void  (*Benchmark) ();

  std::array<Benchmark, 5> task = {
    & nop ,
    & parse ,
    & assing ,
    & get ,
    & iterate
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

