#pragma once

class IFunction
{
public:
    virtual double operator()(double x) = 0;
};