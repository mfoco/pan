
#ifndef _BASE_
#define _BASE_

#include <cmath>
#include <ostream>

namespace pan
{
    namespace {
        template <typename T, typename U> using sum_result_t = decltype(std::declval<T>() + std::declval<U>());
        template <typename T, typename U> using sub_result_t = decltype(std::declval<T>() - std::declval<U>());
        template <typename T, typename U> using mul_result_t = decltype(std::declval<T>() * std::declval<U>());
        template <typename T, typename U> using div_result_t = decltype(std::declval<T>() / std::declval<U>());
    }

    template <typename T, typename U, typename Spec = void> struct prod_tag {};
    template <typename T, typename U> using prod_tag_return_t = typename prod_tag<T, U>::ReturnType;
    template <typename T, typename U> constexpr int prod_tag_s = prod_tag<T, U>::S;

    template <typename T, typename _Tag> class base;

    template<int N> struct Real {};
    template <typename T, int N = 0> struct base_real {
        using type = base<T, Real<N>>;
    };
    template <typename T> struct base_real<T, 0> {
        using type = T;
    };

    template <typename T, int N = 0> using real = typename base_real<T, N>::type;
    //template<typename T> struct prod_tag<T, T> { using ReturnType = T; constexpr static int S = 1; };
    
    template<typename T> struct type_tag
    {
        using self = T;
        using type = Real<0>;
        using underlying_type = T;

        static underlying_type value(self v) noexcept { return v; }

        template<typename U> using cast_underlying_type = U;
        template<typename U> static cast_underlying_type<U> cast_underlying(T t) { return { t }; }
    };

    template<typename T, typename Tag> struct type_tag<base<T, Tag>>
    {
        using self = base<T, Tag>;
        using type = Tag;
        using underlying_type = T;

        static underlying_type value(self v) noexcept { return v.value(); }

        template<typename U> using cast_underlying_type = base<U, Tag>;
        template<typename U> static cast_underlying_type<U> cast_underlying(T t) { return { t }; }
    };

    template<typename U, typename T> auto underlying_cast(T& t) {// -> typename type_tag<T>::cast_underlying_type<U> {
        return type_tag<T>::cast_underlying_type(t);
    }

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
}

#endif
