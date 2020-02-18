
#include <type_traits>
#include <cmath>
#include <limits>
#include <iostream>

#include <pan/bases/dual_math.hpp>
#include <pan/forward_diff/forward_diff.hpp>

auto func_diff(float x) 
{
    return [](float x) { 
		return sin(pan::bases::dual<float>{x, 1}).dx.value(); 
	};
}

template<typename T>
T next_value(T x, T h) {
	auto next = x + h;
	if (next == x) {
		return std::nextafter(x, std::numeric_limits<T>::max());
	}
	return next;
}

template<typename T, typename RT>
auto asymmetric_diff_right(RT (*f)(T), T h) {
    return [=](T x) {
        auto next = next_value(x, h);
        return (RT)((f(next) - f(x))/(next - x)); 
	};
}

template<typename T, typename RT>
auto asymmetric_diff_left(RT (*f)(T), T h) {
    return [=](T x) {
        auto next = next_value(x, h);
        auto prev = x - (next - x);
        return (f(x) - f(prev))/(x - prev);
	};
}

template<typename T, typename RT>
auto symmetric_diff(RT (*f)(T), T h) {
	return [f, h](T x) { 
		auto next = next_value(x, h);
		auto prev = x - (next - x);
		return (RT)((f(next)-f(prev))/(next-prev));
	};
}

template<typename T, typename RT>
auto asymmetric_diff_right_autoh(RT (*f)(T)) {
    using std::sqrt;
    auto h = sqrt(std::numeric_limits<T>::epsilon());
    return asymmetric_diff_right(f, h);
}

template<typename T, typename RT>
auto asymmetric_diff_left_autoh(RT (*f)(T)) {
    using std::sqrt;
    auto h = sqrt(std::numeric_limits<T>::epsilon());
    return asymmetric_diff_left(f, h);
}

template<typename T, typename RT>
auto symmetric_diff_autoh(RT (*f)(T)) {
    using std::sqrt;
    auto h = sqrt(std::numeric_limits<T>::epsilon());
    return symmetric_diff(f, h);
}

float f(float x) {
	return sinf(x);
}

int main() {
	auto numerical_l = asymmetric_diff_left_autoh(f);
	auto numerical_r = asymmetric_diff_right_autoh(f);
	auto numerical_c = symmetric_diff_autoh(f);
	std::cout << "AutoH\t"
	          << abs(numerical_l(1.0f) - cosf(1.0f)) << '\t'
			  << abs(numerical_r(1.0f) - cosf(1.0f)) << '\t'
	          << abs(numerical_c(1.0f) - cosf(1.0f)) << std::endl;
	float h = 1.0f;
	while (1.0f + h != 1.0f) {
		auto numerical_l = asymmetric_diff_left(f, h);
		auto numerical_r = asymmetric_diff_right(f, h);
		auto numerical_c = symmetric_diff(f, h);
		std::cout << h << '\t'
				<< abs(numerical_l(1.0f) - cosf(1.0f)) << '\t'
				<< abs(numerical_r(1.0f) - cosf(1.0f)) << '\t'
				<< abs(numerical_c(1.0f) - cosf(1.0f)) << std::endl;
		h /= 2.0f;
	}
}
