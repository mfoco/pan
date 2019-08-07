
#include <catch2/catch.hpp>

#include <pan/expr.hpp>

#include <array>

using namespace std;
using namespace pan::expr;

TEST_CASE("SymbolicExpression") 
{
	SECTION("SimpleOperations") 
	{
		constexpr std::array<double, 2> variables{8, 4};

		std::integral_constant<int, 1> constant;
		var<0> x;
		sumOp<var<0>, var<1>> sum;
		subOp<var<0>, var<1>> sub;
		mulOp<var<0>, var<1>> mul;
		divOp<var<0>, var<1>> div;

		REQUIRE(evaluate(constant, variables) == 1);
		REQUIRE(evaluate(x, variables) == 8);
		REQUIRE(evaluate(sum, variables) == 12);
		REQUIRE(evaluate(sub, variables) == 4);
		REQUIRE(evaluate(mul, variables) == 32);
		REQUIRE(evaluate(div, variables) == 2);
	}
}
