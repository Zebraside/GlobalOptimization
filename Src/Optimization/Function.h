#pragma once
#include <math.h>
#include "IFunction.h"
#include <vector>
#include <map>
#include <string>

class Function : public IFunction
{
	std::map<std::string, double> variables;
	std::vector<std::string> varsNames = { "a", "b", "c", "d" };

public:
	Function(std::vector<double> _varsValues) {
		for (int i = 0; i < varsNames.size(); ++i) {
			variables[varsNames[i]] = _varsValues[i];
		}
	};

	double operator()(double x) {
		return variables["a"] * sin(variables["b"] * x) + variables["c"] * cos(variables["d"] * x);
	};

	std::vector<std::string> getNameParams() {
		return varsNames;
	};

};
