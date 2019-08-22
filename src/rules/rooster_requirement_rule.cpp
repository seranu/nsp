#include <rules/rooster_requirement_rule.h>
#include <sstream>
#include <string>
#include <utils.h>

namespace nsp {
int RoosterRequirementRule::apply(const Schedule &schedule) {
  auto day = dayOfWeek(1, schedule.month(), currentYear());
  auto numDays = daysInMonth(schedule.month());
  int i = 0, totalPenalty = 0;
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
      totalPenalty += m_penalty;
    }
    i += 7;
  }
  return m_penalty;
}

std::string RoosterRequirementRule::print() const {
  std::stringstream os;
  os << "Rule [ type = \"" << ruleTypeToString(RuleType::RoosterRequirement)
     << "\" value = \"" << dayToString(m_day) << ": " << m_value << "\" ];";
  return os.str();
}
} // namespace nsp
