#pragma once

#include <rules/irule.h>

namespace nsp {
class MaxHoursPerWeekRule : public IRule {
public:
  MaxHoursPerWeekRule(int value) : m_value(value) {}
  RuleType type() const override { return RuleType::MaxHoursPerWeek; }
  virtual bool satisfied(const Schedule &schedule) override;

private:
  unsigned short m_value;
};
} // namespace nsp
