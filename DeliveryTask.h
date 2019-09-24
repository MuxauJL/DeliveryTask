#pragma once
#include <vector>
#include "IBranchingStrategy.h"
class DeliveryTask
{
private:
	// initial parameters
	size_t n;
	std::vector<double> deadlines;
	std::vector<std::vector<double>> T;

	// variable parameters
	// x[i] - number of the order (city), which we deliver (visit) in step i

	std::vector<IBranchingStrategy::v> V; // the current record is always in V[0]
	IBranchingStrategy::v x;
	size_t record;
	size_t count;
public:
	size_t get_count() { return count; }
	DeliveryTask(size_t size, std::vector<double> deadlines, std::vector<std::vector<double>> times);
	~DeliveryTask() = default;
	IBranchingStrategy::v solve(IUpperBoundStrategy*, ILowerBoundStrategy*, IBranchingStrategy*);
	void branching(IUpperBoundStrategy*, ILowerBoundStrategy*, IBranchingStrategy*);
	void clipping();
};

