
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

TEST(Imaginary, ImaginaryComparison)
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

TEST(Imaginary, RealImaginaryComparison)
{
	auto xdImaginary1 = 50.0_i;
	auto xdImaginary2 = 0.0_i;
	auto xdReal1 = 50.0;
	auto xdReal2 = 0.0;
	imaginary<int> xiImaginary1{ 50 };
	imaginary<int> xiImaginary2{ 0 };
	auto xiReal1 = 50;
	auto xiReal2 = 0;

	// same type
	EXPECT_FALSE(xdImaginary1 == xdReal1);
	EXPECT_FALSE(xdReal1 == xdImaginary1);
	EXPECT_FALSE(xdImaginary1 == xdReal2);
	EXPECT_FALSE(xdReal1 == xdImaginary2);
	EXPECT_FALSE(xdImaginary2 == xdReal1);
	EXPECT_FALSE(xdReal2 == xdImaginary1);
	EXPECT_TRUE(xdImaginary2 == xdReal2);
	EXPECT_TRUE(xdReal2 == xdImaginary2);

	EXPECT_TRUE(xdImaginary1 != xdReal1);
	EXPECT_TRUE(xdReal1 != xdImaginary1);
	EXPECT_TRUE(xdImaginary1 != xdReal2);
	EXPECT_TRUE(xdReal1 != xdImaginary2);
	EXPECT_TRUE(xdImaginary2 != xdReal1);
	EXPECT_TRUE(xdReal2 != xdImaginary1);
	EXPECT_FALSE(xdImaginary2 != xdReal2);
	EXPECT_FALSE(xdReal2 != xdImaginary2);

	// mixing types
	EXPECT_FALSE(xdImaginary1 == xiReal1);
	EXPECT_FALSE(xdReal1 == xiImaginary1);
	EXPECT_FALSE(xdImaginary1 == xiReal2);
	EXPECT_FALSE(xdReal1 == xiImaginary2);
	EXPECT_FALSE(xdImaginary2 == xiReal1);
	EXPECT_FALSE(xdReal2 == xiImaginary1);
	EXPECT_TRUE(xdImaginary2 == xiReal2);
	EXPECT_TRUE(xdReal2 == xiImaginary2);
	EXPECT_FALSE(xiImaginary1 == xdReal1);
	EXPECT_FALSE(xiReal1 == xdImaginary1);
	EXPECT_FALSE(xiImaginary1 == xdReal2);
	EXPECT_FALSE(xiReal1 == xdImaginary2);
	EXPECT_FALSE(xiImaginary2 == xdReal1);
	EXPECT_FALSE(xiReal2 == xdImaginary1);
	EXPECT_TRUE(xiImaginary2 == xdReal2);
	EXPECT_TRUE(xiReal2 == xdImaginary2);

	EXPECT_TRUE(xdImaginary1 != xiReal1);
	EXPECT_TRUE(xdReal1 != xiImaginary1);
	EXPECT_TRUE(xdImaginary1 != xiReal2);
	EXPECT_TRUE(xdReal1 != xiImaginary2);
	EXPECT_TRUE(xdImaginary2 != xiReal1);
	EXPECT_TRUE(xdReal2 != xiImaginary1);
	EXPECT_FALSE(xdImaginary2 != xiReal2);
	EXPECT_FALSE(xdReal2 != xiImaginary2);
	EXPECT_TRUE(xiImaginary1 != xdReal1);
	EXPECT_TRUE(xiReal1 != xdImaginary1);
	EXPECT_TRUE(xiImaginary1 != xdReal2);
	EXPECT_TRUE(xiReal1 != xdImaginary2);
	EXPECT_TRUE(xiImaginary2 != xdReal1);
	EXPECT_TRUE(xiReal2 != xdImaginary1);
	EXPECT_FALSE(xiImaginary2 != xdReal2);
	EXPECT_FALSE(xiReal2 != xdImaginary2);
}

