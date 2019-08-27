#pragma once

#include "rules/irule.h"
#include "schedule_action.h"

namespace nsp {
class MinHoursPerWeekRule : public IRule {
 public:
  MinHoursPerWeekRule(size_t employeeId, int value, int penalty)
      : m_employeeId(employeeId), m_value(value) {
    setPenalty(penalty);
 }
 ~MinHoursPerWeekRule() override {}

 RuleType type() const override { return RuleType::MinHoursPerWeek; }
 int apply(const Schedule &schedule) override;
 size_t employeeId() const { return m_employeeId; }
 int value() const { return m_value; }
 std::string print() const override;
 std::vector<ScheduleAction> suggest(const Schedule &schedule) const override;

private:
  size_t m_employeeId;
  int m_value;

  void search(
      const Schedule &,
      std::function<void(const Employee &, int, int, int)> onFail) const;
};
} // namespace nsp
