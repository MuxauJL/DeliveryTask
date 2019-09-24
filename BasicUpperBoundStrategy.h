#pragma once
#include "BoundStrategy.h"
#include "IUpperBoundStrategy.h"
class BasicUpperBoundStrategy :
	public IUpperBoundStrategy, BoundStrategy
{
public:
	virtual size_t upper_bound(
		std::vector<size_t> permutation,			// permutation[i]  from {1, 2, ... , n}
		const std::vector<double>& deadlines,	    // deadlines[i]: i from {0, 1, ... ,n - 1}
		const std::vector<std::vector<double>>& T)  // T[i][j]: i,j    from {0, 1, 2, ... , n}
	{
		auto unused = get_unused(permutation, deadlines.size());
		// find the nearest, first row and column don't check
		for (size_t r = permutation.size(); r < T.size() - 1; ++r) {
			size_t current = permutation.back();
			double min = INTMAX_MAX;
			size_t nmin = -1;
			for (size_t c = 0; c < unused.size(); ++c) {
				if (T[current][unused[c]] < min) {
					min = T[current][unused[c]];
					nmin = c;
				}
			}
			permutation.emplace_back(unused[nmin]);
			for (size_t i = nmin; i < unused.size() - 1; ++i)
				unused[i] = unused[i + 1];
			//unused[nmin] = std::move(unused.back());
			unused.pop_back();
		}
		return calculate(permutation, deadlines, T).first;
	}
};

