//
// Created by Luke Pebody on 16/11/2023.
//

#include <map>
#include <math.h>

#include "Rusza.h"

double score(std::vector<double> sequence, double p)
{
    double ans = 0;
    for (double t : sequence)
        if (t != 0)
            ans += pow(t, p);
    return ans;
}

double score_derivative(std::vector<double> sequence, double p)
{
    double ans = 0;
    for (double t : sequence)
        if (t != 0)
            ans += pow(t, p) * log(t);
    return ans;
}

double rusza_probability(const std::vector<double>& sequence)
{
    if (score_derivative(sequence, 0) >= 0)
        return score(sequence, 0);
    if (score_derivative(sequence, 1) <= 0)
        return score(sequence, 1);
    double lower = 0;
    double upper = 1;
    while (true)
    {
        double mid = (lower + upper) * 0.5;
        if (score_derivative(sequence, mid) >= 0)
        {
            if (upper == mid)
                return score(sequence, mid);
            upper = mid;
        }
        else
        {
            if (lower == mid)
                return score(sequence, mid);
            lower = mid;
        }
    }
}

std::vector<double> rusza_sequence(const std::vector<double>& probs, int k)
{
    std::map<int, double> m;
    int n = probs.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            auto m_it = m.find(i * k + j);
            if (m_it == m.end())
                m[i * k + j] = probs[i] * probs[j];
            else
                m_it->second += probs[i] * probs[j];
        }
    std::vector<double> res;
    for (auto& m_it : m)
    {
        if (m_it.second != 0)
            res.push_back(m_it.second);
    }
    return res;
}

