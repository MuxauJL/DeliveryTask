#pragma once
#include "ILowerBoundStrategy.h"
#include "BoundStrategy.h"

class BasicLowerBoundStrategy :
	public ILowerBoundStrategy, BoundStrategy
{
public:
	virtual size_t lower_bound(
		std::vector<size_t> permutation,			// permutation[i]  from {1, 2, ... , n}
		const std::vector<double>& deadlines,	    // deadlines[i]: i from {0, 1, ... ,n - 1}
		const std::vector<std::vector<double>>& T)  // T[i][j]: i,j    from {0, 1, 2, ... , n}
	{
		auto [criterion, time] = calculate(permutation, deadlines, T);

		size_t last = permutation.back();
		auto unused = get_unused(permutation, deadlines.size());
		for (size_t c = 0; c < unused.size(); ++c) {
			if (time + T[last][unused[c]] > deadlines[unused[c] - 1])
				++criterion;
		}
		return criterion;
	}
};
