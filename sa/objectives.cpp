//
// Created by Luke Pebody on 16/11/2023.
//

#include <math.h>

#include "objectives.h"
#include "Rusza.h"

bool all_zero(const std::vector<double>& probs)
{
    for (auto prob: probs)
        if (prob != 0)
            return false;
    return true;
}


double objective_dilate_two_more_than_one(const std::vector<double>& probs)
{
    if (all_zero(probs))
        return 0;
    double l1 = log(rusza_probability(rusza_sequence(probs, 1)));
    double l2 = log(rusza_probability(rusza_sequence(probs, 2)));

    double sum = 0;
    for (auto prob: probs)
        sum += prob;

    if (sum <= 1)
        return 0;

    return (l1 - l2)/log(sum);
}

double objective_dilate_one_over_two(const std::vector<double>& probs)
{
    if (all_zero(probs))
        return 0;
    double l1 = log(rusza_probability(rusza_sequence(probs, 1)));
    double l2 = log(rusza_probability(rusza_sequence(probs, 2)));

    return l2 / l1;
}

double objective_dilate_hanson_petridis(const std::vector<double>& probs)
{
    if (all_zero(probs))
        return 0;
    double l1 = log(rusza_probability(rusza_sequence(probs, 1)));
    double l2 = log(rusza_probability(rusza_sequence(probs, 2)));

    double sum = 0;
    for (auto prob: probs)
        sum += prob;

    return (l2 - log(sum)) / (l1 - log(sum));
}

double objective_mdts(const std::vector<double>& probs)
{
    if (all_zero(probs))
        return 0;
    double ls = log(rusza_probability(rusza_sequence(probs, 1)));
    double ld = log(rusza_probability(rusza_sequence(probs, -1)));

    double sum = 0;
    for (auto prob: probs)
        sum += prob;

    if (sum <= 1)
        return 0;

    return (ld - ls)/log(sum);
}

double objective_mstd(const std::vector<double>& probs)
{
    if (all_zero(probs))
        return 0;
    double ls = log(rusza_probability(rusza_sequence(probs, 1)));
    double ld = log(rusza_probability(rusza_sequence(probs, -1)));

    double sum = 0;
    for (auto prob: probs)
        sum += prob;

    return (ls - log(sum)) / (ld - log(sum));
}
