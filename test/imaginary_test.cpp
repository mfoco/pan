
#include <pan/imaginary.h>
#include <gtest/gtest.h>

TEST(Imaginary, DefaultConstruction)
{
	imaginary<float> xf;
	imaginary<double> xd;
	imaginary<long double> xl;
	imaginary<int> xi;

	EXPECT_EQ(xf.value(), 0.0f);
	EXPECT_EQ(xd.value(), 0.0);
	EXPECT_EQ(xl.value(), 0.0l);
	EXPECT_EQ(xi.value(), 0);
}

TEST(Imaginary, Construction)
{
	imaginary<float> xf{ 50.1f };
	imaginary<double> xd{ 50.1 };
	imaginary<long double> xl{ 50.1l };
	imaginary<int> xi{ 50 };

	EXPECT_EQ(xf.value(), 50.1f);
	EXPECT_EQ(xd.value(), 50.1);
	EXPECT_EQ(xl.value(), 50.1l);
	EXPECT_EQ(xi.value(), 50);
}

TEST(Imaginary, CopyConstruction)
{
	imaginary<float> xf{ 50.1f };
	imaginary<double> xd{ 50.1 };
	imaginary<long double> xl{ 50.1l };
	imaginary<int> xi{ 50 };

	imaginary<float> xf2{ xf };
	imaginary<double> xd2{ xd };
	imaginary<long double> xl2{ xl };
	imaginary<int> xi2{ xi };

	EXPECT_EQ(xf.value(), xf2.value());
	EXPECT_EQ(xd.value(), xd2.value());
	EXPECT_EQ(xl.value(), xl2.value());
	EXPECT_EQ(xi.value(), xi2.value());
}

TEST(Imaginary, MoveConstruction)
{
	imaginary<float> xf{ 50.1f };
	imaginary<double> xd{ 50.1 };
	imaginary<long double> xl{ 50.1l };
	imaginary<int> xi{ 50 };

	imaginary<float> xf2{ std::move(xf) };
	imaginary<double> xd2{ std::move(xd) };
	imaginary<long double> xl2{ std::move(xl) };
	imaginary<int> xi2{ std::move(xi) };

	EXPECT_EQ(xf2.value(), 50.1f);
	EXPECT_EQ(xd2.value(), 50.1);
	EXPECT_EQ(xl2.value(), 50.1l);
	EXPECT_EQ(xi2.value(), 50);
}

TEST(Imaginary, CopyAssignment)
{
	imaginary<float> xf{ 50.1f };
	imaginary<double> xd{ 50.1 };
	imaginary<long double> xl{ 50.1l };
	imaginary<int> xi{ 50 };

	imaginary<float> xf2;
	imaginary<double> xd2;
	imaginary<long double> xl2;
	imaginary<int> xi2;

	xf2 = xf;
	xd2 = xd;
	xl2 = xl;
	xi2 = xi;

	EXPECT_EQ(xf.value(), xf2.value());
	EXPECT_EQ(xd.value(), xd2.value());
	EXPECT_EQ(xl.value(), xl2.value());
	EXPECT_EQ(xi.value(), xi2.value());
}

TEST(Imaginary, MoveAssignment)
{
	imaginary<float> xf{ 50.1f };
	imaginary<double> xd{ 50.1 };
	imaginary<long double> xl{ 50.1l };
	imaginary<int> xi{ 50 };

	imaginary<float> xf2;
	imaginary<double> xd2;
	imaginary<long double> xl2;
	imaginary<int> xi2;

	xf2 = std::move(xf);
	xd2 = std::move(xd);
	xl2 = std::move(xl);
	xi2 = std::move(xi);


	EXPECT_EQ(xf2.value(), 50.1f);
	EXPECT_EQ(xd2.value(), 50.1);
	EXPECT_EQ(xl2.value(), 50.1l);
	EXPECT_EQ(xi2.value(), 50);
}

