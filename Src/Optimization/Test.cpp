#include "Test.h"

Test::Test(double _point, double _functionValue)
{
	point = _point;
	functionValue = _functionValue;
}

bool compareByPoint(Test t1, Test t2)
{
	return t1.point < t2.point;
}

bool compareByValue(Test t1, Test t2)
{
	return t1.functionValue < t2.functionValue;
}