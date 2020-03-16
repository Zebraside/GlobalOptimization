#pragma once

#include <memory>
#include <string_view>

#include "ISolver.h"

class SolverFactory {
    static std::unique_ptr<ISolver> create(std::string_view method, double _r);
};