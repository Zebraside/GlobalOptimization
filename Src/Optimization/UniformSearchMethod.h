#ifndef UNIFORM_SEARCH_METHOD_H
#define UNIFORM_SEARCH_METHOD_H


class UniformSearchMethod
{
private: 
	int idx;
public:
	UniformSearchMethod();
	void performTest(Function& f, double a, double b, double epsilon, int n);
	void evaluateSolution();
	bool checkStopCriterion(double epsilon, int n);
};
#endif