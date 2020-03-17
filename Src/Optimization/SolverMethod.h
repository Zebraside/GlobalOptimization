#pragma once

#include "IFunction.h"
#include <vector>
#include "Test.h"

class SolverMethod
{
public:
    double solve(IFunction& f, double a, double b, double epsilon, int n, std::vector<Test>& history, int& operationCount);

protected:
    double solution;
    std::vector<Test> testHistory;
    virtual void performTest(IFunction& f, double a, double b, double epsilon, int n) = 0;
    virtual void evaluateSolution() = 0;
    virtual bool checkStopCriterion(double epsilon, int n) = 0;
};