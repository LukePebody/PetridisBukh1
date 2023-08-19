#include <iostream>

#include "Counter.h"
#include "OneSet.h"
#include <ctime>

void print_timestamp(bool to_out)
{
    std::time_t result = std::time(nullptr);
    if (to_out)
        std::cout << std::asctime(std::localtime(&result));
    else
        std::cerr << std::asctime(std::localtime(&result));
}

int main()
{
    int k = 1;
    long long gens = 0;
    long long gmod = 100000000;

    while (true) {
        OneSet ts(true);
        ts.toggle(k);
        Counter c(1);
        while (true)
        {
            if (ts.sum_size() > ts.dilate_size())
            {
                print_timestamp(true);
                std::cout << "Success!" << std::endl;
                std::cout << ts.to_string() << std::endl;
                return 0;
            }
            ++gens;
            if (gens % gmod == 0)
            {
                print_timestamp(false);
                std::cerr << gens << " generations" << " (working on " << k << ")" << std::endl;
                if ((gens == gmod * 10) && (gens <= 10000000000LL))
                    gmod = gens;
            }
            int j = c.count();
            if (j == k)
                break;
            ts.toggle(j);
        }
        print_timestamp(false);
        std::cerr << "Completed [" << (k + 1) << "]" << std::endl;
        ++k;
    }
}
