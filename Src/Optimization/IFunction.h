#pragma once

#include <vector>
#include <string>

class IFunction
{
public:
    virtual double operator()(double x) = 0;

    virtual std::vector<std::string> getParameterNames() const = 0;
};