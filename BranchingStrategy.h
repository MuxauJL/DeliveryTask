#pragma once
#include "IBranchingStrategy.h"
class BranchingStrategy :
	public IBranchingStrategy
{
public:
	virtual IBranchingStrategy::v branching(std::vector<IBranchingStrategy::v>& V) {
		size_t min_range = V[0].upper_bound - V[0].lower_bound;
		size_t nmin_range = 0;
		for (size_t i = 1; i < V.size(); ++i) {
			if (min_range > V[i].upper_bound - V[i].lower_bound) {
				min_range = V[i].upper_bound - V[i].lower_bound;
				nmin_range = i;
			}
		}
		size_t min_upper = INT_MAX;
		size_t nmin_upper = -1;
		for (size_t i = 0; i < V.size(); ++i) {
			if ((min_upper > V[i].upper_bound) && ((V[i].upper_bound - V[i].lower_bound) - min_range <= 1)) {
				min_upper = V[i].upper_bound;
				nmin_upper = i;
			}
		}
		auto result = V[nmin_upper];
		// remove V[nmin_upper]
		V[nmin_upper] = std::move(V.back());
		V.pop_back();
		return result;
	}
};