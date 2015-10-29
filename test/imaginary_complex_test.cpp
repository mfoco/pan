
#include <pan/imaginary.h>
#include <gtest/gtest.h>

TEST(ImaginaryComplex, Comparison)
{
	auto xdImaginary1 = 0.0_i;
	auto xdImaginary2 = 50.0_i;
	std::complex<double> xdComplex1{ 0.0, 0.0 };
	std::complex<double> xdComplex2{ 0.0, 50.0 };
	std::complex<double> xdComplex3{ 50.0, 0.0 };
	std::complex<double> xdComplex4{ 50.0, 50.0 };
	imaginary<int> xiImaginary1{ 0 };
	imaginary<int> xiImaginary2{ 50 };
	std::complex<int> xiComplex1{ 0, 0 };
	std::complex<int> xiComplex2{ 0, 50 };
	std::complex<int> xiComplex3{ 50, 0 };
	std::complex<int> xiComplex4{ 50, 50 };

	// same type
	EXPECT_TRUE(xdImaginary1 == xdComplex1);
	EXPECT_FALSE(xdImaginary1 == xdComplex2);
	EXPECT_FALSE(xdImaginary1 == xdComplex3);
	EXPECT_FALSE(xdImaginary1 == xdComplex4);
	EXPECT_FALSE(xdImaginary2 == xdComplex1);
	EXPECT_TRUE(xdImaginary2 == xdComplex2);
	EXPECT_FALSE(xdImaginary2 == xdComplex3);
	EXPECT_FALSE(xdImaginary2 == xdComplex4);
	EXPECT_TRUE(xdComplex1 == xdImaginary1);
	EXPECT_FALSE(xdComplex2 == xdImaginary1);
	EXPECT_FALSE(xdComplex3 == xdImaginary1);
	EXPECT_FALSE(xdComplex4 == xdImaginary1);
	EXPECT_FALSE(xdComplex1 == xdImaginary2);
	EXPECT_TRUE(xdComplex2 == xdImaginary2);
	EXPECT_FALSE(xdComplex3 == xdImaginary2);
	EXPECT_FALSE(xdComplex4 == xdImaginary2);

	EXPECT_FALSE(xdImaginary1 != xdComplex1);
	EXPECT_TRUE(xdImaginary1 != xdComplex2);
	EXPECT_TRUE(xdImaginary1 != xdComplex3);
	EXPECT_TRUE(xdImaginary1 != xdComplex4);
	EXPECT_TRUE(xdImaginary2 != xdComplex1);
	EXPECT_FALSE(xdImaginary2 != xdComplex2);
	EXPECT_TRUE(xdImaginary2 != xdComplex3);
	EXPECT_TRUE(xdImaginary2 != xdComplex4);
	EXPECT_FALSE(xdComplex1 != xdImaginary1);
	EXPECT_TRUE(xdComplex2 != xdImaginary1);
	EXPECT_TRUE(xdComplex3 != xdImaginary1);
	EXPECT_TRUE(xdComplex4 != xdImaginary1);
	EXPECT_TRUE(xdComplex1 != xdImaginary2);
	EXPECT_FALSE(xdComplex2 != xdImaginary2);
	EXPECT_TRUE(xdComplex3 != xdImaginary2);
	EXPECT_TRUE(xdComplex4 != xdImaginary2);

	EXPECT_TRUE(xiImaginary1 == xiComplex1);
	EXPECT_FALSE(xiImaginary1 == xiComplex2);
	EXPECT_FALSE(xiImaginary1 == xiComplex3);
	EXPECT_FALSE(xiImaginary1 == xiComplex4);
	EXPECT_FALSE(xiImaginary2 == xiComplex1);
	EXPECT_TRUE(xiImaginary2 == xiComplex2);
	EXPECT_FALSE(xiImaginary2 == xiComplex3);
	EXPECT_FALSE(xiImaginary2 == xiComplex4);
	EXPECT_TRUE(xiComplex1 == xiImaginary1);
	EXPECT_FALSE(xiComplex2 == xiImaginary1);
	EXPECT_FALSE(xiComplex3 == xiImaginary1);
	EXPECT_FALSE(xiComplex4 == xiImaginary1);
	EXPECT_FALSE(xiComplex1 == xiImaginary2);
	EXPECT_TRUE(xiComplex2 == xiImaginary2);
	EXPECT_FALSE(xiComplex3 == xiImaginary2);
	EXPECT_FALSE(xiComplex4 == xiImaginary2);

	EXPECT_FALSE(xiImaginary1 != xiComplex1);
	EXPECT_TRUE(xiImaginary1 != xiComplex2);
	EXPECT_TRUE(xiImaginary1 != xiComplex3);
	EXPECT_TRUE(xiImaginary1 != xiComplex4);
	EXPECT_TRUE(xiImaginary2 != xiComplex1);
	EXPECT_FALSE(xiImaginary2 != xiComplex2);
	EXPECT_TRUE(xiImaginary2 != xiComplex3);
	EXPECT_TRUE(xiImaginary2 != xiComplex4);
	EXPECT_FALSE(xiComplex1 != xiImaginary1);
	EXPECT_TRUE(xiComplex2 != xiImaginary1);
	EXPECT_TRUE(xiComplex3 != xiImaginary1);
	EXPECT_TRUE(xiComplex4 != xiImaginary1);
	EXPECT_TRUE(xiComplex1 != xiImaginary2);
	EXPECT_FALSE(xiComplex2 != xiImaginary2);
	EXPECT_TRUE(xiComplex3 != xiImaginary2);
	EXPECT_TRUE(xiComplex4 != xiImaginary2);

	// mixing types
	EXPECT_TRUE(xdImaginary1 == xiComplex1);
	EXPECT_FALSE(xdImaginary1 == xiComplex2);
	EXPECT_FALSE(xdImaginary1 == xiComplex3);
	EXPECT_FALSE(xdImaginary1 == xiComplex4);
	EXPECT_FALSE(xdImaginary2 == xiComplex1);
	EXPECT_TRUE(xdImaginary2 == xiComplex2);
	EXPECT_FALSE(xdImaginary2 == xiComplex3);
	EXPECT_FALSE(xdImaginary2 == xiComplex4);
	EXPECT_TRUE(xdComplex1 == xiImaginary1);
	EXPECT_FALSE(xdComplex2 == xiImaginary1);
	EXPECT_FALSE(xdComplex3 == xiImaginary1);
	EXPECT_FALSE(xdComplex4 == xiImaginary1);
	EXPECT_FALSE(xdComplex1 == xiImaginary2);
	EXPECT_TRUE(xdComplex2 == xiImaginary2);
	EXPECT_FALSE(xdComplex3 == xiImaginary2);
	EXPECT_FALSE(xdComplex4 == xiImaginary2);

	EXPECT_FALSE(xdImaginary1 != xiComplex1);
	EXPECT_TRUE(xdImaginary1 != xiComplex2);
	EXPECT_TRUE(xdImaginary1 != xiComplex3);
	EXPECT_TRUE(xdImaginary1 != xiComplex4);
	EXPECT_TRUE(xdImaginary2 != xiComplex1);
	EXPECT_FALSE(xdImaginary2 != xiComplex2);
	EXPECT_TRUE(xdImaginary2 != xiComplex3);
	EXPECT_TRUE(xdImaginary2 != xiComplex4);
	EXPECT_FALSE(xdComplex1 != xiImaginary1);
	EXPECT_TRUE(xdComplex2 != xiImaginary1);
	EXPECT_TRUE(xdComplex3 != xiImaginary1);
	EXPECT_TRUE(xdComplex4 != xiImaginary1);
	EXPECT_TRUE(xdComplex1 != xiImaginary2);
	EXPECT_FALSE(xdComplex2 != xiImaginary2);
	EXPECT_TRUE(xdComplex3 != xiImaginary2);
	EXPECT_TRUE(xdComplex4 != xiImaginary2);

	EXPECT_TRUE(xiImaginary1 == xdComplex1);
	EXPECT_FALSE(xiImaginary1 == xdComplex2);
	EXPECT_FALSE(xiImaginary1 == xdComplex3);
	EXPECT_FALSE(xiImaginary1 == xdComplex4);
	EXPECT_FALSE(xiImaginary2 == xdComplex1);
	EXPECT_TRUE(xiImaginary2 == xdComplex2);
	EXPECT_FALSE(xiImaginary2 == xdComplex3);
	EXPECT_FALSE(xiImaginary2 == xdComplex4);
	EXPECT_TRUE(xiComplex1 == xdImaginary1);
	EXPECT_FALSE(xiComplex2 == xdImaginary1);
	EXPECT_FALSE(xiComplex3 == xdImaginary1);
	EXPECT_FALSE(xiComplex4 == xdImaginary1);
	EXPECT_FALSE(xiComplex1 == xdImaginary2);
	EXPECT_TRUE(xiComplex2 == xdImaginary2);
	EXPECT_FALSE(xiComplex3 == xdImaginary2);
	EXPECT_FALSE(xiComplex4 == xdImaginary2);

	EXPECT_FALSE(xiImaginary1 != xdComplex1);
	EXPECT_TRUE(xiImaginary1 != xdComplex2);
	EXPECT_TRUE(xiImaginary1 != xdComplex3);
	EXPECT_TRUE(xiImaginary1 != xdComplex4);
	EXPECT_TRUE(xiImaginary2 != xdComplex1);
	EXPECT_FALSE(xiImaginary2 != xdComplex2);
	EXPECT_TRUE(xiImaginary2 != xdComplex3);
	EXPECT_TRUE(xiImaginary2 != xdComplex4);
	EXPECT_FALSE(xiComplex1 != xdImaginary1);
	EXPECT_TRUE(xiComplex2 != xdImaginary1);
	EXPECT_TRUE(xiComplex3 != xdImaginary1);
	EXPECT_TRUE(xiComplex4 != xdImaginary1);
	EXPECT_TRUE(xiComplex1 != xdImaginary2);
	EXPECT_FALSE(xiComplex2 != xdImaginary2);
	EXPECT_TRUE(xiComplex3 != xdImaginary2);
	EXPECT_TRUE(xiComplex4 != xdImaginary2);
}

TEST(ImaginaryComplex, Addition)
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

TEST(ImaginaryComplex, Subtraction)
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

TEST(ImaginaryComplex, Multiplication)
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

TEST(ImaginaryComplex, Division)
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
