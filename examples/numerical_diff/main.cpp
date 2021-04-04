
#include <cmath>
#include <limits>
#include <iostream>
#include <algorithm>

#include <pan/bases/dual_math.hpp>
#include <pan/forward_diff/forward_diff.hpp>

template<typename T>
constexpr T cabs(T t)
{
	return (t >= 0) ? t : -t;
}

template<typename T>
constexpr bool almost_equals(T t1, T t2)
{
	using std::numeric_limits;
	using std::max;
	auto eps = std::max(t1, t2) * numeric_limits<T>::epsilon();
	return (cabs(t1 - t2) < eps);
}

template<typename T>
constexpr auto csqrt(T value)
{
	T result{};
	T cur = 1;
	while (4 * cur * cur <= value)
	{
		cur *= 2;
	}
	while (true)
	{
		T new_result = result + cur;
		if (new_result == result) { return result; }
		if (new_result*new_result <= value)
		{
			result = new_result;
		}
		cur /= 2;
	}
}

static_assert(almost_equals(csqrt(2.0f), 1.4142135623730950488016887242097f));
static_assert(almost_equals(csqrt(0.5f), 1.0f/1.4142135623730950488016887242097f));
static_assert(almost_equals(csqrt(0.5), 1.0 / 1.4142135623730950488016887242097));
static_assert(almost_equals(csqrt(2.0), 1.4142135623730950488016887242097));
static_assert(almost_equals(csqrt(1208925819614629174706176.0), 1099511627776.0));
static_assert(almost_equals(csqrt(1208925819614629174706176.0f), 1099511627776.0f));

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
    auto h = csqrt(std::numeric_limits<T>::epsilon());
    return asymmetric_diff_right(f, h);
}

template<typename T, typename RT>
auto asymmetric_diff_left_autoh(RT (*f)(T)) {
    auto h = csqrt(std::numeric_limits<T>::epsilon());
    return asymmetric_diff_left(f, h);
}

template<typename T, typename RT>
auto symmetric_diff_autoh(RT (*f)(T)) {
    auto h = csqrt(std::numeric_limits<T>::epsilon());
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
