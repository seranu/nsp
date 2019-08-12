#pragma once

#include <date.h>
#include <rules/irule.h>

namespace nsp {
class RoosterRequirementRule : public IRule {
public:
  RoosterRequirementRule(Day day, int value) : m_day(day), m_value(value) {}
  RuleType type() const override { return RuleType::RoosterRequirement; }
  virtual bool satisfied(const Schedule &schedule) override;

private:
  Day m_day;
  int m_value;
};
} // namespace nsp
