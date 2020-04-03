#include "FunctionFactory.h"
#include "Function.h"


std::shared_ptr<IFunction> FunctionFactory::create(std::string_view method) {
    if (method == Function::getName()) {
        return std::make_shared<Function>();
    } else if (method == SinCosFunction::getName()) {
        return std::make_shared<SinCosFunction>();
    } else {
        throw std::logic_error("Not implemented");
    }
}

std::vector<std::string> FunctionFactory::getFunctions() {
    return {Function::getName(), SinCosFunction::getName()};
}

