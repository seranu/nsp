#pragma once

#include <date.h>
#include <rules/irule.h>
#include <utility>

namespace nsp {
class RoosterRequirementRule : public IRule {
public:
  RoosterRequirementRule(Day day, int value) : m_day(day), m_value(value) {}
  RuleType type() const override { return RuleType::RoosterRequirement; }
  virtual bool satisfied(const Schedule &schedule) override;
  std::pair<Day, int> value() const { return std::make_pair(m_day, m_value); }

private:
  Day m_day;
  int m_value;
};
} // namespace nsp
