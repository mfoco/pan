
#include <pan/bases/dual.hpp>
#include <type_traits>
#include <matplotlibcpp.h>
#include <Eigen/Eigen>

using namespace pan::bases;
using namespace std;

int main() {
	auto df = [] (auto &&f, const Eigen::Matrix2f &x, const Eigen::Matrix2f &y) {
		auto dfdxb = [&f](auto x, auto y, auto b) {
			return f(dual{x, b}, y).dx.value();
		};
		auto dfdyb = [&f](auto x, auto y, auto b) {
			return f(x, dual{y, b}).dx.value();
		};
		std::tuple<Eigen::Matrix<Eigen::Matrix2f, 2, 2>, Eigen::Matrix<Eigen::Matrix2f, 2, 2>> result{};
		auto [dfdx, dfdy] = result;
		for(int r = 0; r < x.rows(); ++r) {
			for (int c = 0; c < x.cols(); ++c) {
				Eigen::Matrix2f b;
				b << 0, 0, 0, 0;
				b(r, c) = 1;
				dfdx(r, c) = dfdxb(x, y, b);
				dfdy(r, c) = dfdyb(x, y, b);
			}
		}
		return result;
	};

	Eigen::Matrix2f a, b;
	a << 1, 2, 3, 4;
	b << 5, 6, 7, 9;

	auto f = [](auto x, auto y) { return x*y; };
	auto r = df(f, a, b);

	std::cout << 
		get<0>(r)(0, 0)(0, 0) << "\t" << get<0>(r)(0, 0)(0, 1) << std::endl <<
		get<0>(r)(0, 0)(1, 0) << "\t" << get<0>(r)(0, 0)(1, 1) << std::endl << 
		std::endl;
	std::cout << 
		get<0>(r)(0, 1)(0, 0) << "\t" << get<0>(r)(0, 1)(0, 1) << std::endl <<
		get<0>(r)(0, 1)(1, 0) << "\t" << get<0>(r)(0, 1)(1, 1) << std::endl << 
		std::endl;
	std::cout << 
		get<0>(r)(1, 0)(0, 0) << "\t" << get<0>(r)(1, 0)(0, 1) << std::endl <<
		get<0>(r)(1, 0)(1, 0) << "\t" << get<0>(r)(1, 0)(1, 1) << std::endl << 
		std::endl;
	std::cout << 
		get<0>(r)(1, 1)(0, 0) << "\t" << get<0>(r)(1, 1)(0, 1) << std::endl <<
		get<0>(r)(1, 1)(1, 0) << "\t" << get<0>(r)(1, 1)(1, 1) << std::endl << 
		std::endl;
	std::cout << 
		get<1>(r)(0, 0)(0, 0) << "\t" << get<1>(r)(0, 0)(0, 1) << std::endl <<
		get<1>(r)(0, 0)(1, 0) << "\t" << get<1>(r)(0, 0)(1, 1) << std::endl << 
		std::endl;
	std::cout << 
		get<1>(r)(0, 1)(0, 0) << "\t" << get<1>(r)(0, 1)(0, 1) << std::endl <<
		get<1>(r)(0, 1)(1, 0) << "\t" << get<1>(r)(0, 1)(1, 1) << std::endl << 
		std::endl;
	std::cout << 
		get<1>(r)(1, 0)(0, 0) << "\t" << get<1>(r)(1, 0)(0, 1) << std::endl <<
		get<1>(r)(1, 0)(1, 0) << "\t" << get<1>(r)(1, 0)(1, 1) << std::endl << 
		std::endl;
	std::cout << 
		get<1>(r)(1, 1)(0, 0) << "\t" << get<1>(r)(1, 1)(0, 1) << std::endl <<
		get<1>(r)(1, 1)(1, 0) << "\t" << get<1>(r)(1, 1)(1, 1) << std::endl << 
		std::endl;
}
