//
// Created by Luke Pebody on 16/11/2023.
//

#ifndef PETRIDISBUKH1_RECORDHOLDER_H
#define PETRIDISBUKH1_RECORDHOLDER_H

#endif //PETRIDISBUKH1_RECORDHOLDER_H
class RecordHolder
{
private:
    bool _increasing;
    bool _set;
    double _record;

public:
    RecordHolder(bool increasing): _increasing(increasing), _set(false)
    {

    }

    bool inform(double x);
    double record(){ return _record; }
    bool set(){ return _set; }
};
