
#include <catch2/catch.hpp>

#include <pan/expr/expr.hpp>
#include <pan/expr/diff.hpp>
#include <pan/expr/opt.hpp>
#include <pan/expr/expr_printer.hpp>

#include <array>

using namespace std;
using namespace pan::expr;

TEST_CASE("SymbolicDifferentiation") 
{
	SECTION("PrettyPrinting")
	{
		using f = sumOp<mulOp<subOp<divOp<var<0>, var<1>>, var<2>>, var<3>>, var<4>>;
		using df0 = diff_t<0, f>;
		using df1 = diff_t<1, f>;
		using df2 = diff_t<2, f>;
		using df3 = diff_t<3, f>;
		using df4 = diff_t<4, f>;

		REQUIRE(to_string(df0()) 	== "(((((x0 / x1) - x2) * 0) + ((((1 / x1) - ((x0 * 0) / (x1 * x1))) - 0) * x3)) + 0)");
		REQUIRE(to_string(df1()) 	== "(((((x0 / x1) - x2) * 0) + ((((0 / x1) - ((x0 * 1) / (x1 * x1))) - 0) * x3)) + 0)");
		REQUIRE(to_string(df2()) 	== "(((((x0 / x1) - x2) * 0) + ((((0 / x1) - ((x0 * 0) / (x1 * x1))) - 1) * x3)) + 0)");
		REQUIRE(to_string(df3()) 	== "(((((x0 / x1) - x2) * 1) + ((((0 / x1) - ((x0 * 0) / (x1 * x1))) - 0) * x3)) + 0)");
		REQUIRE(to_string(df4()) 	== "(((((x0 / x1) - x2) * 0) + ((((0 / x1) - ((x0 * 0) / (x1 * x1))) - 0) * x3)) + 1)");
	}
}
