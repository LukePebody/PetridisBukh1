//
// Created by Luke Pebody on 20/07/2023.
//

#ifndef PETRIDISBUKH1_VECTORMULTISET_H
#define PETRIDISBUKH1_VECTORMULTISET_H


#include <vector>

class VectorMultiSet
{
private:
    std::vector<int> _v;
    int _count;
    int _size;
    void resize(int k);

    VectorMultiSet(std::vector<int> v, int count, int size): _v{v}, _count{count}, _size{size}
    {

    }
public:
    VectorMultiSet clone()
    {
        return VectorMultiSet(_v, _count, _size);
    }
    VectorMultiSet();
    void add(int i);
    void remove(int i);
    int size() const;
    std::string to_string() const;
};




#endif //PETRIDISBUKH1_VECTORMULTISET_H
