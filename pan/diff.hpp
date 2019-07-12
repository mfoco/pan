#pragma once

#include <string>
#include <type_traits>

namespace pan {
	namespace diff {
		template<int N> struct var {
			[[nodiscard]] std::string toString() const {
				return std::string("x") + std::to_string(N);
			}
		};

		template<int N> struct int_const {
			static constexpr int value = N;

			constexpr double operator()() const { return value;}

			[[nodiscard]] std::string toString() const {
				return std::to_string(N);
			}
		};

		template<typename T> struct is_int_const : std::false_type {};
		template<int N> struct is_int_const<int_const<N>> : std::true_type {};

		template<typename L, typename R> struct sumOp {
			L l;
			R r;

			constexpr double operator()() const { 
				return l() + r(); 
			}

			[[nodiscard]] std::string toString() const {
				return "(" + l.toString() + " + " + r.toString() + ")";
			}
		};

		template<typename L, typename R> struct subOp {
			L l;
			R r;

			constexpr double operator()() const {
				return l() - r();
			}

			[[nodiscard]] std::string toString() const {
				return "(" + l.toString() + " - " + r.toString() + ")";
			}
		};

		template<typename L, typename R> struct mulOp {
			L l;
			R r;

			constexpr double operator()() const {
				return l() * r();
			}

			[[nodiscard]] std::string toString() const {
				return "(" + l.toString() + " * " + r.toString() + ")";
			}
		};

		template<typename L, typename R> struct divOp {
			L l;
			R r;

			constexpr double operator()() const {
				return l() / r();
			}

			[[nodiscard]] std::string toString() const {
				return "(" + l.toString() + " / " + r.toString() + ")";
			}
		};

		template<int N, typename T> struct diff {
		};

		template<int N, typename T> using diff_t = typename diff<N, T>::type;

		template<int N, int M> struct diff<N, int_const<M>> {
			using type = int_const<0>;
		};

		template<int N, int M> struct diff<N, var<M>> {
			using type = int_const<N == M>;
		};

		template<int N, typename L, typename R> struct diff<N, sumOp<L, R>> {
			using type = sumOp<diff_t<N, L>, diff_t<N, R>>;
		};

		template<int N, typename L, typename R> struct diff<N, subOp<L, R>> {
			using type = subOp<diff_t<N, L>, diff_t<N, R>>;
		};

		template<int N, typename L, typename R> struct diff<N, mulOp<L, R>> {
			using type = sumOp<mulOp<L, diff_t<N, R>>, mulOp<diff_t<N, L>, R>>;
		};

		template<int N, typename L, typename R> struct diff<N, divOp<L, R>> {
			//using type = divOp<subOp<mulOp<diff_t<N, L>, R>, mulOp<L, diff_t<N, R>>>, mulOp<R, R>>;
			using type = subOp<divOp<diff_t<N, L>, R>, divOp<mulOp<L, diff_t<N, R>>, mulOp<R, R>>>;
		};

		template<typename T, typename COND=void> struct opt {
			//using type = T;
		};

		template<typename T> using opt_t = typename opt<T>::type;

		/* var */

		template<int N> struct opt<var<N>> {
			using type = var<N>;
		};

		/* int_const */

		template<int N> struct opt<int_const<N>> {
			using type = int_const<N>;
		};

		/* SumOp */

		template<typename L, typename R> struct opt<sumOp<L, R>, std::enable_if_t<!is_int_const<L>::value && !is_int_const<R>::value>> {
			using type = sumOp<opt_t<L>, opt_t<R>>;
		};

		template<typename T, int N> struct opt<sumOp<int_const<N>, T>, std::enable_if_t<!is_int_const<T>::valu && N != 0>> {
			using type = sumOp<int_const<N>, opt_t<T>>;
		};

		template<typename T> struct opt<sumOp<int_const<0>, T>, std::enable_if_t<!is_int_const<T>::value>> {
			using type = opt_t<T>;
		};

		template<typename T, int N> struct opt<sumOp<T, int_const<N>>, std::enable_if_t<!is_int_const<T>::value && N != 0>> {
			using type = sumOp<opt_t<T>, int_const<N>>;
		};

