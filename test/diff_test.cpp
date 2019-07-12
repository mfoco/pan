
#include <gtest/gtest.h>
#include <pan/diff.hpp>

#include <iostream>

using namespace pan::diff;

using f = sumOp<mulOp<subOp<divOp<var<0>, var<1>>, var<2>>, var<3>>, var<4>>;
//using f = sumOp<var<0>, int_const<0>>;
using df0 = diff_t<0, f>;
using df1 = diff_t<1, f>;
using df2 = diff_t<2, f>;
using df3 = diff_t<3, f>;
using df4 = diff_t<4, f>;

using of   = opt_t<opt_t<opt_t<opt_t<opt_t<f>>>>>;
using odf0 = opt_t<opt_t<opt_t<opt_t<opt_t<df0>>>>>;
using odf1 = opt_t<opt_t<opt_t<opt_t<opt_t<df1>>>>>;
using odf2 = opt_t<opt_t<opt_t<opt_t<opt_t<df2>>>>>;
using odf3 = opt_t<opt_t<opt_t<opt_t<opt_t<df3>>>>>;
using odf4 = opt_t<opt_t<opt_t<opt_t<opt_t<df4>>>>>;

int main() {
	static_assert(is_int_const<int_const<0>>::value);
	static_assert(!is_int_const<var<0>>::value);
	static_assert(!is_int_const<sumOp<var<2>, int_const<5>>>::value);

	std::cout << f().toString() << std::endl;
	std::cout << df0().toString() << std::endl;
	std::cout << df1().toString() << std::endl;
	std::cout << df2().toString() << std::endl;
	std::cout << df3().toString() << std::endl;
	std::cout << df4().toString() << std::endl;
	std::cout << of().toString() << std::endl;
	std::cout << odf0().toString() << std::endl;
	std::cout << odf1().toString() << std::endl;
	std::cout << odf2().toString() << std::endl;
	std::cout << odf3().toString() << std::endl;
	std::cout << odf4().toString() << std::endl;
}