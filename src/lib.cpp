#include <lib.hpp>

#include <tuple>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

std::tuple<double, double> accumulate_vector(const std::vector<double>& values)
{
    double asum = std::accumulate(values.begin(), values.end(), 0.0);
    double amax = *std::max_element(values.begin(), values.end());

    return {asum, asum/amax};
}