TEST(Imaginary, ComplexComparison)
{
	auto xdImaginary1 = 50.0_i;
	auto xdImaginary2 = 0.0_i;
	std::complex<double> xdComplex1{ 50.0, 50.0 };
	std::complex<double> xdComplex2{ 0.0, 50.0 };
	std::complex<double> xdComplex3{ 50.0, 0.0 };
	std::complex<double> xdComplex4{ 0.0, 0.0 };
	imaginary<int> xiImaginary1{ 50 };
	imaginary<int> xiImaginary2{ 0 };
	std::complex<int> xiComplex1{ 50, 50 };
	std::complex<int> xiComplex2{ 0, 50 };
	std::complex<int> xiComplex3{ 50, 0 };
	std::complex<int> xiComplex4{ 0, 0 };

	// same type
	EXPECT_FALSE(xdImaginary1 == xdComplex1);
	EXPECT_TRUE(xdImaginary1 == xdComplex2);
	EXPECT_FALSE(xdImaginary1 == xdComplex3);
	EXPECT_FALSE(xdImaginary1 == xdComplex4);
	EXPECT_FALSE(xdImaginary2 == xdComplex1);
	EXPECT_FALSE(xdImaginary2 == xdComplex2);
	EXPECT_FALSE(xdImaginary2 == xdComplex3);
	EXPECT_TRUE(xdImaginary2 == xdComplex4);
	EXPECT_FALSE(xdComplex1 == xdImaginary1);
	EXPECT_TRUE(xdComplex2 == xdImaginary1);
	EXPECT_FALSE(xdComplex3 == xdImaginary1);
	EXPECT_FALSE(xdComplex4 == xdImaginary1);
	EXPECT_FALSE(xdComplex1 == xdImaginary2);
	EXPECT_FALSE(xdComplex2 == xdImaginary2);
	EXPECT_FALSE(xdComplex3 == xdImaginary2);
	EXPECT_TRUE(xdComplex4 == xdImaginary2);

	EXPECT_TRUE(xdImaginary1 != xdComplex1);
	EXPECT_FALSE(xdImaginary1 != xdComplex2);
	EXPECT_TRUE(xdImaginary1 != xdComplex3);
	EXPECT_TRUE(xdImaginary1 != xdComplex4);
	EXPECT_TRUE(xdImaginary2 != xdComplex1);
	EXPECT_TRUE(xdImaginary2 != xdComplex2);
	EXPECT_TRUE(xdImaginary2 != xdComplex3);
	EXPECT_FALSE(xdImaginary2 != xdComplex4);
	EXPECT_TRUE(xdComplex1 != xdImaginary1);
	EXPECT_FALSE(xdComplex2 != xdImaginary1);
	EXPECT_TRUE(xdComplex3 != xdImaginary1);
	EXPECT_TRUE(xdComplex4 != xdImaginary1);
	EXPECT_TRUE(xdComplex1 != xdImaginary2);
	EXPECT_TRUE(xdComplex2 != xdImaginary2);
	EXPECT_TRUE(xdComplex3 != xdImaginary2);
	EXPECT_FALSE(xdComplex4 != xdImaginary2);
}

TEST(Imaginary, ImaginaryAddition)
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

TEST(Imaginary, RealImaginaryAddition)
{
	auto xdReal = 25.0;
	auto xdImaginary = 50.0_i;
	std::complex<double> xdResult1{ 25.0, 50.0 };
	std::complex<double> xdResult2{ 50.0, 25.0 };
	auto xfReal = 25.0f;
	auto xfImaginary = 50.0_fi;
	std::complex<float> xfResult1{ 25.0f, 50.0f };
	std::complex<float> xfResult2{ 50.0f, 25.0f };
	auto xiReal = 25;
	imaginary<int> xiImaginary{ 50 };
	std::complex<int> xiResult1{ 25, 50 };
	std::complex<int> xiResult2{ 50, 25 };

	// same type
	EXPECT_EQ(xdImaginary + xdReal, xdResult1);
	EXPECT_EQ(xdReal + xdImaginary, xdResult1);
	EXPECT_EQ(xfImaginary + xfReal, xfResult1);
	EXPECT_EQ(xfReal + xfImaginary, xfResult1);
	EXPECT_EQ(xiImaginary + xiReal, xiResult1);
	EXPECT_EQ(xiReal + xiImaginary, xiResult1);

	EXPECT_NE(xdImaginary + xdReal, xdResult2);
	EXPECT_NE(xdReal + xdImaginary, xdResult2);
	EXPECT_NE(xfImaginary + xfReal, xfResult2);
	EXPECT_NE(xfReal + xfImaginary, xfResult2);
	EXPECT_NE(xiImaginary + xiReal, xiResult2);
	EXPECT_NE(xiReal + xiImaginary, xiResult2);

	// mixing types
	EXPECT_EQ(xdImaginary + xiReal, xdResult1);
	EXPECT_EQ(xdReal + xiImaginary, xdResult1);
	EXPECT_EQ(xiImaginary + xdReal, xdResult1);
	EXPECT_EQ(xiReal + xdImaginary, xdResult1);
	EXPECT_NE(xdImaginary + xiReal, xdResult2);
	EXPECT_NE(xdReal + xiImaginary, xdResult2);
	EXPECT_NE(xiImaginary + xdReal, xdResult2);
	EXPECT_NE(xiReal + xdImaginary, xdResult2);

	// This is a problem of complex comparison, not of our code.
	//EXPECT_EQ(xdImaginary + xiReal, xiResult);
	//EXPECT_EQ(xdReal + xiImaginary, xiResult);
	//EXPECT_EQ(xiImaginary + xdReal, xiResult);
	//EXPECT_EQ(xiReal + xdImaginary, xiResult);
}

