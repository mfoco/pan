#pragma once

#include "expr.hpp"

#include <string>

namespace pan::expr
{
	template<int N> [[nodiscard]] std::string to_string(const var<N>& v)
	{
		return std::string("x") + std::to_string(N);
	}

	template<typename L, typename R> [[nodiscard]] std::string to_string(const sumOp<L, R>& op)
	{
		return "(" + to_string(op.l) + " + " + to_string(op.r) + ")";
	}

	template<typename L, typename R> [[nodiscard]] std::string to_string(const subOp<L, R>& op)
	{
		return "(" + to_string(op.l) + " - " + to_string(op.r) + ")";
	}

	template<typename L, typename R> [[nodiscard]] std::string to_string(const mulOp<L, R>& op)
	{
		return "(" + to_string(op.l) + " * " + to_string(op.r) + ")";
	}

	template<typename L, typename R> [[nodiscard]] std::string to_string(const divOp<L, R>& op)
	{
		return "(" + to_string(op.l) + " / " + to_string(op.r) + ")";
	}
}