TEST(Imaginary, Literals)
{
	auto xf = 50.1_fi;
	auto xd = 50.1_i;
	auto xl = 50.1_li;

	EXPECT_EQ(xf.value(), 50.1f);
	EXPECT_EQ(xd.value(), 50.1);
	EXPECT_EQ(xl.value(), 50.1l);
}

TEST(Imaginary, Unary)
{
	auto xpc = +50.1_i;
	auto xmc = -50.1_i;
	auto xpv = +xpc;
	auto xmv = -xpc;
	EXPECT_EQ(xpc.value(), 50.1);
	EXPECT_EQ(xmc.value(), -50.1);
	EXPECT_EQ(xpv.value(), 50.1);
	EXPECT_EQ(xmv.value(), -50.1);

	auto xp2 = +std::move(xpc);
	auto xm2 = -std::move(xpv);
	EXPECT_EQ(xp2.value(), 50.1);
	EXPECT_EQ(xm2.value(), -50.1);
}

TEST(Imaginary, AutoAssignment)
{
	auto xd = 50.0_i;
	imaginary<int> xi{ 50 };

	// Same type

	xd += 1.0_i;
	xi += imaginary<int>(1);
	EXPECT_EQ(xd.value(), 51.0);
	EXPECT_EQ(xi.value(), 51);
	xd -= 1.0_i;
	xi -= imaginary<int>(1);
	EXPECT_EQ(xd.value(), 50.0);
	EXPECT_EQ(xi.value(), 50);
	xd *= 2.0;
	xi *= 2;
	EXPECT_EQ(xd.value(), 100.0);
	EXPECT_EQ(xi.value(), 100);
	xd /= 2.0;
	xi /= 2;
	EXPECT_EQ(xd.value(), 50.0);
	EXPECT_EQ(xi.value(), 50);

	// With conversion

	xd += imaginary<int>(1);
	xi += imaginary<short>(1);
	EXPECT_EQ(xd.value(), 51.0);
	EXPECT_EQ(xi.value(), 51);
	xd -= imaginary<int>(1);
	xi -= imaginary<short>(1);
	EXPECT_EQ(xd.value(), 50.0);
	EXPECT_EQ(xi.value(), 50);
	xd *= 2;
	xi *= static_cast<short>(2);
	EXPECT_EQ(xd.value(), 100.0);
	EXPECT_EQ(xi.value(), 100);
	xd /= 2;
	xi /= static_cast<short>(2);
	EXPECT_EQ(xd.value(), 50.0);
	EXPECT_EQ(xi.value(), 50);
}

