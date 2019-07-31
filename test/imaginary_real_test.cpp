
#include <pan/imaginary.hpp>
#include <gtest/gtest.h>

using namespace pan;

TEST(ImaginaryReal, Comparison)
{
	auto xdImaginary1 = 50.0_i;
	auto xdImaginary2 = 0.0_i;
	auto xdReal1 = 50.0;
	auto xdReal2 = 0.0;

    auto xfImaginary1 = 50.0_fi;
    auto xfImaginary2 = 0.0_fi;
    auto xfReal1 = 50.0f;
    auto xfReal2 = 0.0f;

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

    EXPECT_FALSE(xfImaginary1 == xfReal1);
    EXPECT_FALSE(xfReal1 == xfImaginary1);
    EXPECT_FALSE(xfImaginary1 == xfReal2);
    EXPECT_FALSE(xfReal1 == xfImaginary2);
    EXPECT_FALSE(xfImaginary2 == xfReal1);
    EXPECT_FALSE(xfReal2 == xfImaginary1);
    EXPECT_TRUE(xfImaginary2 == xfReal2);
    EXPECT_TRUE(xfReal2 == xfImaginary2);

    EXPECT_TRUE(xfImaginary1 != xfReal1);
    EXPECT_TRUE(xfReal1 != xfImaginary1);
    EXPECT_TRUE(xfImaginary1 != xfReal2);
    EXPECT_TRUE(xfReal1 != xfImaginary2);
    EXPECT_TRUE(xfImaginary2 != xfReal1);
    EXPECT_TRUE(xfReal2 != xfImaginary1);
    EXPECT_FALSE(xfImaginary2 != xfReal2);
    EXPECT_FALSE(xfReal2 != xfImaginary2);

    EXPECT_FALSE(xiImaginary1 == xiReal1);
    EXPECT_FALSE(xiReal1 == xiImaginary1);
    EXPECT_FALSE(xiImaginary1 == xiReal2);
    EXPECT_FALSE(xiReal1 == xiImaginary2);
    EXPECT_FALSE(xiImaginary2 == xiReal1);
    EXPECT_FALSE(xiReal2 == xiImaginary1);
    EXPECT_TRUE(xiImaginary2 == xiReal2);
    EXPECT_TRUE(xiReal2 == xiImaginary2);

    EXPECT_TRUE(xiImaginary1 != xiReal1);
    EXPECT_TRUE(xiReal1 != xiImaginary1);
    EXPECT_TRUE(xiImaginary1 != xiReal2);
    EXPECT_TRUE(xiReal1 != xiImaginary2);
    EXPECT_TRUE(xiImaginary2 != xiReal1);
    EXPECT_TRUE(xiReal2 != xiImaginary1);
    EXPECT_FALSE(xiImaginary2 != xiReal2);
    EXPECT_FALSE(xiReal2 != xiImaginary2);
    
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

    EXPECT_FALSE(xdImaginary1 == xfReal1);
    EXPECT_FALSE(xdReal1 == xfImaginary1);
    EXPECT_FALSE(xdImaginary1 == xfReal2);
    EXPECT_FALSE(xdReal1 == xfImaginary2);
    EXPECT_FALSE(xdImaginary2 == xfReal1);
    EXPECT_FALSE(xdReal2 == xfImaginary1);
    EXPECT_TRUE(xdImaginary2 == xfReal2);
    EXPECT_TRUE(xdReal2 == xfImaginary2);

    EXPECT_FALSE(xfImaginary1 == xdReal1);
    EXPECT_FALSE(xfReal1 == xdImaginary1);
    EXPECT_FALSE(xfImaginary1 == xdReal2);
    EXPECT_FALSE(xfReal1 == xdImaginary2);
    EXPECT_FALSE(xfImaginary2 == xdReal1);
    EXPECT_FALSE(xfReal2 == xdImaginary1);
    EXPECT_TRUE(xfImaginary2 == xdReal2);
    EXPECT_TRUE(xfReal2 == xdImaginary2);

    EXPECT_TRUE(xdImaginary1 != xfReal1);
    EXPECT_TRUE(xdReal1 != xfImaginary1);
    EXPECT_TRUE(xdImaginary1 != xfReal2);
    EXPECT_TRUE(xdReal1 != xfImaginary2);
    EXPECT_TRUE(xdImaginary2 != xfReal1);
    EXPECT_TRUE(xdReal2 != xfImaginary1);
    EXPECT_FALSE(xdImaginary2 != xfReal2);
    EXPECT_FALSE(xdReal2 != xfImaginary2);

    EXPECT_TRUE(xfImaginary1 != xdReal1);
    EXPECT_TRUE(xfReal1 != xdImaginary1);
    EXPECT_TRUE(xfImaginary1 != xdReal2);
    EXPECT_TRUE(xfReal1 != xdImaginary2);
    EXPECT_TRUE(xfImaginary2 != xdReal1);
    EXPECT_TRUE(xfReal2 != xdImaginary1);
    EXPECT_FALSE(xfImaginary2 != xdReal2);
    EXPECT_FALSE(xfReal2 != xdImaginary2);
    
    EXPECT_FALSE(xfImaginary1 == xiReal1);
    EXPECT_FALSE(xfReal1 == xiImaginary1);
    EXPECT_FALSE(xfImaginary1 == xiReal2);
    EXPECT_FALSE(xfReal1 == xiImaginary2);
    EXPECT_FALSE(xfImaginary2 == xiReal1);
    EXPECT_FALSE(xfReal2 == xiImaginary1);
    EXPECT_TRUE(xfImaginary2 == xiReal2);
    EXPECT_TRUE(xfReal2 == xiImaginary2);

    EXPECT_FALSE(xiImaginary1 == xfReal1);
    EXPECT_FALSE(xiReal1 == xfImaginary1);
    EXPECT_FALSE(xiImaginary1 == xfReal2);
    EXPECT_FALSE(xiReal1 == xfImaginary2);
    EXPECT_FALSE(xiImaginary2 == xfReal1);
    EXPECT_FALSE(xiReal2 == xfImaginary1);
    EXPECT_TRUE(xiImaginary2 == xfReal2);
    EXPECT_TRUE(xiReal2 == xfImaginary2);

    EXPECT_TRUE(xfImaginary1 != xiReal1);
    EXPECT_TRUE(xfReal1 != xiImaginary1);
    EXPECT_TRUE(xfImaginary1 != xiReal2);
    EXPECT_TRUE(xfReal1 != xiImaginary2);
    EXPECT_TRUE(xfImaginary2 != xiReal1);
    EXPECT_TRUE(xfReal2 != xiImaginary1);
    EXPECT_FALSE(xfImaginary2 != xiReal2);
    EXPECT_FALSE(xfReal2 != xiImaginary2);

    EXPECT_TRUE(xiImaginary1 != xfReal1);
    EXPECT_TRUE(xiReal1 != xfImaginary1);
    EXPECT_TRUE(xiImaginary1 != xfReal2);
    EXPECT_TRUE(xiReal1 != xfImaginary2);
    EXPECT_TRUE(xiImaginary2 != xfReal1);
    EXPECT_TRUE(xiReal2 != xfImaginary1);
    EXPECT_FALSE(xiImaginary2 != xfReal2);
    EXPECT_FALSE(xiReal2 != xfImaginary2);
}

