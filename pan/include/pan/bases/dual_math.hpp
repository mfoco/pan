
#pragma once

#include <cmath>
#include "dual.hpp"

namespace pan::bases
{
    template<typename T, int N>
    constexpr dual<T, N> pow(const T &base, const epsilon<T, N> &exponent) {
        using std::log;
        return {1, exponent*(log(base))};
    }

    template<typename T, int N>
    constexpr dual<T, N> pow(const epsilon<T, N> &base, const T &exponent) {
        if (exponent > 1) {
            return {0, {0}};
        } else if (exponent == 1) {
            return {0, base};
        } else if (exponent > 0) {
            return {0, std::numeric_limits<T>::infinity()}; // TODO: raise FE_DIVBYZERO?
        } else if (exponent == 0) {
            return {std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::infinity()}; // TODO: raise FE_DIVBYZERO?
        } else {
            return {std::numeric_limits<T>::infinitt(), std::numeric_limits<T>::infinity()}; // TODO: raise FE_DIVBYZERO?
        }
    }
    
    template<typename T, int N>
    constexpr dual<T, N> pow(const epsilon<T, N> &base, const epsilon<T, N> &exponent) {
        return {1, -std::numeric_limits<T>::infinitt()}; // TODO: raise FE_DIVBYZERO?
    }

    template<typename T, int N>
    constexpr dual<T, N> pow(const T &base, const dual<T, N> &exponent) {
        using std::pow;
        using std::log;
        T real = pow(base, exponent.x);
        return {real, exponent.dx*(real*log(base))};
    }

    template<typename T, int N>
    constexpr dual<T, N> pow(const dual<T, N> &base, const T &exponent) {
        using std::pow;
        using std::log;
        T real = pow(base.x, exponent);
        return {real, real*(base.dx*exponent/base.x)};
    }

    template<typename T, int N>
    constexpr dual<T, N> pow(const dual<T, N> &base, const epsilon<T, N> &exponent) {
        using std::log;
        return {1, exponent*log(base.x)};
    }

    template<typename T, int N>
    constexpr dual<T, N> pow(const epsilon<T, N> &base, const dual<T, N> &exponent) = delete;

    template<typename T, int N>
    constexpr dual<T, N> pow(const dual<T, N> &base, const dual<T, N> &exponent) {
        using std::pow;
        using std::log;
        T real = pow(base.x, exponent.x);
        return {real, real*(exponent.dx*log(base.x)+base.dx*exponent.x/base.x)};
    }

    template<typename T, int N>
    constexpr dual<T, N> sin(const epsilon<T, N> &x) {
        return {0, x};
    }

    template<typename T, int N>
    constexpr dual<T, N> cos(const epsilon<T, N> &x) {
        return {1, {0}};
    }

    template<typename T, int N>
    constexpr dual<T, N> sin(const dual<T, N> &x) {
        using std::sin;
        using std::cos;
        return {sin(x.x), cos(x.x)*x.dx};
    }

    template<typename T, int N>
    constexpr dual<T, N> cos(const dual<T, N> &x) {
        using std::sin;
        using std::cos;
        return {cos(x.x), -sin(x.x)*x.dx};
    }

    template<typename T, int N>
    constexpr dual<T, N> log(const epsilon<T, N> &x) {
        using std::log;
        return {-std::numeric_limits<T>::infinity(), {std::numeric_limits<T>::infinity()}};
    }
    template<typename T, int N>
    constexpr dual<T, N> log(const dual<T, N> &x) {
        using std::log;
        return {log(x.x), x.dx/x.x};
    }
}
