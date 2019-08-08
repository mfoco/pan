
#ifndef _DUAL_BASE_
#define _DUAL_BASE_

#include "base.hpp"

namespace pan::bases
{
    template <int N> struct Epsilon;
    template <typename T, int N = 0> using epsilon = base<T, Epsilon<N>>;
    template<typename T, int N> struct prod_tag<epsilon<T, N>, epsilon<T, N>> { using ReturnType = T; constexpr static int S = 0; };
    template<typename T, int N> struct prod_tag<epsilon<T, N>, T> { using ReturnType = epsilon<T, N>; constexpr static int S = 1; };
    template<typename T, int N> struct prod_tag<T, epsilon<T, N>> { using ReturnType = epsilon<T, N>; constexpr static int S = 1; };

    constexpr epsilon<float> operator ""_feps(long double f)
    {
        return epsilon<float>(static_cast<float>(f));
    }

    constexpr epsilon<double> operator ""_eps(long double f)
    {
        return epsilon<double>(static_cast<double>(f));
    }

    constexpr epsilon<long double> operator ""_leps(long double f)
    {
        return epsilon<long double>(f);
    }

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
}
#endif
