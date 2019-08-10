#pragma once

#include "iconfiguration.h"
#include "solution.h"

namespace nsp
{
class SolutionFactory
{
public:
  static Solution createRandomSolution(const IConfiguration& config);
  static Solution createFrom(const Solution& sol);
};
}
