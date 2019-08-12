
#pragma once

#include "imaginary.hpp"
#include <complex>

namespace pan::bases
{
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

    template <typename T, typename U> constexpr auto operator + (const T & a, const imaginary<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<sum_result_t<T, U>>>
    {
        return std::complex<sum_result_t<T, U>>(a, b.value());
    }

    template <typename T, typename U> constexpr auto operator + (const imaginary<T> & a, const U & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<sum_result_t<T, U>>>
    {
        return std::complex<sum_result_t<T, U>>(b, a.value());
    }

    template <typename T, typename U> constexpr auto operator + (const std::complex<T> & a, const imaginary<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<sum_result_t<T, U>>>
    {
        return std::complex<sum_result_t<T, U>>(a.real(), a.imag() + b.value());
    }

    template <typename T, typename U> constexpr auto operator + (const imaginary<T> & a, const std::complex<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<sum_result_t<T, U>>>
    {
        return std::complex<sum_result_t<T, U>>(b.real(), a.value() + b.imag());
    }

    template <typename T, typename U> constexpr auto operator - (const T & a, const imaginary<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<sub_result_t<T, U>>>
    {
        return std::complex<sub_result_t<T, U>>(a, -b.value());
    }

    template <typename T, typename U> constexpr auto operator - (const imaginary<T> & a, const U & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<sub_result_t<T, U>>>
    {
        return std::complex<sub_result_t<T, U>>(-b, a.value());
    }

    template <typename T, typename U> constexpr auto operator - (const std::complex<T> & a, const imaginary<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<sub_result_t<T, U>>>
    {
        return std::complex<sub_result_t<T, U>>(a.real(), a.imag() - b.value());
    }

    template <typename T, typename U> constexpr auto operator - (const imaginary<T> & a, const std::complex<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<sub_result_t<T, U>>>
    {
        return std::complex<sub_result_t<T, U>>(-b.real(), a.value() - b.imag());
    }

    template <typename T, typename U> constexpr auto operator * (const std::complex<T> & a, const imaginary<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<mul_result_t<T, U>>>
    {
        return { -a.imag() * b.value(), a.real() * b.value() };
    }

    template <typename T, typename U> constexpr auto operator * (const imaginary<T> & a, const std::complex<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<mul_result_t<T, U>>>
    {
        return { -a.value() * b.imag(), a.value() * b.real() };
    }

    template <typename T, typename U> constexpr auto operator / (const std::complex<T> & a, const imaginary<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<div_result_t<T, U>>>
    {
        return { a.imag() / b.value(), -a.real() / b.value() };
    }

    template <typename T, typename U> constexpr auto operator / (const imaginary<T> & a, const std::complex<U> & b) -> std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, std::complex<div_result_t<T, U>>>
    {
		using RT = div_result_t<T, U>;
		RT norm = (RT(b.real()) * b.real() + b.imag() * b.imag());
        return { RT(a.value()) * b.imag() / norm, RT(a.value()) * b.real() / norm };
    }
}
