#pragma once

#include <memory>
#include <string_view>

#include "SolverMethod.h"

class SolverFactory {
    static std::unique_ptr<SolverMethod> create(std::string_view method, double _r);
};