//
// Created by Luke Pebody on 21/07/2023.
//

#ifndef PETRIDISBUKH1_ONESET_H
#define PETRIDISBUKH1_ONESET_H


#include <set>
#include "VectorMultiSet.h"
#include "ListSet.h"

class OneSet
{
private:
    ListSet _contents;
    VectorMultiSet _sum;
    VectorMultiSet _dilate;

public:
    OneSet(int initial_max);
    void toggle(int i);
    size_t size();
    size_t sum_size();
    size_t dilate_size();
    std::string to_string();
};

#endif //PETRIDISBUKH1_ONESET_H
