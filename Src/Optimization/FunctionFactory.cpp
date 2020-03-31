#include "FunctionFactory.h"
#include "Function.h"



std::shared_ptr<IFunction> FunctionFactory::create(std::string_view method, std::map<std::string, double> params) {
    if (method == Function::getName()) {
        return std::make_shared<Function>(params);
    } else if (method == AnotherFunction::getName()) {
        return std::make_shared<AnotherFunction>(params);
    } else {
        throw std::logic_error("Not implemented");
    }
}

std::shared_ptr<IFunction> FunctionFactory::create(std::string_view method) {
    if (method == Function::getName()) {
        return std::make_shared<Function>();
    } else if (method == AnotherFunction::getName()) {
        return std::make_shared<AnotherFunction>();
    } else {
        throw std::logic_error("Not implemented");
    }
}

std::vector<std::string> FunctionFactory::getFunctions() {
    return {Function::getName(), AnotherFunction::getName()};

}

