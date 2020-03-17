#include "SolverFactory.hpp"
#include "PiyavskogoMethod.h"

std::unique_ptr<SolverMethod> SolverFactory::create(std::string_view method, double _r) {
    if (method == "PiyavskogoMethod")
    {
        return std::unique_ptr<SolverMethod>(new PiyavskogoMethod(_r));
    }
    else
    {
        throw std::logic_error("Not implemented");
        return std::unique_ptr<SolverMethod>();
    }
}
