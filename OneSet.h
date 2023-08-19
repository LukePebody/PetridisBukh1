//
// Created by Luke Pebody on 21/07/2023.
//

#ifndef PETRIDISBUKH1_ONESET_H
#define PETRIDISBUKH1_ONESET_H


#include <set>
#include "VectorMultiSet.h"

class OneSet
{
private:
    std::set<int> _a;
    bool _logarithmic;
    VectorMultiSet _sum;
    VectorMultiSet _dilate;

    OneSet(std::set<int> a, VectorMultiSet sum, VectorMultiSet dilate): _a{a}, _sum{sum}, _dilate{dilate}
    {

    }
public:
    OneSet clone()
    {
        return OneSet(_a, _sum.clone(), _dilate.clone());
    }
    OneSet(bool logarithmic);
    void toggle(int i);
    double score();
    size_t size();
    size_t sum_size();
    size_t dilate_size();
    std::string to_string();
};

#endif //PETRIDISBUKH1_ONESET_H
