#pragma once
#include "IFunction.h"
#include "Test.h"
#include <vector>
#include "ISolver.h"

class PiyavskogoMethod : public ISolver
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
	void performTest(IFunction& f, double a, double b, double epsilon, int n);
	void evaluateSolution();
	bool checkStopCriterion(double epsilon, int n);
    double PiyavskogoMethod::solve(IFunction& f, double a, double b, double epsilon, int n, std::vector<Test>& history, int& operationCount);

protected:
	double solution;
	std::vector<Test> testHistory;
};