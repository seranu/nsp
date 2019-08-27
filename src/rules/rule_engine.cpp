#include "rules/rule_engine.h"
#include "iconfiguration.h"
#include "solution.h"

namespace nsp {
std::unique_ptr<RuleEngine>
RuleEngine::createFromConfiguration(const IConfiguration &configuration) {
  return std::make_unique<RuleEngine>(configuration.rules());
}

Penalty RuleEngine::computePenalty(Solution &sol) const {
  Penalty p = 0;
  for (const auto &rule : m_rules) {
    p += rule->apply(sol.schedule());
  }
  sol.setPenalty(p);
  return p;
}

std::vector<ScheduleAction> RuleEngine::suggest(const Solution &sol) const {
  std::vector<ScheduleAction> result;
  for (const auto &rule : m_rules) {
    const auto &suggestions = rule->suggest(sol.schedule());
    result.insert(result.end(), suggestions.begin(), suggestions.end());
  }
  return result;
}

bool RuleEngine::valid(const Solution &) const {
  // TODO: implement
  return true;
}

} // namespace nsp
