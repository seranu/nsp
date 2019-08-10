#pragma once

#include "solution.h"
#include <memory>
#include <optional>

namespace nsp
{
class IConfiguration;
class Solver
{
private:
    std::optional<Solution> m_bestSolutionSoFar;
    std::unique_ptr<IConfiguration> m_config;

  public:
    Solver(std::unique_ptr<IConfiguration> pConfig)
        : m_config(std::move(pConfig)) {}
    void solve() {}
    void iterate() {}
    std::optional<Solution> bestSoFar() { return m_bestSolutionSoFar; }
};
}
