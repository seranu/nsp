#pragma once

#include <rules/irule.h>
#include <vector>

namespace nsp {
class VacationDaysRule : public IRule {
public:
 VacationDaysRule(size_t employeeId, std::vector<unsigned short> values,
                  int penalty)
     : m_employeeId(employeeId), m_vacationDays(move(values)) {
   setPenalty(penalty);
 }
 RuleType type() const override { return RuleType::VacationDays; }
 int apply(const Schedule &) override;
 std::vector<unsigned short> value() const { return m_vacationDays; }
 std::string print() const override;

private:
 size_t m_employeeId;
 std::vector<unsigned short> m_vacationDays;
};
} // namespace nsp
