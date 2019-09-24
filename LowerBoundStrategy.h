#pragma once
#include "ILowerBoundStrategy.h"
#include "BoundStrategy.h"
class LowerBoundStrategy :
	public ILowerBoundStrategy, BoundStrategy
{
public:
	virtual size_t lower_bound(
		std::vector<size_t> permutation,			// permutation[i]  from {1, 2, ... , n}
		const std::vector<double>& deadlines,	    // deadlines[i]: i from {0, 1, ... ,n - 1}
		const std::vector<std::vector<double>>& T)  // T[i][j]: i,j    from {0, 1, 2, ... , n}
	{
		auto [criterion, time] = calculate(permutation, deadlines, T);
		auto unused = get_unused(permutation, deadlines.size());
		size_t last = permutation.back();
		std::vector<size_t> not_yet;
		for (size_t c = 0; c < unused.size(); ++c)
			if (time + T[last][unused[c]] > deadlines[unused[c] - 1]) {
				++criterion;
			}
			else not_yet.emplace_back(unused[c]);

		auto current = permutation.back();
		if (deadlines.size() - permutation.size() >= 2) {
			size_t min_violation = INT_MAX;
			for (size_t c = 0; c < not_yet.size(); ++c) {
				auto time_to_c = time + T[current][not_yet[c]];
				size_t count_of_violation = 0;
				for (size_t i = 0; i < not_yet.size(); ++i)
					if (time_to_c + T[not_yet[c]][not_yet[i]] > deadlines[not_yet[i] - 1])
						++count_of_violation;
				if (min_violation > count_of_violation)
					min_violation = count_of_violation;
			}
			criterion += min_violation;
		}
		return criterion;
	}
};