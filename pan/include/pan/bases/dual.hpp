
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
}
#endif
