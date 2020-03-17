#pragma once
#include <math.h>
#include "IFunction.h"

class Function : public IFunction
{
	double a, b, c, d;

public:
	Function(double _a, double _b, double _c, double _d);
	double operator()(double x);

private:
	double calculateExample(double x);

};
