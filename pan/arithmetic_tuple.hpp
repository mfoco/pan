
#pragma once

#include <tuple>
#include "base.hpp"

namespace pan {
    template<typename ...T> struct arithmetic_tuple;

    template<typename ...T> auto make_arithmetic_tuple(T... t) { return arithmetic_tuple<T...>(t...); }

    template<typename ...T> struct arithmetic_tuple : std::tuple<T...>
    {
        using this_type = arithmetic_tuple<T...>;

        using std::tuple<T...>::tuple;

        template<typename U, typename O> auto compute(const U& rhs, O op) //-> typename std::common_type_t<U, type_tag<decltype(std::get<0>(*this)* rhs)>::underlying_type>
        {
            return make_arithmetic_tuple(op(std::get<T>(*this), rhs)...);
        }

        //template<typename U typename Tag, typename O> this_type compute(const this_type& lhs, const base<U, Tag>& rhs, O op)
        //{

        //}

        //template<typename U... typename O> this_type compute(const this_type& lhs, const arithmetic_tuple& rhs, O op)
        //{

        //}
    };
}
