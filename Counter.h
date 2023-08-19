//
// Created by Luke Pebody on 20/07/2023.
//

#ifndef PETRIDISBUKH1_COUNTER_H
#define PETRIDISBUKH1_COUNTER_H


class Counter
{
private:
    Counter* _next;
    int _n;
    bool _on;

public:
    Counter(int n);
    ~Counter();
    int count();
};


#endif //PETRIDISBUKH1_COUNTER_H
