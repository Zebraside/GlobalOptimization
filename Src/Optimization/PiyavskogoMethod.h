#pragma once
#include "IFunction.h"
#include "SolverMethod.h"

class PiyavskogoMethod : public SolverMethod
{
private:
	int op;
	double r;
	double L;
	double bestScorePoint;
	double bestScoreValue;
	double minimumCharacteristicsValue;
	int minimumCharacteristicsIdx;

	double calculateLipschitzConstant();

public:
	PiyavskogoMethod(double _r);

protected:
    void performTest(IFunction& f, double a, double b, double epsilon, int n);
    void evaluateSolution();
    bool checkStopCriterion(double epsilon, int n);
};