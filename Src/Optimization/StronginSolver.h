#ifndef STRONGIN_SOLVER_METHOD_H
#define STRONGIN_SOLVER_METHOD_H

#include "Function.h"
#include "Test.h"

class StronginSolverMethod
{
private:
    int op;
    double bestScorePoint;
    double bestScoreValue;
    double r;
    double L;
    double calculateLipschitzConstant();
    double minimumCharacteristicsValue;
    int minimumCharacteristicsIdx;
public:
    StronginSolverMethod(double _r);
    void performTest(Function& f, double a, double b, double epsilon, int n);
    void evaluateSolution();
    bool checkStopCriterion(double epsilon, int n);
};
#endif