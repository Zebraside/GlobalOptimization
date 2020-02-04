#pragma once

#include <vector>

#include "IFunction.h"

class ISolver
{
public:
    virtual double solve(const IFunction& f, double a, double b, double epsilon, int n) = 0;
};