		template<typename T> struct opt<sumOp<T, int_const<0>>, std::enable_if_t<!is_int_const<T>::value>> {
			using type = opt_t<T>;
		};

		template<int N, int M> struct opt<sumOp<int_const<N>, int_const<M>>> {
			using type = int_const<N + M>;
		};

		/* SubOp */

		template<typename L, typename R> struct opt<subOp<L, R>, std::enable_if_t<!is_int_const<L>::value && !is_int_const<R>::value>> {
			using type = subOp<opt_t<L>, opt_t<R>>;
		};

		template<typename T, int N> struct opt<subOp<int_const<N>, T>, std::enable_if_t<!is_int_const<T>::value>> {
			using type = subOp<int_const<N>, opt_t<T>>;
		};

		template<typename T, int N> struct opt<subOp<T, int_const<N>>, std::enable_if_t<!is_int_const<T>::value && N != 0>> {
			using type = subOp<opt_t<T>, int_const<N>>;
		};

		template<typename T> struct opt<subOp<T, int_const<0>>, std::enable_if_t<!is_int_const<T>::value>> {
			using type = opt_t<T>;
		};

		template<int N, int M> struct opt<subOp<int_const<N>, int_const<M>>> {
			using type = int_const<N - M>;
		};

		/* MulOp */

		template<typename L, typename R> struct opt<mulOp<L, R>, std::enable_if_t<!is_int_const<L>::value && !is_int_const<R>::value>> {
			using type = mulOp<opt_t<L>, opt_t<R>>;
		};

		template<typename T, int N> struct opt<mulOp<int_const<N>, T>, std::enable_if_t<!is_int_const<T>::value && N != 1 && N != 0>> {
			using type = mulOp<int_const<N>, opt_t<T>>;
		};

		template<typename T> struct opt<mulOp<int_const<1>, T>, std::enable_if_t<!is_int_const<T>::value>> {
			using type = opt_t<T>;
		};

		template<typename T> struct opt<mulOp<int_const<0>, T>, std::enable_if_t<!is_int_const<T>::value>> {
			using type = int_const<0>;
		};

		template<typename T, int N> struct opt<mulOp<T, int_const<N>>, std::enable_if_t<!is_int_const<T>::value && N != 1 && N != 0>> {
			using type = mulOp<opt_t<T>, int_const<N>>;
		};

		template<typename T> struct opt<mulOp<T, int_const<1>>, std::enable_if_t<!is_int_const<T>::value>> {
			using type = opt_t<T>;
		};

		template<typename T> struct opt<mulOp<T, int_const<0>>, std::enable_if_t<!is_int_const<T>::value>> {
			using type = int_const<0>;
		};

		template<int N, int M> struct opt<mulOp<int_const<N>, int_const<M>>> {
			using type = int_const<N* M>;
		};

		/* DivOp */

		template<typename L, typename R> struct opt<divOp<L, R>, std::enable_if_t<!is_int_const<L>::value && !is_int_const<R>::value>> {
			using type = divOp<opt_t<L>, opt_t<R>>;
		};

		template<typename T, int N> struct opt<divOp<int_const<N>, T>, std::enable_if_t<!is_int_const<T>::value && N != 0>> {
			using type = divOp<int_const<N>, opt_t<T>>;
		};

		template<typename T> struct opt<divOp<int_const<0>, T>> {
			using type = int_const<0>;
		};

		template<typename T, int N> struct opt<divOp<T, int_const<N>>, std::enable_if_t<!is_int_const<T>::value && N != 1>> {
			using type = divOp<opt_t<T>, int_const<N>>;
		};

		template<typename T> struct opt<divOp<T, int_const<1>>, std::enable_if_t<!is_int_const<T>::value>> {
			using type = opt_t<T>;
		};

		template<int N, int M> struct opt<divOp<int_const<N>, int_const<M>>, std::enable_if_t<M != 1>> {
			using type = divOp<int_const<N>, int_const<M>>;
		};

		template<int N> struct opt<divOp<int_const<N>, int_const<1>>, std::enable_if_t<N != 0>> {
			using type = int_const<N>;
		};
	}
}