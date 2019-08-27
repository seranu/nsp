#include "rules/consecutive_days_rule.h"
#include <sstream>
#include <string>
#include <unordered_map>
#include "utils.h"

namespace nsp {
void ConsecutiveDaysRule::search(
    const Schedule& schedule,
    std::function<void(const Employee&, int, ShiftType)> onFail) const {
  std::unordered_map<Employee, int, EmployeeHash> seen;
  for (int i = 0; i < daysInMonth(schedule.month()); i++) {
    const auto& dayAgenda = schedule.agenda(i);
    for (auto const& [emp, shift] : dayAgenda) {
      if (shift == ShiftType::OFF) {
        seen[emp] = std::max(seen[emp] - 2, 0);
      } else {
        seen[emp]++;
        if (seen[emp] > 3) {
          onFail(emp, i, shift);
        }
      }
    }
  }
}

int ConsecutiveDaysRule::apply(const Schedule& schedule) {
  int totalPenalty = 0;
  search(schedule,
         [&](const Employee&, int, ShiftType) { totalPenalty += m_penalty; });
  return totalPenalty;
}

std::vector<ScheduleAction> ConsecutiveDaysRule::suggest(
    const Schedule& schedule) const {
  std::vector<ScheduleAction> result;
  search(schedule, [&](const Employee& emp, int day, ShiftType) {
    result.push_back(ScheduleAction::createDeleteAction(emp, day));
  });
  return result;
}

std::string ConsecutiveDaysRule::print() const {
  std::stringstream os;
  os << "Rule [ type = \"" << ruleTypeToString(RuleType::ConsecutiveDays)
     << "\" value = \"" << m_value << "\" ];";
  return os.str();
}

} // namespace nsp
