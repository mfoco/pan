#pragma once

#include <cstdint>
#include <algorithm>
#include <type_traits>
#include "tag.h"

namespace pan
{
    template <bool SIGNED, int BITS, typename... > struct select_integer_from_list;

    template <bool SIGNED, int BITS, typename T, typename... Ts> struct select_integer_from_list<SIGNED, BITS, T, Ts...> : std::conditional_t<((SIGNED == std::numeric_limits<T>::is_signed) && (BITS <= std::numeric_limits<T>::digits)),
        tag<T>,
        select_integer_from_list<SIGNED, BITS, Ts... >>
    { };

    template <bool SIGNED, int BITS>
    using select_integer_t = typename select_integer_from_list<SIGNED, BITS, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>::type;

    template <bool SIGNED, int BITS>
    struct integer
    {
        using this_type = integer<SIGNED, BITS>;
        using underlying_type = select_integer_t<SIGNED, BITS>;
        static constexpr const int bits = BITS;
        static constexpr const bool sign = SIGNED;
        static constexpr const int digits = bits + sign;
    private:
        underlying_type _value;
    public:
        static constexpr const underlying_type min_value = sign ? (~(static_cast<underlying_type>(1) << BITS))+1 : 0; // TODO: fix warnings
        static constexpr const underlying_type max_value = (static_cast<underlying_type>(1) << BITS) - 1; // TODO: fix warnings

        // default constructor
        constexpr integer() noexcept : _value() {}

        template<typename U> class has_smaller_range { enum { value = ((digits <= std::numeric_limits<U>::digits) && (sign || !std::numeric_limits<U>::is_signed)) }; };

        // value-checking constexpr constructor
        template<typename U>
        constexpr integer(U value, std::enable_if_t < std::numeric_limits<U>::is_integer && !has_smaller_range<U>::value>* = nullptr) : _value(value)
        {
            if (value < min_value || value > max_value) throw "Value doesn't fit."; // UB! signed/unsigned comparison. TODO: Find a better way to check
        }

        // non-checking constexpr constructor
        template<typename U>
        constexpr integer(U value, std::enable_if_t < std::numeric_limits<U>::is_integer && has_smaller_range<U>::value>* = nullptr) noexcept : _value(value)
        {
        }

        template<bool FROM_SIGNED, int FROM_BITS, typename = std::enable_if_t<((SIGNED == FROM_SIGNED) && (BITS <= FROM_BITS) || (SIGNED && (BITS < FROM_BITS)))>>
        constexpr integer(const this_type &other) noexcept : _value(other.value)
        {
        }

        // upcast - no need for overflow checks
        template<bool FROM_SIGNED, int FROM_BITS, typename = std::enable_if_t<((SIGNED == FROM_SIGNED) && (BITS <= FROM_BITS) || (SIGNED && (BITS < FROM_BITS)))>>
        constexpr integer(const integer<FROM_SIGNED, FROM_BITS> &other) noexcept : _value(other._value)
        {
        }

        // move constructor
        constexpr integer(this_type &&other) noexcept : _value()
        {
            using std::swap;
            swap(_value, other._value);
        }

        template<bool FROM_SIGNED, int FROM_BITS, typename = std::enable_if_t<((SIGNED == FROM_SIGNED) && (BITS <= FROM_BITS) || (SIGNED && (BITS < FROM_BITS)))>>
        /*constexpr*/ this_type & operator = (const integer<FROM_SIGNED, FROM_BITS> &other)
        {
            value = other.value;
            return *this;
        }

        constexpr underlying_type value() const { return _value; }
    };

    template<bool SIGNED, int A_BITS, int B_BITS>
    constexpr auto operator + (const integer<SIGNED, A_BITS> &a, const integer<SIGNED, B_BITS> &b)
    {
        using result_type = integer<SIGNED, std::max(A_BITS, B_BITS) + 1>;
        return result_type{ static_cast<typename result_type::underlying_type>(a) + static_cast<typename result_type::underlying_type>(b) };
    }
}