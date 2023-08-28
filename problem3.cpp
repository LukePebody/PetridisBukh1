#include <iostream>
#include "math.h"
#include <ctime>
#include "OneSet.h"

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
            if (lss >= rec * log(slen + (k - nxt)))
            {
                ++count;
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
            else if (nxt == k)
            {
                ++count;
                double score = lss / log(slen);
                if (score < rec)
                {
                    print_timestamp(true);
                    std::cout << score << std::endl;
                    rec = score;
                    holder = k;
                    std::cout << set.to_string() << std::endl;
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
