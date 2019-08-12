
#pragma once

#include <tuple>
#include <type_traits>
#include <utility>
#include "base.hpp"

namespace pan::tuple
{
    template <typename T, typename Tuple> struct has_type : std::false_type {};
    template <typename T, typename U, typename... Ts> struct has_type<T, std::tuple<U, Ts...>> : has_type<T, std::tuple<Ts...>> {};
    template <typename T, typename... Ts> struct has_type<T, std::tuple<T, Ts...>> : std::true_type {};
    template<typename T, typename Tuple> constexpr bool has_type_v = has_type<T, Tuple>::value;

    namespace {
        static_assert(has_type_v<int, std::tuple<int>>);
        static_assert(!has_type_v<int, std::tuple<float>>);
    }
}

namespace pan::bases
{
    template<typename ...T> struct arithmetic_tuple;

    template<typename ...T> constexpr auto make_arithmetic_tuple(T... t) { return arithmetic_tuple<T...>(t...); }

    template<typename Tuple, typename U, size_t ... I> constexpr auto arithmetic_tuple_append_helper(Tuple &&t, U &&rhs, std::index_sequence<I ...>) {
        return make_arithmetic_tuple(std::get<I>(t)..., std::forward<U>(rhs));
    }

    template<typename Tuple, typename U, typename... R> constexpr auto arithmetic_tuple_append(Tuple &&t, U &&rhs) {
        using Udec = std::decay_t<U>;
        if constexpr(pan::tuple::has_type_v<Udec, std::decay_t<Tuple>::tuple>) {
            Tuple t1 = t;
            std::get<Udec>(t1) += rhs;
            return t1;
        }
        constexpr size_t sz = std::tuple_size_v<std::decay_t<Tuple>::tuple>;
        return arithmetic_tuple_append_helper(std::forward<Tuple>(t), std::forward<U>(rhs), std::make_index_sequence<sz>{});
    }

    template<typename Tuple, typename U, typename... R> constexpr auto arithmetic_tuple_append(Tuple &&t, U &&rhs, R... r) {
        using Udec = std::decay_t<U>;
        if constexpr(pan::tuple::has_type_v<Udec, Tuple>) {
            Tuple t1 = t;
            std::get<U>(t1) += rhs;
            return arithmetic_tuple_append(t1, std::forward<R>(r)...);
        }
        return arithmetic_tuple_append(arithmetic_tuple_append_helper(std::forward<Tuple>(t), std::forward(U), std::make_index_sequence<std::tuple_size_v<Tuple>>{}), std::forward<R>(r)...);
    }

    template<typename ...T> struct arithmetic_tuple : std::tuple<T...>
    {
        using this_type = arithmetic_tuple<T...>;

        using std::tuple<T...>::tuple;

        constexpr arithmetic_tuple operator -() const {
            return {-std::get<T>(*this)...};
        }

        constexpr const arithmetic_tuple &operator +() const {
            return *this;
        }

        template<typename... U> constexpr arithmetic_tuple operator +(const arithmetic_tuple<U...>&rhs) const {
            return *this + std::get<U>(rhs) + ...;
        }

        template<typename... U> constexpr arithmetic_tuple operator -(const arithmetic_tuple<U...>&rhs) const {
            return *this - std::get<U>(rhs) - ...;
        }
    };

    // TODO: Check that U is not an arithmetic_tuple

    template<typename... T, typename U> constexpr auto operator + (const arithmetic_tuple<T...> &lhs, const U& rhs) {
        return arithmetic_tuple_append(lhs, rhs);
    }

    template<typename U, typename... T> constexpr auto operator + (const U& lhs, const arithmetic_tuple<T...> &rhs) {
        return arithmetic_tuple_append(rhs, lhs);
    }

    template<typename... T, typename U> constexpr auto operator - (const arithmetic_tuple<T...> &lhs, const U& rhs) {
        return arithmetic_tuple_append(lhs, -rhs);
    }

    template<typename U, typename... T> constexpr auto operator - (const U& lhs, const arithmetic_tuple<T...> &rhs) {
        return arithmetic_tuple_append(-rhs, lhs);
    }

    template<typename... T, typename U> constexpr auto operator * (const arithmetic_tuple<T...> &lhs, const U& rhs) {
        return arithmetic_tuple_append(make_arithmetic_tuple(), (lhs*rhs)...);
    }

    template<typename U, typename... T> constexpr auto operator * (const U& lhs, const arithmetic_tuple<T...> &rhs) {
        return make_arithmetic_tuple_append(make_arithmetic_tuple(), (lhs*rhs)...);
    }
}
