
#include <pan/integer.h>
#include <gtest/gtest.h>

using namespace pan;

TEST(Integer, DefaultConstruction)
{
    integer<false, 10> u10{};
    integer<true, 10> s10{};
    integer<false, 20> u20{};
    integer<true, 20> s20{};
    integer<false, 32> u32{};
    integer<true, 31> s31{};
    integer<false, 64> u64{};
    integer<true, 63> s63{};

    ASSERT_EQ(u10.value(), 0);
    ASSERT_EQ(s10.value(), 0);
    ASSERT_EQ(u20.value(), 0);
    ASSERT_EQ(s20.value(), 0);
    ASSERT_EQ(u32.value(), 0);
    ASSERT_EQ(s31.value(), 0);
    ASSERT_EQ(u64.value(), 0);
    ASSERT_EQ(s63.value(), 0);
}

TEST(Integer, Construction)
{
    constexpr integer<false, 10> u10_10s{ 10 };
    constexpr integer<true, 10> s10_10s{ 10 };
    constexpr integer<false, 10> u10_10u{ 10u };
    constexpr integer<true, 10> s10_10u{ 10u };
    constexpr integer<false, 1> s10_10u_fail{ 10241u }; // SHOULD NOT COMPILE!!!


    ASSERT_EQ(u10_10s.value(), u10_10u.value());
    ASSERT_EQ(s10_10s.value(), s10_10u.value());
}

TEST(Integer, CopyConstruction)
{
    integer<false, 10> u10_10s1{ 10 };
    auto u10_10s2 = u10_10s1;
    ASSERT_EQ(u10_10s1.value(), u10_10s2.value());
}

TEST(Integer, MoveConstruction)
{
    integer<false, 10> u10_10s1{ 10 };
    integer<false, 10> u10_10s2(std::move(u10_10s1));
    ASSERT_EQ(u10_10s1.value(), 0);
    ASSERT_EQ(u10_10s2.value(), 10);
}

TEST(Integer, ConvertingConstruction)
{
    integer<false, 10> u10_10s1{ 10 };
    integer<false, 20> u20_10s1 = u10_10s1;
    ASSERT_EQ(u10_10s1.value(), u20_10s1.value());

    integer<true, 11> s11_10s1 = u10_10s1;
    ASSERT_EQ(u10_10s1.value(), s11_10s1.value());
}

TEST(Integer, CopyAssignment)
{
    integer<false, 10> u10_10s1{ 10 };
    integer<false, 10>  u10_10s2;
    u10_10s2 = u10_10s1;
    ASSERT_EQ(u10_10s1.value(), u10_10s2.value());
}

TEST(Integer, MoveAssignment)
{
    integer<false, 10> u10_10s1{ 10 };
    integer<false, 10> u10_10s2;
    u10_10s2 = std::move(u10_10s1);
    //ASSERT_EQ(u10_10s1.value(), 0); // testing the implementation of move-assignment based on the fact we're using swap, but we want efficient implementations!
    ASSERT_EQ(u10_10s2.value(), 10);
}

TEST(Integer, ConvertingAssignment)
{
    integer<false, 10> u10_10s1{ 10 };

    integer<true, 10> s10_10s1;
    s10_10s1 = +u10_10s1;
    ASSERT_EQ(u10_10s1.value(), u10_10s1.value());

    integer<true, 11> s11_10s1;
    s11_10s1 = u10_10s1;
    ASSERT_EQ(u10_10s1.value(), s11_10s1.value());
}

TEST(Integer, Literals)
{
    FAIL();
}

TEST(Integer, Unary)
{
    integer<false, 10> u10_10s1{ 10 };
    integer<false, 20> u20_10s1 = +u10_10s1;
    integer<true, 10> s10_m10s1{ -10 };
    integer<true, 20> s20_m10s1 = -s10_m10s1;

    integer<true, 10> s10_10s1 = +u10_10s1;
    u20_10s1 = u10_10s1;
}

TEST(Integer, AutoAssignment)
{
    FAIL();
}

TEST(Integer, Comparison)
{
    FAIL();
}

TEST(Integer, Addition)
{
    FAIL();
}

TEST(Integer, Subtraction)
{
    FAIL();
}

TEST(Integer, Multiplication)
{
    FAIL();
}

TEST(Integer, Division)
{
    FAIL();
}
