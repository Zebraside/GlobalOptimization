#include "PiyavskogoMethod.h"

#include <math.h>
#include <algorithm>

PiyavskogoMethod::PiyavskogoMethod(double _r)
{
	op = 0;
	r = _r;
}


void PiyavskogoMethod::performTest(IFunction& f, double a, double b, double epsilon, int n)
{
	if (testHistory.size() == 0)
	{
		testHistory.push_back(Test(a, f(a)));
		testHistory.push_back(Test(b, f(b)));
		if (f(a) < f(b))
		{
			bestScorePoint = a;
			bestScoreValue = f(a);
		}
		else
		{
			bestScorePoint = b;
			bestScoreValue = f(b);
		}

		L = calculateLipschitzConstant();
	}
	else
	{
		double points_part = (testHistory[minimumCharacteristicsIdx].point + testHistory[minimumCharacteristicsIdx + 1].point) / 2.0;
		double value_part = (testHistory[minimumCharacteristicsIdx + 1].functionValue - testHistory[minimumCharacteristicsIdx].functionValue) / (2.0 * L);
		double newPoint = points_part - value_part;

		testHistory.push_back(Test(newPoint, f(newPoint)));
		if (f(newPoint) < bestScoreValue)
		{
			bestScorePoint = newPoint;
			bestScoreValue = f(newPoint);
		}

		L = calculateLipschitzConstant();
	}

}

void PiyavskogoMethod::evaluateSolution()
{
	std::sort(testHistory.begin(), testHistory.end(), compareByPoint);
	std::vector<double> characteristics;
	for (unsigned int i = 0; i < testHistory.size() - 1; i++)
	{
		double value_part = (testHistory[i].functionValue + testHistory[i + 1].functionValue) / 2.0;
		double point_part = (testHistory[i + 1].point - testHistory[i].point) / 2.0;
		double p = value_part - L * point_part;
		characteristics.push_back(p);
	}

	minimumCharacteristicsValue = *min_element(characteristics.begin(), characteristics.end());
	minimumCharacteristicsIdx = distance(characteristics.begin(),
		min_element(characteristics.begin(), characteristics.end()));
	solution = bestScorePoint;
}

bool PiyavskogoMethod::checkStopCriterion(double epsilon, int n)
{
	return fabs(minimumCharacteristicsValue - bestScoreValue) < epsilon;
}

double PiyavskogoMethod::calculateLipschitzConstant()
{
	std::vector<double> value;
	for (unsigned int i = 0; i < testHistory.size(); i++)
	{
		for (unsigned int j = i + 1; j < testHistory.size(); j++)
		{
			double pointAbsDiff = fabs(testHistory[i].point - testHistory[j].point);
			double valueAbsDiff = fabs(testHistory[i].functionValue - testHistory[j].functionValue);
			value.push_back(valueAbsDiff / pointAbsDiff);
		}
	}

	double maxValue = *max_element(value.begin(), value.end());
	
	if (maxValue == 0)
	{
		return 1;
	}
	else
	{
		return r * maxValue;
	}
}