TEST(Imaginary, ComplexImaginaryAddition)
{
	auto xdImaginary = 50.0_i;
	std::complex<double> xdComplex{ 25.0, 27.0 };
	std::complex<double> xdResult{ 25.0, 77.0 };
	auto xfImaginary = 50.0_fi;
	std::complex<float> xfComplex{ 25.0f, 27.0f };
	std::complex<float> xfResult{ 25.0f, 77.0f };
	imaginary<int> xiImaginary{ 50 };
	std::complex<int> xiComplex{ 25, 27 };
	std::complex<int> xiResult{ 25, 77 };

	// same type
	EXPECT_EQ(xdImaginary + xdComplex, xdResult);
	EXPECT_EQ(xdComplex + xdImaginary, xdResult);
	EXPECT_EQ(xfImaginary + xfComplex, xfResult);
	EXPECT_EQ(xfComplex + xfImaginary, xfResult);
	EXPECT_EQ(xiImaginary + xiComplex, xiResult);
	EXPECT_EQ(xiComplex + xiImaginary, xiResult);

	// mixing types
	EXPECT_EQ(xdImaginary + xiComplex, xdResult);
	EXPECT_EQ(xdComplex + xiImaginary, xdResult);
	EXPECT_EQ(xiImaginary + xdComplex, xdResult);
	EXPECT_EQ(xiComplex + xdImaginary, xdResult);

	// This is a problem of complex comparison, not of our code.
	//EXPECT_EQ(xdImaginary + xiReal, xiResult);
	//EXPECT_EQ(xdReal + xiImaginary, xiResult);
	//EXPECT_EQ(xiImaginary + xdReal, xiResult);
	//EXPECT_EQ(xiReal + xdImaginary, xiResult);
}

TEST(Imaginary, ImaginarySubtraction)
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

TEST(Imaginary, RealImaginarySubtraction)
{
	auto xdImaginary = 50.0_i;
	auto xdReal = 27.0;
	std::complex<double> xdResult{ -27.0, 50.0 };
	auto xfImaginary = 50.0_fi;
	auto xfReal = 27.0f;
	std::complex<float> xfResult{ -27.0f, 50.0f };
	imaginary<int> xiImaginary{ 50 };
	auto xiReal = 27;
	std::complex<int> xiResult{ -27, 50 };

	// same type
	EXPECT_EQ(xdImaginary - xdReal, xdResult);
	EXPECT_EQ(xdReal - xdImaginary, -xdResult);
	EXPECT_EQ(xfImaginary - xfReal, xfResult);
	EXPECT_EQ(xfReal - xfImaginary, -xfResult);
	EXPECT_EQ(xiImaginary - xiReal, xiResult);
	EXPECT_EQ(xiReal - xiImaginary, -xiResult);

	// mixing types
	EXPECT_EQ(xdImaginary - xiReal, xdResult);
	EXPECT_EQ(xdReal - xiImaginary, -xdResult);
	EXPECT_EQ(xiImaginary - xdReal, xdResult);
	EXPECT_EQ(xiReal - xdImaginary, -xdResult);

	// This is a problem of complex comparison, not of our code.
	//EXPECT_EQ(xd1 + xiReal, xiResult);
	//EXPECT_EQ(xdReal + xi1, xiResult);
	//EXPECT_EQ(xi1 + xdReal, xiResult);
	//EXPECT_EQ(xiReal + xd1, xiResult);
}

