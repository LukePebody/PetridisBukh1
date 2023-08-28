//
// Created by Luke Pebody on 20/07/2023.
//

#include <iostream>
#include <sstream>
#include "VectorMultiSet.h"

VectorMultiSet::VectorMultiSet() : _v({0}), _count(0), _size(1)
{
}

void VectorMultiSet::resize(int k) {
//    std::cout << "Resizing from " << _size << " to " << k << std::endl;
    if (k > _size) {
        _v.resize(k);
        _size = k;
    }
}

void VectorMultiSet::add(int i) {
    if (i >= _size)
        resize(i + 1);
    if (_v[i] == 0)
        ++_count;
    ++_v[i];
}

void VectorMultiSet::remove(int i) {
    --_v[i];
    if (_v[i] == 0)
        --_count;
}

int VectorMultiSet::size() const {
    return _count;
}

std::string VectorMultiSet::to_string() const {
    std::ostringstream oss;
    bool started = false;
    for (int i = 0; i < _v.size(); ++i)
    {
        for (int j = 0; j < _v[i]; ++j)
        {
            if (started)
                oss << ", ";
            oss << i;
            started = true;
        }
    }
    return oss.str();
}

