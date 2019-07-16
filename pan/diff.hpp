#pragma once

#include "expr.hpp"
#include <type_traits>

namespace pan::diff {
	template<int N, typename T> struct diff {
	};

	template<int N, typename T> using diff_t = typename diff<N, T>::type;

	template<int N, int M> struct diff<N, std::integral_constant<int, M>> {
		using type = std::integral_constant<int, 0>;
	};

	template<int N, int M> struct diff<N, expr::var<M>> {
		using type = std::integral_constant<int, N == M>;
	};

	template<int N, typename L, typename R> struct diff<N, expr::sumOp<L, R>> {
		using type = expr::sumOp<diff_t<N, L>, diff_t<N, R>>;
	};

	template<int N, typename L, typename R> struct diff<N, expr::subOp<L, R>> {
		using type = expr::subOp<diff_t<N, L>, diff_t<N, R>>;
	};

	template<int N, typename L, typename R> struct diff<N, expr::mulOp<L, R>> {
		using type = expr::sumOp<expr::mulOp<L, diff_t<N, R>>, expr::mulOp<diff_t<N, L>, R>>;
	};

	template<int N, typename L, typename R> struct diff<N, expr::divOp<L, R>> {
		//using type = expr::divOp<expr::subOp<expr::mulOp<diff_t<N, L>, R>, expr::mulOp<L, diff_t<N, R>>>, expr::mulOp<R, R>>;
		using type = expr::subOp<expr::divOp<diff_t<N, L>, R>, expr::divOp<expr::mulOp<L, diff_t<N, R>>, expr::mulOp<R, R>>>;
	};
}
