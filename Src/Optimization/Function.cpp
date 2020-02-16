#include "Function.h"

Function::Function(double _a, double _b, double _c, double _d)
{
	a = _a;
	b = _b;
	c = _c;
	d = _d;
}
double Function::operator()(double x)
{
	return calculate(x);
}

double Function::calculate(double x)
{
	return a * sin(b*x) + c * cos(d*x);
}