TEST(Imaginary, Comparison)
{
	auto xd1 = 50.0_i;
	auto xd2 = 50.0_i;
	auto xdResult = 50.1_i;
	auto xf1 = 50.0_fi;
	auto xf2 = 50.0_fi;
	auto xfResult = 50.1_fi;
	imaginary<int> xi1{ 50 };
	imaginary<int> xi2{ 50 };
	imaginary<int> xiResult{ 51 };

	// same type
	EXPECT_TRUE(xd1 == xd2);
	EXPECT_TRUE(xd2 == xd1);
	EXPECT_TRUE(xf1 == xf2);
	EXPECT_TRUE(xf2 == xf1);
	EXPECT_TRUE(xi1 == xi2);
	EXPECT_TRUE(xi2 == xi1);
	EXPECT_FALSE(xd1 == xdResult);
	EXPECT_FALSE(xdResult == xd1);
	EXPECT_FALSE(xf1 == xfResult);
	EXPECT_FALSE(xfResult == xf1);
	EXPECT_FALSE(xi1 == xiResult);
	EXPECT_FALSE(xiResult == xi1);

	EXPECT_FALSE(xd1 != xd2);
	EXPECT_FALSE(xd2 != xd1);
	EXPECT_FALSE(xf1 != xf2);
	EXPECT_FALSE(xf2 != xf1);
	EXPECT_FALSE(xi1 != xi2);
	EXPECT_FALSE(xi2 != xi1);
	EXPECT_TRUE(xd1 != xdResult);
	EXPECT_TRUE(xdResult != xd1);
	EXPECT_TRUE(xf1 != xfResult);
	EXPECT_TRUE(xfResult != xf1);
	EXPECT_TRUE(xi1 != xiResult);
	EXPECT_TRUE(xiResult != xi1);

	// mixing types
	EXPECT_TRUE(xd1 == xi2);
	EXPECT_TRUE(xd2 == xi1);
	EXPECT_TRUE(xi1 == xd2);
	EXPECT_TRUE(xi2 == xd1);
	EXPECT_FALSE(xd1 == xiResult);
	EXPECT_FALSE(xdResult == xi1);
	EXPECT_FALSE(xi1 == xdResult);
	EXPECT_FALSE(xiResult == xd1);

	EXPECT_FALSE(xd1 != xi2);
	EXPECT_FALSE(xd2 != xi1);
	EXPECT_FALSE(xi1 != xd2);
	EXPECT_FALSE(xi2 != xd1);
	EXPECT_TRUE(xd1 != xiResult);
	EXPECT_TRUE(xdResult != xi1);
	EXPECT_TRUE(xi1 != xdResult);
	EXPECT_TRUE(xiResult != xd1);
}

TEST(Imaginary, Addition)
{
	auto xd1 = 50.0_i;
	auto xd2 = 25.0_i;
	auto xdResult = 75.0_i;
	auto xf1 = 50.0_fi;
	auto xf2 = 25.0_fi;
	auto xfResult = 75.0_fi;
	imaginary<int> xi1{ 50 };
	imaginary<int> xi2{ 25 };
	imaginary<int> xiResult{ 75 };

	// same type
	EXPECT_EQ(xd1 + xd2, xdResult);
	EXPECT_EQ(xd2 + xd1, xdResult);
	EXPECT_EQ(xf1 + xf2, xfResult);
	EXPECT_EQ(xf2 + xf1, xfResult);
	EXPECT_EQ(xi1 + xi2, xiResult);
	EXPECT_EQ(xi2 + xi1, xiResult);

	// mixing types
	EXPECT_EQ(xd1 + xi2, xdResult);
	EXPECT_EQ(xd2 + xi1, xdResult);
	EXPECT_EQ(xi1 + xd2, xdResult);
	EXPECT_EQ(xi2 + xd1, xdResult);
	EXPECT_EQ(xd1 + xi2, xiResult);
	EXPECT_EQ(xd2 + xi1, xiResult);
	EXPECT_EQ(xi1 + xd2, xiResult);
	EXPECT_EQ(xi2 + xd1, xiResult);
}

TEST(Imaginary, Subtraction)
{
	auto xd1 = 50.0_i;
	auto xd2 = 27.0_i;
	auto xdResult = 23.0_i;
	auto xf1 = 50.0_fi;
	auto xf2 = 27.0_fi;
	auto xfResult = 23.0_fi;
	imaginary<int> xi1{ 50 };
	imaginary<int> xi2{ 27 };
	imaginary<int> xiResult{ 23 };

	// same type
	EXPECT_EQ(xd1 - xd2, xdResult);
	EXPECT_EQ(xd2 - xd1, -xdResult);
	EXPECT_EQ(xf1 - xf2, xfResult);
	EXPECT_EQ(xf2 - xf1, -xfResult);
	EXPECT_EQ(xi1 - xi2, xiResult);
	EXPECT_EQ(xi2 - xi1, -xiResult);

	// mixing types
	EXPECT_EQ(xd1 - xi2, xdResult);
	EXPECT_EQ(xd2 - xi1, -xdResult);
	EXPECT_EQ(xi1 - xd2, xdResult);
	EXPECT_EQ(xi2 - xd1, -xdResult);
	EXPECT_EQ(xd1 - xi2, xiResult);
	EXPECT_EQ(xd2 - xi1, -xiResult);
	EXPECT_EQ(xi1 - xd2, xiResult);
	EXPECT_EQ(xi2 - xd1, -xiResult);
}