TEST(ImaginaryReal, Addition)
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
}

TEST(ImaginaryReal, Subtraction)
{
	auto xdImaginary = 50.0_i;
	auto xdReal = 27.0;
	const std::complex<double> xdResult{ -27.0, 50.0 };
	auto xfImaginary = 50.0_fi;
	auto xfReal = 27.0f;
	const std::complex<float> xfResult{ -27.0f, 50.0f };
	imaginary<int> xiImaginary{ 50 };
	auto xiReal = 27;
	const std::complex<int> xiResult{ -27, 50 };

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
}

TEST(ImaginaryReal, Multiplication)
{
	auto xdImaginary = 50.0_i;
	auto xdReal = 25.0;
	const auto xdResult = 1250.0_i;
	auto xfImaginary = 50.0_fi;
	auto xfReal = 25.0f;
	const auto xfResult = 1250.0_fi;
	imaginary<int> xiImaginary{ 50 };
	auto xiReal = 25;
	const imaginary<int> xiResult{ 1250 };

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

	EXPECT_EQ(xdImaginary * xiReal, xiResult);
	EXPECT_EQ(xdReal * xiImaginary, xiResult);
	EXPECT_EQ(xiImaginary * xdReal, xiResult);
	EXPECT_EQ(xiReal * xdImaginary, xiResult);
}

TEST(ImaginaryReal, Division)
{
	auto xdImaginary = 50.0_i;
	auto xdReal = 25.0;
	const auto xdResult1 = 2.0_i;
	const auto xdResult2 = -0.5_i;
	auto xfImaginary = 50.0_fi;
	auto xfReal = 25.0f;
	const auto xfResult1 = 2.0_fi;
	const auto xfResult2 = -0.5_fi;
	imaginary<int> xiImaginary{ 50 };
	auto xiReal = 25;
	const imaginary<int> xiResult1{ 2 };
	const imaginary<int> xiResult2{ 0 };

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

    EXPECT_EQ(xdImaginary / xiReal, xiResult1);
    EXPECT_EQ(xiImaginary / xdReal, xiResult1);

    // 0.5 is not representable in int, these should be NE
    EXPECT_NE(xdReal / xiImaginary, xiResult2);
    EXPECT_NE(xiReal / xdImaginary, xiResult2);
}
