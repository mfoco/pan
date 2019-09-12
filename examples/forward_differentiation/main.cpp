#include <pan/bases/dual.hpp>
#include <type_traits>
#include <matplotlibcpp.h>

using namespace pan::bases;
using namespace std;

int main() {
	auto f = [](auto x, auto y) { return (x + y) * sin(x * x / 10.0) * cos(y * y / 10.0) + x * x + y * x + y * y; };
	auto dfdx = [&f](auto x, auto y) {
		using T = std::decay_t<decltype(x)>;
		return f(dual<T>{x, T(1)}, y).dx.value();
	};
	auto dfdy = [&f](auto x, auto y) {
		using T = std::decay_t<decltype(y)>;
		return f(x, dual<T>{y, T(1)}).dx.value();
	};

	std::vector<std::vector<double>> x, y, z1, z2, z3;
	for (double i = -5; i <= 5; i += 0.25) {
		std::vector<double> x_row, y_row, z1_row, z2_row, z3_row;
		for (double j = -5; j <= 5; j += 0.25) {
			x_row.push_back(i);
			y_row.push_back(j);
			z1_row.push_back(f(i, j));
			z2_row.push_back(dfdx(i, j));
			z3_row.push_back(dfdy(i, j));
		}
		x.push_back(x_row);
		y.push_back(y_row);
		z1.push_back(z1_row);
		z2.push_back(z2_row);
		z3.push_back(z3_row);
	}

	matplotlibcpp::plot_surface(x, y, z1);
	matplotlibcpp::plot_surface(x, y, z2);
	matplotlibcpp::plot_surface(x, y, z3);
	matplotlibcpp::show();
}
