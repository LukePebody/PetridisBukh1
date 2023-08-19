#include <iostream>

#include "Counter.h"
#include "OneSet.h"
#include <ctime>

void print_timestamp()
{
    std::time_t result = std::time(nullptr);
    std::cout << std::asctime(std::localtime(&result));
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
                std::cout << "Success!" << std::endl;
                std::cout << ts.to_string() << std::endl;
                return 0;
            }
            ++gens;
            if (gens % gmod == 0)
            {
                print_timestamp();
                std::cout << gens << " generations" << " (working on " << k << ")" << std::endl;
//                std::cout << ts.size() << " " << ts.sum_size() << " " << ts.dilate_size() << std::endl;
//                std::cout << ts.to_string() << std::endl;
                if ((gens == gmod * 10) && (gens <= 10000000000LL))
                    gmod = gens;
            }
            int j = c.count();
            if (j == k)
                break;
            ts.toggle(j);
        }
        print_timestamp();
        std::cout << "Completed [" << (k + 1) << "]" << std::endl;
        ++k;
    }
}
