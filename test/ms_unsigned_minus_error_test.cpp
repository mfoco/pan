
#include <type_traits>
#include <iostream>

template<bool B> using type_selector = std::conditional_t<B, int, unsigned int>;

template<bool B> constexpr auto min_value(type_selector<B> value)
{
	return B ? -(type_selector<B>(1) << 31) : 0;
}

int main()
{
	auto x = min_value<true>(10);
	auto y = min_value<false>(10u);
	std::cout << x << " " << y << std::endl;
}