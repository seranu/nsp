#pragma once

#include <rules/irule.h>

namespace nsp {
class MinHoursPerWeekRule : public IRule {
public:
  MinHoursPerWeekRule(size_t employeeId, int value)
      : m_employeeId(employeeId), m_value(value) {}
  ~MinHoursPerWeekRule() override {}

  RuleType type() const override { return RuleType::MinHoursPerWeek; }
  bool satisfied(const Schedule &schedule) override {}
  size_t employeeId() const { return m_employeeId; }
  int value() const { return m_value; }
  std::string print() const override;

private:
  size_t m_employeeId;
  int m_value;
};
} // namespace nsp
