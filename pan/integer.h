#pragma once

#include <cstdint>
#include <algorithm>
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
	private:
		underlying_type _value;
	public:

		constexpr static underlying_type min_value() {
			return SIGNED ? (-(static_cast<underlying_type>(1) << BITS)) : 0;
		}

		constexpr static underlying_type max_value() {
			return (static_cast<underlying_type>(1) << BITS) - 1;
		}

		// default constructor
		integer() : _value() {}

		// constructor
		template<typename U> 
		constexpr integer(U value, std::enable_if_t<std::numeric_limits<U>::is_integer && (((SIGNED == std::numeric_limits<U>::is_signed) && (BITS <= std::numeric_limits<U>::digits)) || (SIGNED && !std::numeric_limits<U>::is_signed && (BITS < std::numeric_limits<U>::digits)))>* = nullptr) : _value(value)
		{
		}

		// value-checking constexpr constructor
		template<typename U>
		constexpr integer(U value, std::enable_if_t<std::numeric_limits<U>::is_integer && !(((SIGNED == std::numeric_limits<U>::is_signed) && (BITS <= std::numeric_limits<U>::digits)) || (SIGNED && !std::numeric_limits<U>::is_signed && (BITS < std::numeric_limits<U>::digits)))>* = nullptr) : _value(value)
		{
			static_assert(value >= min_value() && value <= max_value(), "Value doesn't fit."); // UB! signed/unsigned comparison. TODO: Find a better way to check
		}

		// upcast & copy constructor
		template<bool FROM_SIGNED, int FROM_BITS, typename = std::enable_if_t<((SIGNED == FROM_SIGNED) && (BITS <= FROM_BITS) || (SIGNED && (BITS < FROM_BITS)))>>
		constexpr integer(const integer<FROM_SIGNED, FROM_BITS> &other) : _value(other.value)
		{
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