
#include <catch2/catch.hpp>

#include <pan/util/tuple_view.hpp>

TEST_CASE("TupleView") 
{
	SECTION("Basic")
	{
		std::tuple<int, std::string, std::vector<double>, double> t{
			'1',
			"data",
		    {1.0, 2.0, 3.0},
			5.0
		};
		auto v = pan::util::make_tuple_view<1, 3>(t);

		using std::get;
		REQUIRE(get<0>(v) == "data");
	}
}
