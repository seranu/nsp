#include <rules/min_hours_per_week_rule.h>
#include <sstream>
#include <string>
#include <utils.h>

namespace nsp {
int MinHoursPerWeekRule::apply(const Schedule &schedule) {
  int totalPenalty = 0;
  int hoursThisWeek = 0;
  for (auto const &[emp, shift] : schedule.shifts()) {
    if (emp.id() == m_employeeId) {
      for (size_t i = 0; i < shift.size(); i++) {
        if (i % 7 == 0) {
          if (hoursThisWeek < m_value) {
            totalPenalty += m_penalty;
          }
          hoursThisWeek = 0;
        }
        hoursThisWeek += static_cast<int>(shift[i]);
      }
      if (hoursThisWeek < m_value) {
        totalPenalty += m_penalty;
      }
    }
  }
  return totalPenalty;
}

std::string MinHoursPerWeekRule::print() const {
  std::stringstream os;
  os << "Rule [ type = \"" << ruleTypeToString(RuleType::MinHoursPerWeek)
     << "\" employeeId = \"" << m_employeeId << "\" value = \"" << m_value
     << "\" ];";
  return os.str();
}
} // namespace nsp
