#pragma once

#include <tuple>

namespace pan::util
{
    template<typename T, size_t... Indices> struct tuple_view
    {
        static constexpr size_t indices[] = { Indices... };
        static_assert(((Indices < std::tuple_size_v<T>) && ...));

        const T& _t;

        constexpr tuple_view(const T& t) noexcept : _t(t)
        {
        }

        template<size_t I>
        constexpr friend decltype(auto) get(const tuple_view& t) noexcept
        {
            static_assert(I < sizeof...(Indices));
            using std::get;
            return get<indices[I]>(t._t);
        }
    };

    template<size_t... Indices, typename T> tuple_view(T)->tuple_view<T, Indices...>;
    template<size_t... Indices, typename T> auto make_tuple_view(const T& t) noexcept { return tuple_view<T, Indices...>(t); };
}

namespace std {
    template<typename T, size_t... Indices>
    struct tuple_size<pan::util::tuple_view<T, Indices...>> : std::integral_constant<std::size_t, sizeof...(Indices)> {};

    template<size_t I, typename T, size_t... Indices>
    struct tuple_element<I, pan::util::tuple_view<T, Indices...>>
    {
        static_assert(I < sizeof...(Indices));
        using type = tuple_element<T::indices[I], T>;
    };
}
