
#include <catch2/catch.hpp>

#include <pan/expr/expr.hpp>
#include <pan/expr/diff.hpp>
#include <pan/expr/opt.hpp>
#include <pan/expr/expr_printer.hpp>

using namespace std;
using namespace pan::expr;

TEST_CASE("SymbolicOptimization") 
{
	SECTION("PrettyPrinting")
	{
		// TODO: Reduce this test to remove dependency on diff

		using f = sumOp<mulOp<subOp<divOp<var<0>, var<1>>, var<2>>, var<3>>, var<4>>;
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

		REQUIRE(to_string(f()) 		== "((((x0 / x1) - x2) * x3) + x4)");
		REQUIRE(to_string(df0()) 	== "(((((x0 / x1) - x2) * 0) + ((((1 / x1) - ((x0 * 0) / (x1 * x1))) - 0) * x3)) + 0)");
		REQUIRE(to_string(df1()) 	== "(((((x0 / x1) - x2) * 0) + ((((0 / x1) - ((x0 * 1) / (x1 * x1))) - 0) * x3)) + 0)");
		REQUIRE(to_string(df2()) 	== "(((((x0 / x1) - x2) * 0) + ((((0 / x1) - ((x0 * 0) / (x1 * x1))) - 1) * x3)) + 0)");
		REQUIRE(to_string(df3()) 	== "(((((x0 / x1) - x2) * 1) + ((((0 / x1) - ((x0 * 0) / (x1 * x1))) - 0) * x3)) + 0)");
		REQUIRE(to_string(df4()) 	== "(((((x0 / x1) - x2) * 0) + ((((0 / x1) - ((x0 * 0) / (x1 * x1))) - 0) * x3)) + 1)");
		REQUIRE(to_string(of()) 	== "((((x0 / x1) - x2) * x3) + x4)");
		REQUIRE(to_string(odf0()) 	== "((1 / x1) * x3)");
		REQUIRE(to_string(odf1()) 	== "((0 - (x0 / (x1 * x1))) * x3)");
		REQUIRE(to_string(odf2()) 	== "(-1 * x3)");
		REQUIRE(to_string(odf3()) 	== "((x0 / x1) - x2)");
		REQUIRE(to_string(odf4()) 	== "1");
	}
}
