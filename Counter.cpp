//
// Created by Luke Pebody on 20/07/2023.
//

#include "Counter.h"

Counter::Counter(int n): _n(n), _next(), _on(false)
{

}

Counter::~Counter()
{
    if (_next != nullptr)
        delete _next;
}

int Counter::count()
{
    _on = !_on;
    if (_on)
        return _n;
    if (_next == nullptr)
        _next = new Counter(_n + 1);
    return _next->count();
}
