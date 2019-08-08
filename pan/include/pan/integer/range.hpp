
#pragma once

#include <cstdint>
#include <limits>
#include <type_traits>
#include "tag.h"

namespace pan
{
    // recursive case: check using numeric_limits

    struct unspecified_range {};
    struct unspecified_signed_range {};
    struct unbounded {};

    namespace
    {
        // modified code from http://stackoverflow.com/questions/31334291/select-an-integer-type-based-on-template-integer-parameter, response by Barry
        template <uint64_t MAX, typename... > struct bounded_unsigned;

        template <uint64_t MAX, typename T, typename... Ts> struct bounded_unsigned<MAX, T, Ts...> : std::conditional_t<(!std::numeric_limits<T>::is_signed && MAX <= std::numeric_limits<T>::max()),
            tag<T>,
            bounded_unsigned<MAX, Ts... >>
        { };

        template <int64_t MIN, uint64_t MAX, typename... > struct bounded_signed;

        template <int64_t MIN, uint64_t MAX, typename T, typename... Ts>
        struct bounded_signed<MIN, MAX, T, Ts...> : std::conditional_t<(std::numeric_limits<T>::is_signed && MIN >= std::numeric_limits<T>::min() && MAX <= std::numeric_limits<T>::max()),
            tag<T>,
            bounded_signed<MIN, MAX, Ts... >>
        { };

        template <int64_t MIN, uint64_t MAX, typename... Ts>
        struct best_fitting_integral : std::conditional_t<MIN >= 0, 
            bounded_unsigned<MAX, Ts...>, 
			bounded_signed<MIN, MAX, Ts...>>
        { };

        //template <typename T, uint64_t MAX, typename... Ts> struct best_fitting_integral;
        //template <uint64_t MAX, typename... Ts> 
        //struct best_fitting_integral<unspecified_range, MAX, Ts...> : bounded_unsigned<MAX, Ts...>
        //{ };
        //template <uint64_t MAX, typename... Ts>
        //struct best_fitting_integral<unspecified_signed_range, MAX, Ts...> : bounded_signed<0, MAX, Ts...>
        //{};

        //template <int64_t MIN, typename T, typename... Ts> struct best_fitting_integral;
        //template <int64_t MIN, typename... Ts>
        //struct best_fitting_integral<MIN, unspecified_range, Ts...> : bounded_signed<MIN, 0, Ts...>
        //{};
	}

    template <int64_t MIN, uint64_t MAX>
    using best_fitting_integral_t = typename best_fitting_integral<MIN, MAX, uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, uint64_t, int64_t>::type;

}