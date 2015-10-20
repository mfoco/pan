#pragma once

#include <pan/imaginary.h>

int main()
{
	auto x = 50.0_i;
	auto xf = 50.0_fi;
	auto xp = +50.0_i;
	assert(x == xp);
	assert(x != 50.0);
	auto xm = -50.0_i;
	assert(xm.value() == -50.0);
	assert(-xm == x);
	assert(xm == -x);

	auto a = 10 * x;
	auto b = 10.0 * xp;
	auto c = 10.0f * xf;
	auto d = x * 10;
	auto e = xp * 10.0;
	auto f = xf * 10.0f;
	auto g = a*b;
	auto h = b*a;
	auto i = xf * x;
	auto j = x * xf;

	assert(a == d);
	assert(b == e);
	assert(c == f);
	assert(g == h);
	assert(i == j);

	std::complex<double> q{ 1.0, 2.0 };
	q += x;
	q = x + q;

	auto q1 = q / x;
	auto q2 = 1.0 / x;
	auto q3 = x / q;
	auto q4 = x / 1.0;
	auto t = 1.0f + 5.0_i;

	return 0;
}

