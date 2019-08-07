
#include <catch2/catch.hpp>
#include <pan/imaginary.hpp>
#include <utility>

using namespace pan;

TEMPLATE_PRODUCT_TEST_CASE("ImaginaryReal", "[templated]", std::tuple, ((int, int), (int, float), (int, double), (float, int), (float, float), (float, double), (double, int), (double, float), (double, double)))
{
	using first_type = std::decay_t<decltype(std::get<0>(std::declval<TestType>()))>;
	using second_type = std::decay_t<decltype(std::get<1>(std::declval<TestType>()))>;
	using common_type = decltype(std::declval<first_type>() + std::declval<second_type>());

	SECTION("Comparison")
	{
		imaginary<first_type> xdImaginary1{50};
		imaginary<first_type> xdImaginary2{0};
		second_type xdReal1 = 50;
		second_type xdReal2 = 0;

		REQUIRE(xdImaginary1 != xdReal1);
		REQUIRE(xdReal1 != xdImaginary1);
		REQUIRE(xdImaginary1 != xdReal2);
		REQUIRE(xdReal1 != xdImaginary2);
		REQUIRE(xdImaginary2 != xdReal1);
		REQUIRE(xdReal2 != xdImaginary1);
		REQUIRE(xdImaginary2 == xdReal2);
		REQUIRE(xdReal2 == xdImaginary2);

		REQUIRE(!(xdImaginary1 == xdReal1));
		REQUIRE(!(xdReal1 == xdImaginary1));
		REQUIRE(!(xdImaginary1 == xdReal2));
		REQUIRE(!(xdReal1 == xdImaginary2));
		REQUIRE(!(xdImaginary2 == xdReal1));
		REQUIRE(!(xdReal2 == xdImaginary1));
		REQUIRE(!(xdImaginary2 != xdReal2));
		REQUIRE(!(xdReal2 != xdImaginary2));
	}

	SECTION("Addition")
	{
		first_type xdReal = 25;
		imaginary<second_type> xdImaginary{50};
		std::complex<common_type> xdResult1{25, 50};
		std::complex<common_type> xdResult2{50, 25};

		REQUIRE(xdImaginary + xdReal == xdResult1);
		REQUIRE(xdReal + xdImaginary == xdResult1);
		REQUIRE(xdImaginary + xdReal != xdResult2);
		REQUIRE(xdReal + xdImaginary != xdResult2);
	}

	SECTION("Subtraction")
	{
		imaginary<first_type> xdImaginary{50};
		second_type xdReal = 27;
		const std::complex<common_type> xdResult{-27, 50};

		REQUIRE(xdImaginary - xdReal == xdResult);
		REQUIRE(xdReal - xdImaginary == -xdResult);
	}

	SECTION("Multiplication")
	{
		imaginary<first_type> xdImaginary{50};
		second_type xdReal = 25;
		const imaginary<common_type> xdResult{1250};

		REQUIRE(xdImaginary * xdReal == xdResult);
		REQUIRE(xdReal * xdImaginary == xdResult);
	}

	SECTION("Division")
	{
		imaginary<first_type> xdImaginary{50};
		second_type xdReal = 25;
		const imaginary<common_type> xdResult1{2};
		const imaginary<common_type> xdResult2{-common_type(1) / 2};

		REQUIRE(xdImaginary / xdReal == xdResult1);
		REQUIRE(xdReal / xdImaginary == xdResult2);
	}
}
