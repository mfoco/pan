
#ifndef _BASE_
#define _BASE_

#include <cmath>
#include <ostream>

namespace pan
{
    template <typename T, typename U> struct prod_tag {};
    template <typename T, typename U> using prod_tag_return_t = typename prod_tag<T, U>::ReturnType;
    template <typename T, typename U> constexpr int prod_tag_s = prod_tag<T, U>::S;

    template <typename T, typename _Tag> class base;

    template <typename T> using real = T;
    template <typename T> using imaginary = base<T, struct Imaginary>;
    template <typename T> using epsilon = base<T, struct Epsilon>;

    template<typename T> struct prod_tag<T, T> { using ReturnType = T; constexpr static int S = 1; };
    template<typename T> struct prod_tag<imaginary<T>, imaginary<T>> { using ReturnType = T; constexpr static int S = -1; };
    template<typename T> struct prod_tag<imaginary<T>, T> { using ReturnType = imaginary<T>; constexpr static int S = 1; };
    template<typename T> struct prod_tag<T, imaginary<T>> { using ReturnType = imaginary<T>; constexpr static int S = 1; };
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
            return{ -_value };
        }

        constexpr Self &operator += (const Self &other) noexcept(noexcept(_value += other._value))
        {
            _value += other._value;
            return *this;
        }

        constexpr Self &operator -= (const Self &other) noexcept(noexcept(_value += other._value))
        {
            _value -= other._value;
            return *this;
        }

        constexpr bool operator == (const Self &other) noexcept(noexcept(_value == other._value))
        {
            return _value == other._value;
        }

        constexpr bool operator != (const Self &other) noexcept(noexcept(_value != other._value))
        {
            return _value != other._value;
        }

        template<typename U> constexpr std::enable_if_t<std::is_same_v<Self, prod_tag_return_t<Self, U>>, Self>& operator *= (const U& other) noexcept(noexcept(_value *= type_tag<U>::value(other) * prod_tag_s<Self, U>))
        {
            _value *= type_tag<U>::value(other) *prod_tag_s<Self, U>;
            return *this;
        }

        template<typename U> constexpr std::enable_if_t<std::is_same_v<Self, prod_tag_return_t<Self, U>>, Self> &operator /= (const U& other) noexcept(noexcept(_value /= other))
        {
            _value /= other;
            return *this;
        }
    };

    template <typename T, typename Tag> constexpr bool operator == (const base<T, Tag> &a, const base<T, Tag> &b) noexcept(noexcept(a.value() == b.value()))
    {
        return a.value() == b.value();
    }

    template <typename T, typename Tag> constexpr bool operator != (const base<T, Tag> &a, const base<T, Tag> &b) noexcept(noexcept(a.value() != b.value()))
    {
        return a.value() != b.value();
    }

    template <typename T, typename Tag> constexpr base<T, Tag> operator + (const base<T, Tag> &a, const base<T, Tag> &b) noexcept(noexcept(a.value() + b.value()))
    {
        return{ a.value() + b.value() };
    }

    template <typename T, typename Tag> constexpr base<T, Tag> operator - (const base<T, Tag> &a, const base<T, Tag> &b) noexcept(noexcept(a.value() - b.value()))
    {
        return{ a.value() - b.value() };
    }

    template <typename T, typename Tag1, typename Tag2> constexpr
    auto operator * (const base<T, Tag1> &a, const base<T, Tag2> &b) noexcept(noexcept(a.value()*b.value()*prod_tag_s<base<T, Tag1>, base<T, Tag2>>))
    {
        return prod_tag_return_t<base<T, Tag1>, base<T, Tag2>> { a.value()*b.value()*prod_tag_s<base<T, Tag1>, base<T, Tag2>> };
    }

    template <typename T, typename Tag> constexpr
    auto operator * (const base<T, Tag> &a, const T &b) noexcept(noexcept(a.value()*b*prod_tag_s<base<T, Tag>, T>))
    {
        return prod_tag_return_t<base<T, Tag>, T> { a.value()*b*prod_tag_s<base<T, Tag>, T> };
    }

    template <typename T, typename Tag> constexpr
    auto operator * (const T &a, const base<T, Tag> &b) noexcept(noexcept(a*b.value()*prod_tag_s<T, base<T, Tag>>))
    {
        return prod_tag_return_t<T, base<T, Tag>>{ a*b.value()*prod_tag_s<T, base<T, Tag>> };
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
}

#endif
