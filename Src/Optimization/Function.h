#pragma once
#include <math.h>
#include "IFunction.h"
#include <vector>
#include <map>
#include <string>

class Function : public IFunction
{
public:
    Function() : IFunction({{"a", 10.}, {"b",2.}, {"c",11.}, {"d" ,5.}}) {
    }

	double operator()(double x) override {
		return variables["a"] * sin(variables["b"] * x) + variables["c"] * cos(variables["d"] * x);
	};

    static std::string getName() { return "ExampleFunction";}
};

class SinCosFunction : public IFunction
{
public:
    SinCosFunction() : IFunction({{"a", 1.0}, {"b", 1.0}}) {}

    static std::string getName() { return "SinCosFunction";}

    virtual double operator()(double x) override {
        return sin(variables["a"] * x) * cos(variables["b"] * x);
    }
};