#include "json_object_iterator.h"

Object_Iterator::Object_Iterator (const std::unordered_map<std::string, Value *> & umap)
  : _begin (umap.begin ()),
    _end (umap.end ())
{
}

Value &
Object_Iterator::next ()
{
  return *(*_begin++).second;
}

bool
Object_Iterator::hasNext ()
{
  return _begin != _end;
}
