#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include "irule.h"
#include "nsp_types.h"
#include "schedule_action.h"

namespace nsp
{
class Solution;
class IConfiguration;
class RuleEngine
{
private:
  std::vector<std::shared_ptr<IRule>> m_rules;
  mutable std::unordered_map<Day, int> m_rooterScores;

 public:
  static std::unique_ptr<RuleEngine>
  createFromConfiguration(const IConfiguration &);
  RuleEngine(std::vector<std::shared_ptr<IRule>> rules)
      : m_rules(move(rules)) {}
  Penalty computePenalty(Solution &) const;
  bool valid(const Solution &) const;
  std::vector<ScheduleAction> suggest(const Solution &) const;
  const std::unordered_map<Day, int> &roosterScores() const;
};
}
