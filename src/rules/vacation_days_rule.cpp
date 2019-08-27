#include "rules/vacation_days_rule.h"
#include <sstream>
#include <string>
#include "log.h"
#include "utils.h"

namespace nsp {

void VacationDaysRule::search(
    const Schedule &schedule,
    std::function<void(const Employee &, int)> onFail) const {
  for (auto i : m_vacationDays) {
    for (auto const &[emp, shift] : schedule.agenda(i - 1)) {
      if (emp.id() == m_employeeId && shift != ShiftType::OFF) {
        //        LOG_DEBUG("Employee %s should have a day off on %d!!",
        //                  emp.name().c_str(), i);
        onFail(emp, i - 1);
      }
    }
  }
}

int VacationDaysRule::apply(const Schedule &schedule) {
  int totalPenalty = 0;
  search(schedule, [&](const Employee &, int) { totalPenalty += m_penalty; });
  return totalPenalty;
}
std::vector<ScheduleAction> VacationDaysRule::suggest(
    const Schedule &schedule) const {
  std::vector<ScheduleAction> result;
  search(schedule, [&](const Employee &emp, int day) {
    result.push_back(ScheduleAction::createDeleteAction(emp, day));
  });
  return result;
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
