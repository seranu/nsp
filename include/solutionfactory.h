#pragma once

#include "solution.h"
#include "configuration.h"

namespace nsp
{
class SolutionFactory
{
public:
    static Solution createRandomSolution(const Configuration& config);
    static Solution createFrom(const Solution& sol);
};
}
