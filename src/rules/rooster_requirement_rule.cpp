#include <rules/rooster_requirement_rule.h>
#include <sstream>
#include <string>
#include <utils.h>

namespace nsp {

void RoosterRequirementRule::search(
    const Schedule &schedule, std::function<void(int, int)> onFail) const {
  auto day = dayOfWeek(1, schedule.month(), currentYear());
  auto numDays = daysInMonth(schedule.month());
  int i = 0;
  while (day != m_day) {
    day = nextDay(day);
    i++;
  }
  while (i < numDays) {
    int score = 0;
    for (auto const &[emp, schedule] : schedule.agenda(i)) {
      score += roosterScore(emp.grade());
    }
    if (score < m_value) {
      onFail(i, score);
    }
    i += 7;
  }
}

int RoosterRequirementRule::apply(const Schedule &schedule) {
  int totalPenalty = 0;
  search(schedule, [&](int, int) { totalPenalty += m_penalty; });
  return m_penalty;
}

std::vector<ScheduleAction> RoosterRequirementRule::suggest(
    const Schedule &schedule) const {
  std::vector<ScheduleAction> result;
  search(schedule, [&](int day, int score) {
    const auto &dayAgenda = schedule.agenda(day);
    for (auto const &[emp, shift] : schedule.shifts()) {
      if (dayAgenda.find(emp) != dayAgenda.end()) {
        result.push_back(
            ScheduleAction::createAddAction(emp, day, ShiftType::NORMAL));
        score += static_cast<int>(emp.grade());
        if (score >= m_value) {
          return;
        }
      }
    }
  });
  return result;
}  // namespace nsp

std::string RoosterRequirementRule::print() const {
  std::stringstream os;
  os << "Rule [ type = \"" << ruleTypeToString(RuleType::RoosterRequirement)
     << "\" value = \"" << dayToString(m_day) << ": " << m_value << "\" ];";
  return os.str();
}
} // namespace nsp
