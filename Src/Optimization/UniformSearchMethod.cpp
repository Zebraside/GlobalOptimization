// #include "stdafx.h"
#include "UniformSearchMethod.h"
#include <algorithm>

void UniformSearchMethod::performTest(IFunction& f, double a, double b, double epsilon, int n)
{
	testHistory.push_back(Test(a+idx*(b-a)/n,f(a+idx*(b-a)/n)));
	idx++;
}
void UniformSearchMethod::evaluateSolution()
{
	std::sort(testHistory.begin(), testHistory.end(), compareByValue);
	solution=testHistory[0].point;
}
bool UniformSearchMethod::checkStopCriterion(double epsilon, int n)
{
	return idx>n;
}

UniformSearchMethod::UniformSearchMethod()
{
	idx=0;
}