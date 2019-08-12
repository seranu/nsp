#pragma once

#include "irule.h"
#include "nsp_types.h"
#include <memory>
#include <vector>

namespace nsp
{
class Solution;
class IConfiguration;
class RuleEngine
{
private:
  RuleEngine(std::vector<std::shared_ptr<IRule>> rules)
      : m_rules(move(rules)) {}
  std::vector<std::shared_ptr<IRule>> m_rules;
public:
  static std::unique_ptr<RuleEngine>
  createFromConfiguration(const IConfiguration &);
  Penalty computePenalty(const Solution &) const;
  bool valid(const Solution &) const;
};
}