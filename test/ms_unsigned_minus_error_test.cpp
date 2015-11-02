
#include <type_traits>
#include <iostream>

template<bool B> struct type_selector { typedef typename std::conditional<B, int, unsigned int>::type type; };

template<bool B> typename type_selector<B>::type min_value(typename type_selector<B>::type value)
{
	return B ? -(typename type_selector<B>::type(1) << 31) : 0;
}

int main()
{
	auto x = min_value<true>(10);
	auto y = min_value<false>(10u);
	std::cout << x << " " << y << std::endl;
}