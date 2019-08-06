#pragma once

#include <string>
#include <type_traits>

namespace pan::expr {
	template<int N> struct var {
		//constexpr int n = N;
	};

	template<typename T> struct is_integral_constant : std::false_type {};
	template<typename T, T N> struct is_integral_constant<std::integral_constant<T, N>> : std::true_type {};

	template<typename L, typename R> struct sumOp {
		L l;
		R r;
	};

	template<typename L, typename R> struct subOp {
		L l;
		R r;
	};

	template<typename L, typename R> struct mulOp {
		L l;
		R r;
	};

	template<typename L, typename R> struct divOp {
		L l;
		R r;
	};

	//template<typename T, typename V> constexpr double evaluate(T &&expr, V && variables);

	template<typename V, int N> constexpr double evaluate(const var<N> &expr, V && variables) {
		return variables[N];
	}
	
	template<typename V, typename T, int N> constexpr double evaluate(const std::integral_constant<T, N> &expr, V && variables) {
		return expr();
	}
	
	template<typename V, typename L, typename R> constexpr double evaluate(const sumOp<R, L> &expr, V && variables) {
		return evaluate(expr.l, variables) + evaluate(expr.r, variables);
	}

	template<typename V, typename L, typename R> constexpr double evaluate(const subOp<R, L> &expr, V && variables) {
		return evaluate(expr.l, variables) - evaluate(expr.r, variables);
	}

	template<typename V, typename L, typename R> constexpr double evaluate(const mulOp<R, L> &expr, V && variables) {
		return evaluate(expr.l, variables) * evaluate(expr.r, variables);
	}

	template<typename V, typename L, typename R> constexpr double evaluate(const divOp<R, L> &expr, V && variables) {
		return evaluate(expr.l, variables) / evaluate(expr.r, variables);
	}
}
