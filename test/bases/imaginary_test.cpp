
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

	SECTION("Unary")
	{
		auto xpc = +50.1_i;
		auto xmc = -50.1_i;
		auto xpv = +xpc;
		auto xmv = -xpc;
		REQUIRE(xpc.value() == 50.1);
		REQUIRE(xmc.value() == -50.1);
		REQUIRE(xpv.value() == 50.1);
		REQUIRE(xmv.value() == -50.1);

		auto xp2 = +std::move(xpc);
		auto xm2 = -std::move(xpv);
		REQUIRE(xp2.value() == 50.1);
		REQUIRE(xm2.value() == -50.1);
	}

	SECTION("AutoAssignment")
	{
		auto xd = 50.0_i;
		imaginary<int> xi{50};

		// Same type

		xd += 1.0_i;
		xi += imaginary<int>(1);
		REQUIRE(xd.value() == 51.0);
		REQUIRE(xi.value() == 51);
		xd -= 1.0_i;
		xi -= imaginary<int>(1);
		REQUIRE(xd.value() == 50.0);
		REQUIRE(xi.value() == 50);
		xd *= 2.0;
		xi *= 2;
		REQUIRE(xd.value() == 100.0);
		REQUIRE(xi.value() == 100);
		xd /= 2.0;
		xi /= 2;
		REQUIRE(xd.value() == 50.0);
		REQUIRE(xi.value() == 50);

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
		auto xf1 = 50.0_fi;
		auto xf2 = 50.0_fi;
		auto xfResult = 50.1_fi;
		imaginary<int> xi1{50};
		imaginary<int> xi2{50};
		imaginary<int> xiResult{51};

		// same type
		REQUIRE(xd1 == xd2);
		REQUIRE(xd2 == xd1);
		REQUIRE(xf1 == xf2);
		REQUIRE(xf2 == xf1);
		REQUIRE(xi1 == xi2);
		REQUIRE(xi2 == xi1);
		REQUIRE(xd1 != xdResult);
		REQUIRE(xdResult != xd1);
		REQUIRE(xf1 != xfResult);
		REQUIRE(xfResult != xf1);
		REQUIRE(xi1 != xiResult);
		REQUIRE(xiResult != xi1);

		REQUIRE(xd1 == xd2);
		REQUIRE(xd2 == xd1);
		REQUIRE(xf1 == xf2);
		REQUIRE(xf2 == xf1);
		REQUIRE(xi1 == xi2);
		REQUIRE(xi2 == xi1);
		REQUIRE(xd1 != xdResult);
		REQUIRE(xdResult != xd1);
		REQUIRE(xf1 != xfResult);
		REQUIRE(xfResult != xf1);
		REQUIRE(xi1 != xiResult);
		REQUIRE(xiResult != xi1);

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
		auto xf1 = 50.0_fi;
		auto xf2 = 25.0_fi;
		const auto xfResult = 75.0_fi;
		imaginary<int> xi1{50};
		imaginary<int> xi2{25};
		const imaginary<int> xiResult{75};

		// same type
		REQUIRE(xd1 + xd2 == xdResult);
		REQUIRE(xd2 + xd1 == xdResult);
		REQUIRE(xf1 + xf2 == xfResult);
		REQUIRE(xf2 + xf1 == xfResult);
		REQUIRE(xi1 + xi2 == xiResult);
		REQUIRE(xi2 + xi1 == xiResult);

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
		auto xf1 = 50.0_fi;
		auto xf2 = 27.0_fi;
		const auto xfResult = 23.0_fi;
		imaginary<int> xi1{50};
		imaginary<int> xi2{27};
		const imaginary<int> xiResult{23};

		// same type
		REQUIRE(xd1 - xd2 == xdResult);
		REQUIRE(xd2 - xd1 == -xdResult);
		REQUIRE(xf1 - xf2 == xfResult);
		REQUIRE(xf2 - xf1 == -xfResult);
		REQUIRE(xi1 - xi2 == xiResult);
		REQUIRE(xi2 - xi1 == -xiResult);

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
		auto xf1 = 50.0_fi;
		auto xf2 = 25.0_fi;
		const auto xfResult = -1250.0f;
		imaginary<int> xi1{50};
		imaginary<int> xi2{25};
		const auto xiResult = -1250;

		// same type
		REQUIRE(xd1 * xd2 == xdResult);
		REQUIRE(xd2 * xd1 == xdResult);
		REQUIRE(xf1 * xf2 == xfResult);
		REQUIRE(xf2 * xf1 == xfResult);
		REQUIRE(xi1 * xi2 == xiResult);
		REQUIRE(xi2 * xi1 == xiResult);

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
		auto xf1 = 50.0_fi;
		auto xf2 = 25.0_fi;
		const auto xfResult1 = 2.0f;
		const auto xfResult2 = 0.5f;
		imaginary<int> xi1{50};
		imaginary<int> xi2{25};
		const auto xiResult1 = 2;
		const auto xiResult2 = 0;

		// same type
		REQUIRE(xd1 / xd2 == xdResult1);
		REQUIRE(xd2 / xd1 == xdResult2);
		REQUIRE(xf1 / xf2 == xfResult1);
		REQUIRE(xf2 / xf1 == xfResult2);
		REQUIRE(xi1 / xi2 == xiResult1);
		REQUIRE(xi2 / xi1 == xiResult2);

		// mixing types
		REQUIRE(xd1 / xi2 == xdResult1);
		REQUIRE(xd2 / xi1 == xdResult2);
		REQUIRE(xi1 / xd2 == xdResult1);
		REQUIRE(xi2 / xd1 == xdResult2);
	}
}
