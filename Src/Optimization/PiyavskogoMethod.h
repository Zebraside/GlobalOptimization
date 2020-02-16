#pragma once
#include "Function.h"
#include "Test.h"

class PiyavskogoMethod
{
private:
	int op;
	double r;
	double L;

	double calculateLipschitzConstant();

public:
	PiyavskogoMethod(double _r);
	double solve(Function& f, double a, double b, double epsilon, int n);

protected:
	double solution;
};