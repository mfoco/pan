
#ifndef _IMAGINARY_H_
#define _IMAGINARY_H_

#include "base.hpp"
#include <complex>

namespace pan::bases
{
    template <int T> struct Imaginary {};
    template <typename T, int N> using imaginary_base = base<T, Imaginary<N>>;
    template <typename T> using imaginary = imaginary_base<T, 0>;
    template <typename T> using jmaginary = imaginary_base<T, 1>;
    template <typename T> using kmaginary = imaginary_base<T, 2>;

    template<typename T, int N> struct prod_tag<imaginary_base<T, N>, imaginary_base<T, N>> { using ReturnType = T; constexpr static int S = -1; };
    template<typename T, int N> struct prod_tag<imaginary_base<T, N>, T> { using ReturnType = imaginary_base<T, N>; constexpr static int S = 1; };
    template<typename T, int N> struct prod_tag<T, imaginary_base<T, N>> { using ReturnType = imaginary_base<T, N>; constexpr static int S = 1; };

    template<typename T, int N, int M> struct prod_tag<imaginary_base<T, N>, imaginary_base<T, M>, std::enable_if_t<(N > M)>> { using ReturnType = typename prod_tag<imaginary_base<T, M>, imaginary_base<T, N>>::ReturnType; constexpr static int S = -prod_tag<imaginary_base<T, M>, imaginary_base<T, N>>::S; };

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

    constexpr imaginary<float> operator ""_fi(long double f)
    {
        return imaginary<float>(static_cast<float>(f));
    }

    constexpr imaginary<double> operator ""_i(long double f)
    {
        return imaginary<double>(static_cast<double>(f));
    }

    constexpr imaginary<long double> operator ""_li(long double f)
    {
        return imaginary<long double>(f);
    }
}

#endif
