#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <ctime>
#include "Counter.h"
#include "VectorMultiSet.h"

void print_timestamp()
{
    std::time_t result = std::time(nullptr);
    std::cout << std::asctime(std::localtime(&result));
}

void get_groups(int n, int k, const std::vector<int>& v, std::vector<std::vector<int>>& out) {
    std::vector<int> v2(v.begin(), v.end());
    v2.push_back(n);
    out.push_back(v2);

    int p = (k == 1) ? 2 : k;
    while (p * p <= n) {
        if (n % (p * p) == 0) {
            std::vector<int> vp(v.begin(), v.end());
            vp.push_back(p);
            get_groups(n / p, p, vp, out);
        }
        p += k;
    }
}

double rec = 1000;
std::vector<int> holder;

double attempt(const std::vector<int>& group)
{
    int size = 1;
    for (int k : group)
        size *= k;
    std::vector<std::vector<int>> mul;
    for (int i = 0; i < size; ++i)
        mul.push_back(std::vector<int>(size, -1));

    mul[0][0] = 0;
    size = 1;
    for (int k : group)
    {
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                for (int p = 0; p < k; ++p)
                    for (int q = 0; q < k; ++q)
                        mul[p * size + i][q * size + j] = ((p + q) % k) * size + mul[i][j];
        size *= k;
    }
//    for (int k : group)
//        std::cout << k << " ";
//    std::cout << std::endl;
//    for (int i = 0; i < size; ++i) {
//        for (int j = 0; j < size; ++j)
//            std::cout << mul[i][j] << " ";
//        std::cout << std::endl;
//    }
    double rec2 = 1000;
    int dims = group.size();

    VectorMultiSet v1;
    VectorMultiSet v2;
    std::vector<int> v(size, 0);
    v[0] = 1;

    Counter k(1);

    while (true)
    {
        int j = k.count();
        if (j == size)
            break;
        if (v[j] == 0)
        {
            for (int t = 0; t < size; ++t)
            {
                if (v[t] == 1)
                {
                    int p = mul[j][t];
                    v1.add(p);
                    v2.add(mul[j][p]);
                    v2.add(mul[t][p]);
                }
            }
            v[j] = 1;
            int p = mul[j][j];
            v1.add(p);
            v2.add(mul[j][p]);
        }
        else
        {
            int p = mul[j][j];
            v2.remove(mul[j][p]);
            v1.remove(p);
            v[j] = 0;
            for (int t = 0; t < size; ++t)
            {
                if (v[t] == 1)
                {
                    int p = mul[j][t];
                    v1.remove(p);
                    v2.remove(mul[j][p]);
                    v2.remove(mul[t][p]);
                }
            }
        }
        double scr = pow(double(v2.size())/v1.size(), 1.0/dims);
        if (scr < rec)
        {
            rec = scr;
            holder = std::vector<int>(group.begin(), group.end());
            print_timestamp();
            std::cout << v.size() << " " << v1.size() << " " << v2.size() << " " << scr << std::endl;
            for (int i = 0; i < size; ++i)
            {
                if (v[i]) {
                    int j = i;
                    for (int p: group) {
                        std::cout << (j % p) << " ";
                        j /= p;
                    }
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl;
        }
        if (scr < rec2)
            rec2 = scr;
    }
    return rec2;
}

int main()
{
    for (int n = 2; ; ++n)
    {
        std::vector<int> v;
        std::vector<std::vector<int>> groups;
        get_groups(n, 1, v, groups);
        for (const auto& group : groups)
        {
            print_timestamp();
            std::cout << n << ": [";
            bool started = false;
            for (int k : group)
            {
                if (started)
                    std :: cout << ", ";
                std :: cout << k;
                started = true;
            }
            std::cout << "]" << " " << rec << " ";
            for (int k : holder)
                std:: cout << k << " ";
            std::cout << std::endl;
            double ans4 = attempt(group);
            std::cout << ans4 << std::endl;
        }
    }
}