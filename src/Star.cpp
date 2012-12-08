#include <assert.h>

#include "Star.hpp"

Star::Star(size_t center, 
    size_t exclude1, size_t exclude2) :
    _center(center),
    _exclude1(exclude1),
    _exclude2(exclude2)
{
    assert(_center >= 0 || 
        _exclude1 >= -1 || _exclude2 >= -1);
    assert(!(_exclude1 == -1 && _exclude2 != -1));
    assert(_center != _exclude1);
    assert(_exclude1 == -1 || _exclude1 != _exclude2);
}

size_t Star::center() const
{
    return _center;
}
size_t Star::exclude1() const
{
    return _exclude1;
}
size_t Star::exclude2() const
{
    return _exclude2;
}

