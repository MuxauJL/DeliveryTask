#include "DeliveryTask.h"
#include <stdexcept>

DeliveryTask::DeliveryTask(size_t size, std::vector<double> deadlines, std::vector<std::vector<double>> times):x(IBranchingStrategy::v({})) {
	if (deadlines.size() != size || times.size() != size + 1 || times[0].size() != size + 1)
		throw std::invalid_argument("Incorrect size of arguments");
	n = size;
	this->deadlines = deadlines;
	T = times;
	count = 0;
	record = size;
}

void DeliveryTask::branching(IUpperBoundStrategy* upper, ILowerBoundStrategy* lower, IBranchingStrategy* branching_strategy)
{
	auto v = branching_strategy->branching(V);
	// add representatives of v
	auto is_contained = [&v](size_t value) {
		for (auto e : v.permutation)
			if (value == e)
				return true;
		return false;
	};
	auto get_unused = [&is_contained](size_t n) {
		std::vector<size_t> result;
		for (size_t i = 0; i < n; ++i)
			if (!is_contained(i + 1))
				result.emplace_back(i + 1);
		return result;
	};
	auto unused = get_unused(deadlines.size());
	for (size_t i = 0; i < unused.size(); ++i) {
		++count;
		v.permutation.emplace_back(unused[i]);
		V.emplace_back(v.permutation,
			upper->upper_bound(v.permutation, deadlines, T),
			lower->lower_bound(v.permutation, deadlines, T));
		v.permutation.pop_back();
	}
}

void DeliveryTask::clipping()
{
	// record updating
	size_t nrecord = -1;
	for (size_t i = 0; i < V.size(); ++i)
		if (record >= V[i].upper_bound) {
			record = V[i].upper_bound;
			if (!(record == x.upper_bound && V[i].permutation.size() < x.permutation.size()))
				x = V[i];
			nrecord = i;
		}
	// if V contains record then place it at the begin of V and don't check it
	size_t i;
	if (nrecord != -1) {
		if(V[0].upper_bound != record)
			std::swap(V[nrecord], V[0]);
		i = 1;
	}
	else { // it happens when record is a leaf and it is chosen by branching strategy
		// check from the first position
		i = 0;
	}
	for ( ; i < V.size(); ++i)
		if (V[i].lower_bound >= record) {
			// remove V[i]
			V[i] = std::move(V.back());
			V.pop_back();
			--i;
		}
}

IBranchingStrategy::v DeliveryTask::solve(IUpperBoundStrategy* upper, ILowerBoundStrategy* lower, IBranchingStrategy* branching_strategy)
{
	V.reserve(n);
	for (size_t i = 0; i < deadlines.size(); ++i)
		V.emplace_back(IBranchingStrategy::v({ i + 1 }));
	for (auto& v : V) {
		v.upper_bound = upper->upper_bound(v.permutation, deadlines, T);
		v.lower_bound = lower->lower_bound(v.permutation, deadlines, T);
	}
	IBranchingStrategy::v v = IBranchingStrategy::v({});
	while (true) {
		branching(upper, lower, branching_strategy);
		clipping();
		if (V.size() == 0)
			if (x.permutation.size() == n)
				break;
			else V.emplace_back(x);
	}
	return x;
}
