#pragma once

#include <memory>
#include <string_view>

#include "SolverMethod.h"

class SolverFactory {
public:
    static std::unique_ptr<SolverMethod> create(std::string_view method, double _r);
    static std::vector<std::string> getMethods();
};