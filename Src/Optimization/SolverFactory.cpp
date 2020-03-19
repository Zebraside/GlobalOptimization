#include "SolverFactory.hpp"
#include "PiyavskogoMethod.h"
#include "StronginSolver.h"
#include "UniformSearchMethod.h"

std::unique_ptr<SolverMethod> SolverFactory::create(std::string_view method, double _r) {
    if (method == "PiyavskogoMethod")
    {
        return std::unique_ptr<SolverMethod>(new PiyavskogoMethod(_r));
    }
    else if (method == "StronginSolverMethod")
    {
        return std::unique_ptr<SolverMethod>(new StronginSolverMethod(_r));
    }
    else if (method == "UniformSearchMethod")
    {
        return std::unique_ptr<SolverMethod>(new UniformSearchMethod());
    }
    else
    {
        throw std::logic_error("Not implemented");
        return std::unique_ptr<SolverMethod>();
    }
}
