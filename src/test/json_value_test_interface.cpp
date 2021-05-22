#include "json_value_test_interface.h"

const char *json_value_test_interface::_input[] =  {
    "{\"Image\": {\
          \"Width\":  800,\
          \"Height\": 600,\
          \"Title\":  \"View from 15th Floor\",\
          \"Thumbnail\": {\
                \"Url\": \"http://www.example.com/image/481989943\",\
                \"Height\": 125,\
                \"Width\":  100},\
            },\
          \"Animated\" : false,\
          \"IDs\": [116, 943, 234, 38793]\
        }\
     }",

    "[\
        {\
            \"precision\": \"zip\",\
            \"Latitude\":  37.7668,\
            \"Longitude\": -122.3959,\
            \"Address\":   \"\"\,\
            \"City\":      \"SAN FRANCISCO\",\
            \"State\":     \"CA\",\
            \"Zip\":       \"94107\",\
            \"Country\":   \"US\"\
        },\
        {\
            \"precision\": \"zip\",\
            \"Latitude\":  37.371991,\
            \"Longitude\": -122.026020,\
            \"Address\":   \"\",\
            \"City\":      \"SUNNYVALE\",\
            \"State\":     \"CA\",\
            \"Zip\":       \"94085\",\
            \"Country\":   \"US\"\
        }\
    ]"
};