TEST(Imaginary, ComplexImaginarySubtraction)
{
	auto xdImaginary = 50.0_i;
	std::complex<double> xdComplex{ 25.0, 27.0 };
	std::complex<double> xdResult1{ -25.0, 23.0 };
	std::complex<double> xdResult2{ 25.0, -23.0 };
	auto xfImaginary = 50.0_fi;
	std::complex<float> xfComplex{ 25.0f, 27.0f };
	std::complex<float> xfResult1{ -25.0f, 23.0f };
	std::complex<float> xfResult2{ 25.0f, -23.0f };
	imaginary<int> xiImaginary{ 50 };
	std::complex<int> xiComplex{ 25, 27 };
	std::complex<int> xiResult1{ -25, 23 };
	std::complex<int> xiResult2{ 25, -23 };

	// same type
	EXPECT_EQ(xdImaginary - xdComplex, xdResult1);
	EXPECT_EQ(xdComplex - xdImaginary, xdResult2);
	EXPECT_EQ(xfImaginary - xfComplex, xfResult1);
	EXPECT_EQ(xfComplex - xfImaginary, xfResult2);
	EXPECT_EQ(xiImaginary - xiComplex, xiResult1);
	EXPECT_EQ(xiComplex - xiImaginary, xiResult2);

	// mixing types
	EXPECT_EQ(xdImaginary - xiComplex, xdResult1);
	EXPECT_EQ(xdComplex - xiImaginary, xdResult2);
	EXPECT_EQ(xiImaginary - xdComplex, xdResult1);
	EXPECT_EQ(xiComplex - xdImaginary, xdResult2);

	// This is a problem of complex comparison, not of our code.
	//EXPECT_EQ(xdImaginary + xiReal, xiResult);
	//EXPECT_EQ(xdReal + xiImaginary, xiResult);
	//EXPECT_EQ(xiImaginary + xdReal, xiResult);
	//EXPECT_EQ(xiReal + xdImaginary, xiResult);
}

TEST(Imaginary, ImaginaryMultiplication)
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

TEST(Imaginary, RealImaginaryMultiplication)
{
	auto xdImaginary = 50.0_i;
	auto xdReal = 25.0;
	auto xdResult = 1250.0_i;
	auto xfImaginary = 50.0_fi;
	auto xfReal = 25.0f;
	auto xfResult = 1250.0_fi;
	imaginary<int> xiImaginary{ 50 };
	auto xiReal = 25;
	imaginary<int> xiResult{ 1250 };

	// same type
	EXPECT_EQ(xdImaginary * xdReal, xdResult);
	EXPECT_EQ(xdReal * xdImaginary, xdResult);
	EXPECT_EQ(xfImaginary * xfReal, xfResult);
	EXPECT_EQ(xfReal * xfImaginary, xfResult);
	EXPECT_EQ(xiImaginary * xiReal, xiResult);
	EXPECT_EQ(xiReal * xiImaginary, xiResult);

	// mixing types
	EXPECT_EQ(xdImaginary * xiReal, xdResult);
	EXPECT_EQ(xdReal * xiImaginary, xdResult);
	EXPECT_EQ(xiImaginary * xdReal, xdResult);
	EXPECT_EQ(xiReal * xdImaginary, xdResult);

	// This is a problem of complex comparison, not of our code.
	EXPECT_EQ(xdImaginary * xiReal, xiResult);
	EXPECT_EQ(xdReal * xiImaginary, xiResult);
	EXPECT_EQ(xiImaginary * xdReal, xiResult);
	EXPECT_EQ(xiReal * xdImaginary, xiResult);
}

