#pragma once

#include "expr.hpp"
#include <type_traits>

namespace pan::expr
{
	template<typename T, typename Cond = void> struct opt {};

	template<typename T> using opt_t = typename opt<T>::type;

	/* var */

	template<int N> struct opt<var<N>>
	{
		using type = var<N>;
	};

	/* int_const */

	template<typename T, T N> struct opt<std::integral_constant<T, N>>
	{
		using type = std::integral_constant<T, N>;
	};

	/* SumOp */

	template<typename L, typename R> struct opt<sumOp<L, R>, std::enable_if_t<!is_integral_constant<L>::value && !is_integral_constant<R>::value>>
	{
		using type = sumOp<opt_t<L>, opt_t<R>>;
	};

	template<typename T, int N> struct opt<sumOp<std::integral_constant<int, N>, T>, std::enable_if_t<!is_integral_constant<T>::valu&& N != 0>>
	{
		using type = sumOp<std::integral_constant<int, N>, opt_t<T>>;
	};

	template<typename T> struct opt<sumOp<std::integral_constant<int, 0>, T>, std::enable_if_t<!is_integral_constant<T>::value>>
	{
		using type = opt_t<T>;
	};

	template<typename T, int N> struct opt<sumOp<T, std::integral_constant<int, N>>, std::enable_if_t<!is_integral_constant<T>::value&& N != 0>>
	{
		using type = sumOp<opt_t<T>, std::integral_constant<int, N>>;
	};

	template<typename T> struct opt<sumOp<T, std::integral_constant<int, 0>>, std::enable_if_t<!is_integral_constant<T>::value>>
	{
		using type = opt_t<T>;
	};

	template<int N, int M> struct opt<sumOp<std::integral_constant<int, N>, std::integral_constant<int, M>>>
	{
		using type = std::integral_constant<int, N + M>;
	};

	/* SubOp */

	template<typename L, typename R> struct opt<subOp<L, R>, std::enable_if_t<!is_integral_constant<L>::value && !is_integral_constant<R>::value>>
	{
		using type = subOp<opt_t<L>, opt_t<R>>;
	};

	template<typename T, int N> struct opt<subOp<std::integral_constant<int, N>, T>, std::enable_if_t<!is_integral_constant<T>::value>>
	{
		using type = subOp<std::integral_constant<int, N>, opt_t<T>>;
	};

	template<typename T, int N> struct opt<subOp<T, std::integral_constant<int, N>>, std::enable_if_t<!is_integral_constant<T>::value&& N != 0>>
	{
		using type = subOp<opt_t<T>, std::integral_constant<int, N>>;
	};

	template<typename T> struct opt<subOp<T, std::integral_constant<int, 0>>, std::enable_if_t<!is_integral_constant<T>::value>>
	{
		using type = opt_t<T>;
	};

	template<int N, int M> struct opt<subOp<std::integral_constant<int, N>, std::integral_constant<int, M>>>
	{
		using type = std::integral_constant<int, N - M>;
	};

	/* MulOp */

	template<typename L, typename R> struct opt<mulOp<L, R>, std::enable_if_t<!is_integral_constant<L>::value && !is_integral_constant<R>::value>>
	{
		using type = mulOp<opt_t<L>, opt_t<R>>;
	};

	template<typename T, int N> struct opt<mulOp<std::integral_constant<int, N>, T>, std::enable_if_t<!is_integral_constant<T>::value&& N != 1 && N != 0>>
	{
		using type = mulOp<std::integral_constant<int, N>, opt_t<T>>;
	};

	template<typename T> struct opt<mulOp<std::integral_constant<int, 1>, T>, std::enable_if_t<!is_integral_constant<T>::value>>
	{
		using type = opt_t<T>;
	};

	template<typename T> struct opt<mulOp<std::integral_constant<int, 0>, T>, std::enable_if_t<!is_integral_constant<T>::value>>
	{
		using type = std::integral_constant<int, 0>;
	};

	template<typename T, int N> struct opt<mulOp<T, std::integral_constant<int, N>>, std::enable_if_t<!is_integral_constant<T>::value&& N != 1 && N != 0>>
	{
		using type = mulOp<opt_t<T>, std::integral_constant<int, N>>;
	};

	template<typename T> struct opt<mulOp<T, std::integral_constant<int, 1>>, std::enable_if_t<!is_integral_constant<T>::value>>
	{
		using type = opt_t<T>;
	};

	template<typename T> struct opt<mulOp<T, std::integral_constant<int, 0>>, std::enable_if_t<!is_integral_constant<T>::value>>
	{
		using type = std::integral_constant<int, 0>;
	};

	template<int N, int M> struct opt<mulOp<std::integral_constant<int, N>, std::integral_constant<int, M>>>
	{
		using type = std::integral_constant<int, N* M>;
	};

	/* DivOp */

	template<typename L, typename R> struct opt<divOp<L, R>, std::enable_if_t<!is_integral_constant<L>::value && !is_integral_constant<R>::value>>
	{
		using type = divOp<opt_t<L>, opt_t<R>>;
	};

	template<typename T, int N> struct opt<divOp<std::integral_constant<int, N>, T>, std::enable_if_t<!is_integral_constant<T>::value&& N != 0>>
	{
		using type = divOp<std::integral_constant<int, N>, opt_t<T>>;
	};

	template<typename T> struct opt<divOp<std::integral_constant<int, 0>, T>>
	{
		using type = std::integral_constant<int, 0>;
	};

	template<typename T, int N> struct opt<divOp<T, std::integral_constant<int, N>>, std::enable_if_t<!is_integral_constant<T>::value&& N != 1>>
	{
		using type = divOp<opt_t<T>, std::integral_constant<int, N>>;
	};

	template<typename T> struct opt<divOp<T, std::integral_constant<int, 1>>, std::enable_if_t<!is_integral_constant<T>::value>>
	{
		using type = opt_t<T>;
	};

	template<int N, int M> struct opt<divOp<std::integral_constant<int, N>, std::integral_constant<int, M>>, std::enable_if_t<M != 1>>
	{
		using type = divOp<std::integral_constant<int, N>, std::integral_constant<int, M>>;
	};

	template<int N> struct opt<divOp<std::integral_constant<int, N>, std::integral_constant<int, 1>>, std::enable_if_t<N != 0>>
	{
		using type = std::integral_constant<int, N>;
	};

	/* Recursive Optimization */

	template<typename T, typename Cond = void> struct recursive_opt
	{
		using type = T;
	};

	template<typename T> struct recursive_opt<T, std::enable_if_t<!std::is_same_v<T, opt_t<T>>>> : recursive_opt<opt_t<T>>
	{
	};
	
	template<typename T> using recursive_opt_t = typename recursive_opt<T>::type;
}
