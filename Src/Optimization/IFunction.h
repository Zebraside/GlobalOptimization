#pragma once

#include <vector>
#include <string>
#include <map>

class IFunction
{
public:
    explicit IFunction(const std::map<std::string, double>& variables) : variables(variables) {}
    virtual double operator()(double x) = 0;

    virtual std::vector<std::string> getParameterNames() const {
        std::vector<std::string> varsNames;
        for (auto& [key, value] : variables) {
            varsNames.push_back(key);
        }
        return varsNames;
    }

    virtual void setParams(const std::map<std::string, double> &params) {
        variables = params;
    }

protected:
    std::map<std::string, double> variables;
};