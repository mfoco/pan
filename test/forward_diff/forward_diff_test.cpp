
#include <catch2/catch.hpp>

#include <pan/bases/dual.hpp>

#include <array>

using namespace std;
using namespace pan::bases;

TEST_CASE("ForwardDifferentiation") 
{
	SECTION("TwoValues")
	{
		auto f = [](auto x, auto y) { return x*x+y*x+y*y; };
		auto dfdx = [&f](auto x, auto y) { 
			using T = std::decay_t<decltype(x)>;
			return f(dual<T>{x, T(1)}, y).dx.value();
		};
		auto dfdy = [&f](auto x, auto y) { 
			using T = std::decay_t<decltype(y)>;
			return f(x, dual<T>{y, T(1)}).dx.value();
		};


		REQUIRE(f(0.0, 0.0) == 0.0);
		REQUIRE(f(1.0, 0.0) == 1.0);
		REQUIRE(f(3.0, 0.0) == 9.0);
		REQUIRE(f(0.0, 2.0) == 4.0);
		REQUIRE(f(1.0, 2.0) == 7.0);
		REQUIRE(f(3.0, 2.0) == 19.0);

		REQUIRE(dfdx(0.0, 0.0) == 0.0);
		REQUIRE(dfdx(1.0, 0.0) == 2.0);
		REQUIRE(dfdx(3.0, 0.0) == 6.0);
		REQUIRE(dfdx(0.0, 2.0) == 2.0);
		REQUIRE(dfdx(1.0, 2.0) == 4.0);
		REQUIRE(dfdx(3.0, 2.0) == 8.0);

		REQUIRE(dfdy(0.0, 0.0) == 0.0);
		REQUIRE(dfdy(1.0, 0.0) == 1.0);
		REQUIRE(dfdy(3.0, 0.0) == 3.0);
		REQUIRE(dfdy(0.0, 2.0) == 4.0);
		REQUIRE(dfdy(1.0, 2.0) == 5.0);
		REQUIRE(dfdy(3.0, 2.0) == 7.0);
	}
}
