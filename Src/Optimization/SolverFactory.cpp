#include "SolverFactory.hpp"
#include "PiyavskogoMethod.h"
#include "StronginSolver.h"
#include "UniformSearchMethod.h"

std::unique_ptr<SolverMethod> SolverFactory::create(std::string_view method, double _r) {
    if (method == "PiyavskogoMethod") {
        return PiyavskogoMethod::create(_r);
    } else if (method == "StronginaMethod") {
        return StronginSolverMethod::create(_r);
    } else if (method == "UniformMethod") {
        return UniformSearchMethod::create(_r);
    }
    else {
        throw std::logic_error("Not implemented");
        return std::unique_ptr<SolverMethod>();
    }
}

std::vector<std::string> SolverFactory::getMethods() {
    return {"PiyavskogoMethod", "StronginaMethod", "UniformMethod"};

}
