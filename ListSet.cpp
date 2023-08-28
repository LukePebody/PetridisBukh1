//
// Created by Luke Pebody on 27/08/2023.
//

#include <iostream>
#include "ListSet.h"
#include <set>

ListSet::ListSet(int initial_max)
{
    _range = initial_max;
    _size = 0;

    _nodes = std::vector<Node>(initial_max+3);
    for (int i = 0; i <= initial_max; ++i)
        _nodes[i + 2].content = i;

    _nodes[0].next = 1;
    _nodes[0].content = -2;
    _nodes[0].included = true;

    _nodes[1].previous = 0;
    _nodes[1].content = -1;
    _nodes[1].included = true;

    _range = initial_max;

    _size = 0;
//    if (!verify())
//        throw std::runtime_error("ListSet failed at construction");
}

//bool ListSet::verify()
//{
//    if (!(_nodes[0].included && _nodes[1].included))
//        return false;
//    std::set<int> s;
//    auto prev_node = 0;
//    for (auto node_in_list = _nodes[0].next; node_in_list != 1; node_in_list = _nodes[node_in_list].next)
//    {
//        if (prev_node != _nodes[node_in_list].previous)
//            return false;
//        if (s.find(_nodes[node_in_list].content) != s.end())
//            return false;
//        if (_nodes[node_in_list].content < 0 || _nodes[node_in_list].content > _range)
//            return false;
//        s.insert(_nodes[node_in_list].content);
//        prev_node = node_in_list;
//    }
//    if (_range + 3 != _nodes.size())
//        return false;
//    for (int i = 0; i <= _range; ++i)
//    {
//        bool should_be_included = s.find(i) != s.end();
//        bool is_included = _nodes[i + 2].included;
//        if (should_be_included != is_included)
//            return false;
//        if (_nodes[i + 2].content != i)
//            return false;
//    }
//    return true;
//}

bool ListSet::contains(int i)
{
    if (i < 0)
        return false;
    if (i > _range)
        return false;
    return _nodes[i + 2].included;
}

void ListSet::insert(int i)
{
    if (i < 0)
        throw std::runtime_error("Cannot insert negative numbers from ListSet");
    if (i > _range) {
//        std::cout << "resizing listset from " << _range << " to " << i << std::endl;
        for (int j = _range + 1; j <= i; ++j) {
            _nodes.push_back(Node());
            _nodes[j + 2].content = j;
        }
        _range = i;
    }
    if (_nodes[i + 2].included)
        throw std::runtime_error("Cannot insert already inserted element into set");
    auto previous_end = _nodes[1].previous;
    _nodes[i + 2].previous = previous_end;
    _nodes[previous_end].next = i + 2;
    _nodes[i + 2].next = 1;
    _nodes[1].previous = i + 2;
    _nodes[i + 2].included = true;
    ++_size;
//    if (!verify())
//        throw std::runtime_error("ListSet failed at insertion");
}

void ListSet::remove(int i)
{
    if (i < 0)
        throw std::runtime_error("Cannot remove negative numbers from ListSet");
    if (i > _range || !_nodes[i + 2].included)
        throw std::runtime_error("Cannot remove non-inserted elements from ListSet");
    auto previous_previous = _nodes[i + 2].previous;
    auto previous_next = _nodes[i + 2].next;
    _nodes[previous_previous].next = previous_next;
    _nodes[previous_next].previous = previous_previous;
    _nodes[i + 2].previous = -1;
    _nodes[i + 2].next = -1;
    _nodes[i + 2].included = false;
    --_size;
//    if (!verify())
//        throw std::runtime_error("ListSet failed at removal");
}

int ListSet::size()
{
    return _size;
}

