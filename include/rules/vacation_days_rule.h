#pragma once

#include <rules/irule.h>
#include <vector>

namespace nsp {
class VacationDaysRule : public IRule {
public:
  VacationDaysRule(std::vector<unsigned short> values)
      : m_vacationDays(move(values)) {}
  RuleType type() const override { return RuleType::VacationDays; }
  bool satisfied(const Schedule &) override;
  std::vector<unsigned short> value() const { return m_vacationDays; }
  std::string print() const override;

private:
  std::vector<unsigned short> m_vacationDays;
};
} // namespace nsp
