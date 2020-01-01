
#include <catch2/catch.hpp>

#include <pan/bases/imaginary.hpp>

using namespace pan::bases;

TEMPLATE_TEST_CASE("Imaginary", "[template]", int, float, double, long double)
{
	SECTION("DefaultConstruction")
	{
		imaginary<TestType> x;

		REQUIRE(x.value() == 0);
	}

	SECTION("Construction")
	{
		imaginary<TestType> x{50};

		REQUIRE(x.value() == 50);
	}

	SECTION("CopyConstruction")
	{
		imaginary<TestType> x{50};

		const imaginary<TestType> x2{x};

		REQUIRE(x.value() == x2.value());
	}

	SECTION("MoveConstruction")
	{
		imaginary<TestType> x{50};

		imaginary<TestType> x2{std::move(x)};

		REQUIRE(x2.value() == 50);
	}

	SECTION("CopyAssignment")
	{
		imaginary<TestType> x{50};

		// ReSharper disable CppJoinDeclarationAndAssignment
		imaginary<TestType> x2;
		// ReSharper restore CppJoinDeclarationAndAssignment

		x2 = x;

		REQUIRE(x.value() == x2.value());
	}

	SECTION("MoveAssignment")
	{
		imaginary<TestType> x{50};

		// ReSharper disable CppJoinDeclarationAndAssignment
		imaginary<TestType> x2;
		// ReSharper restore CppJoinDeclarationAndAssignment

		x2 = std::move(x);

		REQUIRE(x2.value() == 50);
	}
	
	SECTION("Unary")
	{
		imaginary<TestType> xpc{50};
		imaginary<TestType> xmc{-50};
		auto xpv = +xpc;
		auto xmv = -xpc;
		REQUIRE(xpc.value() == 50);
		REQUIRE(xmc.value() == -50);
		REQUIRE(xpv.value() == 50);
		REQUIRE(xmv.value() == -50);

		auto xp2 = +std::move(xpc);
		auto xm2 = -std::move(xpv);
		REQUIRE(xp2.value() == 50);
		REQUIRE(xm2.value() == -50);
	}

	SECTION("AutoAssignment")
	{
		imaginary<TestType> x{50};
		x += imaginary<TestType>(1);
		REQUIRE(x.value() == 51);
		x -= imaginary<TestType>(1);
		REQUIRE(x.value() == 50);
		x *= TestType{2};
		REQUIRE(x.value() == 100);
		x /= TestType{2};
		REQUIRE(x.value() == 50);
	}

	SECTION("Comparison")
	{
		imaginary<TestType> x1{50};
		imaginary<TestType> x2{50};
		imaginary<TestType> x3{51};

		REQUIRE(x1 == x2);
		REQUIRE(x2 == x1);
		REQUIRE(x1 != x3);
		REQUIRE(x3 != x1);
	}

	SECTION("Addition")
	{
		imaginary<TestType> x1{50};
		imaginary<TestType> x2{25};
		const imaginary<TestType> xResult{75};

		REQUIRE(x1 + x2 == xResult);
		REQUIRE(x2 + x1 == xResult);
	}

	SECTION("Subtraction")
	{
		imaginary<TestType> x1{50};
		imaginary<TestType> x2{27};
		const imaginary<TestType> xResult{23};

		REQUIRE(x1 - x2 == xResult);
		REQUIRE(x2 - x1 == -xResult);
	}

	SECTION("Multiplication")
	{
		imaginary<TestType> x1{50};
		imaginary<TestType> x2{25};
		const TestType xResult{-1250};

		REQUIRE(x1 * x2 == xResult);
		REQUIRE(x2 * x1 == xResult);
	}

	SECTION("Division")
	{
		imaginary<TestType> x1{50};
		imaginary<TestType> x2{25};
		const TestType xResult1{2};
		const TestType xResult2{TestType{25}/TestType{50}};

		REQUIRE(x1 / x2 == xResult1);
		REQUIRE(x2 / x1 == xResult2);
	}

	SECTION("Interaction") 
	{
		imaginary<TestType> x1{50};
		jmaginary<TestType> x2{25};
		const kmaginary<TestType> xResult1{1250};
		const kmaginary<TestType> xResult2{-1250};

		REQUIRE(x1 * x2 == xResult1);
		REQUIRE(x2 * x1 == xResult2);
	}
}

