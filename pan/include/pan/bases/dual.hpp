
#pragma once

#include <limits>
#include "epsilon.hpp"

namespace pan::bases
{
    template<typename T, int N = 0>
    struct dual {
        T x;
        epsilon<T, N> dx;
        
        constexpr dual() = default;
        constexpr dual(const T &_x) : x(_x) {}
        constexpr dual(const epsilon<T, N> &_dx) : x(0), dx(_dx) {}
        constexpr dual(const T &_x, const epsilon<T, N> &_dx) : x(_x), dx(_dx) {}
        constexpr dual(const T &_x, const T &_dx) : x(_x), dx{_dx} {}
        
        constexpr dual &operator += (const T &r) {
            x += r;
            return *this;
        }

        constexpr dual &operator -= (const T &r) {
            x -= r;
            return *this;
        }

        constexpr dual &operator *= (const T &r) {
            x *= r;
            dx *= r;
            return *this;
        }

        constexpr dual &operator /= (const T &r) {
            x /= r;
            return *this;
        }

        constexpr dual &operator += (const epsilon<T, N> &r) {
            dx += r;
            return *this;
        }

        constexpr dual &operator -= (const epsilon<T, N> &r) {
            dx -= r;
            return *this;
        }

        constexpr dual &operator *= (const epsilon<T, N> &r) {
            dx = x*r;
            x = 0;
            return *this;
        }

        constexpr dual &operator /= (const epsilon<T, N> &r) {
            if (x == 0) {
                x = dx/r.value();
                dx = {};
            } else
            {
                dx = - x*r.value()*std::numeric_limits<T>::infinity();
                x *= std::numeric_limits<T>::infinity();
            }
            return *this;
        }

        constexpr dual &operator += (const dual<T, N> &r) {
            x += r.x;
            dx += r.dx;
            return *this;
        }

        constexpr dual &operator -= (const dual<T, N> &r) {
            x -= r.x;
            dx -= r.dx;
            return *this;
        }

        constexpr dual &operator *= (const dual<T, N> &r) {
            dx = dx*r.x + x*r.dx;
            x *= r.x;
            return *this;
        }

        constexpr dual &operator /= (const dual<T, N> &r) {
            dx = (dx*r.x - x*r.dx)/(r.x*r.x);
            x /= r.x;
            return *this;
        }
    };

    template<typename T, int N>
    constexpr dual<T, N> operator + (const T &lhs, const epsilon<T, N> &rhs) {
        return {lhs, rhs};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator - (const T &lhs, const epsilon<T, N> &rhs) {
        return {lhs, -rhs};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator + (const epsilon<T, N> &lhs, const T &rhs) {
        return {rhs, lhs};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator - (const epsilon<T, N> &lhs, const T &rhs) {
        return {rhs, lhs};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator + (const dual<T, N> &lhs, const T &rhs) {
        return {lhs.x+rhs, lhs.dx};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator - (const dual<T, N> &lhs, const T &rhs) {
        return {lhs.x-rhs, lhs.dx};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator * (const dual<T, N> &lhs, const T &rhs) {
        return {lhs.x*rhs, lhs.dx*rhs};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator / (const dual<T, N> &lhs, const T &rhs) {
        return {lhs.x/rhs, lhs.dx/rhs};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator + (const T &lhs, const dual<T, N> &rhs) {
        return {lhs+rhs.x, rhs.dx};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator - (const T &lhs, const dual<T, N> &rhs) {
        return {lhs-rhs.x, -rhs.dx};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator * (const T &lhs, const dual<T, N> &rhs) {
        return {lhs*rhs.x, lhs*rhs.dx};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator / (const T &lhs, const dual<T, N> &rhs) {
        return {lhs/rhs.x, lhs*rhs.dx/(rhs.x*rhs.x)};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator + (const dual<T, N> &lhs, const epsilon<T, N> &rhs) {
        return {lhs.x, lhs.dx+rhs};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator - (const dual<T, N> &lhs, const epsilon<T, N> &rhs) {
        return {lhs.x, lhs.dx-rhs};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator * (const dual<T, N> &lhs, const epsilon<T, N> &rhs) {
        return {0, lhs.x*rhs};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator / (const dual<T, N> &lhs, const epsilon<T, N> &rhs) = delete;

    template<typename T, int N>
    constexpr dual<T, N> operator + (const epsilon<T, N> &lhs, const dual<T, N> &rhs) {
        return {rhs.x, lhs+rhs.dx};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator - (const epsilon<T, N> &lhs, const dual<T, N> &rhs) {
        return {-rhs.x, lhs-rhs.dx};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator * (const epsilon<T, N> &lhs, const dual<T, N> &rhs) {
        return {0, lhs*rhs.x};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator / (const epsilon<T, N> &lhs, const dual<T, N> &rhs) {
        return {0, lhs/rhs.x};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator + (const dual<T, N> &lhs, const dual<T, N> &rhs) {
        return {lhs.x + rhs.x, lhs.dx + rhs.dx};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator - (const dual<T, N> &lhs, const dual<T, N> &rhs) {
        return {lhs.x - rhs.x, lhs.dx - rhs.dx};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator * (const dual<T, N> &lhs, const dual<T, N> &rhs) {
        return {lhs.x*rhs.x, lhs.dx*rhs.x + lhs.x*rhs.dx};
    }

    template<typename T, int N>
    constexpr dual<T, N> operator / (const dual<T, N> &lhs, const dual<T, N> &rhs) {
        return {lhs.x/rhs.x, (lhs.dx*rhs.x - lhs.x*rhs.dx)/(rhs.x*rhs.x)};
    }
}
