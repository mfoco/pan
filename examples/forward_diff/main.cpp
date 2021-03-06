
#include <type_traits>
#include <matplotlibcpp.h>

#include "df.hpp"

using namespace std;

int main() {
	std::vector<std::vector<double>> x, y, z1, z2, z3;
	for (double i = -5; i <= 5; i += 0.25) {
		std::vector<double> x_row, y_row, z1_row, z2_row, z3_row;
		for (double j = -5; j <= 5; j += 0.25) {
			x_row.push_back(i);
			y_row.push_back(j);

			auto [value, dfdx, dfdy] = func_diff(i, j);

			z1_row.push_back(value);
			z2_row.push_back(dfdx);
			z3_row.push_back(dfdy);
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
