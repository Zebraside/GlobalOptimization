#pragma once
class Test
{
public:
	Test(double _point, double _functionValue);
	double point, functionValue;
};

bool compareByPoint(Test t1, Test t2);
bool compareByValue(Test t1, Test t2);