TEST(Imaginary, Multiplication)
{
	auto xd1 = 50.0_i;
	auto xd2 = 25.0_i;
	auto xdResult = -1250.0;
	auto xf1 = 50.0_fi;
	auto xf2 = 25.0_fi;
	auto xfResult = -1250.0f;
	imaginary<int> xi1{ 50 };
	imaginary<int> xi2{ 25 };
	auto xiResult = -1250;

	// same type
	EXPECT_EQ(xd1 * xd2, xdResult);
	EXPECT_EQ(xd2 * xd1, xdResult);
	EXPECT_EQ(xf1 * xf2, xfResult);
	EXPECT_EQ(xf2 * xf1, xfResult);
	EXPECT_EQ(xi1 * xi2, xiResult);
	EXPECT_EQ(xi2 * xi1, xiResult);

	// mixing types
	EXPECT_EQ(xd1 * xi2, xdResult);
	EXPECT_EQ(xd2 * xi1, xdResult);
	EXPECT_EQ(xi1 * xd2, xdResult);
	EXPECT_EQ(xi2 * xd1, xdResult);
	EXPECT_EQ(xd1 * xi2, xiResult);
	EXPECT_EQ(xd2 * xi1, xiResult);
	EXPECT_EQ(xi1 * xd2, xiResult);
	EXPECT_EQ(xi2 * xd1, xiResult);
}

TEST(Imaginary, Division)
{
	auto xd1 = 50.0_i;
	auto xd2 = 25.0_i;
	auto xdResult1 = 2.0;
	auto xdResult2 = 0.5;
	auto xf1 = 50.0_fi;
	auto xf2 = 25.0_fi;
	auto xfResult1 = 2.0f;
	auto xfResult2 = 0.5f;
	imaginary<int> xi1{ 50 };
	imaginary<int> xi2{ 25 };
	auto xiResult1 = 2;
	auto xiResult2 = 0;

	// same type
	EXPECT_EQ(xd1 / xd2, xdResult1);
	EXPECT_EQ(xd2 / xd1, xdResult2);
	EXPECT_EQ(xf1 / xf2, xfResult1);
	EXPECT_EQ(xf2 / xf1, xfResult2);
	EXPECT_EQ(xi1 / xi2, xiResult1);
	EXPECT_EQ(xi2 / xi1, xiResult2);

	// mixing types
	EXPECT_EQ(xd1 / xi2, xdResult1);
	EXPECT_EQ(xd2 / xi1, xdResult2);
	EXPECT_EQ(xi1 / xd2, xdResult1);
	EXPECT_EQ(xi2 / xd1, xdResult2);
}

/*
TEST(Imaginary, Rest)
{
	assert(x == xp);
	assert(x != 50.0);
	assert(xm.value() == -50.0);
	assert(-xm == x);
	assert(xm == -x);

	auto a = 10 * x;
	auto b = 10.0 * xp;
	auto c = 10.0f * xf;
	auto d = x * 10;
	auto e = xp * 10.0;
	auto f = xf * 10.0f;
	auto g = a*b;
	auto h = b*a;
	auto i = xf * x;
	auto j = x * xf;

	assert(a == d);
	assert(b == e);
	assert(c == f);
	assert(g == h);
	assert(i == j);

	std::complex<double> q{ 1.0, 2.0 };
	q += x;
	q = x + q;

	auto q1 = q / x;
	auto q2 = 1.0 / x;
	auto q3 = x / q;
	auto q4 = x / 1.0;
	auto t = 1.0f + 5.0_i;
}
*/
