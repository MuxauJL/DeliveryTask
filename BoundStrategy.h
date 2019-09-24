#pragma once
#include <vector>
class BoundStrategy {
public:
	bool is_contained(const std::vector<size_t>& permutation, size_t value) {
		for (auto e : permutation)
			if (value == e)
				return true;
		return false;
	}
	std::vector<size_t> get_unused(const std::vector<size_t>& permutation, size_t n) {
		std::vector<size_t> result;
		for (size_t i = 0; i < n; ++i) 
			if (!is_contained(permutation, i + 1))
				result.emplace_back(i + 1);
		return result;
	}
	std::pair<size_t, double> calculate(
		std::vector<size_t> permutation,    // permutation[i]  from {1, 2, ... , n}
		std::vector<double> deadlines,	    // deadlines[i]: i from {0, 1, ... ,n - 1}
		std::vector<std::vector<double>> T) // T[i][j]: i,j    from {0, 1, 2, ... , n}
	{
		size_t criterion = 0;
		double time = T[0][permutation[0]];
		if (time > deadlines[permutation[0] - 1])
			++criterion;
		for (size_t j = 0; j < permutation.size() - 1; ++j) {
			time += T[permutation[j]][permutation[j + 1]];
			if (time > deadlines[permutation[j + 1] - 1])
				++criterion;
		}
		return std::make_pair(criterion, time);
	}
};