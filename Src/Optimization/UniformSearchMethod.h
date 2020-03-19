#pragma once
#include "IFunction.h"
#include "SolverMethod.h"

class UniformSearchMethod : public SolverMethod
{
private: 
	int idx;
public:
	UniformSearchMethod();
	void performTest(IFunction& f, double a, double b, double epsilon, int n);
	void evaluateSolution();
	bool checkStopCriterion(double epsilon, int n);
};
