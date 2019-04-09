
#include <gtest/gtest.h>
#include <pan/base.h>
#include <imaginary.h>
#include <dual_base.hpp>

using namespace pan;

TEST(Base, Construction)
{
    constexpr float r0{ 0 };
    constexpr float r1{ 1 };
    constexpr imaginary<float> i0{ 0 };
    constexpr imaginary<float> i1{ 1 };
    constexpr epsilon<float> e0{ 0 };
    constexpr epsilon<float> e1{ 1 };

    EXPECT_EQ(r0, 0);
    EXPECT_EQ(r1, 1);
    EXPECT_EQ(i0.value(), 0);
    EXPECT_EQ(i1.value(), 1);
    EXPECT_EQ(e0.value(), 0);
    EXPECT_EQ(e1.value(), 1);
}

TEST(Base, Multiplication)
{
    constexpr float r0{ 0 };
    constexpr float r1{ 1 };
    constexpr float rm1{ -1 };
    constexpr imaginary<float> i0{ 0 };
    constexpr imaginary<float> i1{ 1 };
    constexpr epsilon<float> e0{ 0 };
    constexpr epsilon<float> e1{ 1 };

    EXPECT_EQ(r0 * r0, r0);
    EXPECT_EQ(r1 * r0, r0);
    EXPECT_EQ(r0 * r1, r0);
    EXPECT_EQ(r1 * r1, r1);

    EXPECT_EQ(i0 * i0, r0);
    EXPECT_EQ(i0 * i1, r0);
    EXPECT_EQ(i1 * i0, r0);
    EXPECT_EQ(i1 * i1, rm1);

    EXPECT_EQ(e0 * e0, r0);
    EXPECT_EQ(e0 * e1, r0);
    EXPECT_EQ(e1 * e0, r0);
    EXPECT_EQ(e1 * e1, r0);

    EXPECT_EQ(r0 * i0, i0);
    EXPECT_EQ(r1 * i0, i0);
    EXPECT_EQ(r0 * i1, i0);
    EXPECT_EQ(r1 * i1, i1);

    EXPECT_EQ(i0 * r0, i0);
    EXPECT_EQ(i1 * r0, i0);
    EXPECT_EQ(i0 * r1, i0);
    EXPECT_EQ(i1 * r1, i1);

    EXPECT_EQ(r0 * e0, e0);
    EXPECT_EQ(r0 * e1, e0);
    EXPECT_EQ(r1 * e0, e0);
    EXPECT_EQ(r1 * e1, e1);

    EXPECT_EQ(e0 * r0, e0);
    EXPECT_EQ(e0 * r1, e0);
    EXPECT_EQ(e1 * r0, e0);
    EXPECT_EQ(e1 * r1, e1);

}
