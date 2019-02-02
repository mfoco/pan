/* Performance measurements of binary search with a flat binary tree structure.
*
* Copyright 2015 Joaquin M Lopez Munoz.
* Distributed under the Boost Software License, Version 1.0.
* (See accompanying file LICENSE_1_0.txt or copy at
* http://www.boost.org/LICENSE_1_0.txt)
*/

#pragma once

#include <algorithm>
#include <vector>

template<typename T>
class levelorder_vector
{
	typedef std::vector<T> vector;

public:
	typedef typename vector::value_type             value_type;
	typedef typename vector::reference              reference;
	typedef typename vector::const_reference        const_reference;
	typedef typename vector::const_iterator         iterator;
	typedef typename vector::const_iterator         const_iterator;
	typedef typename vector::difference_type        difference_type;
	typedef typename vector::size_type              size_type;

	levelorder_vector() {}
	levelorder_vector(const levelorder_vector& x) :impl(x.impl) {}
	levelorder_vector& operator=(const levelorder_vector& x) { impl = x.impl; return *this; }

	template<typename InputIterator>
	levelorder_vector(InputIterator first, InputIterator last)
	{
		vector aux(first, last);
		std::sort(aux.begin(), aux.end());
		impl = aux;
		insert(0, aux.size(), aux.begin());
	}

	const_iterator begin()const { return impl.begin(); }
	const_iterator end()const { return impl.end(); }
	const_iterator cbegin()const { return impl.cbegin(); }
	const_iterator cend()const { return impl.cend(); }
	friend bool    operator==(const levelorder_vector& x, const levelorder_vector& y)
	{
		return x.impl == y.impl;
	}
	friend bool    operator!=(const levelorder_vector& x, const levelorder_vector& y)
	{
		return x.impl != y.impl;
	}
	void           swap(levelorder_vector& x) { impl.swap(x.impl); }
	friend void    swap(levelorder_vector& x, levelorder_vector& y) { x.swap(y); }
	size_type      size()const { return impl.size(); }
	size_type      max_size()const { return impl.max_size(); }
	bool           empty()const { return impl.empty(); }

	const_iterator lower_bound(const T& x)const
	{
		size_type n = impl.size(), i = n, j = 0;
		while (j<n) {
			if (impl[j]<x) {
				j = 2 * j + 2;
			}
			else {
				i = j;
				j = 2 * j + 1;
			}
		}
		return begin() + i;
	}

private:
	void insert(size_type i, size_type n, const_iterator first)
	{
		if (n) {
			size_type h = root(n);
			impl[i] = *(first + h);
			insert(2 * i + 1, h, first);
			insert(2 * i + 2, n - h - 1, first + h + 1);
		}
	}

	size_type root(size_type n)
	{
		if (n <= 1)return 0;
		size_type i = 2;
		while (i <= n)i *= 2;
		return std::min(i / 2 - 1, n - i / 4);
	}

	vector impl;
};

class chunked_levelorder_vector
{
	struct chunk
	{
		int nodes;
		unsigned int data[15];
	};

	typedef std::vector<chunk> chunks;

public:
	const unsigned int *end() const { return nullptr; }

	size_t size() const
	{
		return data.empty() ? 0 : data[0].nodes;
	}

	template<typename InputIterator>
	chunked_levelorder_vector(InputIterator first, InputIterator last)
	{
		std::vector<unsigned int> aux(first, last);
		std::sort(aux.begin(), aux.end());
		if (aux.size() > 0) {
			size_t full_chunk_levels = 0;

			size_t level_size = 1;
			size_t full_block_count = 0;
			size_t remaining_items = aux.size();
			while (remaining_items > level_size*15)
			{
				remaining_items -= level_size * 15;
				full_block_count += level_size;
				level_size *= 16;
			}
			auto nonfull_block_count = std::min(level_size, remaining_items);
			data.resize(full_block_count + nonfull_block_count);
			insert(0, 0, aux.size(), aux.begin());
		}
	}

	const unsigned int *lower_bound(const unsigned int& x) const
	{
		const unsigned int *ret = nullptr;
		size_t chunk_index = 0;
		while (chunk_index < data.size()) {
			const chunk &current_chunk = data[chunk_index];
			size_t j = 0;
			size_t n = std::min(15, current_chunk.nodes);

			while (j < n) {
				if (current_chunk.data[j] < x) {
					j = 2 * j + 2;
				}
				else {
					ret = current_chunk.data + j;
					j = 2 * j + 1;
				}
			}
			chunk_index = chunk_index * 16 + (j - 14);
		}
		return ret;
	}

private:
	void insert(size_t chunk_index, size_t i, size_t n, std::vector<unsigned int>::const_iterator first)
	{
		if (n) {
			if (i == 0)
			{
				data[chunk_index].nodes = n;
			}
			size_t h = root(n);
			data[chunk_index].data[i] = first[h];
			int new_i = 2 * i + 1;
			if (new_i < 15) {
				insert(chunk_index, new_i, h, first);
				insert(chunk_index, new_i + 1, n - h - 1, first + h + 1);
			} 
			else
			{
				insert(chunk_index * 16 + new_i - 14, 0, h, first);
				insert(chunk_index * 16 + new_i - 13, 0, n - h - 1, first + h + 1);
			}
		}
	}

	size_t root(size_t n)
	{
		if (n <= 1) return 0;
		size_t i = 2;
		while (i <= n) i *= 2;
		return std::min(i / 2 - 1, n - i / 4);
	}

	chunks data;
};
