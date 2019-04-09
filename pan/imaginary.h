
#ifndef _IMAGINARY_H_
#define _IMAGINARY_H_

#include "base.h"

namespace pan
{
    template <int T> struct Imaginary {};
    template <typename T, int N> using imaginary_base = base<T, Imaginary<N>>;
    template <typename T> using imaginary = imaginary_base<T, 0>;
    template <typename T> using jmaginary = imaginary_base<T, 1>;
    template <typename T> using kmaginary = imaginary_base<T, 2>;

    template<typename T, int N> struct prod_tag<imaginary_base<T, N>, imaginary_base<T, N>> { using ReturnType = T; constexpr static int S = -1; };
    template<typename T, int N> struct prod_tag<imaginary_base<T, N>, T> { using ReturnType = imaginary_base<T, N>; constexpr static int S = 1; };
    template<typename T, int N> struct prod_tag<T, imaginary_base<T, N>> { using ReturnType = imaginary_base<T, N>; constexpr static int S = 1; };

    template<typename T, int N, int M> struct prod_tag<imaginary_base<T, N>, imaginary_base<T, M>, typename std::enable_if_t<(N > M)>> { using ReturnType = typename prod_tag<imaginary_base<T, M>, imaginary_base<T, N>>::ReturnType; constexpr static int S = -prod_tag<imaginary_base<T, M>, imaginary_base<T, N>>::S; };

    template<typename T> struct prod_tag<imaginary_base<T, 0>, imaginary_base<T, 1>> { using ReturnType = imaginary_base<T, 2>; constexpr static int S = +1; };
    template<typename T> struct prod_tag<imaginary_base<T, 0>, imaginary_base<T, 2>> { using ReturnType = imaginary_base<T, 1>; constexpr static int S = -1; };
    template<typename T> struct prod_tag<imaginary_base<T, 0>, imaginary_base<T, 3>> { using ReturnType = imaginary_base<T, 4>; constexpr static int S = +1; };
    template<typename T> struct prod_tag<imaginary_base<T, 0>, imaginary_base<T, 4>> { using ReturnType = imaginary_base<T, 3>; constexpr static int S = -1; };
    template<typename T> struct prod_tag<imaginary_base<T, 0>, imaginary_base<T, 5>> { using ReturnType = imaginary_base<T, 6>; constexpr static int S = -1; };
    template<typename T> struct prod_tag<imaginary_base<T, 0>, imaginary_base<T, 6>> { using ReturnType = imaginary_base<T, 5>; constexpr static int S = +1; };

    template<typename T> struct prod_tag<imaginary_base<T, 1>, imaginary_base<T, 2>> { using ReturnType = imaginary_base<T, 0>; constexpr static int S = +1; };
    template<typename T> struct prod_tag<imaginary_base<T, 1>, imaginary_base<T, 3>> { using ReturnType = imaginary_base<T, 5>; constexpr static int S = +1; };
    template<typename T> struct prod_tag<imaginary_base<T, 1>, imaginary_base<T, 4>> { using ReturnType = imaginary_base<T, 6>; constexpr static int S = +1; };
    template<typename T> struct prod_tag<imaginary_base<T, 1>, imaginary_base<T, 5>> { using ReturnType = imaginary_base<T, 3>; constexpr static int S = -1; };
    template<typename T> struct prod_tag<imaginary_base<T, 1>, imaginary_base<T, 6>> { using ReturnType = imaginary_base<T, 4>; constexpr static int S = -1; };

    template<typename T> struct prod_tag<imaginary_base<T, 2>, imaginary_base<T, 3>> { using ReturnType = imaginary_base<T, 6>; constexpr static int S = +1; };
    template<typename T> struct prod_tag<imaginary_base<T, 2>, imaginary_base<T, 4>> { using ReturnType = imaginary_base<T, 5>; constexpr static int S = -1; };
    template<typename T> struct prod_tag<imaginary_base<T, 2>, imaginary_base<T, 5>> { using ReturnType = imaginary_base<T, 4>; constexpr static int S = +1; };
    template<typename T> struct prod_tag<imaginary_base<T, 2>, imaginary_base<T, 6>> { using ReturnType = imaginary_base<T, 3>; constexpr static int S = -1; };

    template<typename T> struct prod_tag<imaginary_base<T, 3>, imaginary_base<T, 4>> { using ReturnType = imaginary_base<T, 0>; constexpr static int S = +1; };
    template<typename T> struct prod_tag<imaginary_base<T, 3>, imaginary_base<T, 5>> { using ReturnType = imaginary_base<T, 1>; constexpr static int S = +1; };
    template<typename T> struct prod_tag<imaginary_base<T, 3>, imaginary_base<T, 6>> { using ReturnType = imaginary_base<T, 2>; constexpr static int S = +1; };

