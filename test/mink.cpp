
#include <functional>

template <int F, typename R = nullptr_t> struct static_list
{
	static constexpr int first = F;
	using rest = R;
};

template <int... L> struct make_static_list
{
};

template <int... L> using make_static_list_t = typename make_static_list<L...>::type;

template <int F, int... R> struct make_static_list<F, R...>
{
	using type = static_list<F, typename make_static_list<R...>::type>;
};

template <> struct make_static_list<>
{
	using type = nullptr_t;
};

template <int el, typename L> struct push_front
{
	using type = static_list<el, typename push_front<L::first, typename L::rest>::type>;
};

template <int el> struct push_front<el, nullptr_t>
{
	using type = static_list<el>;
};

template <int l, typename L> using push_front_t = typename push_front<l, L>::type;

template <typename L, int l> struct push_back
{
	using type = static_list<L::first, typename push_back<typename L::rest, l>::type>;
};

template <int l> struct push_back<nullptr_t, l>
{
	using type = static_list<l>;
};

template <typename L, int l> using push_back_t = typename push_back<L, l>::type;

template <typename L, int N> struct skip {
	using type = typename skip<typename L::rest, N - 1>::type;
};

template <typename L, int N> using skip_t = typename skip<L, N>::type;

template <typename L> struct skip<L, 0> {
	using type = L;
};

//template <typename L, int N> int at = skip_t<L, N>::first;

template <typename L, int N> struct take {
	using type = static_list<L::first, typename take<typename L::rest, N - 1>::type>;
};

template <typename L, int N> using take_t = typename take<L, N>::type;

template <typename L> struct take<L, 0> {
	using type = nullptr_t;
};

template <typename... L> struct join
{
	using type = nullptr_t;
};

template <typename... L> using join_t = typename join<L...>::type;

template <typename F, typename... R> struct join<F, R...>
{
	using type = static_list<F::first, typename join<typename F::rest, R...>::type>;
};

template <typename... R> struct join<nullptr_t, R...>
{
	using type = typename join<R...>::type;
};

template <int N, typename L> struct count_occurrencies
{
	constexpr static int value = ((N == L::first) ? 1 : 0) + count_occurrencies<N, typename L::rest>::value;
};

template <int N> struct count_occurrencies<N, nullptr_t>
{
	constexpr static int value = 0;
};

template <int V, int N> struct repeat
{
	using type = static_list<V, typename repeat<V, N - 1>::type>;
};

template <int V> struct repeat<V, 0>
{
	using type = static_list<V>;
};

template <int V, int N> using repeat_t = typename repeat<V, N>::type;

//template <int N, typename L> struct remove_first_occurrency
//{
//	using type = static_list<L::first, typename remove_first_occurrency<N, typename L::rest>::type>;
//};
//
//template <int N, typename L> struct remove_first_occurrency<N, L> : std::enable_if<L::first == N>
//{
//	using type = typename L::rest;
//};
//
//template <int N, typename L> using remove_first_occurrency_t = typename remove_first_occurrency<N, L>::type;
//
//
//template <int N, typename L> struct remove_all_occurrencies<N, L> : std::enable_if<N == L::first>, remove_all_occurrencies<N, typename L::rest>
//{
//};
//
//template <int N, typename L> struct remove_all_occurrencies<N, L> : std::enable_if<N != L::first>
//{
//	using type = static_list<L::first, typename remove_all_occurrencies<N, typename L::rest>::type>;
//};
//
//template <int N, typename L> using remove_all_occurrencies_t = typename remove_all_occurrencies<N, L>::type;
//
//template <typename L> struct remove_duplicates
//{
//	using type = static_list<L::first, typename remove_duplicates<remove_all_occurrencies_t<L::first, typename L::rest>>::type>;
//};




#include <iostream>

int main()
{
	using q = make_static_list_t<>;
	using q1 = make_static_list_t<1>;
	using q23 = make_static_list_t<2, 3>;
	using q11 = push_back_t<q1, 1>;
	using q21 = push_front_t<2, q1>;

	using biglist = join_t<q, q1, q23, q11, q21>;

	std::cout << take_t<skip_t<push_front_t<0, make_static_list_t<1, 2, 3, 4>>, 2>, 2>::first << std::endl;
	std::cout << count_occurrencies<1, biglist>::value << std::endl;
	std::cout << count_occurrencies<1, repeat_t<1, 10>>::value << std::endl;
	std::cout << count_occurrencies<1, repeat_t<2, 10>>::value << std::endl;
}

//template <typename arr, int length> using take = static_list<>;
//template <typename arr, int start, int length> using static_subarray = take<skip<arr, start>, length>;
//
//
//template <typename B, size_t N, int... S> struct base
//{
//	B _values[N];
//
//	auto &operator += (base&other) noexcept(noexcept(_values[0] += _values[0])) {
//		for (size_t i = 0; i < N; ++i)
//		{
//			_values[i] += other[i];
//		}
//		return *this;
//	}
//
//	auto &operator -= (base&other) noexcept(noexcept(_values[0] -= _values[0])) {
//		for (size_t i = 0; i < N; ++i)
//		{
//			_values[i] -= other[i];
//		}
//		return *this;
//	}
//};
//
//template<typename B> using complex = base<B, 2, 1, 2, 2, -1>;
//template<typename B> using dual = base<B, 2, 1, 2, 2, 0>;
//template<typename B> using quaternion = base<B, 4, 1, 2, 3, 4,
//	2, -1, 4, -3,
//	3, -4, -1, 2,
//	4, 3, -2, -1>;
//template<typename B> using spacetime = base<B, 4, 1, 0, 0, 0,
//	0, 1, 0, 0,
//	0, 0, 1, 0,
//	0, 0, 0, -1>;
