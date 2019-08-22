#include <rules/vacation_days_rule.h>
#include <sstream>
#include <string>
#include <utils.h>

namespace nsp {
int VacationDaysRule::apply(const Schedule& schedule) {
  int totalPenalty = 0;
  const auto& shift = schedule.shifts(m_employeeId);
  for (auto i : m_vacationDays) {
    if (shift[i - 1] != ShiftType::OFF) {
      totalPenalty += m_penalty;
    }
  }
  return totalPenalty;
}

std::string VacationDaysRule::print() const {
  std::stringstream os;
  os << "Rule [ type = \"" << ruleTypeToString(RuleType::VacationDays)
     << "\" value = \""
     << "{ ";
  for (auto day : m_vacationDays) {
    os << day << " ";
  }
  os << "} \" ]";
  return os.str();
}
} // namespace nsp