    template<typename T> struct prod_tag<imaginary_base<T, 4>, imaginary_base<T, 5>> { using ReturnType = imaginary_base<T, 2>; constexpr static int S = -1; };
    template<typename T> struct prod_tag<imaginary_base<T, 4>, imaginary_base<T, 6>> { using ReturnType = imaginary_base<T, 1>; constexpr static int S = +1; };

    template<typename T> struct prod_tag<imaginary_base<T, 5>, imaginary_base<T, 6>> { using ReturnType = imaginary_base<T, 0>; constexpr static int S = -1; };

    inline constexpr imaginary<float> operator ""_fi(long double f)
    {
        return imaginary<float>(static_cast<float>(f));
    }

    inline constexpr imaginary<double> operator ""_i(long double f)
    {
        return imaginary<double>(static_cast<double>(f));
    }

    inline constexpr imaginary<long double> operator ""_li(long double f)
    {
        return imaginary<long double>(f);
    }

    template <typename T, typename U> constexpr std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, bool> operator == (const std::complex<T>& a, const imaginary<U>& b)
    {
        return (a.real() == T{}) && (a.imag() == b.value());
    }

    template <typename T, typename U> constexpr std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, bool> operator == (const imaginary<T> & a, const std::complex<U> & b)
    {
        return (b.real() == T{}) && (a.value() == b.imag());
    }

    template <typename T, typename U> constexpr std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, bool> operator != (const std::complex<T> & a, const imaginary<U> & b)
    {
        return (a.real() != T{}) || (a.imag() != b.value());
    }

    template <typename T, typename U> constexpr std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, bool> operator != (const imaginary<T> & a, const std::complex<U> & b)
    {
        return (b.real() != T{}) || (a.value() != b.imag());
    }

    template <typename T, typename U> constexpr auto operator + (const T & a, const imaginary<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<sum_result_t<T, U>>> {
        return std::complex<sum_result_t<T, U>>(a, b.value());
    }

    template <typename T, typename U> constexpr auto operator + (const imaginary<T> & a, const U & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<sum_result_t<T, U>>> {
        return std::complex<sum_result_t<T, U>>(b, a.value());
    }

    template <typename T, typename U> constexpr auto operator + (const std::complex<T> & a, const imaginary<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<sum_result_t<T, U>>> {
        return std::complex<sum_result_t<T, U>>(a.real(), a.imag() + b.value());
    }

    template <typename T, typename U> constexpr auto operator + (const imaginary<T> & a, const std::complex<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<sum_result_t<T, U>>> {
        return std::complex<sum_result_t<T, U>>(b.real(), a.value() + b.imag());
    }

    template <typename T, typename U> constexpr auto operator - (const T & a, const imaginary<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<sub_result_t<T, U>>> {
        return std::complex<sub_result_t<T, U>>(a, -b.value());
    }

    template <typename T, typename U> constexpr auto operator - (const imaginary<T> & a, const U & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<sub_result_t<T, U>>> {
        return std::complex<sub_result_t<T, U>>(-b, a.value());
    }

    template <typename T, typename U> constexpr auto operator - (const std::complex<T> & a, const imaginary<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<sub_result_t<T, U>>> {
        return std::complex<sub_result_t<T, U>>(a.real(), a.imag() - b.value());
    }

    template <typename T, typename U> constexpr auto operator - (const imaginary<T> & a, const std::complex<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<sub_result_t<T, U>>> {
        return std::complex<sub_result_t<T, U>>(-b.real(), a.value() - b.imag());
    }

    template <typename T, typename U> constexpr auto operator * (const std::complex<T> & a, const imaginary<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<mul_result_t<T, U>>> {
        return { -a.imag() * b.value(), a.real() * b.value() };
    }

    template <typename T, typename U> constexpr auto operator * (const imaginary<T> & a, const std::complex<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<mul_result_t<T, U>>> {
        return { -a.value() * b.imag(), a.value() * b.real() };
    }

    template <typename T, typename U> constexpr auto operator / (const std::complex<T> & a, const imaginary<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<div_result_t<T, U>>> {
        return { a.imag() / b.value(), -a.real() / b.value() };
    }

    template <typename T, typename U> constexpr auto operator / (const imaginary<T> & a, const std::complex<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<div_result_t<T, U>>> {
        return { a.value() * b.imag() / (b.real() * b.real() + b.imag() * b.imag()), a.value() * b.real() / (b.real() * b.real() + b.imag() * b.imag()) };
    }
}

#endif
