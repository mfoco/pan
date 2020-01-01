
#include <catch2/catch.hpp>

#include <pan/bases/epsilon.hpp>

using namespace pan::bases;

TEMPLATE_TEST_CASE("Epsilon", "[template]", int, float, double, long double)
{
	SECTION("DefaultConstruction")
	{
		epsilon<TestType> x;

		REQUIRE(x.value() == 0);
	}

	SECTION("Construction")
	{
		epsilon<TestType> x{50};

		REQUIRE(x.value() == 50);
	}

	SECTION("CopyConstruction")
	{
		epsilon<TestType> x{50};

		const epsilon<TestType> x2{x};

		REQUIRE(x.value() == x2.value());
	}

	SECTION("MoveConstruction")
	{
		epsilon<TestType> x{50};

		epsilon<TestType> x2{std::move(x)};

		REQUIRE(x2.value() == 50);
	}

	SECTION("CopyAssignment")
	{
		epsilon<TestType> x{50};

		// ReSharper disable CppJoinDeclarationAndAssignment
		epsilon<TestType> x2;
		// ReSharper restore CppJoinDeclarationAndAssignment

		x2 = x;

		REQUIRE(x.value() == x2.value());
	}

	SECTION("MoveAssignment")
	{
		epsilon<TestType> x{50};

		// ReSharper disable CppJoinDeclarationAndAssignment
		epsilon<TestType> x2;
		// ReSharper restore CppJoinDeclarationAndAssignment

		x2 = std::move(x);

		REQUIRE(x2.value() == 50);
	}

	SECTION("Unary")
	{
		epsilon<TestType> xpc{50};
		epsilon<TestType> xmc{-50};
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
		epsilon<TestType> x{50};
		x += epsilon<TestType>(1);
		REQUIRE(x.value() == 51);
		x -= epsilon<TestType>(1);
		REQUIRE(x.value() == 50);
		x *= TestType{2};
		REQUIRE(x.value() == 100);
		x /= TestType{2};
		REQUIRE(x.value() == 50);
	}

	SECTION("Comparison")
	{
		epsilon<TestType> x1{50};
		epsilon<TestType> x2{50};
		epsilon<TestType> x3{51};

		REQUIRE(x1 == x2);
		REQUIRE(x2 == x1);
		REQUIRE(x1 != x3);
		REQUIRE(x3 != x1);
	}

	SECTION("Addition")
	{
		epsilon<TestType> x1{50};
		epsilon<TestType> x2{25};
		const epsilon<TestType> xResult{75};

		REQUIRE(x1 + x2 == xResult);
		REQUIRE(x2 + x1 == xResult);
	}

	SECTION("Subtraction")
	{
		epsilon<TestType> x1{50};
		epsilon<TestType> x2{27};
		const epsilon<TestType> xResult{23};

		REQUIRE(x1 - x2 == xResult);
		REQUIRE(x2 - x1 == -xResult);
	}

	SECTION("Multiplication")
	{
		epsilon<TestType> x1{50};
		epsilon<TestType> x2{25};
		const TestType xResult{};

		REQUIRE(x1 * x2 == xResult);
		REQUIRE(x2 * x1 == xResult);
	}

	SECTION("Division")
	{
		epsilon<TestType> x1{50};
		epsilon<TestType> x2{25};
		const TestType xResult1{2};
		const TestType xResult2{TestType{25}/TestType{50}};

		REQUIRE(x1 / x2 == xResult1);
		REQUIRE(x2 / x1 == xResult2);
	}

	SECTION("Interaction") 
	{
		epsilon<TestType, 0> x1{50};
		epsilon<TestType, 1> x2{25};
		const epsilon<TestType, 43> xResult{0};

		REQUIRE(x1 * x2 == xResult);
		REQUIRE(x2 * x1 == xResult);
	}
}

TEST_CASE("Epsilon")
{
	SECTION("Literals")
	{
		auto xf = 50.1_feps;
		auto xd = 50.1_eps;
		auto xl = 50.1_leps;

		REQUIRE(xf.value() == 50.1f);
		REQUIRE(xd.value() == 50.1);
		REQUIRE(xl.value() == 50.1l);
	}

	SECTION("AutoAssignment")
	{
		auto xd = 50.0_eps;
		epsilon<int> xi{50};

		// With conversion

		xd += epsilon<int>(1);
		xi += epsilon<short>(1);
		REQUIRE(xd.value() == 51.0);
		REQUIRE(xi.value() == 51);
		xd -= epsilon<int>(1);
		xi -= epsilon<short>(1);
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
		auto xd1 = 50.0_eps;
		auto xd2 = 50.0_eps;
		auto xdResult = 50.1_eps;
		epsilon<int> xi1{50};
		epsilon<int> xi2{50};
		epsilon<int> xiResult{51};

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
		auto xd1 = 50.0_eps;
		auto xd2 = 25.0_eps;
		const auto xdResult = 75.0_eps;
		epsilon<int> xi1{50};
		epsilon<int> xi2{25};
		const epsilon<int> xiResult{75};

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
		auto xd1 = 50.0_eps;
		auto xd2 = 27.0_eps;
		const auto xdResult = 23.0_eps;
		epsilon<int> xi1{50};
		epsilon<int> xi2{27};
		const epsilon<int> xiResult{23};

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
		auto xd1 = 50.0_eps;
		auto xd2 = 25.0_eps;
		const auto xdResult = 0.0;
		epsilon<int> xi1{50};
		epsilon<int> xi2{25};
		const auto xiResult = 0;

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
		auto xd1 = 50.0_eps;
		auto xd2 = 25.0_eps;
		const auto xdResult1 = 2.0;
		const auto xdResult2 = 0.5;
		epsilon<int> xi1{50};
		epsilon<int> xi2{25};
		const auto xiResult1 = 2;
		const auto xiResult2 = 0;

		// mixing types
		REQUIRE(xd1 / xi2 == xdResult1);
		REQUIRE(xd2 / xi1 == xdResult2);
		REQUIRE(xi1 / xd2 == xdResult1);
		REQUIRE(xi2 / xd1 == xdResult2);
	}
}
