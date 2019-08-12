#pragma once

#include <rules/irule.h>
#include <vector>

namespace nsp {
class VacationDaysRule : public IRule {
public:
  VacationDaysRule(std::vector<unsigned short> values)
      : m_vacationDays(move(values)) {}
  RuleType type() const override { return RuleType::VacationDays; }
  virtual bool satisfied(const Schedule &schedule) override {}

private:
  std::vector<unsigned short> m_vacationDays;
};
} // namespace nsp
