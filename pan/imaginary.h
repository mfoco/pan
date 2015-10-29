#pragma once


#include <functional>
#include <complex>

template <typename T, typename U> using sum_result_t = decltype(*static_cast<T*>(nullptr) + *static_cast<U*>(nullptr));
template <typename T, typename U> using sub_result_t = decltype(*static_cast<T*>(nullptr) - *static_cast<U*>(nullptr));
template <typename T, typename U> using mul_result_t = decltype(*static_cast<T*>(nullptr) * *static_cast<U*>(nullptr));
template <typename T, typename U> using div_result_t = decltype(*static_cast<T*>(nullptr) / *static_cast<U*>(nullptr));

template<typename T>
class imaginary
{
	T value_;
	template<typename U> bool equal(const U &other) { return false; }
	template<typename U> bool equal(const imaginary<U> &other) { return other.value() == value_; }
public:
	constexpr imaginary() noexcept(std::is_nothrow_constructible<T>::value) : value_(T{}) {}
	explicit constexpr imaginary(T value) : value_(value) {}
	constexpr imaginary(const imaginary<T> &other) : value_(other.value_) {}
	template <typename U> constexpr imaginary(const imaginary<U> &other) : value_(other.value_) {}
	constexpr imaginary(imaginary<T> &&other) : value_(std::move(other.value_)) {}

	template <typename U> constexpr std::enable_if_t<std::is_assignable<T&, U>::value, imaginary<T>> &operator = (const imaginary<U> &other) noexcept(noexcept(value_ = other.value_))
	{
		value_ = other.value_;
		return *this;
	}

	imaginary<T> &operator = (const imaginary<T> &other) noexcept(noexcept(value_ = other.value_))
	{
		value_ = other.value_;
		return *this;
	}

	// TODO: Verify: does this make any sense at all?
	imaginary<T> &operator = (imaginary<T> &&other) && = delete;

	// TODO: MS BUG? constexpr makes the operator const, creating confusion with copy constructor (wat?)
	/*constexpr*/ imaginary<T> &operator = (imaginary<T> &&other) & noexcept(noexcept(std::swap(value_, other.value_)))
	{
		std::swap(value_, other.value_);
		return *this;
	}

	constexpr operator std::complex<T>() const
	{
		return{ 0, value_ };
	}

	// TODO: MS BUG? constexpr makes the operator const.
	template <typename U> /*constexpr*/ std::enable_if_t<std::is_assignable<T&, U>::value, imaginary<T>> &operator += (const imaginary<U> &other) & noexcept(noexcept(value_ += other.value()))
	{
		value_ += other.value();
		return *this;
	}

	// TODO: MS BUG? constexpr makes the operator const.
	template <typename U> /*constexpr*/ std::enable_if_t<std::is_assignable<T&, U>::value, imaginary<T>> &operator -= (const imaginary<U> &other) & noexcept(noexcept(value_ += other.value()))
	{
		value_ -= other.value();
		return *this;
	}

	// TODO: MS BUG? constexpr makes the operator const.
	template <typename U> /*constexpr*/ std::enable_if_t<std::is_assignable<T&, U>::value, imaginary<T>> &operator *= (const U &other) & noexcept(noexcept(value_ *= other))
	{
		value_ *= other;
		return *this;
	}

	// TODO: MS BUG? constexpr makes the operator const.
	template <typename U> /*constexpr*/ std::enable_if_t<std::is_assignable<T&, U>::value, imaginary<T>> operator /= (const U &other) & noexcept(noexcept(value_ /= other))
	{
		value_ /= other;
		return *this;
	}

	constexpr const T &value() const & noexcept { return value_; }
	constexpr T value() && { return move(value_); } // NOTE: what noexcept clause should we use here? is_noexcept_moveable<T>?

	constexpr const imaginary<T> &operator + () const & noexcept
	{
		return *this;
	}

	constexpr imaginary<T> operator + () && // NOTE: what noexcept clause should we use here? is_noexcept_moveable<imaginary<T>>?
	{
		return{ std::move(*this) };
	}

	constexpr imaginary<T> operator - () const // NOTE: what noexcept clause should we use here? is_noexcept_moveable<imaginary<T>>?
	{
		return imaginary<T>(-value_);
	}

	static constexpr imaginary<T> zero() { return imaginary<T>{}; }
};

template <typename T, typename U> constexpr std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, bool> operator == (const imaginary<T> &a, const imaginary<U> &b)
{
	return a.value() == b.value();
}

template <typename T, typename U> constexpr std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, bool> operator == (const T &a, const imaginary<U> &b)
{
	return (a == T{}) && (b.value() == U{});
}

template <typename T, typename U> constexpr std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, bool> operator == (const imaginary<T> &a, const U &b)
{
	return (b == U{}) && (a.value() == T{});
}

template <typename T, typename U> constexpr std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, bool> operator == (const std::complex<T> &a, const imaginary<U> &b)
{
	return (a.real() == T{}) && (a.imag() == b.value());
}

template <typename T, typename U> constexpr std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, bool> operator == (const imaginary<T> &a, const std::complex<U> &b)
{
	return (b.real() == T{}) && (a.value() == b.imag());
}

template <typename T, typename U> constexpr std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, bool> operator != (const imaginary<T> &a, const imaginary<U> &b)
{
	return a.value() != b.value();
}

template <typename T, typename U> constexpr std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, bool> operator != (const T &a, const imaginary<U> &b)
{
	return (a != T{}) || (b.value() != U{});
}

