
#pragma once

#include <tuple>
#include <cstddef>
#include <utility>
#include <type_traits>
#include <pan/bases/dual.hpp>
#include <pan/bases/dual_math.hpp>

namespace pan::forward_diff 
{
    namespace details {
        template<size_t Index, size_t SelectedIndex, typename Tuple>
        constexpr auto get_optionally_dualized_element(Tuple &&t) 
        {
            auto &v = std::get<Index>(t);
            if constexpr (Index == SelectedIndex) 
            {
                return pan::bases::dual<std::decay_t<decltype(v)>>{v, 1};
            } else {
                return v;
            }
        }

        template<size_t SelectedIndex, typename Tuple, std::size_t ... I>
        constexpr auto dualize_element_in_tuple_impl(Tuple&& t, std::index_sequence<I...>) 
        {
            return std::make_tuple(get_optionally_dualized_element<I, SelectedIndex>(std::forward<Tuple>(t))...);
        }

        template<size_t SelectedIndex, typename Tuple>
        constexpr auto dualize_element_in_tuple(Tuple &&t) 
        {
            using Indices = std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>;
            return dualize_element_in_tuple_impl<SelectedIndex>(std::forward<Tuple>(t), Indices());
        }

        template <size_t SelectedIndex, typename F, typename Tuple> 
        constexpr auto dfN_tuple(F &&f, Tuple &&t) 
        {
            return std::apply(std::forward<F>(f), dualize_element_in_tuple<SelectedIndex>(t)).dx.value();
        } 

        template <typename F, typename Tuple, std::size_t... I> 
        constexpr auto df_impl(F &&f, Tuple &&t, std::index_sequence<I...>) 
        {
            return std::make_tuple(dfN_tuple<I>(std::forward<F>(f), t)...);
        }
    }

    template <size_t Index, typename F, typename... TPACK>
    constexpr auto dfN(F &&f, TPACK ...v) 
    {
        return details::dfN_tuple<Index>(std::forward<F>(f), std::forward_as_tuple(v...));
    }

    template <typename F, typename... TPACK>
    constexpr auto df(F &&f, TPACK ...v) 
    {
        return details::df_impl(std::forward<F>(f), std::forward_as_tuple(v...), std::index_sequence_for<TPACK...>{});
    }

    template <typename F, typename... TPACK>
    constexpr auto fdf(F &&f, TPACK ...v) 
    {
        auto r = f(v...);
        return std::tuple_cat(std::make_tuple(r), df(std::forward<F>(f), v...));
    } 
}
