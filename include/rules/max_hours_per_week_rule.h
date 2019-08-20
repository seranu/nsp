#pragma once

#include <rules/irule.h>

namespace nsp {
class MaxHoursPerWeekRule : public IRule {
public:
 MaxHoursPerWeekRule(size_t employeeId, int value, int penalty)
     : m_employeeId(employeeId), m_value(value) {
   setPenalty(penalty);
 }
 ~MaxHoursPerWeekRule() override {}

 RuleType type() const override { return RuleType::MaxHoursPerWeek; }
 int apply(const Schedule &) override;
 size_t employeeId() const { return m_employeeId; }
 int value() const { return m_value; }
 std::string print() const override;

private:
  size_t m_employeeId;
  int m_value;
};
} // namespace nsp
