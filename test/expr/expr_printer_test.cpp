
#include <catch2/catch.hpp>

#include <pan/expr/expr.hpp>
#include <pan/expr/expr_printer.hpp>

#include <array>

using namespace std;
using namespace pan::expr;

TEST_CASE("SymbolicExpressionPrinter") 
{
	SECTION("PrettyPrinting")
	{
		using f = sumOp<mulOp<subOp<divOp<var<0>, var<1>>, var<2>>, var<3>>, var<4>>;
		REQUIRE(to_string(f()) == "((((x0 / x1) - x2) * x3) + x4)");
	}
}
