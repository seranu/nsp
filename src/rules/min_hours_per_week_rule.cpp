#include <rules/min_hours_per_week_rule.h>
#include <sstream>
#include <string>
#include <utils.h>

namespace nsp {
std::string MinHoursPerWeekRule::print() const {
  std::stringstream os;
  os << "Rule [ type = \"" << ruleTypeToString(RuleType::MinHoursPerWeek)
     << "\" employeeId = \"" << m_employeeId << "\" value = \"" << m_value
     << "\" ];";
  return os.str();
}
} // namespace nsp
