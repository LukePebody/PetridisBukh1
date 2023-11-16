//
// Created by Luke Pebody on 15/11/2023.
//

#include <functional>
#include <iostream>
#include <map>
#include <math.h>
#include <random>
#include <sstream>
#include <time.h>
#include <vector>

#include "objectives.h"
#include "RecordHolder.h"

void print_timestamp(bool to_out)
{
    std::time_t result = std::time(nullptr);
    if (to_out)
        std::cout << std::asctime(std::localtime(&result));
    else
        std::cerr << std::asctime(std::localtime(&result));
}


std::uniform_real_distribution<double> uniform;
std::normal_distribution<double> normal;

void simulated_annealing(
        const std::string& label,
        RecordHolder& holder,
        std::mt19937& gen,
        const std::function<double(const std::vector<double>&)>& objective,
        const std::vector<std::pair<double, double>>& bounds,
        int n_iterations,
        double step_size,
        double temp,
        bool increasing
        )
{
    int n_dimensions = bounds.size();
    std::vector<double> curr(n_dimensions, 0);
    std::vector<double> candidate(n_dimensions, 0);
    for (int i = 0; i < n_dimensions; ++i)
        curr[i] = bounds[i].first + uniform(gen) * (bounds[i].second - bounds[i].first);
    double curr_eval = objective(curr);
    if (holder.inform(curr_eval))
    {
        std::cout << label << " start " << curr_eval << " = f(";
        for (int i = 0; i < n_dimensions; ++i)
        {
            if (i > 0)
                std::cout << ", ";
            std::cout << curr[i];
        }
        std::cout << ")" << std::endl;
    }
    for (int i = 0; i < n_iterations; ++i)
    {
        for (int j = 0; j < n_dimensions; ++j)
            candidate[j] = std::max(bounds[j].first,
                                    std::min(bounds[j].second,
                                             curr[j] + (bounds[j].second - bounds[j].first) * normal(gen)));
        double cand_eval = objective(candidate);
        if (holder.inform(cand_eval))
        {
            print_timestamp(true);

            std::cout << label << " step " << (i + 1) << " " << cand_eval << " = f(";
            for (int j = 0; j < n_dimensions; ++j)
            {
                if (j > 0)
                    std::cout << ", ";
                std::cout << candidate[j];
            }
            std::cout << ")" << std::endl;
        }
        double diff = (increasing) ? (curr_eval - cand_eval) : (cand_eval - curr_eval);
        if (diff < 0)
        {
            curr = candidate;
            curr_eval = cand_eval;
        }
        else
        {
            double t = temp / (i + 1);
            double metropolis = exp(-diff / t);
            if (uniform(gen) < metropolis)
            {
                curr = candidate;
                curr_eval = cand_eval;
            }
        }
    }
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    RecordHolder rh_two_more_than_one(true); // >0 would be something
    RecordHolder rh_one_over_two(true); // <log(3)/log(4) would be something
    RecordHolder rh_hanson_petridis(true); // >2 would be something
    RecordHolder rh_mdts(true); // Don't know yet what would be something
    RecordHolder rh_mstd(true); // Don't know yet what would be something, but certainly approaching 2 would

    long long num_iterations = 0;
    long long iteration_mod = 1;
    while (true)
    {
        ++num_iterations;
        if (num_iterations % iteration_mod == 0)
        {
            print_timestamp(false);
            std::cerr << "Start of generation " << num_iterations << std::endl;
            if (rh_two_more_than_one.set())
            {
                std::cerr << "Max found for p1-p2 is " << rh_two_more_than_one.record() << std::endl;
                std::cerr << "Any positive value would be interesting." << std::endl << std::endl;
            }
            if (rh_one_over_two.set())
            {
                std::cerr << "Max found for p2/p1 is " << rh_one_over_two.record() << std::endl;
                std::cerr << "Any value over " << log(4)/log(3) << " would be interesting"
                << std::endl << std::endl;
            }
            if (rh_hanson_petridis.set())
            {
                std::cerr << "Max found for (p2 - 1) / (p1 - 1) is " << rh_hanson_petridis.record() << std::endl;
                std::cerr << "Any value over 2 would be interesting" << std::endl << std::endl;
            }
            if (rh_mdts.set())
            {
                std::cerr << "Max found for p(-1)-p1 is " << rh_mdts.record() << std::endl << std::endl;
            }
            if (rh_mstd.set())
            {
                std::cerr << "Max found for (p1-1)/(p(-1)-1) is " << rh_mstd.record() << std::endl << std::endl;
            }
        }
        for (int k = 3; k <= 20; ++k)
        {
            std::vector<std::pair<double, double>> bounds;
            for (int t = 0; t < k; ++t)
                bounds.push_back(std::make_pair(0, 1));
            std::ostringstream oss;
            oss << num_iterations << " " << k;
            simulated_annealing(oss.str()+" 2>1",
                                rh_two_more_than_one,
                                gen,
                                objective_dilate_two_more_than_one,
                                bounds,
                                10000,
                                0.1,
                                200,
                                true);
            simulated_annealing(oss.str()+" 1/2",
                                rh_one_over_two,
                                gen,
                                objective_dilate_one_over_two,
                                bounds,
                                10000,
                                0.1,
                                200,
                                true);
            simulated_annealing(oss.str()+" HP",
                                rh_hanson_petridis,
                                gen,
                                objective_dilate_hanson_petridis,
                                bounds,
                                10000,
                                0.1,
                                200,
                                true);
            simulated_annealing(oss.str()+" MDTS",
                                rh_mdts,
                                gen,
                                objective_mdts,
                                bounds,
                                10000,
                                0.1,
                                200,
                                true);
            simulated_annealing(oss.str()+" MSTD",
                                rh_mstd,
                                gen,
                                objective_mstd,
                                bounds,
                                10000,
                                0.1,
                                200,
                                true);
        }
    }
}
