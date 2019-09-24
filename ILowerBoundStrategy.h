#pragma once
#include <vector>
class ILowerBoundStrategy {
public:
	virtual size_t lower_bound(
		std::vector<size_t> permutation,
		const std::vector<double>& deadlines,
		const std::vector<std::vector<double>>& T) = 0;
};