#include "PiyavskogoMethod.h"

using namespace std;


PiyavskogoMethod::PiyavskogoMethod(double _r)
{
	op = 0;
	r = _r;
}

double PiyavskogoMethod::solve(Function& f, double a, double b, double epsilon, int n)
{
	while (true)
	{
		// TODO: algorithm
		L = calculateLipschitzConstant();
	}

	return solution;
}

double PiyavskogoMethod::calculateLipschitzConstant()
{
	// TODO: define how to better calculate Lipschitz Constant

	return 1;
}