TEST_CASE("Imaginary")
{
	SECTION("Literals")
	{
		auto xf = 50.1_fi;
		auto xd = 50.1_i;
		auto xl = 50.1_li;

		REQUIRE(xf.value() == 50.1f);
		REQUIRE(xd.value() == 50.1);
		REQUIRE(xl.value() == 50.1l);
	}

	SECTION("AutoAssignment")
	{
		auto xd = 50.0_i;
		imaginary<int> xi{50};

		// With conversion

		xd += imaginary<int>(1);
		xi += imaginary<short>(1);
		REQUIRE(xd.value() == 51.0);
		REQUIRE(xi.value() == 51);
		xd -= imaginary<int>(1);
		xi -= imaginary<short>(1);
		REQUIRE(xd.value() == 50.0);
		REQUIRE(xi.value() == 50);
		xd *= 2;
		xi *= static_cast<short>(2);
		REQUIRE(xd.value() == 100.0);
		REQUIRE(xi.value() == 100);
		xd /= 2;
		xi /= static_cast<short>(2);
		REQUIRE(xd.value() == 50.0);
		REQUIRE(xi.value() == 50);
	}

	SECTION("Comparison")
	{
		auto xd1 = 50.0_i;
		auto xd2 = 50.0_i;
		auto xdResult = 50.1_i;
		imaginary<int> xi1{50};
		imaginary<int> xi2{50};
		imaginary<int> xiResult{51};

		// mixing types
		REQUIRE(xd1 == xi2);
		REQUIRE(xd2 == xi1);
		REQUIRE(xi1 == xd2);
		REQUIRE(xi2 == xd1);
		REQUIRE(xd1 != xiResult);
		REQUIRE(xdResult != xi1);
		REQUIRE(xi1 != xdResult);
		REQUIRE(xiResult != xd1);

		REQUIRE(xd1 == xi2);
		REQUIRE(xd2 == xi1);
		REQUIRE(xi1 == xd2);
		REQUIRE(xi2 == xd1);
		REQUIRE(xd1 != xiResult);
		REQUIRE(xdResult != xi1);
		REQUIRE(xi1 != xdResult);
		REQUIRE(xiResult != xd1);
	}

	SECTION("Addition")
	{
		auto xd1 = 50.0_i;
		auto xd2 = 25.0_i;
		const auto xdResult = 75.0_i;
		imaginary<int> xi1{50};
		imaginary<int> xi2{25};
		const imaginary<int> xiResult{75};

		// mixing types
		REQUIRE(xd1 + xi2 == xdResult);
		REQUIRE(xd2 + xi1 == xdResult);
		REQUIRE(xi1 + xd2 == xdResult);
		REQUIRE(xi2 + xd1 == xdResult);
		REQUIRE(xd1 + xi2 == xiResult);
		REQUIRE(xd2 + xi1 == xiResult);
		REQUIRE(xi1 + xd2 == xiResult);
		REQUIRE(xi2 + xd1 == xiResult);
	}

	SECTION("Subtraction")
	{
		auto xd1 = 50.0_i;
		auto xd2 = 27.0_i;
		const auto xdResult = 23.0_i;
		imaginary<int> xi1{50};
		imaginary<int> xi2{27};
		const imaginary<int> xiResult{23};

		// mixing types
		REQUIRE(xd1 - xi2 == xdResult);
		REQUIRE(xd2 - xi1 == -xdResult);
		REQUIRE(xi1 - xd2 == xdResult);
		REQUIRE(xi2 - xd1 == -xdResult);
		REQUIRE(xd1 - xi2 == xiResult);
		REQUIRE(xd2 - xi1 == -xiResult);
		REQUIRE(xi1 - xd2 == xiResult);
		REQUIRE(xi2 - xd1 == -xiResult);
	}

	SECTION("Multiplication")
	{
		auto xd1 = 50.0_i;
		auto xd2 = 25.0_i;
		const auto xdResult = -1250.0;
		imaginary<int> xi1{50};
		imaginary<int> xi2{25};
		const auto xiResult = -1250;

		// mixing types
		REQUIRE(xd1 * xi2 == xdResult);
		REQUIRE(xd2 * xi1 == xdResult);
		REQUIRE(xi1 * xd2 == xdResult);
		REQUIRE(xi2 * xd1 == xdResult);
		REQUIRE(xd1 * xi2 == xiResult);
		REQUIRE(xd2 * xi1 == xiResult);
		REQUIRE(xi1 * xd2 == xiResult);
		REQUIRE(xi2 * xd1 == xiResult);
	}

	SECTION("Division")
	{
		auto xd1 = 50.0_i;
		auto xd2 = 25.0_i;
		const auto xdResult1 = 2.0;
		const auto xdResult2 = 0.5;
		imaginary<int> xi1{50};
		imaginary<int> xi2{25};
		const auto xiResult1 = 2;
		const auto xiResult2 = 0;

		// mixing types
		REQUIRE(xd1 / xi2 == xdResult1);
		REQUIRE(xd2 / xi1 == xdResult2);
		REQUIRE(xi1 / xd2 == xdResult1);
		REQUIRE(xi2 / xd1 == xdResult2);
	}
}
