
#include <catch2/catch.hpp>

#include <pan/bases/imaginary.hpp>

#include <utility>

using namespace pan::bases;

TEMPLATE_PRODUCT_TEST_CASE("ImaginaryComplex", "[templated]", std::tuple, ((int, int), (int, float), (int, double), (float, int), (float, float), (float, double), (double, int), (double, float), (double, double)))
{
	using first_type = std::decay_t<decltype(std::get<0>(std::declval<TestType>()))>;
	using second_type = std::decay_t<decltype(std::get<1>(std::declval<TestType>()))>;
	using common_type = decltype(std::declval<first_type>() + std::declval<second_type>());

	SECTION("Comparison")
	{
		imaginary<first_type> xdImaginary1{0};
		imaginary<first_type> xdImaginary2{50};
		std::complex<first_type> xdComplex1{0, 0};
		std::complex<first_type> xdComplex2{0, 50};
		std::complex<first_type> xdComplex3{50, 0};
		std::complex<first_type> xdComplex4{50, 50};
		imaginary<second_type> xiImaginary1{0};
		imaginary<second_type> xiImaginary2{50};
		std::complex<second_type> xiComplex1{0, 0};
		std::complex<second_type> xiComplex2{0, 50};
		std::complex<second_type> xiComplex3{50, 0};
		std::complex<second_type> xiComplex4{50, 50};

		REQUIRE(xdImaginary1 == xiComplex1);
		REQUIRE(xdImaginary1 != xiComplex2);
		REQUIRE(xdImaginary1 != xiComplex3);
		REQUIRE(xdImaginary1 != xiComplex4);
		REQUIRE(xdImaginary2 != xiComplex1);
		REQUIRE(xdImaginary2 == xiComplex2);
		REQUIRE(xdImaginary2 != xiComplex3);
		REQUIRE(xdImaginary2 != xiComplex4);
		REQUIRE(xdComplex1 == xiImaginary1);
		REQUIRE(xdComplex2 != xiImaginary1);
		REQUIRE(xdComplex3 != xiImaginary1);
		REQUIRE(xdComplex4 != xiImaginary1);
		REQUIRE(xdComplex1 != xiImaginary2);
		REQUIRE(xdComplex2 == xiImaginary2);
		REQUIRE(xdComplex3 != xiImaginary2);
		REQUIRE(xdComplex4 != xiImaginary2);

		REQUIRE(!(xdImaginary1 != xiComplex1));
		REQUIRE(!(xdImaginary1 == xiComplex2));
		REQUIRE(!(xdImaginary1 == xiComplex3));
		REQUIRE(!(xdImaginary1 == xiComplex4));
		REQUIRE(!(xdImaginary2 == xiComplex1));
		REQUIRE(!(xdImaginary2 != xiComplex2));
		REQUIRE(!(xdImaginary2 == xiComplex3));
		REQUIRE(!(xdImaginary2 == xiComplex4));
		REQUIRE(!(xdComplex1 != xiImaginary1));
		REQUIRE(!(xdComplex2 == xiImaginary1));
		REQUIRE(!(xdComplex3 == xiImaginary1));
		REQUIRE(!(xdComplex4 == xiImaginary1));
		REQUIRE(!(xdComplex1 == xiImaginary2));
		REQUIRE(!(xdComplex2 != xiImaginary2));
		REQUIRE(!(xdComplex3 == xiImaginary2));
		REQUIRE(!(xdComplex4 == xiImaginary2));
	}

	SECTION("Addition")
	{
		imaginary<first_type> xdImaginary{50};
		std::complex<second_type> xdComplex{25, 27};
		const std::complex<common_type> xdResult{25, 77};

		// same type
		REQUIRE(xdImaginary + xdComplex == xdResult);
		REQUIRE(xdComplex + xdImaginary == xdResult);
	}

	SECTION("Subtraction")
	{
		imaginary<first_type> xdImaginary{50};
		std::complex<second_type> xdComplex{25, 27};
		const std::complex<common_type> xdResult1{-25, 23};
		const std::complex<common_type> xdResult2{25, -23};

		// same type
		REQUIRE(xdImaginary - xdComplex == xdResult1);
		REQUIRE(xdComplex - xdImaginary == xdResult2);
	}

	SECTION("Multiplication")
	{
		imaginary<first_type> xdImaginary{50};
		std::complex<second_type> xdComplex{25, 27};
		const std::complex<common_type> xdResult{-1350, 1250};

		// same type
		REQUIRE(xdImaginary * xdComplex == xdResult);
		REQUIRE(xdComplex * xdImaginary == xdResult);
	}

	SECTION("Division")
	{
		imaginary<first_type> xdImaginary{52};
		std::complex<second_type> xdComplex{26, 13};
		const std::complex<common_type> xdResult1{common_type(4)/5, common_type(8)/5};
		const std::complex<common_type> xdResult2{common_type(1)/4, -common_type(1)/2};

		// same type
		REQUIRE(xdImaginary / xdComplex == xdResult1);
		REQUIRE(xdComplex / xdImaginary == xdResult2);
	}
}
