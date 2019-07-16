#pragma once

#include <string>
#include <type_traits>

namespace pan::expr {
	template<int N> struct var {};

	template<typename T> struct is_integral_constant : std::false_type {};
	template<typename T, T N> struct is_integral_constant<std::integral_constant<T, N>> : std::true_type {};

	template<typename L, typename R> struct sumOp {
		L l;
		R r;

		constexpr double operator()() const {
			return l() + r();
		}
	};

	template<typename L, typename R> struct subOp {
		L l;
		R r;

		constexpr double operator()() const {
			return l() - r();
		}
	};

	template<typename L, typename R> struct mulOp {
		L l;
		R r;

		constexpr double operator()() const {
			return l() * r();
		}
	};

	template<typename L, typename R> struct divOp {
		L l;
		R r;

		constexpr double operator()() const {
			return l() / r();
		}
	};
}
