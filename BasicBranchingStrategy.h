#pragma once
#include "IBranchingStrategy.h"
class BasicBranchingStrategy :
	public IBranchingStrategy
{
public:
	virtual IBranchingStrategy::v branching(std::vector<IBranchingStrategy::v>& V){
		size_t min = V[0].lower_bound;
		size_t nmin = 0;
		for (size_t i = 1; i < V.size(); ++i) {
			if (min > V[i].lower_bound) {
				min = V[i].lower_bound;
				nmin = i;
			}
		}
		auto result = V[nmin];
		// remove V[nmin]
		V[nmin] = std::move(V.back());
		V.pop_back();
		return result;
	}
};

