
#include <catch2/catch.hpp>

#include <pan/bases/dual.hpp>

#include <pan/forward_diff/forward_diff.hpp>

#include <array>

using namespace std;
using namespace pan::bases;

TEST_CASE("ForwardDifferentiation") 
{
	SECTION("TwoValues")
	{
		auto f = [](auto x, auto y) { return x*x+y*x+y*y; };

		auto diff_f_0_0 = pan::forward_diff::fdf(f, 0.0, 0.0);
		auto diff_f_1_0 = pan::forward_diff::fdf(f, 1.0, 0.0);
		auto diff_f_3_0 = pan::forward_diff::fdf(f, 3.0, 0.0);
		auto diff_f_0_2 = pan::forward_diff::fdf(f, 0.0, 2.0);
		auto diff_f_1_2 = pan::forward_diff::fdf(f, 1.0, 2.0);
		auto diff_f_3_2 = pan::forward_diff::fdf(f, 3.0, 2.0);

		REQUIRE(get<0>(diff_f_0_0) == 0.0);
		REQUIRE(get<0>(diff_f_1_0) == 1.0);
		REQUIRE(get<0>(diff_f_3_0) == 9.0);
		REQUIRE(get<0>(diff_f_0_2) == 4.0);
		REQUIRE(get<0>(diff_f_1_2) == 7.0);
		REQUIRE(get<0>(diff_f_3_2) == 19.0);

		REQUIRE(get<1>(diff_f_0_0) == 0.0);
		REQUIRE(get<1>(diff_f_1_0) == 2.0);
		REQUIRE(get<1>(diff_f_3_0) == 6.0);
		REQUIRE(get<1>(diff_f_0_2) == 2.0);
		REQUIRE(get<1>(diff_f_1_2) == 4.0);
		REQUIRE(get<1>(diff_f_3_2) == 8.0);

		REQUIRE(get<2>(diff_f_0_0) == 0.0);
		REQUIRE(get<2>(diff_f_1_0) == 1.0);
		REQUIRE(get<2>(diff_f_3_0) == 3.0);
		REQUIRE(get<2>(diff_f_0_2) == 4.0);
		REQUIRE(get<2>(diff_f_1_2) == 5.0);
		REQUIRE(get<2>(diff_f_3_2) == 7.0);

		// REQUIRE(dfdx2(0.0, 0.0) == 2.0);
		// REQUIRE(dfdxdy(1.0, 0.0) == 1.0);
		// REQUIRE(dfdy2(0.0, 1.0) == 2.0);
	}
}
