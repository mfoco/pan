#pragma once

#include "expr.hpp"
#include <type_traits>

namespace pan::expr
{
	template<int N, typename T> struct diff {};

	template<int N, typename T> using diff_t = typename diff<N, T>::type;

	template<int N, int M> struct diff<N, std::integral_constant<int, M>>
	{
		using type = std::integral_constant<int, 0>;
	};

	template<int N, int M> struct diff<N, var<M>>
	{
		using type = std::integral_constant<int, N == M>;
	};

	template<int N, typename L, typename R> struct diff<N, sumOp<L, R>>
	{
		using type = sumOp<diff_t<N, L>, diff_t<N, R>>;
	};

	template<int N, typename L, typename R> struct diff<N, subOp<L, R>>
	{
		using type = subOp<diff_t<N, L>, diff_t<N, R>>;
	};

	template<int N, typename L, typename R> struct diff<N, mulOp<L, R>>
	{
		using type = sumOp<mulOp<L, diff_t<N, R>>, mulOp<diff_t<N, L>, R>>;
	};

	template<int N, typename L, typename R> struct diff<N, divOp<L, R>>
	{
		//using type = divOp<subOp<mulOp<diff_t<N, L>, R>, mulOp<L, diff_t<N, R>>>, mulOp<R, R>>;
		using type = subOp<divOp<diff_t<N, L>, R>, divOp<mulOp<L, diff_t<N, R>>, mulOp<R, R>>>;
	};
}
