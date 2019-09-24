#pragma once
#include "IUpperBoundStrategy.h"
#include "BoundStrategy.h"
class UpperBoundStrategy :
	public IUpperBoundStrategy, BoundStrategy {
public:
	virtual size_t upper_bound(
		std::vector<size_t> permutation,			// permutation[i]  from {1, 2, ... , n}
		const std::vector<double>& deadlines,	    // deadlines[i]: i from {0, 1, ... ,n - 1}
		const std::vector<std::vector<double>>& T)  // T[i][j]: i,j    from {0, 1, 2, ... , n}
	{
		auto [criterion, time] = calculate(permutation, deadlines, T);
		auto unused = get_unused(permutation, deadlines.size());
		for (size_t r = permutation.size(); r < T.size() - 1; ++r) {
			size_t current = permutation.back();
			size_t min_violation = INTMAX_MAX;
			size_t nmin_violation = 0;
			double min_deadline = INTMAX_MAX;
			size_t nmin_deadline = 0;
			size_t count_of_violation = -1;
			for (size_t c = 0; c < unused.size(); ++c) {
				auto time_to_c = time + T[current][unused[c]];
				count_of_violation = 0;
				if ((double)deadlines[unused[c] - 1] - time >= 0		         // not violated yet
					&& deadlines[unused[c] - 1] < min_deadline				     // may be min
					&& time_to_c <= deadlines[unused[c] - 1])					 // won't be violated
				{
					min_deadline = deadlines[unused[c] - 1];
					nmin_deadline = c;
				}
				for (size_t i = 0; i < unused.size();++i)
					if (time_to_c > deadlines[unused[i] - 1])
						++count_of_violation;
				if (min_violation > count_of_violation) {
					min_violation = count_of_violation;
					nmin_violation = c;
				}
			}
			if (count_of_violation<=1) {
				time += T[current][unused[nmin_violation]];
				permutation.emplace_back(unused[nmin_violation]);
				//unused[nmin_violation] = std::move(unused.back());
				for (size_t i = nmin_violation; i < unused.size() - 1; ++i)
					unused[i] = unused[i + 1];
			}
			else {
				time += T[current][unused[nmin_deadline]];
				permutation.emplace_back(unused[nmin_deadline]);
				//unused[nmin_deadline] = std::move(unused.back());
				for (size_t i = nmin_deadline; i < unused.size() - 1; ++i)
					unused[i] = unused[i + 1];
			}
			unused.pop_back();
		}
		return calculate(permutation, deadlines, T).first;
	}
};