#include "rules/rule_engine.h"
#include "iconfiguration.h"
#include "rules/include_all_rules.h"
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

const std::unordered_map<Day, int> &RuleEngine::roosterScores() const {
  if (m_rooterScores.empty()) {
    for (const auto &rule : m_rules) {
      if (rule->type() == RuleType::RoosterRequirement) {
        const auto *rrRule =
            dynamic_cast<const RoosterRequirementRule *>(rule.get());
        assert(rrRule);
        const auto &[day, value] = rrRule->value();
        m_rooterScores[day] = value;
      }
    }
  }
  return m_rooterScores;
}

} // namespace nsp
