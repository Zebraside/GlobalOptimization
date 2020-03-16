#pragma once

#include <vector>

#include "IFunction.h"
#include "Test.h"

class ISolver
{
public:
    virtual void performTest(IFunction& f, double a, double b, double epsilon, int n) = 0;
    virtual void evaluateSolution() = 0;
    virtual bool checkStopCriterion(double epsilon, int n) = 0;
    virtual double solve(IFunction& f, double a, double b, double epsilon, int n, std::vector<Test>& history, int& operationCount) = 0;

protected:
    double solution;
    std::vector<Test> testHistory;
};