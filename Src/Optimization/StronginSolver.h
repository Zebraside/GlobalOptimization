#include <memory>
#include "Function.h"
#include "Test.h"
#include "IFunction.h"
#include "SolverMethod.h"

class StronginSolverMethod : public SolverMethod
{
private:
    int op;
    double bestScorePoint;
    double bestScoreValue;
    double r;
    double L;
    double calculateLipschitzConstant();
    double minimumCharacteristicsValue;
    int minimumCharacteristicsIdx;
public:
    StronginSolverMethod(double _r);
    void performTest(IFunction& f, double a, double b, double epsilon, int n);
    void evaluateSolution();
    bool checkStopCriterion(double epsilon, int n);

    static std::unique_ptr<SolverMethod> create(double r) {
        return std::make_unique<StronginSolverMethod>(r);
    }
};
