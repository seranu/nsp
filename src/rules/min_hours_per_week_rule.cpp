#include <rules/min_hours_per_week_rule.h>
#include <sstream>
#include <string>
#include <utils.h>

namespace nsp {
void MinHoursPerWeekRule::search(
    const Schedule &schedule,
    std::function<void(const Employee &, int, int, int)> onFail) const {
  int hoursThisWeek = 0;
  for (auto const &[emp, shift] : schedule.shifts()) {
    if (emp.id() == m_employeeId) {
      for (size_t i = 0; i < shift.size(); i++) {
        if (i != 0 && i % 7 == 0) {
          if (hoursThisWeek < m_value) {
            onFail(emp, i - 7, i, hoursThisWeek);
          }
          hoursThisWeek = 0;
        }
        hoursThisWeek += static_cast<int>(shift[i]);
      }
      if (hoursThisWeek < m_value) {
        auto days = daysInMonth(schedule.month());
        onFail(emp, days, days - 7, hoursThisWeek);
      }
    }
  }
}

int MinHoursPerWeekRule::apply(const Schedule &schedule) {
  int totalPenalty = 0;
  search(schedule,
         [&](const Employee &, int, int, int) { totalPenalty += m_penalty; });
  return totalPenalty;
}

std::vector<ScheduleAction> MinHoursPerWeekRule::suggest(
    const Schedule &schedule) const {
  std::vector<ScheduleAction> result;
  search(schedule, [&](const Employee &emp, int startOfWeek, int endOfWeek,
                       int hoursThisWeek) {
    assert(startOfWeek >= 0);
    const auto &shift = schedule.shifts(emp);
    while (startOfWeek < endOfWeek) {
      if (hoursThisWeek > m_value) {
        return;
      }
      if (shift[startOfWeek] == ShiftType::OFF &&
          shift[startOfWeek - 1] == ShiftType::OFF) {
        result.push_back(ScheduleAction::createAddAction(emp, startOfWeek,
                                                         ShiftType::NORMAL));
        hoursThisWeek += static_cast<int>(shift[startOfWeek]);
      }
      startOfWeek++;
    }
  });
  return result;
}

std::string MinHoursPerWeekRule::print() const {
  std::stringstream os;
  os << "Rule [ type = \"" << ruleTypeToString(RuleType::MinHoursPerWeek)
     << "\" employeeId = \"" << m_employeeId << "\" value = \"" << m_value
     << "\" ];";
  return os.str();
  }
} // namespace nsp
