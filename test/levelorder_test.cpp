/* Performance measurements of binary search with a flat binary tree structure.
*
* Copyright 2015 Joaquin M Lopez Munoz.
* Distributed under the Boost Software License, Version 1.0.
* (See accompanying file LICENSE_1_0.txt or copy at
* http://www.boost.org/LICENSE_1_0.txt)
*/

#include <algorithm>
#include <array>
#include <chrono>
#include <numeric> 

#include "levelorder_vector.hpp"

std::chrono::high_resolution_clock::time_point measure_start, measure_pause;

template<typename F>
double measure(F f)
{
	using namespace std::chrono;

	static const int              num_trials = 10;
	static const milliseconds     min_time_per_trial(200);
	std::array<double, num_trials> trials;
	static decltype(f())          res; /* to avoid optimizing f() away */

	for (int i = 0; i<num_trials; ++i) {
		int                               runs = 0;
		high_resolution_clock::time_point t2;

		measure_start = high_resolution_clock::now();
		do {
			res = f();
			++runs;
			t2 = high_resolution_clock::now();
		} while (t2 - measure_start<min_time_per_trial);
		trials[i] = duration_cast<duration<double>>(t2 - measure_start).count() / runs;
	}
	(void)res; /* var not used warn */

	std::sort(trials.begin(), trials.end());
	return std::accumulate(
		trials.begin() + 2, trials.end() - 2, 0.0) / (trials.size() - 4);
}

void pause_timing()
{
	measure_pause = std::chrono::high_resolution_clock::now();
}

void resume_timing()
{
	measure_start += std::chrono::high_resolution_clock::now() - measure_pause;
}


#include <iostream>
#include <functional>
#include <random>
#include <vector>

struct rand_seq
{
	rand_seq(unsigned int n) :dist(0, n - 1), gen(34862) {}
	unsigned int operator()() { return dist(gen); }

private:
	std::uniform_int_distribution<unsigned int> dist;
	std::mt19937                                gen;
};

template<typename Container>
Container create(unsigned int n)
{
	std::vector<unsigned int> v;
	for (unsigned int m = 0; m<n; ++m)v.push_back(m);
	std::shuffle(v.begin(), v.end(), std::mt19937(131075));
	return Container(v.begin(), v.end());
}

template<typename Container>
struct binary_search
{
	typedef unsigned int result_type;

	unsigned int operator()(const Container & c)const
	{
		unsigned int res = 0;
		unsigned int n = c.size();
		rand_seq     rnd(c.size());
		auto         end_ = c.end();
		while (n--) {
			if (c.lower_bound(rnd()) != end_)++res;
		}
		return res;
	}
};

template<
	template<typename> class Tester,
	typename Container1, typename Container2, typename Container3, typename Container4>
	void test(
		const char* title,
		const char* name1, const char* name2, const char* name3, const char* name4)
{
	const unsigned int n0 = 15;
	const unsigned int n1 = 3000000;

	std::cout << title << ":" << std::endl;
	std::cout << name1 << ";" << name2 << ";" << name3 << std::endl;

	for (unsigned int n = n0; n <= n1; n = (n+1)*16-1) {
		double t;
		{
			auto c = create<Container1>(n);
			t = measure(std::bind(Tester<Container1>(), std::cref(c)));
			std::cout << n << ";" << (t / n)*10E6;
		}
		{
			auto c = create<Container2>(n);
			t = measure(std::bind(Tester<Container2>(), std::cref(c)));
			std::cout << ";" << (t / n)*10E6;
		}
		{
			auto c = create<Container3>(n);
			t = measure(std::bind(Tester<Container3>(), std::cref(c)));
			std::cout << ";" << (t / n)*10E6;
		}
		{
			auto c = create<Container4>(n);
			t = measure(std::bind(Tester<Container4>(), std::cref(c)));
			std::cout << ";" << (t / n)*10E6;
		}
		std::cout << std::endl;
	}
}

#include <boost/container/flat_set.hpp>
#include <set>

int main()
{
	typedef std::set<unsigned int>                   container_t1;
	typedef boost::container::flat_set<unsigned int> container_t2;
	typedef levelorder_vector<unsigned int>          container_t3;
	typedef chunked_levelorder_vector          container_t4;

	const auto v1 = create<chunked_levelorder_vector>(15);
	auto v2 = create<chunked_levelorder_vector>(16);
	const auto v3 = create<chunked_levelorder_vector>(255);
	const auto v4 = create<chunked_levelorder_vector>(256);
	auto a = v1.lower_bound(10);
	auto b = v3.lower_bound(100);
	auto c = v4.lower_bound(1000);

	test<
		binary_search,
		container_t1,
		container_t2,
		container_t3,
		container_t4>
		(
			"Binary search",
			"std::set",
			"boost::container::flat_set",
			"levelorder_vector",
			"chunekd_levelorder_vector"
			);
}
