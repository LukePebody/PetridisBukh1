#include <iostream>
#include "math.h"
#include <ctime>
#include "OneSet.h"
#include <map>

void print_timestamp(bool to_out)
{
    std::time_t result = std::time(nullptr);
    if (to_out)
        std::cout << std::asctime(std::localtime(&result));
    else
        std::cerr << std::asctime(std::localtime(&result));
}

// Look for a set A with |A+2.A| = |A|^2, but minimising log |A+A| / |A|

int main(int argc, char** argv)
{
    //
    int k;
    int k_step;
    if (argc == 3)
    {
        k = strtol(argv[1], nullptr, 0);
        k_step = strtol(argv[2], nullptr, 0);
    }
    else
    {
        k = 1;
        k_step = 1;
    }

    double rec = 3;
    int holder = -1;
    long long ubercount = 0;

    while (true) {
        print_timestamp(false);
        std::cerr << k << " " << holder << std::endl;
        long long count = 0;
        OneSet set(true);
        set.toggle(0);
        set.toggle(k);
        double lss = log(set.sum_size());
        double slen = set.size();
        std::vector<int> v4;
        std::vector<int> w;
        w.push_back(1);
        while (true)
        {
            int nxt = w.back();
            if (nxt == k)
            {
                ++count;

                // Check for separation
                auto vec = set.as_vector();
                int ww = 0;
                for (int j: vec)
                    ww += 1 << j;
                bool verbose = (ww == 155667);
                int N = vec.size();
                if (N >= 2)
                {
                    int pow = 1 << N;
                    bool ok = false;
                    for (int k = 2; !ok && (k < pow); k += 2)
                    {
                        std::map<int, int> m;
                        if (verbose)
                        {
                            for (int i = 0; i < N; ++i)
                                if ((k >> i) & 1)
                                {
                                    std::cout << vec[i] << " ";
                                }
                            std::cout<<std::endl;
                        }
                        bool broken = false;
                        for (int j = 1; (j < N) && (!broken); ++j)
                            for (int i = 0; (i < j) && (!broken); ++i)
                            {
                                int tot = vec[i] + vec[j];
                                int typ = ((k >> i) & 1) + ((k >> j) & 1);
                                auto mit = m.find(tot);
                                if (mit != m.end() && mit->second != typ)
                                {
                                    if (verbose) {
                                        std::cout << vec[i] << " + " << vec[j] << " = " << tot << ": " << typ <<
                                                  " vs " << mit->second << std::endl;
                                    }
                                    broken = true;
                                }
                                m[tot] = typ;
                            }
                        if (!broken)
                            ok = true;
                    }
                    if (!ok)
                    {
                        std::cout << "NO SEPARATION" << std::endl;
                        std::cout << set.to_string() << std::endl;
                        return 0;
                    }
                }
                if (v4.size() == 0)
                    break;
                int r = v4.back();
                set.toggle(r);
                --slen;
                lss = log(set.sum_size());
                v4.pop_back();
                w.pop_back();
                int j = w.back();
                w.pop_back();
                w.push_back(j + 1);
            }
            else
            {
                set.toggle(nxt);
                ++slen;
                if (set.dilate_size() == slen * slen)
                {
                    w.push_back(nxt + 1);
                    v4.push_back(nxt);
                    lss = log(set.sum_size());
                    }
                else
                {
                    set.toggle(nxt);
                    --slen;
                    w.pop_back();
                    w.push_back(nxt + 1);
                }
            }
        }
        ubercount += count;
        std::cerr << count << " sets. Total = " << ubercount << "." << std::endl << std::endl;
        k += k_step;
    }
}
