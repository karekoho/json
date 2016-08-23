#include "json_value_parse_mock.h"

json_value_parse_mock::json_value_parse_mock (const char *endp, value *parent, size_t charc, otype type)
    : value (endp, parent, charc)
{
    _type = type;
}

const value &
json_value_parse_mock::at (const char *key) const
{
    return *this;
}

value::otype
json_value_parse_mock::type () const
{
    return _type;
}

size_t
json_value_parse_mock::size () const
{
    return 0;
}
