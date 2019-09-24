#pragma once
#include <vector>
class IUpperBoundStrategy {
public:
	virtual size_t upper_bound(
		std::vector<size_t> permutation,
		const std::vector<double>& deadlines,
		const std::vector<std::vector<double>>& T) = 0;
};