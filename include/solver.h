#pragma once

#include <optional>
#include "solution.h"

namespace nsp
{
class Configuration;
class Solver
{
private:
    std::optional<Solution> m_bestSolutionSoFar;
    Configuration m_config;
public:
    Solver(const Configuration& config) 
        : m_config(config)
        {
        }
    void solve();
    void iterate();
    std::optional<Solution> bestSoFar() { return m_bestSolutionSoFar; }
};
}
