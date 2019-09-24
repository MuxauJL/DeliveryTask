#pragma once
#include <vector>
#include "IUpperBoundStrategy.h"
#include "ILowerBoundStrategy.h"
class IBranchingStrategy {
public:
	struct v
	{
		std::vector<size_t> permutation;
		size_t upper_bound;
		size_t lower_bound;
		v(std::vector<size_t> p, size_t u = -1, size_t l = -1) {
			permutation = p;
			upper_bound = u;
			lower_bound = l;
		}
	};
	virtual v branching(std::vector<v>& V) = 0;
};