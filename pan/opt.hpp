#pragma once

#include "expr.hpp"
#include <type_traits>

namespace pan::opt {
	template<typename T, typename COND = void> struct opt {
		//using type = T;
	};

	template<typename T> using opt_t = typename opt<T>::type;

	/* var */

	template<int N> struct opt<expr::var<N>> {
		using type = expr::var<N>;
	};

	/* int_const */

	template<typename T, T N> struct opt<std::integral_constant<T, N>> {
		using type = std::integral_constant<T, N>;
	};

	/* SumOp */

	template<typename L, typename R> struct opt<expr::sumOp<L, R>, std::enable_if_t<!expr::is_integral_constant<L>::value && !expr::is_integral_constant<R>::value>> {
		using type = expr::sumOp<opt_t<L>, opt_t<R>>;
	};

	template<typename T, int N> struct opt<expr::sumOp<std::integral_constant<int, N>, T>, std::enable_if_t<!expr::is_integral_constant<T>::valu&& N != 0>> {
		using type = expr::sumOp<std::integral_constant<int, N>, opt_t<T>>;
	};

	template<typename T> struct opt<expr::sumOp<std::integral_constant<int, 0>, T>, std::enable_if_t<!expr::is_integral_constant<T>::value>> {
		using type = opt_t<T>;
	};

	template<typename T, int N> struct opt<expr::sumOp<T, std::integral_constant<int, N>>, std::enable_if_t<!expr::is_integral_constant<T>::value&& N != 0>> {
		using type = expr::sumOp<opt_t<T>, std::integral_constant<int, N>>;
	};

	template<typename T> struct opt<expr::sumOp<T, std::integral_constant<int, 0>>, std::enable_if_t<!expr::is_integral_constant<T>::value>> {
		using type = opt_t<T>;
	};

	template<int N, int M> struct opt<expr::sumOp<std::integral_constant<int, N>, std::integral_constant<int, M>>> {
		using type = std::integral_constant<int, N + M>;
	};

	/* SubOp */

	template<typename L, typename R> struct opt<expr::subOp<L, R>, std::enable_if_t<!expr::is_integral_constant<L>::value && !expr::is_integral_constant<R>::value>> {
		using type = expr::subOp<opt_t<L>, opt_t<R>>;
	};

	template<typename T, int N> struct opt<expr::subOp<std::integral_constant<int, N>, T>, std::enable_if_t<!expr::is_integral_constant<T>::value>> {
		using type = expr::subOp<std::integral_constant<int, N>, opt_t<T>>;
	};

	template<typename T, int N> struct opt<expr::subOp<T, std::integral_constant<int, N>>, std::enable_if_t<!expr::is_integral_constant<T>::value&& N != 0>> {
		using type = expr::subOp<opt_t<T>, std::integral_constant<int, N>>;
	};

	template<typename T> struct opt<expr::subOp<T, std::integral_constant<int, 0>>, std::enable_if_t<!expr::is_integral_constant<T>::value>> {
		using type = opt_t<T>;
	};

	template<int N, int M> struct opt<expr::subOp<std::integral_constant<int, N>, std::integral_constant<int, M>>> {
		using type = std::integral_constant<int, N - M>;
	};

	/* MulOp */

	template<typename L, typename R> struct opt<expr::mulOp<L, R>, std::enable_if_t<!expr::is_integral_constant<L>::value && !expr::is_integral_constant<R>::value>> {
		using type = expr::mulOp<opt_t<L>, opt_t<R>>;
	};

	template<typename T, int N> struct opt<expr::mulOp<std::integral_constant<int, N>, T>, std::enable_if_t<!expr::is_integral_constant<T>::value&& N != 1 && N != 0>> {
		using type = expr::mulOp<std::integral_constant<int, N>, opt_t<T>>;
	};

	template<typename T> struct opt<expr::mulOp<std::integral_constant<int, 1>, T>, std::enable_if_t<!expr::is_integral_constant<T>::value>> {
		using type = opt_t<T>;
	};

	template<typename T> struct opt<expr::mulOp<std::integral_constant<int, 0>, T>, std::enable_if_t<!expr::is_integral_constant<T>::value>> {
		using type = std::integral_constant<int, 0>;
	};

	template<typename T, int N> struct opt<expr::mulOp<T, std::integral_constant<int, N>>, std::enable_if_t<!expr::is_integral_constant<T>::value&& N != 1 && N != 0>> {
		using type = expr::mulOp<opt_t<T>, std::integral_constant<int, N>>;
	};

	template<typename T> struct opt<expr::mulOp<T, std::integral_constant<int, 1>>, std::enable_if_t<!expr::is_integral_constant<T>::value>> {
		using type = opt_t<T>;
	};

	template<typename T> struct opt<expr::mulOp<T, std::integral_constant<int, 0>>, std::enable_if_t<!expr::is_integral_constant<T>::value>> {
		using type = std::integral_constant<int, 0>;
	};

	template<int N, int M> struct opt<expr::mulOp<std::integral_constant<int, N>, std::integral_constant<int, M>>> {
		using type = std::integral_constant<int, N* M>;
	};

	/* DivOp */

	template<typename L, typename R> struct opt<expr::divOp<L, R>, std::enable_if_t<!expr::is_integral_constant<L>::value && !expr::is_integral_constant<R>::value>> {
		using type = expr::divOp<opt_t<L>, opt_t<R>>;
	};

	template<typename T, int N> struct opt<expr::divOp<std::integral_constant<int, N>, T>, std::enable_if_t<!expr::is_integral_constant<T>::value&& N != 0>> {
		using type = expr::divOp<std::integral_constant<int, N>, opt_t<T>>;
	};

	template<typename T> struct opt<expr::divOp<std::integral_constant<int, 0>, T>> {
		using type = std::integral_constant<int, 0>;
	};

	template<typename T, int N> struct opt<expr::divOp<T, std::integral_constant<int, N>>, std::enable_if_t<!expr::is_integral_constant<T>::value&& N != 1>> {
		using type = expr::divOp<opt_t<T>, std::integral_constant<int, N>>;
	};

	template<typename T> struct opt<expr::divOp<T, std::integral_constant<int, 1>>, std::enable_if_t<!expr::is_integral_constant<T>::value>> {
		using type = opt_t<T>;
	};

	template<int N, int M> struct opt<expr::divOp<std::integral_constant<int, N>, std::integral_constant<int, M>>, std::enable_if_t<M != 1>> {
		using type = expr::divOp<std::integral_constant<int, N>, std::integral_constant<int, M>>;
	};

	template<int N> struct opt<expr::divOp<std::integral_constant<int, N>, std::integral_constant<int, 1>>, std::enable_if_t<N != 0>> {
		using type = std::integral_constant<int, N>;
	};

}
