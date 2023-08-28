//
// Created by Luke Pebody on 21/07/2023.
//

#include "math.h"
#include <sstream>

#include "OneSet.h"

OneSet::OneSet(int N):
    _contents(N),
    _sum(),
    _dilate()
{
}

void OneSet::toggle(int i) {
    if (_contents.contains(i))
    {
        _contents.remove(i);
        for (int j: _contents)
        {
            _sum.remove(i + j);
            _dilate.remove(2 * i + j);
            _dilate.remove(2 * j + i);
        }
        _sum.remove(2*i);
        _dilate.remove(3*i);
    }
    else
    {
        _sum.add(2*i);
        _dilate.add(3*i);
        for (int j: _contents)
        {
            _sum.add(i + j);
            _dilate.add(2 * i + j);
            _dilate.add(2 * j + i);
        }
        _contents.insert(i);
    }
}

std::string OneSet::to_string()
{
    std::ostringstream oss;
    oss << "A = {";
    bool started = false;
    for (int a: _contents)
    {
        if (started)
            oss << ", ";
        oss << a;
        started = true;
    }
    oss << "}" << std::endl;
    oss << "A + A = " << _sum.to_string() << std::endl;
    oss << "A + 2.A = " << _dilate.to_string() << std::endl;
    oss << _contents.size() << "," << _sum.size() << "," << _dilate.size() << std::endl;
    return oss.str();
}

size_t OneSet::size()
{
    return _contents.size();
}

size_t OneSet::sum_size()
{
    return _sum.size();
};

size_t OneSet::dilate_size()
{
    return _dilate.size();
}
