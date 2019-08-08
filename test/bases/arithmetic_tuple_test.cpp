
#include <catch2/catch.hpp>

#include <pan/bases/arithmetic_tuple.hpp>
#include <pan/bases/base.hpp>
#include <pan/bases/imaginary.hpp>

using namespace pan::bases;

TEST_CASE("ArithmeticTuple")
{
	SECTION("Construction")
	{
		arithmetic_tuple<float, imaginary<float>> at0;
	}
}
