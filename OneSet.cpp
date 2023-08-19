//
// Created by Luke Pebody on 21/07/2023.
//

#include "math.h"
#include <sstream>

#include "OneSet.h"

OneSet::OneSet(bool logarithmic) :
                 _logarithmic(logarithmic),
                 _a({0}),
                 _sum(),
                 _dilate()
{
}

void OneSet::toggle(int i) {
    if (_a.find(i) == _a.end())
    {
        _sum.add(2*i);
        _dilate.add(3*i);
        for (int j: _a)
        {
            _sum.add(i + j);
            _dilate.add(2 * i + j);
            _dilate.add(2 * j + i);
        }
        _a.insert(i);
    }
    else
    {
        _a.erase(i);
        for (int j: _a)
        {
            _sum.remove(i + j);
            _dilate.remove(2 * i + j);
            _dilate.remove(2 * j + i);
        }
        _sum.remove(2*i);
        _dilate.remove(3*i);
    }
}

double OneSet::score() {
    if (_logarithmic)
    {
        double log1 = log(_dilate.size())-log(_a.size());
        double log2 = log(_sum.size())-log(_a.size());
        double ans = log1 / log2;
        return ans;
    }
    else
    {
        double response = _sum.size() * _sum.size();
        response /= _a.size() * _dilate.size();
        return score();
    }
}

std::string OneSet::to_string()
{
    std::ostringstream oss;
    oss << "A = {";
    bool started = false;
    for (int a: _a)
    {
        if (started)
            oss << ", ";
        oss << a;
        started = true;
    }
    oss << "}" << std::endl;
    oss << "A + A = " << _sum.to_string() << std::endl;
    oss << "A + 2.A = " << _dilate.to_string() << std::endl;
    oss << _a.size() << "," << _sum.size() << "," << _dilate.size() << std::endl;
    return oss.str();
}

size_t OneSet::size()
{
    return _a.size();
}

size_t OneSet::sum_size()
{
    return _sum.size();
};

size_t OneSet::dilate_size()
{
    return _dilate.size();
}
