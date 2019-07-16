
#include <gtest/gtest.h>

#include <pan/expr.hpp>
#include <pan/diff.hpp>
#include <pan/opt.hpp>
#include <pan/expr_printer.hpp>

#include <iostream>

using namespace std;
using namespace pan::diff;
using namespace pan::expr;
using namespace pan::opt;

using f = sumOp<mulOp<subOp<divOp<var<0>, var<1>>, var<2>>, var<3>>, var<4>>;
//using f = sumOp<var<0>, std::integral_constant<int, 0>>;
using df0 = diff_t<0, f>;
using df1 = diff_t<1, f>;
using df2 = diff_t<2, f>;
using df3 = diff_t<3, f>;
using df4 = diff_t<4, f>;



using of   = recursive_opt_t<f>;
using odf0 = recursive_opt_t<df0>;
using odf1 = recursive_opt_t<df1>;
using odf2 = recursive_opt_t<df2>;
using odf3 = recursive_opt_t<df3>;
using odf4 = recursive_opt_t<df4>;

int main() {
	static_assert(is_integral_constant<std::integral_constant<int, 0>>::value);
	static_assert(!is_integral_constant<var<0>>::value);
	static_assert(!is_integral_constant<sumOp<var<2>, std::integral_constant<int, 5>>>::value);

	std::cout << to_string(f()) << std::endl;
	std::cout << to_string(df0()) << std::endl;
	std::cout << to_string(df1()) << std::endl;
	std::cout << to_string(df2()) << std::endl;
	std::cout << to_string(df3()) << std::endl;
	std::cout << to_string(df4()) << std::endl;
	std::cout << to_string(of()) << std::endl;
	std::cout << to_string(odf0()) << std::endl;
	std::cout << to_string(odf1()) << std::endl;
	std::cout << to_string(odf2()) << std::endl;
	std::cout << to_string(odf3()) << std::endl;
	std::cout << to_string(odf4()) << std::endl;
}