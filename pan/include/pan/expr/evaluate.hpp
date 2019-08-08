
#pragma once

#include "expr.hpp"

#include <type_traits>

namespace pan::expr {
	//template<typename T, typename V> constexpr auto evaluate(T &&expr, V && variables);

	template<typename V, int N> constexpr auto evaluate(const var<N> &expr, V && variables)
	{
		return variables[N];
	}
	
	template<typename V, typename T, int N> constexpr auto evaluate(const std::integral_constant<T, N> &expr, V && variables)
	{
		return expr();
	}
	
	template<typename V, typename L, typename R> constexpr auto evaluate(const sumOp<R, L> &expr, V && variables)
	{
		return evaluate(expr.l, variables) + evaluate(expr.r, variables);
	}

	template<typename V, typename L, typename R> constexpr auto evaluate(const subOp<R, L> &expr, V && variables)
	{
		return evaluate(expr.l, variables) - evaluate(expr.r, variables);
	}

	template<typename V, typename L, typename R> constexpr auto evaluate(const mulOp<R, L> &expr, V && variables)
	{
		return evaluate(expr.l, variables) * evaluate(expr.r, variables);
	}

	template<typename V, typename L, typename R> constexpr auto evaluate(const divOp<R, L> &expr, V && variables)
	{
		return evaluate(expr.l, variables) / evaluate(expr.r, variables);
	}
}