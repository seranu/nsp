#pragma once

#include <memory>
#include <optional>
#include "iconfiguration.h"
#include "rules/rule_engine.h"
#include "solution.h"

namespace nsp
{
class Solver
{
private:
    std::optional<Solution> m_bestSolutionSoFar;
    std::unique_ptr<IConfiguration> m_config;
    std::unique_ptr<RuleEngine> m_ruleEngine;

   public:
    Solver(std::unique_ptr<IConfiguration> pConfig)
        : m_config(std::move(pConfig)),
          m_ruleEngine(RuleEngine::createFromConfiguration(*m_config)) {}

    void solve(int numIterations = 100);
    Solution iterate(const Solution& solution);
    std::optional<Solution> bestSoFar() { return m_bestSolutionSoFar; }
};
}
