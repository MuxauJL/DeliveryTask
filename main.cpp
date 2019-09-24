#include "DeliveryTask.h"
#include "BasicBranchingStrategy.h"
#include "BasicLowerBoundStrategy.h"
#include "BasicUpperBoundStrategy.h"
#include "UpperBoundStrategy.h"
#include "LowerBoundStrategy.h"
#include "BranchingStrategy.h"
#include <iostream>
#include <fstream>

int main() {
	std::string dir = "Task2\\";
	std::vector<std::string> files = {
		"task_2_01_n3.txt",
		"task_2_02_n3.txt",
		"task_2_03_n10.txt",
		"task_2_04_n10.txt",
		"task_2_05_n10.txt",
		"task_2_06_n15.txt",
		"task_2_07_n15.txt",
		"task_2_08_n50.txt",
		"task_2_09_n50.txt",
		"task_2_10_n50.txt"
	};

	size_t n;
	std::vector<double> deadlines;
	std::vector<std::vector<double>> T;
	std::ofstream results;
	results.open("results.csv");
	if (results.is_open())
	{
		double total = 0;
		for (size_t i = 0; i < files.size(); ++i) {
			std::ifstream in(dir + files[i]);
			if (in.is_open()) {
				in >> n;
				deadlines = std::vector<double>();
				deadlines.reserve(n);
				for (size_t j = 0; j < n; ++j) {
					double time;
					in >> time;
					deadlines.emplace_back(time);
				}
				T = std::vector<std::vector<double>>();
				T.reserve(n + 1);
				for (size_t r = 0; r < n + 1; ++r) {
					T.emplace_back(std::vector<double>());
					T.back().reserve(n + 1);
					for (size_t c = 0; c < n + 1; ++c) {
						double time;
						in >> time;
						T.back().emplace_back(time);
					}
				}
			}
			in.close();
			DeliveryTask task(n, deadlines, T);
			DeliveryTask my_task(n, deadlines, T);
			BasicUpperBoundStrategy upper;
			BasicLowerBoundStrategy lower;
			UpperBoundStrategy my_upper;
			LowerBoundStrategy my_lower;
			BasicBranchingStrategy branching;
			BranchingStrategy my_branching;
			auto v = task.solve(&upper, &lower, &branching);
			auto my_v = my_task.solve(&upper, &my_lower, &branching);
			std::cout << i + 1 << ").\n";
			std::cout << v.lower_bound << " " << v.upper_bound << " " << task.get_count() << '\n';
			std::cout << my_v.lower_bound << " " << my_v.upper_bound << " " << my_task.get_count() << '\n';
			for (auto e : v.permutation)
				std::cout << e << " ";
			std::cout << '\n';
			for (auto e : my_v.permutation)
				std::cout << e << " ";
			std::cout << '\n';

			double basic_count = task.get_count();
			double my_count = my_task.get_count();
			total += (basic_count - my_count) / basic_count;
			results << i + 1 << ";" << basic_count << ";" << my_count << ";" << (basic_count - my_count) / basic_count*100 << ";" << std::endl;
		}
		results << ";;;" << total / 10*100;
	}
	results.close();
	return 0;
}