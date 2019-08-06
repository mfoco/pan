
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <pan/arithmetic_tuple.hpp>
#include <pan/base.hpp>
#include <pan/imaginary.hpp>

using namespace pan;

TEST_CASE("ArithmeticTuple")
{
	SECTION("Construction")
	{
		arithmetic_tuple<float, imaginary<float>> at0;
	}
}
