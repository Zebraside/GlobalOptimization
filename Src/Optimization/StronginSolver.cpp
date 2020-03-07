#include "stdafx.h"
#include "StronginSolver.h"
#include <math.h>
#include <algorithm>

using namespace std;
void StronginSolverMethod::performTest(Function& f, double a, double b, double epsilon, int n)
{
    if(testHistory.size()==0)
    {
        testHistory.push_back(Test(a,f(a)));
        testHistory.push_back(Test(b,f(b)));
        if(f(a)<f(b))
        {
            bestScorePoint=a;
            bestScoreValue=f(a);
        }
        else
        {
            bestScorePoint=b;
            bestScoreValue=f(b);
        }
        L=calculateLipschitzConstant();
    }
    else
    {
        double newPoint=(testHistory[minimumCharacteristicsIdx].point+testHistory[minimumCharacteristicsIdx+1].point)/2.0
            -(testHistory[minimumCharacteristicsIdx+1].functionValue-testHistory[minimumCharacteristicsIdx].functionValue)/(2.0*L);

        testHistory.push_back(Test(newPoint,f(newPoint)));
        if(f(newPoint)<bestScoreValue)
        {
            bestScorePoint=newPoint;
            bestScoreValue=f(newPoint);
        }
        L=calculateLipschitzConstant();
    }

}
void StronginSolverMethod::evaluateSolution()
{
    std::sort(testHistory.begin(), testHistory.end(), compareByPoint);
    vector<double> characteristics;
    for(unsigned int i=0;i<testHistory.size()-1;i++)
    {
        double pointDiff=testHistory[i+1].point-testHistory[i].point;
        double valueDiff=testHistory[i+1].functionValue-testHistory[i].functionValue;
        double p=(testHistory[i].functionValue+testHistory[i+1].functionValue)/2.0
            -L*(pointDiff)*(1+pow(valueDiff/(L*pointDiff),2))/4.0;
        characteristics.push_back(p);
    }
    minimumCharacteristicsValue=*min_element(characteristics.begin(), characteristics.end());
    minimumCharacteristicsIdx=distance(characteristics.begin(),
        min_element(characteristics.begin(), characteristics.end()));
    solution=bestScorePoint;
}
bool StronginSolverMethod::checkStopCriterion(double epsilon, int n)
{
    return fabs(testHistory[minimumCharacteristicsIdx+1].point-testHistory[minimumCharacteristicsIdx].point)<epsilon;

}

double StronginSolverMethod::calculateLipschitzConstant()
{
    std::vector<double> value;
    for(unsigned int i=0;i<testHistory.size();i++)
    {
        for(unsigned int j=i+1;j<testHistory.size();j++)
        {
            double pointAbsDiff=fabs(testHistory[i].point-testHistory[j].point);
            double valueAbsDiff=fabs(testHistory[i].functionValue-testHistory[j].functionValue);
            value.push_back(valueAbsDiff/pointAbsDiff);
        }
    }
    double maxValue=*max_element(value.begin(), value.end());
    if(maxValue==0)
    {
        return 1;
    }
    else
    {
        return r*maxValue;
    }
}
StronginSolverMethod::StronginSolverMethod(double _r)
{
    op=0;
    r=_r;
}
