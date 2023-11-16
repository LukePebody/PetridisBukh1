//
// Created by Luke Pebody on 16/11/2023.
//

#include "RecordHolder.h"

bool RecordHolder::inform(double x)
{
    if (!_set)
    {
        _set = true;
        _record = x;
        return true;
    }
    if ((_increasing && (_record < x)) || ((!_increasing) && (_record > x)))
    {
        _record = x;
        return true;
    }
    return false;
}
