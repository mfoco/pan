#pragma once

#include <bit>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace pan::expr 
{
	template<int N> struct var {};

	template<typename T> struct is_integral_constant : std::false_type {};
	template<typename T, T N> struct is_integral_constant<std::integral_constant<T, N>> : std::true_type {};

	template<typename T> struct constexpr_space_for {
		using type = T;
	};
	
	template<> struct constexpr_space_for<double> {
		using type = std::uint64_t;
	};	

	template<typename T>
	struct constexpr_value_for {
		using underlying_type = constexpr_space_for<T>;
		underlying_type v;

		constexpr constexpr_value_for(T t) { 
			v = std::bit_cast<underlying_type>(t);
		}

		constexpr operator T() {
			return std::bit_set<T>(v);
		}
	};

	template<typename T, std::enable_if_t<!std::has_strong_structural_equality<T>>> struct constexpr_space_for<T> {
		using type = t;
	};	

	template<typename T, ValueType<T> V> struct constant {
		
	};

	template<typename L, typename R> struct sumOp
	{
		L l;
		R r;
	};

	template<typename L, typename R> struct subOp
	{
		L l;
		R r;
	};

	template<typename L, typename R> struct mulOp
	{
		L l;
		R r;
	};

	template<typename L, typename R> struct divOp
	{
		L l;
		R r;
	};
}
