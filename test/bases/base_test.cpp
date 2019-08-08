
#include <catch2/catch.hpp>

#include <pan/bases/base.hpp>
#include <pan/bases/imaginary.hpp>
#include <pan/bases/dual.hpp>

using namespace pan::bases;

TEMPLATE_TEST_CASE("Base", "[template]", int, float, double)
{
    SECTION("Construction")
    {
        constexpr TestType r0{0};
        constexpr TestType r1{1};
        constexpr imaginary<TestType> i0{0};
        constexpr imaginary<TestType> i1{1};
        constexpr epsilon<TestType> e0{0};
        constexpr epsilon<TestType> e1{1};

        REQUIRE(r0 == 0);
        REQUIRE(r1 == 1);
        REQUIRE(i0.value() == 0);
        REQUIRE(i1.value() == 1);
        REQUIRE(e0.value() == 0);
        REQUIRE(e1.value() == 1);
    }

    SECTION("Multiplication")
    {
        constexpr TestType r0{0};
        constexpr TestType r1{1};
        constexpr TestType rm1{-1};
        constexpr imaginary<TestType> i0{0};
        constexpr imaginary<TestType> i1{1};
        constexpr epsilon<TestType> e0{0};
        constexpr epsilon<TestType> e1{1};

        REQUIRE(r0 * r0 == r0);
        REQUIRE(r1 * r0 == r0);
        REQUIRE(r0 * r1 == r0);
        REQUIRE(r1 * r1 == r1);

        REQUIRE(i0 * i0 == r0);
        REQUIRE(i0 * i1 == r0);
        REQUIRE(i1 * i0 == r0);
        REQUIRE(i1 * i1 == rm1);

        REQUIRE(e0 * e0 == r0);
        REQUIRE(e0 * e1 == r0);
        REQUIRE(e1 * e0 == r0);
        REQUIRE(e1 * e1 == r0);

        REQUIRE(r0 * i0 == i0);
        REQUIRE(r1 * i0 == i0);
        REQUIRE(r0 * i1 == i0);
        REQUIRE(r1 * i1 == i1);

        REQUIRE(i0 * r0 == i0);
        REQUIRE(i1 * r0 == i0);
        REQUIRE(i0 * r1 == i0);
        REQUIRE(i1 * r1 == i1);

        REQUIRE(r0 * e0 == e0);
        REQUIRE(r0 * e1 == e0);
        REQUIRE(r1 * e0 == e0);
        REQUIRE(r1 * e1 == e1);

        REQUIRE(e0 * r0 == e0);
        REQUIRE(e0 * r1 == e0);
        REQUIRE(e1 * r0 == e0);
        REQUIRE(e1 * r1 == e1);
    }
}
