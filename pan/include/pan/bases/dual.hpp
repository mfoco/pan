
#pragma once

#include <cmath>
#include "epsilon.hpp"

namespace pan::bases
{
    template<typename T>
    struct dual {
        T x;
        epsilon<T> dx;
        
        constexpr dual() = default;
        constexpr dual(const T &_x) : x(_x) {}
        constexpr dual(const epsilon<T> &_dx) : x(0), dx(_dx) {}
        constexpr dual(const T &_x, const epsilon<T> &_dx) : x(_x), dx(_dx) {}
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
            x -= r;
            return *this;
        }

        constexpr dual &operator += (const epsilon<T> &r) {
            dx += r;
            return *this;
        }

        constexpr dual &operator -= (const epsilon<T> &r) {
            dx -= r;
            return *this;
        }

        constexpr dual &operator *= (const epsilon<T> &r) {
            dx = x*r;
            x = 0;
            return *this;
        }

        // constexpr dual &operator /= (const epsilon<T> &r) {
        //     x -= r;
        //     return *this;
        // }

        constexpr dual &operator += (const dual<T> &r) {
            x += r.x;
            dx += r.dx;
            return *this;
        }

        constexpr dual &operator -= (const dual<T> &r) {
            x -= r.x;
            dx -= r.dx;
            return *this;
        }

        constexpr dual &operator *= (const dual<T> &r) {
            dx = dx*r.x + x*r.dx;
            x *= r.x;
            return *this;
        }

        constexpr dual &operator /= (const dual<T> &r) {
            dx = (dx*r.x - x*r.dx)/(r.x*r.x);
            x /= r.x;
            return *this;
        }
    };

    template<typename T>
    constexpr dual<T> operator + (const T &lhs, const epsilon<T> &rhs) {
        return {lhs, rhs};
    }

    template<typename T>
    constexpr dual<T> operator - (const T &lhs, const epsilon<T> &rhs) {
        return {lhs, -rhs};
    }

    template<typename T>
    constexpr dual<T> operator + (const epsilon<T> &lhs, const T &rhs) {
        return {rhs, lhs};
    }

    template<typename T>
    constexpr dual<T> operator - (const epsilon<T> &lhs, const T &rhs) {
        return {rhs, lhs};
    }

    template<typename T>
    constexpr dual<T> operator + (const dual<T> &lhs, const T &rhs) {
        return {lhs.x+rhs, lhs.dx};
    }

    template<typename T>
    constexpr dual<T> operator - (const dual<T> &lhs, const T &rhs) {
        return {lhs.x-rhs, lhs.dx};
    }

    template<typename T>
    constexpr dual<T> operator * (const dual<T> &lhs, const T &rhs) {
        return {lhs.x*rhs, lhs.dx*rhs};
    }

    template<typename T>
    constexpr dual<T> operator / (const dual<T> &lhs, const T &rhs) {
        return {lhs.x/rhs, lhs.dx/rhs};
    }

    template<typename T>
    constexpr dual<T> operator + (const T &lhs, const dual<T> &rhs) {
        return {lhs+rhs.x, rhs.dx};
    }

    template<typename T>
    constexpr dual<T> operator - (const T &lhs, const dual<T> &rhs) {
        return {lhs-rhs.x, -rhs.dx};
    }

    template<typename T>
    constexpr dual<T> operator * (const T &lhs, const dual<T> &rhs) {
        return {lhs*rhs.x, lhs*rhs.dx};
    }

    template<typename T>
    constexpr dual<T> operator / (const T &lhs, const dual<T> &rhs) {
        return {lhs/rhs.x, lhs*rhs.dx/(rhs.x*rhs.x)};
    }

    template<typename T>
    constexpr dual<T> operator + (const dual<T> &lhs, const epsilon<T> &rhs) {
        return {lhs.x, lhs.dx+rhs};
    }

    template<typename T>
    constexpr dual<T> operator - (const dual<T> &lhs, const epsilon<T> &rhs) {
        return {lhs.x, lhs.dx-rhs};
    }

    template<typename T>
    constexpr dual<T> operator * (const dual<T> &lhs, const epsilon<T> &rhs) {
        return {0, lhs.x*rhs};
    }

    template<typename T>
    constexpr dual<T> operator + (const epsilon<T> &lhs, const dual<T> &rhs) {
        return {rhs.x, lhs+rhs.dx};
    }

    template<typename T>
    constexpr dual<T> operator - (const epsilon<T> &lhs, const dual<T> &rhs) {
        return {-rhs.x, lhs-rhs.dx};
    }

    template<typename T>
    constexpr dual<T> operator * (const epsilon<T> &lhs, const dual<T> &rhs) {
        return {0, lhs*rhs.x};
    }

    template<typename T>
    constexpr dual<T> operator / (const epsilon<T> &lhs, const dual<T> &rhs) {
        return {0, lhs*rhs.x};
    }

    // constexpr dual operator / (const epsilon<T> &rhs) {
    //     return {lhs.x/rhs, lhs.dx/rhs};
    // }

    template<typename T>
    constexpr dual<T> operator + (const dual<T> &lhs, const dual<T> &rhs) {
        return {lhs.x + rhs.x, lhs.dx + rhs.dx};
    }

    template<typename T>
    constexpr dual<T> operator - (const dual<T> &lhs, const dual<T> &rhs) {
        return {lhs.x - rhs.x, lhs.dx - rhs.dx};
    }

    template<typename T>
    constexpr dual<T> operator * (const dual<T> &lhs, const dual<T> &rhs) {
        return {lhs.x*rhs.x, lhs.dx*rhs.x + lhs.x*rhs.dx};
    }

    template<typename T>
    constexpr dual<T> operator / (const dual<T> &lhs, const dual<T> &rhs) {
        return {lhs.x/rhs.x, (lhs.dx*rhs.x - lhs.x*rhs.dx)/(rhs.x*rhs.x)};
    }

    template<typename T>
    constexpr epsilon<T> sin(const epsilon<T> &x) {
        return x;
    }

    template<typename T>
    constexpr epsilon<T> cos(const epsilon<T> &x) {
        return {0};
    }

    template<typename T>
    constexpr dual<T> sin(const dual<T> &x) {
        using std::sin;
        using std::cos;
        return {sin(x.x), cos(x.x)*x.dx};
    }

    template<typename T>
    constexpr dual<T> cos(const dual<T> &x) {
        using std::sin;
        using std::cos;
        return {cos(x.x), -sin(x.x)*x.dx};
    }

}