template <typename T, typename U> constexpr std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, bool> operator != (const imaginary<T> &a, const U &b)
{
	return (b != U{}) || (a.value() != T{});
}

template <typename T, typename U> constexpr std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, bool> operator != (const std::complex<T> &a, const imaginary<U> &b)
{
	return (a.real() != T{}) || (a.imag() != b.value());
}

template <typename T, typename U> constexpr std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, bool> operator != (const imaginary<T> &a, const std::complex<U> &b)
{
	return (b.real() != T{}) || (a.value() != b.imag());
}

template <typename T, typename U> constexpr auto operator + (const imaginary<T> &a, const imaginary<U> &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, imaginary<sum_result_t<T, U>>> {
	return imaginary<sum_result_t<T, U>>{ a.value() + b.value() };
}

template <typename T, typename U> constexpr auto operator + (const T &a, const imaginary<U> &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, std::complex<sum_result_t<T, U>>> {
	return std::complex<sum_result_t<T, U>>(a, b.value());
	//return{ a, b.value() };
}

template <typename T, typename U> constexpr auto operator + (const imaginary<T> &a, const U &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, std::complex<sum_result_t<T, U>>> {
	return std::complex<sum_result_t<T, U>>(b, a.value());
}

template <typename T, typename U> constexpr auto operator + (const std::complex<T> &a, const imaginary<U> &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, std::complex<sum_result_t<T, U>>> {
	return std::complex<sum_result_t<T, U>>(a.real(), a.imag() + b.value());
}

template <typename T, typename U> constexpr auto operator + (const imaginary<T> &a, const std::complex<U> &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, std::complex<sum_result_t<T, U>>> {
	return std::complex<sum_result_t<T, U>>(b.real(), a.value() + b.imag());
}

template <typename T, typename U> constexpr auto operator - (const imaginary<T> &a, const imaginary<U> &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, imaginary<sub_result_t<T, U>>> {
	return imaginary<sub_result_t<T, U>>{ a.value() - b.value() };
}

template <typename T, typename U> constexpr auto operator - (const T &a, const imaginary<U> &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, std::complex<sub_result_t<T, U>>> {
	return std::complex<sub_result_t<T, U>>(a, -b.value());
}

template <typename T, typename U> constexpr auto operator - (const imaginary<T> &a, const U &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, std::complex<sub_result_t<T, U>>> {
	return std::complex<sub_result_t<T, U>>(-b, a.value());
}

template <typename T, typename U> constexpr auto operator - (const std::complex<T> &a, const imaginary<U> &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, std::complex<sub_result_t<T, U>>> {
	return std::complex<sub_result_t<T, U>>(a.real(), a.imag() - b.value());
}

template <typename T, typename U> constexpr auto operator - (const imaginary<T> &a, const std::complex<U> &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, std::complex<sub_result_t<T, U>>> {
	return std::complex<sub_result_t<T, U>>(-b.real(), a.value() - b.imag());
}

template <typename T, typename U> constexpr auto operator * (const imaginary<T> &a, const imaginary<U> &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, mul_result_t<T, U>> {
	return{ -a.value()*b.value() };
}

template <typename T, typename U> constexpr auto operator * (const T &a, const imaginary<U> &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, imaginary<mul_result_t<T, U>>> {
	return imaginary<mul_result_t<T, U>>{ a*b.value() };
}

template <typename T, typename U> constexpr auto operator * (const imaginary<T> &a, const U &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, imaginary<mul_result_t<T, U>>> {
	return imaginary<mul_result_t<T, U>>{ a.value()*b };
}

template <typename T, typename U> constexpr auto operator * (const std::complex<T> &a, const imaginary<U> &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, std::complex<mul_result_t<T, U>>> {
	return std::complex<mul_result_t<T, U>>(-a.imag()*b.value(), a.real()*b.value());
}

template <typename T, typename U> constexpr auto operator * (const imaginary<T> &a, const std::complex<U> &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, std::complex<mul_result_t<T, U>>> {
	return std::complex<mul_result_t<T, U>>(-a.value()*b.imag(), a.value()*b.real());
}

template <typename T, typename U> constexpr auto operator / (const imaginary<T> &a, const imaginary<U> &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, div_result_t<T, U>> {
	return{ a.value() / b.value() };
}

template <typename T, typename U> constexpr auto operator / (const T &a, const imaginary<U> &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, imaginary<div_result_t<T, U>>> {
	return imaginary<mul_result_t<T, U>>{ -a / b.value() };
}

template <typename T, typename U> constexpr auto operator / (const imaginary<T> &a, const U &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, imaginary<div_result_t<T, U>>> {
	return imaginary<mul_result_t<T, U>>{ a.value() / b };
}

template <typename T, typename U> constexpr auto operator / (const std::complex<T> &a, const imaginary<U> &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, std::complex<div_result_t<T, U>>> {
	return std::complex<div_result_t<T, U>>(a.imag() / b.value(), -a.real() / b.value());
}

template <typename T, typename U> constexpr auto operator / (const imaginary<T> &a, const std::complex<U> &b) -> std::enable_if_t<std::is_assignable<T&, U>::value || std::is_assignable<U&, T>::value, std::complex<div_result_t<T, U>>> {
	return  std::complex<div_result_t<T, U>>(a.value()*b.imag() / (b.real()*b.real() + b.imag()*b.imag()), a.value()*b.real() / (b.real()*b.real() + b.imag()*b.imag()));
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
