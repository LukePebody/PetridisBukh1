//
// Created by Luke Pebody on 27/08/2023.
//

#ifndef PETRIDISBUKH1_LISTSET_H
#define PETRIDISBUKH1_LISTSET_H

#include <vector>

struct Node
{
    // standard pointers but no ownership
    int previous;
    int next;
    int content;
    bool included;

    Node(): previous(-1), next(-1), content(-1), included(false) { }
};

class ListSet
{
private:
    int _size;
    int _range;
    std::vector<Node> _nodes;

public:
    class iterator {
    public:
        iterator(const std::vector<Node>& nodes, const int ptr): _nodes(nodes), ptr(ptr){}
        iterator operator++() {ptr = _nodes[ptr].next; return *this; }
        bool operator!=(const iterator & other) const { return ptr != other.ptr;  }
        const int& operator*() const { return _nodes[ptr].content; }
    private:
        int ptr;
        const std::vector<Node>& _nodes;
    };
    iterator begin() const { return iterator(_nodes, _nodes[0].next); }
    iterator end() const { return iterator(_nodes, 1); }
//    bool verify();
    ListSet(int initial_max);

    bool contains(int i);
    void remove(int i);
    void insert(int i);
    int size();
    std::vector<int> as_vector()
    {
        std::vector<int> v;
        for (auto it = begin(); it != end(); ++it)
        {
            v.push_back(*it);
        }
        return v;
    }
};

#endif //PETRIDISBUKH1_LISTSET_H
