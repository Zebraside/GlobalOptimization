#ifndef UNIFORM_SEARCH_METHOD_H
#define UNIFORM_SEARCH_METHOD_H

#include <IFunction.h>
#include <memory>
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

    static std::unique_ptr<SolverMethod> create(double r) {
        return std::make_unique<UniformSearchMethod>();
    }
};
#endif