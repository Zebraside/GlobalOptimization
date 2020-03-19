#include <math.h>
#include <algorithm>
#include "SolverMethod.h"
#include "IFunction.h"

double SolverMethod::solve(IFunction& f, double a, double b, double epsilon, int n, std::vector<Test>& history, int& operationCount)
{
    operationCount = 0;
    while (true)
    {
        performTest(f, a, b, epsilon, n);
        operationCount++;
        evaluateSolution();
        if (checkStopCriterion(epsilon, n) == true)
        {
            break;
        }
    }

    history = testHistory;
    return solution;
}