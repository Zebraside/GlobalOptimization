#pragma once
#include "Function.h"
#include "Test.h"
#include <vector>

class PiyavskogoMethod
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
	void performTest(Function& f, double a, double b, double epsilon, int n);
	void evaluateSolution();
	bool checkStopCriterion(double epsilon, int n);
	double solve(Function& f, double a, double b, double epsilon, int n, std::vector<Test>& history, int& operationCount);

protected:
	double solution;
	std::vector<Test> testHistory;
};