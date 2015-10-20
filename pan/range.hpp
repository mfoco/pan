
#pragma once

#include <cstdint>
#include <limits>
#include <type_traits>

namespace pan {
    // recursive case: check using numeric_limits

    struct unspecified_range {};
    struct unspecified_signed_range {};
    struct unbounded {};

    namespace {
        template <typename T>
        struct tag {
            using type = T;
        };

        // modified code from http://stackoverflow.com/questions/31334291/select-an-integer-type-based-on-template-integer-parameter, response by Barry
        template <uint64_t MAX, typename... > struct bounded_unsigned_t;

        template <uint64_t MAX, typename T, typename... Ts> struct bounded_unsigned_t<MAX, T, Ts...> : std::conditional_t<(!std::numeric_limits<T>::is_signed && MAX <= std::numeric_limits<T>::max()),
            tag<T>,
            bounded_unsigned_t<MAX, Ts... >>
        { };

        template <int64_t MIN, uint64_t MAX, typename... > struct bounded_signed_t;

        template <int64_t MIN, uint64_t MAX, typename T, typename... Ts>
        struct bounded_signed_t<MIN, MAX, T, Ts...> : std::conditional_t<(std::numeric_limits<T>::is_signed && MIN >= std::numeric_limits<T>::min() && MAX <= std::numeric_limits<T>::max()),
            tag<T>,
            bounded_signed_t<MIN, MAX, Ts... >>
        { };

        template <int64_t MIN, uint64_t MAX, typename... Ts>
        struct best_fitting_integral_t : std::conditional_t<MIN >= 0, 
            bounded_unsigned_t<MAX, Ts...>, 
            bounded_signed_t<MIN, MAX, Ts...>> 
        { };

        //template <typename T, uint64_t MAX, typename... Ts> struct best_fitting_integral_t;
        //template <uint64_t MAX, typename... Ts> 
        //struct best_fitting_integral_t<unspecified_range, MAX, Ts...> : bounded_unsigned_t<MAX, Ts...>
        //{ };
        //template <uint64_t MAX, typename... Ts>
        //struct best_fitting_integral_t<unspecified_signed_range, MAX, Ts...> : bounded_signed_t<0, MAX, Ts...>
        //{};

        //template <int64_t MIN, typename T, typename... Ts> struct best_fitting_integral_t;
        //template <int64_t MIN, typename... Ts>
        //struct best_fitting_integral_t<MIN, unspecified_range, Ts...> : bounded_signed_t<MIN, 0, Ts...>
        //{};

		template <int BITS, typename... > struct unsigned_integer_t;

		template <int BITS, typename T, typename... Ts> struct unsigned_integer_t<BITS, T, Ts...> : std::conditional_t<(!std::numeric_limits<T>::is_signed && BITS <= std::numeric_limits<T>::digits()),
			tag<T>,
			unsigned_integer_t<BITS, Ts... >>
		{ };

		template <int BITS, typename... > struct signed_integer_t;

		template <int BITS, typename T, typename... Ts> struct signed_integer_t<BITS, T, Ts...> : std::conditional_t<(!std::numeric_limits<T>::is_signed && BITS <= std::numeric_limits<T>::digits()),
			tag<T>,
			signed_integer_t<BITS, Ts... >>
		{ };
	}

    template <int64_t MIN, uint64_t MAX>
    using best_fitting_integral = typename best_fitting_integral_t<MIN, MAX, uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, uint64_t, int64_t>::type;

	template <int BITS>
	using unsigned_integer = typename unsigned_integer_t<BITS, uint8_t, uint16_t, uint32_t, uint64_t>::type;

	template <int BITS>
	using signed_integer = typename signed_integer_t<BITS, int8_t, int16_t, int32_t, int64_t>::type;
}