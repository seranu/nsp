#pragma once

#include <rules/irule.h>

namespace nsp {
class MinHoursPerWeekRule : public IRule {
public:
  MinHoursPerWeekRule(int value) : m_value(value) {}
  RuleType type() const override { return RuleType::MinHoursPerWeek; }
  virtual bool satisfied(const Schedule &schedule) override;

private:
  unsigned short m_value;
};
} // namespace nsp
