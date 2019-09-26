
#include "df.hpp"
#include <pan/forward_diff/forward_diff.hpp>

namespace {
    // Function we want to differentiate
    constexpr auto f = [](auto x, auto y) { return (x + y) * sin(x * x / 10.0) * cos(y * y / 10.0) + x * x + y * x + y * y; };
}

std::tuple<double, double, double> func_diff(double x, double y) 
{
    return pan::forward_diff::fdf(f, x, y);
}

double func_base(double x, double y) {
    return f(x, y);
}
