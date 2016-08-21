#include "json_value_parse_mock.h"

json_value_parse_mock::json_value_parse_mock (const char *readp, const char *endp, value *parent)
    : value(readp,endp, parent)
{
}

const char *
json_value_parse_mock::parse (const char *readp)
{
    return readp;
}

const value &
json_value_parse_mock::at (const char *key) const
{
    return *this;
}

value::otype
json_value_parse_mock::type () const
{
    return value::null;
}

size_t
json_value_parse_mock::size () const
{
    return 0;
}
