#ifndef GLOBALOPTIMIZATION_FUNCTIONFACTORY_H
#define GLOBALOPTIMIZATION_FUNCTIONFACTORY_H

#include <memory>
#include "IFunction.h"
#include <map>

class FunctionFactory {
public:
    static std::shared_ptr<IFunction> create(std::string_view);
    static std::vector<std::string> getFunctions();
};

#endif //GLOBALOPTIMIZATION_FUNCTIONFACTORY_H
