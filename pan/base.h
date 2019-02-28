
#ifndef _BASE_
#define _BASE_

#include <cmath>
#include <ostream>
#include <complex>

namespace pan
{
    namespace {
        template <typename T, typename U> using sum_result_t = decltype(std::declval<T>() + std::declval<U>());
        template <typename T, typename U> using sub_result_t = decltype(std::declval<T>() - std::declval<U>());
        template <typename T, typename U> using mul_result_t = decltype(std::declval<T>()* std::declval<U>());
        template <typename T, typename U> using div_result_t = decltype(std::declval<T>() / std::declval<U>());
    }

    template <typename T, typename U, typename Spec = void> struct prod_tag {};
    template <typename T, typename U> using prod_tag_return_t = typename prod_tag<T, U>::ReturnType;
    template <typename T, typename U> constexpr int prod_tag_s = prod_tag<T, U>::S;

    template <typename T, typename _Tag> class base;

    template <typename T> using real = T;
    template <int T> struct Imaginary {};
    template <typename T, int N> using imaginary_base = base<T, Imaginary<N>>;
    template <typename T> using imaginary = imaginary_base<T, 0>;
    template <typename T> using jmaginary = imaginary_base<T, 1>;
    template <typename T> using kmaginary = imaginary_base<T, 2>;
    template <typename T> using epsilon = base<T, struct Epsilon>;

    //template<typename T> struct prod_tag<T, T> { using ReturnType = T; constexpr static int S = 1; };

    template<typename T, int N> struct prod_tag<imaginary_base<T, N>, imaginary_base<T, N>> { using ReturnType = T; constexpr static int S = -1; };
    template<typename T, int N> struct prod_tag<imaginary_base<T, N>, T> { using ReturnType = imaginary_base<T, N>; constexpr static int S = 1; };
    template<typename T, int N> struct prod_tag<T, imaginary_base<T, N>> { using ReturnType = imaginary_base<T, N>; constexpr static int S = 1; };

    template<typename T, int N, int M> struct prod_tag<imaginary_base<T, N>, imaginary_base<T, M>, typename std::enable_if_t<(N > M)>> { using ReturnType = typename prod_tag<imaginary_base<T, M>, imaginary_base<T, N>>::ReturnType; constexpr static int S = - prod_tag<imaginary_base<T, M>, imaginary_base<T, N>>::S; };

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

    template<typename T> struct prod_tag<epsilon<T>, epsilon<T>> { using ReturnType = T; constexpr static int S = 0; };
    template<typename T> struct prod_tag<epsilon<T>, T> { using ReturnType = epsilon<T>; constexpr static int S = 1; };
    template<typename T> struct prod_tag<T, epsilon<T>> { using ReturnType = epsilon<T>; constexpr static int S = 1; };

    struct Real;
    
    template<typename T> struct type_tag
    {
        using self = T;
        using type = Real;
        using underlying_type = T;

        static underlying_type value(self v) noexcept { return v; }
    };

    template<typename T, typename Tag> struct type_tag<base<T, Tag>>
    {
        using self = base<T, Tag>;
        using type = Tag;
        using underlying_type = T;

        static underlying_type value(self v) noexcept { return v.value(); }
    };


    template <typename T, typename _Tag> class base
    {
        T _value;
    public:
        using Tag = _Tag;
        using Self = base<T, _Tag>;

        explicit constexpr base() noexcept : _value{} {}
        explicit constexpr base(T value) noexcept : _value{value} {}

        constexpr T value() const noexcept { return _value; }

        constexpr auto operator + () const noexcept
        {
            return *this;
        }

        constexpr Self operator - () const noexcept(noexcept(-_value))
        {
            return Self{ -_value };
        }

        template<typename U> constexpr std::enable_if_t<std::is_convertible_v<T, U>, Self>& operator += (const base<U, Tag>& other) noexcept(noexcept(_value += other.value()))
        {
            _value += other.value();
            return *this;
        }

        template<typename U> constexpr std::enable_if_t<std::is_convertible_v<T, U>, Self>& operator -= (const base<U, Tag>& other) noexcept(noexcept(_value -= other.value()))
        {
            _value -= other.value();
            return *this;
        }

        template<typename U> constexpr std::enable_if_t<std::is_convertible_v<T, U>, Self>& operator *= (const U& other) noexcept(noexcept(_value *= other))
        {
            _value *= other;
            return *this;
        }

        template<typename U> constexpr std::enable_if_t<std::is_convertible_v<T, U>, Self>& operator /= (const U& other) noexcept(noexcept(_value /= other))
        {
            _value /= other;
            return *this;
        }

        template<typename U> constexpr std::enable_if_t<std::is_convertible_v<T, U> || std::is_convertible_v<U, T>, bool> operator == (const base<U, Tag>& other) const noexcept(noexcept(_value == other.value())) 
        { 
            return _value == other.value(); 
        }

        template<typename U> constexpr std::enable_if_t<!std::is_convertible_v<T, U> && !std::is_convertible_v<U, T>, bool> operator == (const base<U, Tag>& other) const noexcept(noexcept(_value == T{} && other.value() == U{}))
        {
            return _value == T{} && other.value() == U{};
        }

        template<typename U> constexpr std::enable_if_t<std::is_convertible_v<T, U> || std::is_convertible_v<U, T>, bool> operator == (const U& other) const noexcept(noexcept(_value == T{} && other == U{}))
        {
            return _value == T{} && other == U{};
        }

        template<typename U> constexpr std::enable_if_t<std::is_convertible_v<T, U> || std::is_convertible_v<U, T>, bool> operator != (const base<U, Tag>& other) const noexcept(noexcept(_value != other.value()))
        { 
            return _value != other.value(); 
        }

        template<typename U> constexpr std::enable_if_t<!std::is_convertible_v<T, U> && !std::is_convertible_v<U, T>, bool> operator != (const base<U, Tag>& other) const noexcept(noexcept(_value != T{} || other.value() != U{}))
        {
            return _value != T{} || other.value() != U{};
        }

        template<typename U> constexpr std::enable_if_t<std::is_convertible_v<T, U> || std::is_convertible_v<U, T>, bool> operator != (const U& other) const noexcept(noexcept(_value != T{} || other != U{}))
        {
            return _value != T{} || other != U{};
        }

    };

