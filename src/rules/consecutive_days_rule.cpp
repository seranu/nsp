#include "rules/consecutive_days_rule.h"
#include <sstream>
#include <string>
#include <unordered_map>
#include "utils.h"

namespace nsp {
int ConsecutiveDaysRule::apply(const Schedule& schedule) {
  int totalPenalty = 0;
  std::unordered_map<Employee, int, EmployeeHash> seen;
  for (int i = 0; i < daysInMonth(schedule.month()); i++) {
    const auto& dayAgenda = schedule.agenda(i);
    for (auto const& [emp, shift] : dayAgenda) {
      if (shift == ShiftType::OFF) {
        seen[emp] = std::max(seen[emp] - 2, 0);
      } else {
        seen[emp]++;
        if (seen[emp] > 3) {
          totalPenalty += m_penalty;
        }
      }
    }
  }
  return totalPenalty;
}

std::string ConsecutiveDaysRule::print() const {
  std::stringstream os;
  os << "Rule [ type = \"" << ruleTypeToString(RuleType::ConsecutiveDays)
     << "\" value = \"" << m_value << "\" ];";
  return os.str();
}

} // namespace nsp
