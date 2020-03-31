#pragma once
#include <math.h>
#include "IFunction.h"
#include <vector>
#include <map>
#include <string>

class Function : public IFunction
{
	std::map<std::string, double> variables;
	std::vector<std::string> varsNames = { "a", "b", "c", "d"};

public:
    Function() {
        variables = {{"a", 10.}, {"b",2.}, {"c",11.}, {"d" ,5.}};
    }

	Function(std::map<std::string, double>& varsValues) {
	    variables = varsValues;
	};

	double operator()(double x) {
		return variables["a"] * sin(variables["b"] * x) + variables["c"] * cos(variables["d"] * x) + variables["z"];
	};

    std::vector<std::string> getParameterNames() const override {
        return varsNames;
    }

    static std::string getName() {return "ExampleFunction";}
};