TEST(Imaginary, ComplexImaginaryMultiplication)
{
	auto xdImaginary = 50.0_i;
	std::complex<double> xdComplex{ 25.0, 27.0 };
	std::complex<double> xdResult{ -1350.0, 1250.0 };
	auto xfImaginary = 50.0_fi;
	std::complex<float> xfComplex{ 25.0f, 27.0f };
	std::complex<float> xfResult{ -1350.0f, 1250.0f };
	imaginary<int> xiImaginary{ 50 };
	std::complex<int> xiComplex{ 25, 27 };
	std::complex<int> xiResult{ -1350, 1250 };

	// same type
	EXPECT_EQ(xdImaginary * xdComplex, xdResult);
	EXPECT_EQ(xdComplex * xdImaginary, xdResult);
	EXPECT_EQ(xfImaginary * xfComplex, xfResult);
	EXPECT_EQ(xfComplex * xfImaginary, xfResult);
	EXPECT_EQ(xiImaginary * xiComplex, xiResult);
	EXPECT_EQ(xiComplex * xiImaginary, xiResult);

	// mixing types
	EXPECT_EQ(xdImaginary * xiComplex, xdResult);
	EXPECT_EQ(xdComplex * xiImaginary, xdResult);
	EXPECT_EQ(xiImaginary * xdComplex, xdResult);
	EXPECT_EQ(xiComplex * xdImaginary, xdResult);

	// This is a problem of complex comparison, not of our code.
	//EXPECT_EQ(xdImaginary * xiComplex, xiResult);
	//EXPECT_EQ(xdComplex * xiImaginary, xiResult);
	//EXPECT_EQ(xiImaginary * xdComplex, xiResult);
	//EXPECT_EQ(xiComplex * xdImaginary, xiResult);
}

TEST(Imaginary, ImaginaryDivision)
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

TEST(Imaginary, RealImaginaryDivision)
{
	auto xdImaginary = 50.0_i;
	auto xdReal = 25.0;
	auto xdResult1 = 2.0_i;
	auto xdResult2 = -0.5_i;
	auto xfImaginary = 50.0_fi;
	auto xfReal = 25.0f;
	auto xfResult1 = 2.0_fi;
	auto xfResult2 = -0.5_fi;
	imaginary<int> xiImaginary{ 50 };
	auto xiReal = 25;
	imaginary<int> xiResult1{ 2 };
	imaginary<int> xiResult2{ 0 };

	// same type
	EXPECT_EQ(xdImaginary / xdReal, xdResult1);
	EXPECT_EQ(xdReal / xdImaginary, xdResult2);
	EXPECT_EQ(xfImaginary / xfReal, xfResult1);
	EXPECT_EQ(xfReal / xfImaginary, xfResult2);
	EXPECT_EQ(xiImaginary / xiReal, xiResult1);
	EXPECT_EQ(xiReal / xiImaginary, xiResult2);

	// mixing types
	EXPECT_EQ(xdImaginary / xiReal, xdResult1);
	EXPECT_EQ(xdReal / xiImaginary, xdResult2);
	EXPECT_EQ(xiImaginary / xdReal, xdResult1);
	EXPECT_EQ(xiReal / xdImaginary, xdResult2);
}

TEST(Imaginary, ComplexImaginaryDivision)
{
	auto xdImaginary = 52.0_i;
	std::complex<double> xdComplex{ 26.0, 13.0 };
	std::complex<double> xdResult1{ 0.8, 1.6 };
	std::complex<double> xdResult2{ 0.25, -0.5 };
	auto xfImaginary = 52.0_fi;
	std::complex<float> xfComplex{ 26.0f, 13.0f };
	std::complex<float> xfResult1{ 0.8f, 1.6f };
	std::complex<float> xfResult2{ 0.25f, -0.5f };
	imaginary<int> xiImaginary{ 52 };
	std::complex<int> xiComplex{ 26, 13 };
	std::complex<int> xiResult1{ 0, 1 };
	std::complex<int> xiResult2{ 0, 0 };

	// same type
	EXPECT_EQ(xdImaginary / xdComplex, xdResult1);
	EXPECT_EQ(xdComplex / xdImaginary, xdResult2);
	EXPECT_EQ(xfImaginary / xfComplex, xfResult1);
	EXPECT_EQ(xfComplex / xfImaginary, xfResult2);
	EXPECT_EQ(xiImaginary / xiComplex, xiResult1);
	EXPECT_EQ(xiComplex / xiImaginary, xiResult2);

	// mixing types
	EXPECT_EQ(xdImaginary / xiComplex, xdResult1);
	EXPECT_EQ(xdComplex / xiImaginary, xdResult2);
	EXPECT_EQ(xiImaginary / xdComplex, xdResult1);
	EXPECT_EQ(xiComplex / xdImaginary, xdResult2);
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