    template <typename T, typename Tag, typename U> constexpr std::enable_if_t<std::is_convertible_v<T, U> || std::is_convertible_v<U, T>, bool> operator == (const U& left, const base<T, Tag>& right) noexcept(noexcept(left == U{} && right.value() == T{}))
    {
        return left == U{} && right.value() == T{};
    }

    template <typename T, typename Tag, typename U> constexpr std::enable_if_t<std::is_convertible_v<T, U> || std::is_convertible_v<U, T>, bool> operator != (const U& left, const base<T, Tag>& right) noexcept(noexcept(left != U{} || right.value() != T{}))
    {
        return left != U{} || right.value() != T{};
    }

    template <typename T, typename U, typename Tag> constexpr base<std::common_type_t<T, U>, Tag> operator + (const base<T, Tag> &a, const base<U, Tag> &b) noexcept(noexcept(a.value() + b.value()))
    {
        return base<std::common_type_t<T, U>, Tag>{ a.value() + b.value() };
    }

    template <typename T, typename U, typename Tag> constexpr base<std::common_type_t<T, U>, Tag> operator - (const base<T, Tag>& a, const base<U, Tag>& b) noexcept(noexcept(a.value() - b.value()))
    {
        return base<std::common_type_t<T, U>, Tag>{ a.value() - b.value() };
    }

    template <typename T, typename U, typename Tag1, typename Tag2> constexpr std::enable_if_t<std::is_convertible_v<T, U> || std::is_convertible_v<U, T>, prod_tag_return_t<base<std::common_type_t<T, U>, Tag1>, base<std::common_type_t<T, U>, Tag2>>> operator * (const base<T, Tag1> &a, const base<U, Tag2> &b) noexcept(noexcept(a.value()*b.value()))
    {
        using V = std::common_type_t<T, U>;
        V l = a.value();
        V r = b.value();
        return prod_tag_return_t<base<V, Tag1>, base<V, Tag2>>{ l * r * prod_tag_s<base<V, Tag1>, base<V, Tag2>> };
    }

    template <typename T, typename U, typename Tag> constexpr std::enable_if_t<std::is_convertible_v<T, U> || std::is_convertible_v<U, T>, base<std::common_type_t<T, U>, Tag>> operator * (const base<T, Tag>& a, const U& b) noexcept(noexcept(a.value()* b))
    {
        using V = std::common_type_t<T, U>;
        V l = a.value();
        V r = b;
        return base<V, Tag>{ l * r };
    }

    template <typename T, typename U, typename Tag> constexpr std::enable_if_t<std::is_convertible_v<T, U> || std::is_convertible_v<U, T>, base<std::common_type_t<T, U>, Tag>>  operator * (const T& a, const base<U, Tag>& b) noexcept(noexcept(a* b.value()))
    {
        using V = std::common_type_t<T, U>;
        V l = a;
        V r = b.value();
        return base<V, Tag>{ l * r };
    }

    template <typename T, typename U, typename Tag> constexpr std::enable_if_t<std::is_convertible_v<T, U> || std::is_convertible_v<U, T>, std::common_type_t<T, U>>  operator / (const base<T, Tag>& a, const base<U, Tag>& b) noexcept(noexcept(a.value()/ b.value()))
    {
        using V = std::common_type_t<T, U>;
        V l = a.value();
        V r = b.value();
        return l / r;
    }

    template <typename T, typename U, typename Tag> constexpr std::enable_if_t<std::is_convertible_v<T, U> || std::is_convertible_v<U, T>, base<std::common_type_t<T, U>, Tag>> operator / (const base<T, Tag>& a, const U& b) noexcept(noexcept(a.value() / b))
    {
        using V = std::common_type_t<T, U>;
        V l = a.value();
        V r = b;
        return base<V, Tag>{ l / r };
    }

    template <typename T, typename U, typename Tag> constexpr std::enable_if_t<std::is_convertible_v<T, U> || std::is_convertible_v<U, T>, base<std::common_type_t<T, U>, Tag>> operator / (const U& left, const base<T, Tag>& right) noexcept(noexcept((left* right) / (right * right)))
    {
        return (left*right) / (right*right);
    }

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

    template <typename T, typename U> constexpr std::enable_if_t<std::is_assignable_v<T&, U> || std::is_assignable_v<U&, T>, bool> operator == (const std::complex<T> & a, const imaginary<U> & b)
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
