
#include <catch2/catch.hpp>

#include <pan/bases/arithmetic_tuple.hpp>
#include <pan/bases/base.hpp>
#include <pan/bases/imaginary.hpp>

using namespace pan::bases;

TEST_CASE("ArithmeticTuple")
{
	SECTION("Construction")
	{
		arithmetic_tuple<float, imaginary<float>> at0;
		arithmetic_tuple<float> at_real{1.0f};
		imaginary<float> im_imaginary{1.0f};
		arithmetic_tuple<imaginary<float>> at_imaginary{1.0f};
		auto check1 = at_real + im_imaginary;
		//auto check2 = at_real + at_imaginary;

		using CheckType1 = std::decay_t<decltype(check1)::tuple>;
		//using CheckType2 = std::decay_t<decltype(check2)::tuple>;

		static_assert(pan::tuple::has_type_v<float, CheckType1>);
		static_assert(!pan::tuple::has_type_v<int, CheckType1>);
		static_assert(pan::tuple::has_type_v<imaginary<float>, CheckType1>);
		//static_assert(pan::tuple::has_type_v<float, CheckType2>);
		//static_assert(!pan::tuple::has_type_v<int, CheckType2>);
		//static_assert(pan::tuple::has_type_v<imaginary<float>, CheckType2>);
	}
}
